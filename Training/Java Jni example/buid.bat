@echo off
rem generate C/C++ header file called HelloJNI.h
javac -h . HelloJNI.java

rem build HelloJNI.c to hello.dll
x86_64-w64-mingw32-gcc -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -shared -o hello.dll HelloJNI.c

rem x86_64-w64-mingw32-gcc -c -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" HelloJNI.c
rem x86_64-w64-mingw32-gcc -shared -o hello.dll HelloJNI.o

rem execute
java -Djava.library.path=. HelloJNI

rem for LINUX
rem export JAVA_HOME=/your/java/installed/dir
rem echo $JAVA_HOME
rem g++ -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" -shared -o libhello.so HelloJNI.cpp
rem java -Djava.library.path=. HelloJNI

rem jarray  -> int[] -> jint *inCArray -> 
rem jboolean
rem jbooleanArray
rem jbyte
rem jbyteArray
rem jchar
rem jcharArray
rem jclass
rem jdouble
REM jdoubleArray
REM jfieldID
REM jfloat
REM jfloatArray
REM jint
REM jintArray
REM jlong
REM jlongArray
REM jmethodID
REM jobject
REM jobjectArray
REM jobjectRefType
REM jshort
REM jshortArray
REM jsize
REM jstring : String -> jstring -> const char*
REM jthrowable
REM jweak
REM va_list