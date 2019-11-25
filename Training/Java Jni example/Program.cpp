// Save as "HelloJNI.cpp"
#include <jni.h>       // JNI header provided by JDK
#include <iostream>    // C++ standard IO header
#include "HelloJNI.h"  // Generated
using namespace std;

// Implementation of the native method sayHello()
JNIEXPORT void JNICALL Java_HelloJNI_sayHello(JNIEnv *env, jobject thisObj) {
	cout << "Hello World from C++!" << endl;
   return;
}

//1.1.2 Passing Primitives
JNIEXPORT jdouble JNICALL Java_HelloJNI_testJNIPrimitive
  (JNIEnv * env, jobject thisObj, jboolean a, jbyte b, jchar c, jshort d, jint e, jlong f, jfloat g, jdouble h){
  printf("C++:\n");
  printf("%d %d %c %d %d %lld %f %f\n",a,b,c,d,e,f,g,h);
  jdouble ret = b + c + d + e + f + g + h;
  return ret;
}

//1.2.1 Passing Array of Primitives
JNIEXPORT jdoubleArray JNICALL Java_HelloJNI_testJNIArrayPrimitive
          (JNIEnv *env, jobject thisObj, jintArray inJNIArray) {
   // Step 1: Convert the incoming JNI jintarray to C's jint[]
   jint *inCArray = env->GetIntArrayElements(inJNIArray, NULL);
   if (NULL == inCArray) return NULL;
   jsize length = env->GetArrayLength(inJNIArray);
   // Step 2: Perform its intended operations
   jint sum = 0; int i; 
   for (i = 0; i < length; i++) {      sum += inCArray[i];   }
   jdouble average = (jdouble)sum / length;
   // release resources
   env->ReleaseIntArrayElements(inJNIArray,inCArray,0); 
 
   jdouble outCArray[] = {sum, average};
   //Step 3: Convert the C's Native jdouble[] to JNI jdoublearray, and return
   jdoubleArray outJNIArray = env->NewDoubleArray(2);  // allocate
   if (NULL == outJNIArray) return NULL;
   env->SetDoubleArrayRegion(outJNIArray,0,2,outCArray);  // copy
   return outJNIArray;
}

//1.3 Passing Strings
JNIEXPORT jstring JNICALL  Java_HelloJNI_testJNIString
(JNIEnv *env, jobject thisObj, jstring inJNIStr) {
   // Step 1: Convert the JNI String (jstring) into C-String (char*)
   const char *inCStr = env->GetStringUTFChars(inJNIStr, NULL);
   if (NULL == inCStr) return NULL;
 
   // Step 2: Perform its intended operations
   printf("In C, the received string is: %s\n", inCStr);
   env->ReleaseStringUTFChars(inJNIStr, inCStr);  // release resources
 
   // Prompt user for a C-string
   char outCStr[128];
   printf("Enter a String: ");
   scanf("%s", outCStr);    // not more than 127 characters
 
   // Step 3: Convert the C-string (char*) into JNI String (jstring) and return
   return env->NewStringUTF(outCStr);
}


//2.1 Accessing Object's Variables 
JNIEXPORT void JNICALL Java_HelloJNI_testModifyInstanceVariable
  (JNIEnv * env, jobject thisObj) {
    //2.1.1 Accessing primitive variable
    {
        // Get a reference to this object's class
        jclass thisClass = env->GetObjectClass(thisObj);
        // int
        // Get the Field ID of the instance variables "number"
        jfieldID fidNumber = env->GetFieldID(thisClass, "number", "I"  );
        if (NULL == fidNumber) return;
        // Get the int given the Field ID
        jint number = env->GetIntField(thisObj, fidNumber);
        printf("In C, the int is %d\n", number);

        // Change the variable
        number = 99;
        env->SetIntField(thisObj, fidNumber, number);
    }

   
   //2.1.1 Accessing object variable
   {
        jclass thisClass = env->GetObjectClass(thisObj);
        // Get the Field ID of the instance variables "message"
        jfieldID fidMessage = env->GetFieldID( thisClass, "message", "Ljava/lang/String;");
        if (NULL == fidMessage) return;

        // String
        // Get the object given the Field ID
        jstring message = (jstring)env->GetObjectField( thisObj, fidMessage);

        // Create a C-string with the JNI String
        const char *cStr = env->GetStringUTFChars( message, NULL);
        if (NULL == cStr) return;

        printf("In C, the string is %s\n", cStr);
        env->ReleaseStringUTFChars( message, cStr);

        // Create a new C-string and assign to the JNI string
        message = env->NewStringUTF( "Hello from C");
        if (NULL == message) return;

        // modify the instance variables
        env->SetObjectField( thisObj, fidMessage, message);
   }

    //2.1.4 Accessing Class' Static Variables
    {
        jclass cls = env->GetObjectClass(thisObj);

        // Read the int static variable and modify its value
        jfieldID fidS_Number = env->GetStaticFieldID(cls, "s_number", "D");
        if (NULL == fidS_Number) return;

        jdouble s_number = env->GetStaticDoubleField(cls, fidS_Number);
        printf("In C, the double is %f\n", s_number);
        s_number = 77.88;

        env->SetStaticDoubleField(cls, fidS_Number, s_number);
    }


}
//2.and Calling Back Methods
JNIEXPORT void  JNICALL Java_HelloJNI_testCallbackMethod
  (JNIEnv * env, jobject thisObj) {
     //2.2.1 Callback Instance Methods
    {
        //Get a class reference for this object
        jclass thisClass = env->GetObjectClass( thisObj);

        //call method of Java class
        jmethodID midCallBackAverage = env->GetMethodID( thisClass,
                              "callbackAverage", "(II)D");
        if (NULL == midCallBackAverage) return;
        jdouble average = env->CallDoubleMethod( thisObj, midCallBackAverage, 2, 3);
        printf("In C, the average is %f\n", average);
    }
    
    //2.2.2 Callback Static Methods
    {
        //Get a class reference for this object
        jclass thisClass = env->GetObjectClass( thisObj);
        //Get method ID
        jmethodID midCallBackStatic = env->GetStaticMethodID( thisClass,
                             "callbackStatic", "()Ljava/lang/String;");
        if (NULL == midCallBackStatic) return;
        jstring resultJNIStr = (jstring)env->CallStaticObjectMethod( thisClass, midCallBackStatic);
        const char *resultCStr = env->GetStringUTFChars( resultJNIStr, NULL);
        if (NULL == resultCStr) return;
        printf("In C, the returned string is %s\n", resultCStr);
        env->ReleaseStringUTFChars( resultJNIStr, resultCStr);
    }
 
}

//2.1 Creating Objects
JNIEXPORT jobject JNICALL Java_HelloJNI_testCreateObject
   (JNIEnv *env, jobject thisObj, jint number) {
   // Get a class reference for java.lang.Integer
   jclass cls = env->FindClass( "java/lang/Integer");
 
   // Get the Method ID of the constructor which takes an int
   jmethodID midInit = env->GetMethodID( cls, "<init>", "(I)V");
   if (NULL == midInit) return NULL;
   // Call back constructor to allocate a new instance, with an int argument
   jobject newObj = env->NewObject( cls, midInit, number);
 
   //May need to call releaseStringUTFChars() before return
   return newObj;
}

//2.1 Creating Object Arrays
JNIEXPORT jobjectArray JNICALL Java_HelloJNI_testCreateArrayObject
  (JNIEnv * env, jobject thisObj){
   // Get a class reference for java.lang.Double
   jclass classDouble = env->FindClass( "java/lang/Double");
   // Allocate a jobjectArray of 2 java.lang.Double
   jobjectArray outJNIArray = env->NewObjectArray( 2, classDouble, NULL);
 
   // Construct 2 Double objects by calling the constructor
   jmethodID midDoubleInit = env->GetMethodID( classDouble, "<init>", "(D)V");
   if (NULL == midDoubleInit) return NULL;
   jobject objSum = env->NewObject( classDouble, midDoubleInit, 1.0);
   jobject objAve = env->NewObject( classDouble, midDoubleInit, 2.0);
   // Set to the jobjectArray
   env->SetObjectArrayElement( outJNIArray, 0, objSum);
   env->SetObjectArrayElement( outJNIArray, 1, objAve);
 
   return outJNIArray;
}

//4. Local and Global References
static jclass classInteger = NULL;
static jmethodID midIntegerInit = NULL;
JNIEXPORT jobject JNICALL Java_HelloJNI_testLocalReference
  (JNIEnv * env, jobject thisObj) {
  // Get a class reference for java.lang.Integer if missing
   if (NULL == classInteger) {
      //printf("Find java.lang.Integer\n");
      //classInteger = env->FindClass( "java/lang/Integer");
      
      if (NULL == classInteger) {
      printf("Find java.lang.Integer\n");
      // FindClass returns a local reference
      jclass classIntegerLocal = env->FindClass("java/lang/Integer");
      // Create a global reference from the local reference
      classInteger = (jclass)env->NewGlobalRef(classIntegerLocal);
      // No longer need the local reference, free it!
      env->DeleteLocalRef(classIntegerLocal);
}

   }
   if (NULL == classInteger) return NULL;
 
   // Get the Method ID of the Integer's constructor if missing
   if (NULL == midIntegerInit) {
      printf("Get Method ID for java.lang.Integer's constructor\n");
      midIntegerInit = env->GetMethodID( classInteger, "<init>", "(I)V");
   }
   if (NULL == midIntegerInit) return NULL;
 
   // Call back constructor to allocate a new instance, with an int argument
   jint number = 1;
   jobject newObj = env->NewObject( classInteger, midIntegerInit, number);
   printf("In C, constructed java.lang.Integer with number %d\n", number);
   return newObj;
}


