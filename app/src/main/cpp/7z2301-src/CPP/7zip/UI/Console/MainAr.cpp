// MainAr.cpp

#include "StdAfx.h"

#ifdef _WIN32
#include "../../../../C/DllSecur.h"
#endif

#include "../../../../C/CpuArch.h"

#include "../../../Common/MyException.h"
#include "../../../Common/StdOutStream.h"

#include "../../../Windows/ErrorMsg.h"
#include "../../../Windows/NtCheck.h"

#include "../Common/ArchiveCommandLine.h"
#include "../Common/ExitCode.h"

#include "ConsoleClose.h"

using namespace NWindows;

extern
CStdOutStream *g_StdStream;
CStdOutStream *g_StdStream = NULL;
extern
CStdOutStream *g_ErrStream;
CStdOutStream *g_ErrStream = NULL;

extern int Main2(
#ifndef _WIN32
        int numArgs, char *args[]
#endif
);

static const char *const kException_CmdLine_Error_Message = "Command Line Error:";
static const char *const kExceptionErrorMessage = "ERROR:";
static const char *const kUserBreakMessage = "Break signaled";
static const char *const kMemoryExceptionMessage = "ERROR: Can't allocate required memory!";
static const char *const kUnknownExceptionMessage = "Unknown Error";
static const char *const kInternalExceptionMessage = "\n\nInternal Error #";

static void FlushStreams() {
    if (g_StdStream)
        g_StdStream->Flush();
}

static void PrintError(const char *message) {
    FlushStreams();

    if (g_ErrStream) {
        *g_ErrStream << "\n\n" << message << endl;
        g_ErrStream->printAll();
        g_StdStream->printAll();
    }

}

#if defined(_WIN32) && defined(_UNICODE) && !defined(_WIN64) && !defined(UNDER_CE)
#define NT_CHECK_FAIL_ACTION *g_StdStream << "Unsupported Windows version"; return NExitCode::kFatalError;
#endif

static inline bool CheckIsa() {
    // __try
    {
#if defined(__AVX2__)
        if (!CPU_IsSupported_AVX2())
          return false;
#elif defined(__AVX__)
        if (!CPU_IsSupported_AVX())
          return false;
#elif defined(__SSE2__) && !defined(MY_CPU_AMD64) || defined(_M_IX86_FP) && (_M_IX86_FP >= 2)
        if (!CPU_IsSupported_SSE2())
          return false;
#elif defined(__SSE__) && !defined(MY_CPU_AMD64) || defined(_M_IX86_FP) && (_M_IX86_FP >= 1)
        if (!CPU_IsSupported_SSE() ||
            !CPU_IsSupported_CMOV())
          return false;
#endif
        /*
        __asm
        {
          _emit 0fH
          _emit 038H
          _emit 0cbH
          _emit (0c0H + 0 * 8 + 0)
        }
        */
        return true;
    }
    /*
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
      return false;
    }
    */
}

int Z7_CDECL main
        (
#ifndef _WIN32
        int numArgs, char *args[]
#endif
) {
    g_ErrStream = &g_StdErr;
    g_StdStream = &g_StdOut;

    // #if (defined(_MSC_VER) && defined(_M_IX86))
    if (!CheckIsa()) {
        PrintError("ERROR: processor doesn't support required ISA extension");
        return NExitCode::kFatalError;
    }
    // #endif

    NT_CHECK

    NConsoleClose::CCtrlHandlerSetter ctrlHandlerSetter;
    int res = 0;

    try {
#ifdef _WIN32
        My_SetDefaultDllDirectories();
#endif

        res = Main2(
#ifndef _WIN32
                numArgs, args
#endif
        );
    }
    catch (const CNewException &) {
        PrintError(kMemoryExceptionMessage);
        return (NExitCode::kMemoryError);
    }
    catch (const NConsoleClose::CCtrlBreakException &) {
        PrintError(kUserBreakMessage);
        return (NExitCode::kUserBreak);
    }
    catch (const CMessagePathException &e) {
        PrintError(kException_CmdLine_Error_Message);
        if (g_ErrStream)
            *g_ErrStream << e << endl;
        return (NExitCode::kUserError);
    }
    catch (const CSystemException &systemError) {
        if (systemError.ErrorCode == E_OUTOFMEMORY) {
            PrintError(kMemoryExceptionMessage);
            return (NExitCode::kMemoryError);
        }
        if (systemError.ErrorCode == E_ABORT) {
            PrintError(kUserBreakMessage);
            return (NExitCode::kUserBreak);
        }
        if (g_ErrStream) {
            PrintError("System ERROR:");
            *g_ErrStream << NError::MyFormatMessage(systemError.ErrorCode) << endl;
        }
        return (NExitCode::kFatalError);
    }
    catch (NExitCode::EEnum exitCode) {
        FlushStreams();
        if (g_ErrStream)
            *g_ErrStream << kInternalExceptionMessage << exitCode << endl;
        return (exitCode);
    }
    catch (const UString &s) {
        if (g_ErrStream) {
            PrintError(kExceptionErrorMessage);
            *g_ErrStream << s << endl;
        }
        return (NExitCode::kFatalError);
    }
    catch (const AString &s) {
        if (g_ErrStream) {
            PrintError(kExceptionErrorMessage);
            *g_ErrStream << s << endl;
        }
        return (NExitCode::kFatalError);
    }
    catch (const char *s) {
        if (g_ErrStream) {
            PrintError(kExceptionErrorMessage);
            *g_ErrStream << s << endl;
        }
        return (NExitCode::kFatalError);
    }
    catch (const wchar_t *s) {
        if (g_ErrStream) {
            PrintError(kExceptionErrorMessage);
            *g_ErrStream << s << endl;
        }
        return (NExitCode::kFatalError);
    }
    catch (int t) {
        if (g_ErrStream) {
            FlushStreams();
            *g_ErrStream << kInternalExceptionMessage << t << endl;
            return (NExitCode::kFatalError);
        }
    }
    catch (...) {
        PrintError(kUnknownExceptionMessage);
        return (NExitCode::kFatalError);
    }

    return res;
}

int Z7_CDECL main2
        (
#ifndef _WIN32
        int numArgs, char *args[]
#endif
);

int Z7_CDECL main2
        (
#ifndef _WIN32
        int numArgs, char *args[]
#endif
) {
    g_ErrStream = &g_StdErr;
    g_StdStream = &g_StdOut;

    // #if (defined(_MSC_VER) && defined(_M_IX86))
    if (!CheckIsa()) {
        PrintError("ERROR: processor doesn't support required ISA extension");
        return NExitCode::kFatalError;
    }
    // #endif

    NT_CHECK

    NConsoleClose::CCtrlHandlerSetter ctrlHandlerSetter;
    int res = 0;

    try {
#ifdef _WIN32
        My_SetDefaultDllDirectories();
#endif

        res = Main2(
#ifndef _WIN32
                numArgs, args
#endif
        );
    }
    catch (const CNewException &) {
        PrintError(kMemoryExceptionMessage);
        return (NExitCode::kMemoryError);
    }
    catch (const NConsoleClose::CCtrlBreakException &) {
        PrintError(kUserBreakMessage);
        return (NExitCode::kUserBreak);
    }
    catch (const CMessagePathException &e) {
        PrintError(kException_CmdLine_Error_Message);
        if (g_ErrStream)
            *g_ErrStream << e << endl;
        return (NExitCode::kUserError);
    }
    catch (const CSystemException &systemError) {
        if (systemError.ErrorCode == E_OUTOFMEMORY) {
            PrintError(kMemoryExceptionMessage);
            return (NExitCode::kMemoryError);
        }
        if (systemError.ErrorCode == E_ABORT) {
            PrintError(kUserBreakMessage);
            return (NExitCode::kUserBreak);
        }
        if (g_ErrStream) {
            PrintError("System ERROR:");
            *g_ErrStream << NError::MyFormatMessage(systemError.ErrorCode) << endl;
        }
        return (NExitCode::kFatalError);
    }
    catch (NExitCode::EEnum exitCode) {
        FlushStreams();
        if (g_ErrStream)
            *g_ErrStream << kInternalExceptionMessage << exitCode << endl;
        return (exitCode);
    }
    catch (const UString &s) {
        if (g_ErrStream) {
            PrintError(kExceptionErrorMessage);
            *g_ErrStream << s << endl;
        }
        return (NExitCode::kFatalError);
    }
    catch (const AString &s) {
        if (g_ErrStream) {
            PrintError(kExceptionErrorMessage);
            *g_ErrStream << s << endl;
        }
        return (NExitCode::kFatalError);
    }
    catch (const char *s) {
        if (g_ErrStream) {
            PrintError(kExceptionErrorMessage);
            *g_ErrStream << s << endl;
        }
        return (NExitCode::kFatalError);
    }
    catch (const wchar_t *s) {
        if (g_ErrStream) {
            PrintError(kExceptionErrorMessage);
            *g_ErrStream << s << endl;
        }
        return (NExitCode::kFatalError);
    }
    catch (int t) {
        if (g_ErrStream) {
            FlushStreams();
            *g_ErrStream << kInternalExceptionMessage << t << endl;
            return (NExitCode::kFatalError);
        }
    }
    catch (...) {
        PrintError(kUnknownExceptionMessage);
        return (NExitCode::kFatalError);
    }
    g_ErrStream->printAll();
    g_StdStream->printAll();
    return res;
}

#include <jni.h>
#include <string>
#include<vector>
#include <memory>
#include <cstring>
#include <cstdlib>
#include <android/log.h>

std::shared_ptr<char *> makeUniqueString(const char *str);

std::shared_ptr<char *> makeUniqueString(const char *str) {
    char *s = static_cast<char *>(malloc(strlen(str) + 1));
    memcpy(s, str, strlen(str) + 1);
    return std::make_shared<char *>(s);
}

int main2(int numArgs, char *args[]);

extern "C"
JNIEXPORT jint JNICALL
Java_com_xz_szbinding_MainActivity_compress2(JNIEnv *env, jobject thiz, jobjectArray args);

#define jLogDD(s) __android_log_print(ANDROID_LOG_DEBUG, "jhc" , "%s",s)

extern "C"
JNIEXPORT jint JNICALL
Java_com_xz_szbinding_MainActivity_compress2(JNIEnv *env, jobject thiz, jobjectArray args) {
    int length = env->GetArrayLength(args);
    std::vector<std::shared_ptr<char *>> argsv;

    for (int i = 0; i < length; i++) {
        auto str = (jstring) env->GetObjectArrayElement(args, i);
        argsv.emplace_back(makeUniqueString(env->GetStringUTFChars(str, nullptr)));
    }
    char **ar = new char *[length + 1];
    for (int i = 0; i < length; i++) {
        ar[i + 1] = *argsv[i].get();
    }
    __android_log_print(ANDROID_LOG_DEBUG, "jhc", "%s", "in main2 ");

    char arg0[] = "7z";
    char arg1[] = "l";
    char arg2[] = "/storage/emulated/0/test5/nameunlock.7z";
    char arg3[] = "-o/storage/emulated/0/test4";
    char arg4[] = "-p1234";
    char arg5[] = "-y";
    jLogDD(arg1);
    jLogDD(arg2);
    jLogDD(arg3);
    jLogDD(arg4);
    char *ar2[] = {arg0, arg1, arg2, arg3, arg4, arg5};

    int res = main2(5, ar2);
    __android_log_print(ANDROID_LOG_DEBUG, "jhc", "%d--%s", res, "已经退出");
    delete[] ar;
    //  _openCallback.release();
//    _callback .release();
    return res;
}
