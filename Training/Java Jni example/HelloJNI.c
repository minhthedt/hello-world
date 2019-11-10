// Save as "HelloJNI.c"
#include <jni.h>        // JNI header provided by JDK
#include <stdio.h>      // C Standard IO Header
#include "HelloJNI.h"   // Generated
 
// Implementation of the native method sayHello()
JNIEXPORT void JNICALL Java_HelloJNI_sayHello(JNIEnv *env, jobject thisObj) {
   printf("Hello World!\n");
   return;
}

JNIEXPORT jstring JNICALL Java_HelloJNI_sayHelloStr(JNIEnv * env, jobject thisObj, jstring inJNIStr){
   // Step 1: Convert the JNI String (jstring) into C-String (char*)
   const char *inCStr = (*env)->GetStringUTFChars(env, inJNIStr, NULL);
   if (NULL == inCStr) return NULL;
 
   // Step 2: Perform its intended operations
   printf("In C, the received string is: %s\n", inCStr);
   (*env)->ReleaseStringUTFChars(env, inJNIStr, inCStr);  // release resources
 
   // Prompt user for a C-string
   char outCStr[128];
   printf("Enter a String: ");
   scanf("%s", outCStr);    // not more than 127 characters
 
   // Step 3: Convert the C-string (char*) into JNI String (jstring) and return
   return (*env)->NewStringUTF(env, outCStr);
}

JNIEXPORT jdoubleArray JNICALL Java_HelloJNI_sumAndAverage(JNIEnv * env, jobject thisObj, jintArray inJNIArray){
   // Step 1: Convert the incoming JNI jintarray to C's jint[]
   jint *inCArray = (*env)->GetIntArrayElements(env, inJNIArray, NULL);
   if (NULL == inCArray) return NULL;
   jsize length = (*env)->GetArrayLength(env, inJNIArray);
 
   // Step 2: Perform its intended operations
   jint sum = 0;
   int i;
   for (i = 0; i < length; i++) {
      sum += inCArray[i];
   }
   jdouble average = (jdouble)sum / length;
   (*env)->ReleaseIntArrayElements(env, inJNIArray, inCArray, 0); // release resources
 
   jdouble outCArray[] = {sum, average};
 
   // Step 3: Convert the C's Native jdouble[] to JNI jdoublearray, and return
   jdoubleArray outJNIArray = (*env)->NewDoubleArray(env, 2);  // allocate
   if (NULL == outJNIArray) return NULL;
   (*env)->SetDoubleArrayRegion(env, outJNIArray, 0 , 2, outCArray);  // copy
   return outJNIArray;

}