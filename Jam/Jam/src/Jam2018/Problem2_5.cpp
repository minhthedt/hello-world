#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <chrono>
#include <string>
#include <array>
#ifdef __CYGWIN__
#include <dirent.h>
#endif
#include <limits>

using namespace std;
//http://collab.lge.com/main/pages/viewpage.action?pageId=878214082

namespace Jam2018
{
    #define MODULO 1000000007
    #define UINT8 unsigned char
    #define INT16 short int
    #define UINT32 unsigned int
    #define INT32  int
    #define INT64 signed long long
    #define UINT64 unsigned long long
    #define MAX_VALUE 200000
        #define uint32 unsigned long long
        uint32 GetOutPut(const char* inputPath)
        {
            FILE *fi = fopen(inputPath, "r");
            if(!fi)
            {
                printf("ERROR : %s",inputPath);
                return 0;
            }
            uint32 out;
            fscanf(fi, "%llu", &out);
            fclose(fi);
            return out;
        }


        bool CheckExistedFile(const std::string& filepath)
        {
            struct stat buffer;
            return (stat (filepath.c_str(), &buffer) == 0);
        };

        void GetFilePaths(const std::string&  path,std::vector<std::string>& output,std::vector<std::string> ext = std::vector<std::string>())
        {
#ifdef __CYGWIN__


           struct dirent *entry;
           DIR *dir = opendir(path.c_str());

           if (dir == NULL) {
              printf("ERROR: %s",path.c_str());
              return;
           }

           while ((entry = readdir(dir)) != NULL)
           {
              std::string str = (const char*)entry->d_name;
              std::string filepath =path + "\\" + str;
               if(entry->d_type == DT_DIR)
               {
                   if(str.compare(".") != 0 && str.compare(".."))
                   {
                       //cout << entry->d_name << endl;
                       GetFilePaths(filepath,output);
                   }

               }
               else if(CheckExistedFile(filepath))
               {
                    //printf("%s\n",filepath.c_str());
                   std::string extension = "";
                   if(str.length() > 3)
                   {
                       extension = str.substr(str.length()-3,str.length());
                   }
                    if(ext.size() == 0)
                    {
                       if (extension.compare(".in") == 0)
                       {
                         output.push_back(filepath);
                       }
                    }else
                    {
                        for(int k =0; k < ext.size();k++)
                        {
                            std::string ex = ext.at(k);
                            if (extension.compare(ex) == 0)
                            {
                               output.push_back(filepath);
                            }
                        }
                    }

               }
           }
#else
            //need to take time to implement this function without using <dirent.h>
            printf("ERROR: GetFilePaths(...) is not supported ***\n");
#endif
        };

    namespace Bruteforce_Fail
    {


        std::vector<char> specialChars = { '*','-','.' };
        std::vector<char> vowelChars = { 'a','e', 'i', 'o', 'u' };

        bool isSpecialChar(char ch)
        {
            auto it = std::find(specialChars.begin(), specialChars.end(),ch);
            if (it != specialChars.end()) return true;
            return false;
        }

        bool isConsecutiveSpecialChar(const char* chs)
        {
            if (isSpecialChar(chs[0]) && isSpecialChar(chs[1]) && isSpecialChar(chs[2]))
            {
                return true;
            }

            return false;
        }



        bool isVowelChar(char ch)
        {
            auto it = std::find(vowelChars.begin(), vowelChars.end(), ch);
            if (it != vowelChars.end()) return true;
            return false;
        }

        bool isConsecutiveVowelChar(const char* chs)
        {
            if (isVowelChar(chs[0]) && isVowelChar(chs[1]) && isVowelChar(chs[2]))
            {
                return true;
            }

            return false;
        }

        bool isSameChar(const char* chs)
        {
            if (chs[0] == chs[1] && chs[0] == chs[2])
            {
                return true;
            }
            return false;;
        }

        bool CheckValid(const char* word)
        {
            int length = strlen(word);

            if (length >= 3)
            {
                for (int i = 0; i <= length-3; i++)
                {
                    if (isConsecutiveSpecialChar(&word[i])) return false;
                    if (isConsecutiveVowelChar(&word[i])) return false;
                    if (isSameChar(&word[i])) return false;
                }
            }

            if (isSpecialChar(word[0]) || isSpecialChar(word[length - 1]))
            {
                return false;
            }

            return true;
        }

        std::vector<char> characters;
        void CreateWords(const int length,char* const word, int index,uint32& count)
        {
            //đã điền xong các ô trống
            if (index == -1)
            {
                char* chrs = word;
                //printf("word = %s\n",chrs);
                //for (int i = 0; i < length; i++) chrs--;
                //tạo xong từ rồi check
                if (CheckValid(chrs))
                {
                    count++;
                }
                else
                {
                    //printf("word = %s\n", chrs);
                }
                return;
            }

            for (uint32 i = 0; i < characters.size(); i++)
            {
                //điền từng ký tự vào từ cần tạo
                word[index] = characters[i];
                if (index == 0 || index == length - 1)
                {
                    if (!isSpecialChar(word[index]))
                    {
                        CreateWords(length, word, index - 1, count);
                    }
                }
                else
                {
                    CreateWords(length, word, index - 1, count);
                }

            }
        }



        void Run_Problem2_5(const char* inputPath)
        {
            printf("Problem 5: %s\n", inputPath);
            uint32 a, b;

            FILE *fi = fopen(inputPath, "r");
            if(!fi)
            {
                printf("ERROR : %s",inputPath);
                return;
            }
            fscanf(fi, "%llu", &a);
            fscanf(fi, "%llu", &b);
            printf("%llu %llu \n",a,b);

            for (char ch = 'a'; ch <= 'z'; ch++)
            {
                characters.push_back(ch);
            }
            characters.push_back('*');
            characters.push_back('-');
            characters.push_back('.');

            uint32 count = 0;
            for ( uint32 i = a; i <= b; i++)
            {
                uint32 length = i;
                char* word = new char[length + 1];
                memset(word,0, length +1);
                CreateWords(length,word, length -1, count);
                delete[] word;
            }
            printf("output = %lld \n", count);
            fclose(fi);

            std::string outpath = inputPath;
            outpath = outpath.substr(0,outpath.length()-3);
            outpath += ".out";
            uint32 out = GetOutPut(outpath.c_str());
            if(out == count) printf("PASS\n");
        }
    }

    //pass sample test 1 (0 < a,b <=5)
    namespace Bruteforce_OK
    {


        std::vector<char> specialChars = { '*','-','.' };
        std::vector<char> vowelChars = { 'a','e', 'i', 'o', 'u' };
        const std::vector<char>& getAlphabets()
        {
            static std::vector<char> alphabets;
            if(alphabets.empty())
            {
                for (char ch = 'a'; ch <= 'z'; ch++)
                {
                    alphabets.push_back(ch);
                }
            };

            return alphabets;
        };

        bool is_vowel(char c)
        {
            return std::find(vowelChars.begin(),vowelChars.end(),c) != vowelChars.end();
        }

        bool is_special(char c)
        {
            return std::find(specialChars.begin(),specialChars.end(),c) != specialChars.end();
        }

        const std::vector<char>& consonants()
        {
            static std::vector<char> consonants;

            if(consonants.empty())
            {
                for (char ch = 'a'; ch <= 'z'; ch++)
                {
                    if(is_vowel(ch) == false)
                        consonants.push_back(ch);
                }
            };

            return consonants;
        }

        const std::vector<char>& allcharacters()
        {
            static std::vector<char> allcharacters;
            if(allcharacters.empty())
            {
                allcharacters = getAlphabets();
                allcharacters.insert(allcharacters.end(),specialChars.begin(),specialChars.end());
            }

            return allcharacters;
        }
         //length: độ dài của từ cần tạo
         //buffer: buffer chứa từ sẽ tạo
         //index: chứa vị trí ký tự sắp tạo
         //count: đếm số từ đã tạo được
         void CreateWords(const int length,char* buffer, int index,uint32& count)
         {
            if(index == length)
            {
                count++;
                //printf("%s\n",buffer);
                return;
            }

            //
            if(index == 0)
            {
                const std::vector<char>& alphabet = getAlphabets();
                for(int i =0; i < alphabet.size();i++)
                {
                    char c = alphabet[i];
                    buffer[index] = c;
                    CreateWords(length,buffer,index+1,count);

                }
            }

            if(index == 1)
            {
                if(index == length - 1)
                {
                    const std::vector<char>& chs = getAlphabets();
                    for(int i =0; i < chs.size();i++)
                    {
                        char c = chs[i];
                        buffer[index] = c;
                        CreateWords(length,buffer,index+1,count);
                    }
                }else
                {
                    const std::vector<char>& chs = allcharacters();
                    for(int i =0; i < chs.size();i++)
                    {
                        char c = chs[i];
                        buffer[index] = c;
                        CreateWords(length,buffer,index+1,count);
                    }
                }

            }

            if(index >= 2)
            {
                //ky tu cuoi cung
                if(index == length - 1)
                {
                    const std::vector<char>& chs = getAlphabets();
                    for(int i =0; i < chs.size();i++)
                    {
                         buffer[index] = chs[i];
                         CreateWords(length,buffer,index+1,count);
                    }

                }else{
                    const std::vector<char>& chs = allcharacters();
                    for(int i =0; i < chs.size();i++)
                    {
                        char c = chs[i];
                        //3 ký tự đặc biệt liên tiếp
                        if(is_special(c) && is_special(buffer[index-1])&& is_special(buffer[index-2])) continue;
                        //3 nguyên âm liên tiếp
                        if(is_vowel(c) && is_vowel(buffer[index-1])&& is_vowel(buffer[index-2])) continue;
                        //3 ký tự giống nhau
                        if(c == buffer[index-1] && c == buffer[index-2]) continue;

                         buffer[index] = c;
                         CreateWords(length,buffer,index+1,count);
                    }
                }

            }


         }

         //remain : số ký tụ chưa điền
         //buffer: lưu từ thỏa mãn
         //length: số ký tự đã đc điền
         void generate(int remain, char* buffer, int length,uint32& count)
         {
             if(remain == 0)
             {
                 count++;
                 return;
             }

             const std::vector<char>& conso = consonants();
             for(int i =0; i < conso.size(); i++)
             {
                 char c = conso[i];
                 if(length < 2)
                 {
                     buffer[length] = c;
                     generate(remain - 1,buffer,length+1,count);
                 }else
                 {
                     // No three consecutive characters are of the same character
                     if(buffer[length-1] == c && c == buffer[length-2])
                     {

                     }else{
                         buffer[length] = c;
                         generate(remain - 1,buffer,length+1,count);
                     }
                 }
             }

             for(int i =0; i < vowelChars.size();i++)
             {
                 char v = vowelChars[i];
                 if(length < 2)
                 {
                     buffer[length] = v;
                     generate(remain - 1,buffer,length+1,count);
                 }else{
                     // No three consecutive vowels are found
                     if( is_vowel(buffer[length-1])&& is_vowel(buffer[length-2]) )
                     {

                     }
                     else
                     {
                         buffer[length] = v;
                         generate(remain - 1,buffer,length+1,count);
                     }
                 }
             }

             //Neither the first character nor the last character is a special character.
             if(remain != 1 && length != 0)
             {
                 for(int i =0; i < specialChars.size();i++)
                 {
                    char s = specialChars[i];
                    if(length < 2)
                    {
                         buffer[length] = s;
                         generate(remain - 1,buffer,length+1,count);
                    }else
                    {
                        if(is_special(buffer[length-1]) && is_special(buffer[length-2]) )
                        {

                        }else
                        {
                            buffer[length] = s;
                            generate(remain - 1,buffer,length+1,count);
                        }
                    }
                 }
             }

         }
        //[2019.05.13] do subtask2:  //Complex O(N)
         UINT64 CollabSource_Subtask3(INT64 a, INT64 b)
        {
            INT64 sum = 0;
            INT64  n = max<INT64>(a,b);
            INT64  m_size = 10;
            //[2019.05.14] this is very important when use "INT64" instead of "UINT64"
            INT64* s = new INT64[m_size];
            INT64* v = new INT64[m_size];
            INT64* c = new INT64[m_size];
            INT64* f = new INT64[m_size];
            memset(s,0,m_size*sizeof(INT64));
            memset(v,0,m_size*sizeof(INT64));
            memset(c,0,m_size*sizeof(INT64));
            memset(f,0,m_size*sizeof(INT64));
            s[1] = 0;
            s[2] = 26 * 3;
            v[1] = 5;
            v[2] = 26*5;
            v[3] = (26 * 3) * 5 + (26 * 26) * 5 - (5 * 5 * 5);
            c[1] = 21;
            c[2] = 26 * 21;
            c[3] = (26 * 3) * 21 + (26 * 26) * 21 - 21;

            INT64 i =0;
            for(INT64 k = 1; k <= n;k++ )
            {
                i = k;
                if(k > 4)
                {
                    i = 4;
                    //dich chuyen sang trai
                    s[1] = s[2];s[2] = s[3];s[3] = s[4];
                    v[1] = v[2];v[2] = v[3];v[3] = v[4];
                    c[1] = c[2];c[2] = c[3];c[3] = c[4];
                    f[1] = f[2];f[2] = f[3];f[3] = f[4];
                }
                if(i > 2)//i not in S
                {
                    s[i] = f[i - 2] * 9 + f[i - 1] * 3;
                }

                if(i > 3)
                {
                    v[i] = s[i - 1] * 5 + f[i - 1] * 5 - (c[i - 3] + s[i - 3]) * 5 * 5 * 5;
                }

                if(i > 3)
                {
                    c[i] = s[i - 1] * 21 + f[i - 1] * 21 - (v[i - 3] + s[i - 3]) * 21 - c[i - 3] * 20;
                }

                f[i] = v[i] + c[i];//i =1,2


                f[i] %= MODULO;
                s[i] %= MODULO;
                v[i] %= MODULO;
                c[i] %= MODULO;

                if(k >= a && k <=b)
                {
                    sum += f[i];
                    sum %= MODULO;
                }
            }

            if(sum < 0 ) sum =  sum + MODULO;
            return sum;
        };

        //[2019.05.14] do subtask3,4
        //typedef Maxtrix<INT64,10> Matrix10

        template<typename T,INT64 N>
        struct Maxtrix
        {
            T val[N][N];
            Maxtrix()
            {
                for(int i =0; i < N;i++)
                {
                    for(int j =0; j < N; j++)
                    {
                        val[i][j] = 0;
                    }
                }
            }

            Maxtrix& setIdentity()
            {
                for(int i =0; i < N; i++)
                {
                    val[i][i] = 1;
                }
                return *this;
            }

            //Maxtrix&  copy(const Maxtrix<T,N>& other)
            Maxtrix&  copy(const Maxtrix& other)
            {
                for(int i =0; i <N;i++)
                {
                    for(int j =0; j < N;j++)
                    {
                        val[i][j] = other.val[i][j];
                    }
                }
                 return *this;
            }
        };

        template<typename T, INT64 N>
        Maxtrix<T,N> mutilply(const Maxtrix<T,N>& a, const Maxtrix<T,N>& b)
        {
            Maxtrix<T,N> temp;
            for(int i =0; i < N;i++)
            {
                for(int j =0; j < N; j++)
                {
                    for(int k =0; k < N;k++)
                    {
                        temp.val[i][j] += a.val[i][k] * b.val[k][j];
                        temp.val[i][j] %= MODULO;
                    }
                }
            }

            return temp;
        }


        template<typename T, INT64 N>
        std::array<T,N> mat_mul(const Maxtrix<T,N> &matrix, const std::array<T,N>& arr)
        {
            std::array<T,N> res = {0,};
            for(int i =0; i < N; i++)
            {
                for(int k =0; k < N;k++)
                {
                    res[i] += matrix.val[i][k] * arr[k];
                    res[i] %= MODULO;
                }
            }

            return res;
        }

        template<typename T, INT64 N>
        Maxtrix<T,N> mat_pow(const Maxtrix<T,N> &M, INT64 n)
        {
            Maxtrix<T,N> matrix = M;
            Maxtrix<T,N> result;
            result.setIdentity();
            while(n > 0)
            {
                if(n % 2 == 1)
                {
                    result = mutilply<T,N>(result,matrix);

                    n = (n-1)/2;
                }else{
                    n = n /2;
                }
                //NOTICE: FAIL FAIL FAIL
                //n = std::floor<INT64>((double)n/2.0f);//INT64 -> double: only with 15 digits can cast correct

                matrix  = mutilply<T,N>(matrix,matrix);
            }

            return result;
        }



        INT64 subsum(const Maxtrix<INT64,10>& M,const std::array<INT64,10>& a3,INT64 n)
        {
            if(n ==0) return 0;
            else if(n == 1) return 26;
            else if(n == 2) return 702;
            else if(n == 3) return 20160;

            Maxtrix<INT64,10> temp = mat_pow<INT64,10>(M,n-3);
            std::array<INT64,10> an = mat_mul<INT64,10>(temp,a3);
            INT64 gn =  an[9]% MODULO;
            return gn;
        }
        //Complex O(log(N))
         INT64 CollabSource_Subtask4(INT64 a, INT64 b)
         {
             //chuyển công thức tính s(n),v(n),c(n) thành nhân ma trận
             //a(n) = M * a(n-1)
             //a(n) = [s(n),s(n-1),s(n-2),v(n),v(n-1),v(n-2),c(n),v(n-1),v(n-2),g(n)] //g(n) = sum of f(1->n)
             std::array<INT64,10> a3 = {2262,78,0,3645,130,5,15813,546,21,20160};
             Maxtrix<INT64,10> M;
             INT64 temp[10][10] = {
                {0, 0, 0, 3, 9, 0, 3, 9, 0, 0},
                {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                {5, 0, -125, 5, 0, 0, 5, 0, -125, 0},
                {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                {21, 0, -21, 21, 0, -21, 21, 0, -20, 0},
                {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                {5 + 21, 0, -125 - 21, 5 + 21, 0, -21, 5 + 21, 0, -125 - 20, 1}
             };

             for(int i = 0; i < 10; i++)
             {
                 for(int j =0; j < 10; j++)
                 {
                     M.val[i][j] = temp[i][j];
                 }
             }

            INT64 res = subsum(M,a3,b) - subsum(M,a3,a-1);
            if(res < 0) res += MODULO;

//            Unit TEST FOR mat_mul, mat_pow
//            std::array<INT64,3> a3 = {1,2,3};
//            Maxtrix<INT64,3> N;
//            INT64 temp1[3][3] = {
//                {2,2,2},
//                {2,2,2},
//                {2,2,2}
//            };
//
//             for(int i = 0; i < 3; i++)
//             {
//                 for(int j =0; j < 3; j++)
//                 {
//                     N.val[i][j] = temp1[i][j];
//                 }
//             }
//
//            std::array<INT64,3> tt = mat_mul<INT64,3>(N,a3);
//            Maxtrix<INT64,3> mm =  mat_pow(N,3);

            return res;
         }



         void Run_Problem2_5(const char* inputPath)
        {
            //const std::vector<char>& arr = allcharacters();
            //printf("size = %d\n",arr.size());

            printf("Problem 5: %s\n", inputPath);
            uint32 a, b;

            FILE *fi = fopen(inputPath, "r");
            if(!fi)
            {
                printf("ERROR : %s",inputPath);
                return;
            }
            fscanf(fi, "%llu", &a);
            fscanf(fi, "%llu", &b);
            //printf("%llu %llu \n",a,b);


            uint32 count = 0;
//            for ( uint32 i = a; i <= b; i++)
//            {
//                uint32 length = i;
//                char* word = new char[length + 1];
//                memset(word,0, length +1);
//                CreateWords(length,word, 0, count);
//                //generate(length,word,0,count);
//                delete[] word;
//            }
            //count = CollabSource_Subtask3(a,b);
            count = CollabSource_Subtask4(a,b);
            //printf("output = %llu \n", count);
            fclose(fi);

            std::string outpath = inputPath;
            outpath = outpath.substr(0,outpath.length()-3);
            outpath += ".out";
            uint32 out = GetOutPut(outpath.c_str());
            if(out == count)
            {
                printf("%llu %llu \n",a,b);
                printf("PASS %lld %lld\n",out,count);
            }
            else
            {
                printf("%llu %llu \n",a,b);
                printf("FAIL %lld %lld\n",out,count);
            }
        }
    }


    void Problem2_5()
    {
        std::string folder = "D:\\Training\\github\\data\\2018_round2\\E\\subtask4";
        std::vector<std::string> output;
        GetFilePaths(folder,output);
        printf("number of samples = %d\n",output.size());
        auto begin = chrono::high_resolution_clock::now();
        //for(int i =0; i< output.size();i++)
        {
            //Bruteforce_Fail::characters.clear();
            //printf("%s\n",output[i].c_str());

            Bruteforce_OK::Run_Problem2_5("D:\\Training\\github\\data\\2018_round2\\E\\subtask4\\E-data-086.in");
            //Bruteforce_OK::Run_Problem2_5("D:\\Training\\github\\data\\2018_round2\\E\\sample-5.in");
            //Bruteforce_OK::Run_Problem2_5(output[i].c_str());
        }
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout <<"\n"<< ms << " ms" << endl;//2 ms

    }
}
