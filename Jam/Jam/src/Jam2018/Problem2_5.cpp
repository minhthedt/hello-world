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

using namespace std;

namespace Jam2018
{
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
            printf("%llu %llu \n",a,b);


            uint32 count = 0;
            for ( uint32 i = a; i <= b; i++)
            {
                uint32 length = i;
                char* word = new char[length + 1];
                memset(word,0, length +1);
                CreateWords(length,word, 0, count);
                //generate(length,word,0,count);
                delete[] word;
            }
            printf("output = %lld \n", count);
            fclose(fi);

            std::string outpath = inputPath;
            outpath = outpath.substr(0,outpath.length()-3);
            outpath += ".out";
            uint32 out = GetOutPut(outpath.c_str());
            if(out == count) printf("PASS\n");
            else printf("FAIL %lld %lld\n",out,count);
        }
    }

    void Problem2_5()
    {
        std::string folder = "D:\\Training\\github\\data\\2018_round2\\E";
        std::vector<std::string> output;
        GetFilePaths(folder,output);
        printf("number of samples = %d\n",output.size());
        //for(int i =0; i< output.size();i++)
        {
            //Bruteforce_Fail::characters.clear();
            //printf("%s\n",output[i].c_str());
             auto begin = chrono::high_resolution_clock::now();
            //Run_Problem2_5(DATA_PROBLEM_2018_2_501);
            Bruteforce_OK::Run_Problem2_5("D:\\Training\\github\\data\\2018_round2\\E\\sample-5.in");
            //Bruteforce_OK::Run_Problem2_5(output[i].c_str());
            //Run_Problem2_5(DATA_PROBLEM_2018_2_512);
            //Run_Problem2_5(DATA_PROBLEM_2018_2_513);

            auto end = chrono::high_resolution_clock::now();
            auto dur = end - begin;
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
            cout <<"\n"<< ms << " ms" << endl;//2 ms
        }

    }
}
