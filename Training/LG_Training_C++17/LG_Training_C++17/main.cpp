#include <stdio.h>
#include <iostream>
#include <string>
#include <memory>

extern void test_argument_deduction();





void parse_Module( char* cmd) {
    char m_ModuleName[16];
    memset(m_ModuleName, '\0', 16);
    (void)memcpy(m_ModuleName, cmd, 4);
    unsigned short m_HardwareIndex = 0;
    cmd[5] = 1;
    cmd[6] = 2;
    cmd[7] = 3;
    m_HardwareIndex = *(cmd + 4);
    unsigned short major = ((cmd[8] << 0) | (cmd[7] << 8) | (cmd[6] << 16) | (cmd[5] << 24));
    unsigned short  minor = ((cmd[12] << 0) | (cmd[11] << 8) | (cmd[10] << 16) | (cmd[9] << 24));
    unsigned short  patch = ((cmd[16] << 0) | (cmd[15] << 8) | (cmd[14] << 16) | (cmd[13] << 24));
    printf("major = %d \n", major);
    printf("minor = %d \n", minor);
    printf("patch = %d \n", patch);

    major = ((cmd[20] << 0) | (cmd[19] << 8) | (cmd[18] << 16) | (cmd[17] << 24));
    minor = ((cmd[24] << 0) | (cmd[23] << 8) | (cmd[22] << 16) | (cmd[21] << 24));
    patch = ((cmd[28] << 0) | (cmd[27] << 8) | (cmd[26] << 16) | (cmd[25] << 24));

    printf("major = %d \n", major);
    printf("minor = %d \n", minor);
    printf("patch = %d \n", patch);

}

#include <exception>
class Student
{
    char* name;
    int age;
public:
    //allocate and set value for name
    //Set value for age, throw when  age < 10
    Student(const char* _name, int _age):name(nullptr) {
        name = new char[strlen(_name) + 1];
        memset(name,0, strlen(_name) + 1);
        strcpy(name, _name);

        if (age < 10)  throw std::exception("invalid age");
        age = _age;
    }
    //delete name to avoid leak memory
    ~Student() {
        printf("CALL ~Student()");
        if (name) {
            delete[] name; name = nullptr;
        }
    }
};

//bool callFuntionA(Student* st) {};
//bool callFuntionB(Student* st) {};
//bool callFuntionC() {};
//bool callFuntionD() {};
//
//void HandleSomeThing()
//{
//    callFuntionA();
//    callFuntionB();
//    if (callFuntionC())
//    {
//        //do something
//    }
//}
//
////create new instance of Student with input arguments
//Student* createNewStudent(const char* _name, int age)
//{
//    Student* st = nullptr;
//    try {
//        st = new  Student(_name, age);
//    }
//    catch (const std::exception& e) {
//        printf("FAIL createNewStudent: %s\n",e.what());
//    }
//    return st;
//}
//
//
//void Check(Student* st)
//{
//    //do some thing
//    if (callFuntionA(st))
//    {
//        //do some thing
//        if (callFuntionB(st))
//        {
//            //do some thing
//            if (callFuntionC())
//            {
//                //do some thing
//            }
//            if (callFuntionD())
//            {
//                //do some thing
//            }
//        }
//    }
//    //do some thing
//}
//#include <stdarg.h>
//void WriteFormatted(const char * format, ...)
//{
//    va_list args;
//    va_start(args, format);
//    vfprintf(stdout, format, args);
//    va_end(args);
//}
char mybuffer[80];
void main(char argn, char** argv)
{
    //Student* st = createNewStudent("vvthe",9);
    //if (st == nullptr) printf("createNewStudent == null");
    //else printf("createNewStudent != null");
    //delete st;

    //WriteFormatted("%s","abc");
    // redirect console output to a file
    FILE * pFile;
    pFile = fopen("text_file.txt", "r+");
    if (pFile == NULL) perror("Error opening file");
    else {
        fputs("test", pFile);
        fputs("abcd", pFile);
        fflush(pFile);    // flushing or repositioning required
        fgets(mybuffer, 80, pFile);
        puts(mybuffer);
        fclose(pFile);
    }
    getchar();
}

