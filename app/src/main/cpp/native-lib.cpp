#include <jni.h>
#include <string>
#include<vector>
#include <memory>
#include <cstring>
#include <cstdlib>

std::shared_ptr<char *> makeUniqueString(const char *str) {
    char *s = static_cast<char *>(malloc(strlen(str) + 1));
    memcpy(s, str, strlen(str) + 1);
    return std::make_shared<char *>(s);
}

int main2(int numArgs, char *args[]);

extern "C"
JNIEXPORT jint JNICALL
Java_jhc_pic_sz23binding_MainActivity_compress(JNIEnv *env, jobject thiz, jobjectArray args) {
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

    int res = main2(length + 1, ar);

    delete[] ar;
    //  _openCallback.release();
//    _callback .release();
    return res;
}
