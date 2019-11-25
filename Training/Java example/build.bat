@echo off
rem set JAVA_HOME=C:\Program Files\Java\jdk1.8.0_161\bin
set JAVA_HOME=D:\SD2-Android\Old_documents\Tools\AndroidStudio\android-studio-3.4.1\jre\bin
set PATH=%PATH%;%JAVA_HOME%

RMDIR /Q/S build
mkdir build
rem build mutil java file
rem javac People.java Simple.java Student.java

rem -d <directory>  Specify where to place generated class files
javac -d ./build ./*.java

rem -cp <path>      Specify where to find user class files and annotation processors
rem javac -cp ./build ./Simple.java

rem execute main method in class MainJava
java -cp ./build com.example.MainJava

pause