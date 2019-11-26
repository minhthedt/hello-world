@echo off
rem generate C/C++ header file called HelloJNI.h
set CYGWIN_HOME=C:\cygwin64\bin
set JAVA_HOME=D:\SD2-Android\Old_documents\Tools\AndroidStudio\android-studio-3.4.1\jre
rem set JAVA_HOME=C:\Program Files\Java\jdk1.8.0_161
set PATH=%PATH%;%CYGWIN_HOME%;%JAVA_HOME%\bin

rem complie to HelloJNI.class
javac HelloJNI.java
rem generate HelloJNI.h
javah HelloJNI

rem build Program.cpp to program.dll
x86_64-w64-mingw32-g++ -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -shared -o program.dll Program.cpp

mv program.dll ./bin
mv HelloJNI.class ./bin
rem execute
cd bin
java -Djava.library.path=. HelloJNI

pause

