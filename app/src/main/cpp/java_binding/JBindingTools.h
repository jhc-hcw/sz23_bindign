/*
 * JBindingTools.h
 *
 *  Created on: Jan 29, 2010
 *      Author: boris
 */

#ifndef JBINDINGTOOLS_H_
#define JBINDINGTOOLS_H_

#include "Debug.h"
#include "BaseSystem.h"
#include "JObjectList.h"
#include <algorithm>
#include <map>

#define NO_HRESULT -1

class JNINativeCallContext;

class JBindingSession;

class JNIEnvInstance;

#ifdef __ANDROID_API__

#include <string>

namespace jni { inline void prepareExceptionCheck(JNIEnv *env); }

jclass findClass(JNIEnv *env, std::string name);

#endif

template<typename T>
struct CMyComPtrWrapper {
    CMyComPtr<T> _ptr;

    CMyComPtrWrapper() {
    }

    CMyComPtrWrapper(T *ptr) :
            _ptr(ptr) {
    }

    T *operator->() const {
        return (T *) _ptr;
    }
};

class ThreadContext {
public:
    JNIEnv *_env;
    int _attachedThreadCount;
    bool _wasAttached;
    std::list<JNINativeCallContext *> _javaNativeContext;//一个线程保存若干个jni本地上下文对象

    ThreadContext() :
            _env(NULL), _attachedThreadCount(0), _wasAttached(false) {
    }
};

/*
 * Represents a single session of 7-Zip-JBinding.
 * For example OpenArchive->QueryArchiveItems->ExtractItems->CloseArchive.
 */
class JBindingSession {
    friend class JNINativeCallContext;

    friend class JNIEnvInstance;

    typedef std::map<ThreadId, ThreadContext> ThreadContextMap;

    std::list<CMyComPtrWrapper<IUnknown> > _objectList; // TODO REMOVE unused list
    std::list<JNINativeCallContext> _jniNativeCallContextList;
    ThreadContextMap _threadContextMap;  //线程上下文
    PlatformCriticalSection _threadContextMapCriticalSection;//保存一个线程锁
    static JavaVM *_vm;

#ifdef __ANDROID_API__
public:
    static jmethodID _classLoaderID;
    static std::map<std::string, jobject> _classLoaderObjects;
#endif

#ifdef USE_MY_ASSERTS
    public:
        static int _attachedThreadCount;
        static PlatformCriticalSection _attachedThreadCountCriticalSection;
    private:
#endif

    void registerNativeContext(JNIEnv *initEnv, JNINativeCallContext *jniNativeCallContext) {
        ThreadId threadId = PlatformGetCurrentThreadId();
        _threadContextMapCriticalSection.Enter();
        ThreadContext &threadContext = _threadContextMap[threadId];//将id存入map，value会调用默认构造器
        _threadContextMapCriticalSection.Leave();
        //TRACE("JNINativeCallContext=" << jniNativeCallContext)
        threadContext._javaNativeContext.push_front(jniNativeCallContext);
    }

    void unregisterNativeContext(JNINativeCallContext &javaNativeContext) {
        ThreadId threadId = PlatformGetCurrentThreadId();

        _threadContextMapCriticalSection.Enter();
        ThreadContext &threadContext = _threadContextMap[threadId];
        MY_ASSERT(*(threadContext._javaNativeContext.begin()) == &javaNativeContext)

        threadContext._javaNativeContext.pop_front();
        if (!threadContext._javaNativeContext.size() && !threadContext._attachedThreadCount) {
            MY_ASSERT(!threadContext._wasAttached)
            _threadContextMap.erase(threadId);
        }
        _threadContextMapCriticalSection.Leave();
    }

    //处理java异常
    void handleThrownException(jthrowable exceptionLocalRef);

    void reportError(const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        vReportError(NO_HRESULT, fmt, args);
        va_end(args);
    }

    //reportError会调用此方法
    void vReportError(const int hresult, const char *fmt, va_list args);

    //应该重点理解此方法
    JNIEnv *beginCallback(JNINativeCallContext **jniNativeCallContext) {
        _threadContextMapCriticalSection.Enter();//进入锁，
        ThreadContext &threadContext = _threadContextMap[PlatformGetCurrentThreadId()];//拿到一个当前线程id,存入map，并默认构造一个线程上下文
        _threadContextMapCriticalSection.Leave();
        if (!threadContext._javaNativeContext.size() && !threadContext._env) { //判断如果线程是新建的，没有上下文
            // Attach new thread
            TRACE("Attaching current thread to VM.")
#ifdef USE_MY_ASSERTS
            _attachedThreadCountCriticalSection.Enter();
            _attachedThreadCount++;
            _attachedThreadCountCriticalSection.Leave();
#endif
            jint result;
#ifdef __ANDROID_API__
            if ((result = _vm->AttachCurrentThread((JNIEnv **) &threadContext._env, NULL))
                #else
                if ((result = _vm->AttachCurrentThread((void**) &threadContext._env, NULL))
                #endif
                || threadContext._env == NULL) {
                TRACE("New thread couldn't be attached: " << result)
                // throw SevenZipException("Can't attach current thread (id: %i) to the VM", currentThreadId);
                // TODO Decide, what to do with it
                fatal("Can't attach current thread (id: %i) to the VM",
                      PlatformGetCurrentThreadId());
            }
            threadContext._wasAttached = true;
            TRACE("Thread attached. New env=" << (void *) threadContext._env)
        }
        if (threadContext._javaNativeContext.size()) {
            *jniNativeCallContext = *threadContext._javaNativeContext.begin();
        }
        threadContext._attachedThreadCount++;
        if (threadContext._env) {
            return threadContext._env;
        }
        MY_ASSERT(*jniNativeCallContext)
        return NULL;
    }

    void endCallback() {
        ThreadId threadId = PlatformGetCurrentThreadId();

        _threadContextMapCriticalSection.Enter();
        ThreadContext &threadContext = _threadContextMap[threadId];
        if (!--threadContext._attachedThreadCount && threadContext._wasAttached) {
            MY_ASSERT(threadContext._javaNativeContext.size() == 0)
#ifdef USE_MY_ASSERTS
            _attachedThreadCountCriticalSection.Enter();
            _attachedThreadCount--;
            _attachedThreadCountCriticalSection.Leave();
#endif
            _vm->DetachCurrentThread();
            _threadContextMap.erase(threadId);
        }
        _threadContextMapCriticalSection.Leave();
    }

public:
    JBindingSession(JNIEnv *initEnv) {
        if (!_vm && initEnv->GetJavaVM(&_vm)) {
            fatal("Can't get JavaVM from JNIEnv");
        }
        MY_ASSERT(_vm)
#ifdef TRACE_OBJECTS_ON
        TraceJBindingSessionCreation();
#endif
    }

    bool exceptionCheck(JNIEnv *env) {
        jni::prepareExceptionCheck(env);
        jthrowable exceptionLocalRef = env->ExceptionOccurred();
        if (exceptionLocalRef) {
            env->ExceptionClear();
            handleThrownException(exceptionLocalRef);
            env->DeleteLocalRef(exceptionLocalRef);
            return true;
        }
        return false;
    }

    void addObject(IUnknown *object) {//可以加入许多java对象引用，然后可以删除
        _objectList.push_back(CMyComPtrWrapper<IUnknown>(object));
    }

    void closeSession(JNIEnv *initEnv) {
        _objectList.clear();
    }

    ~JBindingSession() {
        MY_ASSERT(_objectList.size() == 0)
        //        ThreadContextMap::iterator i = _threadContextMap.begin();
        //        while (i != _threadContextMap.end()) {
        //            printf("Thread Id: %i, attached threads: %i, native contexts: %i\n", i->first,
        //                    i->second._attachedThreadCount, i->second._javaNativeContext.size());
        //            fflush(stdout);
        //            i++;
        //        }
        MY_ASSERT(_threadContextMap.size() == 0)
#ifdef TRACE_OBJECTS_ON
        TraceJBindingSessionDestruction();
#endif
    }
};

class JNINativeCallContext {
    friend class JBindingSession;

    friend class JNIEnvInstance;

    jthrowable _firstThrownException;
    jthrowable _lastThrownException;
    jthrowable _firstThrownExceptionInOtherThread;
    jthrowable _lastThrownExceptionInOtherThread;

    JBindingSession &_jbindingSession;
    JNIEnv *_jniCallOriginalEnv;
    char *_errorMessage;

    JNINativeCallContext(JNINativeCallContext const &) = delete; //私有的拷贝构造，就是禁止使用的
    void *operator new(size_t i) = delete;

    void exceptionThrown(JNIEnv *env, jthrowable throwableLocalRef) { //就是将最近的两个异常存储起来
        jthrowable throwableGlobalRef = static_cast<jthrowable> (env->NewGlobalRef(
                throwableLocalRef));
        if (!_firstThrownException) {
            _firstThrownException = throwableGlobalRef;
        } else {
            if (_lastThrownException) {
                env->DeleteGlobalRef(_lastThrownException);
            }
            _lastThrownException = throwableGlobalRef;
        }
    }

    void exceptionThrownInOtherThread(JNIEnv *env, jthrowable throwableLocalRef) {//将最近的两个别的现车异常存储
        jthrowable throwableGlobalRef = static_cast<jthrowable> (env->NewGlobalRef(
                throwableLocalRef));
        if (!_firstThrownExceptionInOtherThread) {
            _firstThrownExceptionInOtherThread = throwableGlobalRef;
        } else {
            if (_lastThrownExceptionInOtherThread) {
                env->DeleteGlobalRef(_lastThrownExceptionInOtherThread);
            }
            _lastThrownExceptionInOtherThread = throwableGlobalRef;
        }
    }

    void assertNoExceptionOnJniCallOriginalEnv() {
        jni::prepareExceptionCheck(_jniCallOriginalEnv);
        if (_jniCallOriginalEnv->ExceptionCheck()) {
            // TODO Print unexpected exception
            fatal("assertNoExceptionOnJniCallOriginalEnv(): Unexpected exception occurs.");
        }
    }

public:

    JNINativeCallContext(JBindingSession &_jbindingSession1, JNIEnv *initEnv) : //复杂的构造
            _firstThrownException(NULL),
            _lastThrownException(NULL),
            _firstThrownExceptionInOtherThread(NULL),
            _lastThrownExceptionInOtherThread(NULL),
            _jbindingSession(_jbindingSession1),
            _jniCallOriginalEnv(initEnv),
            _errorMessage(NULL) {
        _jbindingSession.registerNativeContext(initEnv, this);
    }

    ~JNINativeCallContext();

    bool exceptionCheck(JNIEnv *env) {
        jni::prepareExceptionCheck(env);

        jthrowable exceptionLocalRef = env->ExceptionOccurred();
        if (exceptionLocalRef) {
            env->ExceptionClear();
            exceptionThrown(env, exceptionLocalRef);
            env->DeleteLocalRef(exceptionLocalRef);
            return true;
        }

        // if (_errorMessage) {
        //     free(_errorMessage);
        // }
        return false;
    }

    void reportError(const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        vReportError(NO_HRESULT, fmt, args);
        va_end(args);
    }

    void reportError(const int hresult, const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        vReportError(hresult, fmt, args);
        va_end(args);
    }

    void vReportError(const int hresult, const char *fmt, va_list args);

    bool willExceptionBeThrown();
};

class JNIEnvInstance {
    JBindingSession &_jbindingSession;
    JNINativeCallContext *_jniNativeCallContext;
    JNIEnv *_env;
    bool _isCallback;

    void *operator new(size_t i) = delete;

    void initCallback() {
        MY_ASSERT(_isCallback)

        _env = _jbindingSession.beginCallback(&_jniNativeCallContext);
        if (!_env) {
            MY_ASSERT(_jniNativeCallContext)
            _env = _jniNativeCallContext->_jniCallOriginalEnv;
            MY_ASSERT(_env)
        }
    }

public:
    JNIEnvInstance(JBindingSession &jbindingSession, JNINativeCallContext &jniNativeCallContext,
                   JNIEnv *env) :
            _jbindingSession(jbindingSession),
            _jniNativeCallContext(&jniNativeCallContext),
            _env(env),
            _isCallback(false) {
        MY_ASSERT(env)
    }

    JNIEnvInstance(JBindingSession &jbindingSession) :
            _jbindingSession(jbindingSession),
            _jniNativeCallContext(NULL),
            _env(NULL),
            _isCallback(
                    true) {
        initCallback();
    }

    ~JNIEnvInstance() {
        if (_isCallback) {
            _jbindingSession.endCallback();
            MY_ASSERT(_env)
        }
    }

    bool exceptionCheck() {
        if (_jniNativeCallContext) {
            return _jniNativeCallContext->exceptionCheck(_env);
        }

        return _jbindingSession.exceptionCheck(_env);
    }

    operator JNIEnv *() {
        MY_ASSERT(_env)
        return _env;
    }

    JNIEnv *operator->() {
        return (JNIEnv *) *this;
    }

    void reportError(const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        vReportError(NO_HRESULT, fmt, args);
        va_end(args);
    }

    void reportError(const int hresult, const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        vReportError(hresult, fmt, args);
        va_end(args);
    }

    void vReportError(const int hresult, const char *fmt, va_list args) {
        if (_jniNativeCallContext) {
            return _jniNativeCallContext->vReportError(hresult, fmt, args);
        }

        return _jbindingSession.vReportError(hresult, fmt, args);
    }
};

// TODO Remove this (used by a test only)
template<class T>
class AbstractJavaCallback : public Object {//用与绑定一次java callback类，但这个只用于测试
protected:
    const jobject _implementation;
    T *_javaClass;
    JBindingSession &_jbindingSession;

    AbstractJavaCallback(JBindingSession &jbindingSession, JNIEnv *initEnv,
                         jobject implementation) :
            _jbindingSession(jbindingSession),
            _implementation(initEnv->NewGlobalRef(implementation)), /**/
            _javaClass(T::_getInstanceFromObject(initEnv, implementation)) {
        TRACE_OBJECT_CREATION("CPPToJavaAbstract")
    }

    ~AbstractJavaCallback() {
        JNIEnvInstance jniEnvInstance(_jbindingSession);
        jniEnvInstance->DeleteGlobalRef(_implementation);
    }

};

template<class T>
class DeleteInErrorCase {
private:
    T &_object;
    bool _errorCase;
public:
    DeleteInErrorCase(T &object) :
            _object(object), _errorCase(false) {
    }

    ~DeleteInErrorCase() {
        if (_errorCase) {
            delete &_object;
        }
    }

    void setErrorCase() {
        _errorCase = true;
    }
};

#endif /* JBINDINGTOOLS_H_ */
