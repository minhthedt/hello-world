#!/bin/sh
# generate C/C++ header file called HelloJNI.h
# /mnt/d/Training/hello-world/Training/Java\ Jni\ example/simple\ example/
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64/
echo $JAVA_HOME
# complie to HelloJNI.class
javac HelloJNI.java
# generate HelloJNI.h
javah HelloJNI
# build Program.cpp to libprogram.so
g++ -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" -shared -o libprogram.so Program.cpp
# execute
java -Djava.library.path=. HelloJNI