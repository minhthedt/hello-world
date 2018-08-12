#include "Common.h"

namespace Jam2018
{
    bool CheckRight(int x, int y, const  char* S, char** data, const int M, const int N)
    {
        if (y + strlen(S) >= M) return false;
        for (int i = 0; i < strlen(S); i++)
        {
            if (S[i] != data[x][y + i])
            {
                return false;
            }
        }

        return true;
    }

    bool CheckDown(int x, int y, const  char* S, char** data, const int M, const int N)
    {
        if (x + strlen(S) >= N) return false;
        for (int i = 0; i < strlen(S); i++)
        {
            if (S[i] != data[x + i][y])
            {
                return false;
            }
        }

        return true;
    }

    bool CheckLeft(int x, int y, const  char* S, char** data, const int M, const int N)
    {
        if (y + 1 < strlen(S)) return false;
        for (int i = 0; i < strlen(S); i++)
        {
            if (S[i] != data[x][y-i])
            {
                return false;
            }
        }

        return true;
    }

    bool CheckUp(int x, int y, const  char* S, char** data, const int M, const int N)
    {
        if (x + 1 < strlen(S)) return false;
        for (int i = 0; i < strlen(S); i++)
        {
            if (S[i] != data[x-i][y])
            {
                return false;
            }
        }

        return true;
    }

    bool CheckRightUp(int x, int y, const  char* S, char** data, const int M, const int N)
    {
        if (x + 1 < strlen(S)) return false;
        if (y + strlen(S) >= M) return false;
        for (int i = 0; i < strlen(S); i++)
        {
            if (S[i] != data[x - i][y+i])
            {
                return false;
            }
        }

        return true;
    }

    bool CheckRightDown(int x, int y, const  char* S, char** data, const int M, const int N)
    {
        if (y + strlen(S) >= M) return false;
        if (x + strlen(S) >= N) return false;
        for (int i = 0; i < strlen(S); i++)
        {
            if (S[i] != data[x + i][y + i])
            {
                return false;
            }
        }

        return true;
    }

    bool CheckLeftUp(int x, int y, const  char* S, char** data, const int M, const int N)
    {
        if (y + 1 < strlen(S)) return false;
        if (x + 1 < strlen(S)) return false;
        for (int i = 0; i < strlen(S); i++)
        {
            if (S[i] != data[x-i][y - i])
            {
                return false;
            }
        }

        return true;
    }

    bool CheckLeftDown(int x, int y, const  char* S, char** data, const int M, const int N)
    {
        if (y + 1 < strlen(S)) return false;
        if (x + strlen(S) >= N) return false;
        for (int i = 0; i < strlen(S); i++)
        {
            if (S[i] != data[x+i][y - i])
            {
                return false;
            }
        }

        return true;
    }

    void Run_Problem1_1(const char* inputPath)
    {
        printf("Resolve 2018 problem 1: %s\n", inputPath);

        FILE * pFile;
        long lSize;
        char * buffer;
        size_t result;

        pFile = fopen(inputPath, "r");
        if (pFile == NULL) 
        { 
            fputs("File error", stderr); 
            exit(1); 
        }

        // obtain file size:
        fseek(pFile, 0, SEEK_END);
        lSize = ftell(pFile);

        char line[512];
        memset(line,0,512);
        char* S = nullptr;
        int M = 0, N = 0;//columns,rows
        char** data = nullptr;
            
        int currentLine = 0;
        char chr;

        int row = 0;
        int count = 0;
        for (int i = 0; i < lSize; i++)
        {
            fseek(pFile, i, SEEK_SET);
            fread(&chr, 1, 1, pFile);
           
            if (chr == '\n' || chr == EOF)//end of line
            {
                currentLine++;
                //read word S 
                if (currentLine == 1)
                {
                    int sizeOfLine = count;
                    S = new char[sizeOfLine +1];
                    memset(S, 0, sizeOfLine +1);
                    memcpy(S, line, count);
                    //printf("S = %s\n",S);
                }

                //read M,N
                if (currentLine == 2)
                {
                    char buf[16];
                    memset(buf,0,16);
                    unsigned char index = 0;
                    int sizeOfLine = count;
                    unsigned char number_word = 0;
                    for (int i = 0; i < sizeOfLine + 1; i++)
                    {
                        if (line[i] != ' ' && line[i] != 0)
                        {
                            memcpy(buf + index, &line[i], 1);
                            index++;
                        }
                        else
                        {
                            if (index != 0)
                            {
                                number_word++;
                                if (number_word == 1)
                                {
                                    M = atoi(buf);
                                    //printf("M = %d \n", M);
                                }

                                if (number_word == 2)
                                {
                                    N = atoi(buf);
                                    //printf("N = %d \n", M);
                                }

                            }

                            index = 0;
                            memset(buf, 0, 16);
                        }
                    }
                }

                if (currentLine > 2)
                {
                    if(data == nullptr) data = new char*[N];//N row
                    if(strlen(line) == M)
                    {
                        char* new_line = new char[M+1];
                        memcpy(new_line, line, M);
                        new_line[M] = 0;
                        data[row] = new_line;
                        row++;
                    }
                    else
                    {
                        printf("ERROR\n");
                    }
                   
                }


                //printf("%s\n", line);
                count = 0;
                memset(line, 0, 512);


            }
            else
            {
                memcpy(line + count, &chr, 1);
                count++;
            }

        }
        fclose(pFile);

        //TODO: resolve problem here

        bool existed = false;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (CheckUp(i, j, S, data, M, N))
                {
                    printf("CheckUp i = %d j = %d\n",i,j);
                    existed = true;
                    //break;
                }

                if (CheckRight(i, j, S, data, M, N))
                {
                    printf("CheckRight i = %d j = %d\n", i,j);
                    existed = true;
                    //break;
                }

                if (CheckDown(i, j, S, data, M, N))
                {
                    printf("CheckDown i = %d j = %d\n",i,j);
                    existed = true;
                    //break;
                }

                if (CheckLeft(i, j, S, data, M, N))
                {
                    printf("CheckLeft i = %d j = %d\n",i,j);
                    existed = true;
                    //break;
                }

                if (CheckRightUp(i, j, S, data, M, N))
                {
                    printf("CheckRightUp i = %d j = %d\n", i, j);
                    existed = true;
                    //break;
                }

                if (CheckRightDown(i, j, S, data, M, N))
                {
                    printf("CheckRightDown i = %d j = %d\n", i, j);
                    existed = true;
                    //break;
                }

                if (CheckLeftUp(i, j, S, data, M, N))
                {
                    printf("CheckLeftUp i = %d j = %d\n", i, j);
                    existed = true;
                    //break;
                }

                if (CheckLeftDown(i, j, S, data, M, N))
                {
                    printf("CheckLeftDown i = %d j = %d\n", i, j);
                    existed = true;
                    //break;
                }
            }
        }

        printf("find = %s\n\n",existed ? "TRUE" : "false");
        //printf("S = %s\n",S);
        //printf("M = %d N = %d\n",M, N);
        //printf("data: \n");
        //for (int i = 0; i < N; i++)
        //{
        //    printf("%s \n",data[i]);
        //}

        delete S;
        for (int i = 0; i < N; i++)
        {
            delete[] data[i];
        }

        delete[] data;

    }

    void Problem1_1()
    {
        Run_Problem1_1(DATA_PROBLEM_2018_1_101);
        Run_Problem1_1(DATA_PROBLEM_2018_1_110);
        Run_Problem1_1(DATA_PROBLEM_2018_1_111);
        Run_Problem1_1(DATA_PROBLEM_2018_1_112);
        Run_Problem1_1(DATA_PROBLEM_2018_1_113);
        Run_Problem1_1(DATA_PROBLEM_2018_1_114);
        Run_Problem1_1(DATA_PROBLEM_2018_1_115);
    }
}