#include <jni.h>
#include "judgeString.h"
#include "judgeClient.cc"
JNIEXPORT jstring JNICALL Java_judgeString_getSolution
  (JNIEnv *env, jobject obj, jstring path)
{

	const char *str = env->GetStringUTFChars(path,NULL);
	if(str == NULL) return NULL;
	
	
	char buf[100];
	judgeMain(str,buf);

	env->ReleaseStringUTFChars(path,str);
	return env->NewStringUTF(buf); 

}
