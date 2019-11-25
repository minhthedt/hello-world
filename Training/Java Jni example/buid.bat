@echo off
rem generate C/C++ header file called HelloJNI.h
set CYGWIN_HOME=C:\cygwin64\bin
set JAVA_HOME=D:\SD2-Android\Old_documents\Tools\AndroidStudio\android-studio-3.4.1\jrepw
set PATH=%PATH%;%CYGWIN_HOME%;%JAVA_HOME%\bin

rem complie to HelloJNI.class
javac HelloJNI.java
rem generate HelloJNI.h
javah HelloJNI

rem build Program.cpp to program.dll
x86_64-w64-mingw32-g++ -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -shared -o program.dll Program.cpp


rem execute
java -Djava.library.path=. HelloJNI

pause
rem for LINUX
rem export JAVA_HOME=/your/java/installed/dir
rem echo $JAVA_HOME
rem g++ -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" -shared -o libhello.so HelloJNI.cpp
rem java -Djava.library.path=. HelloJNI
