#include "Common.h"

namespace Jam2018
{
    void Run_Problem1_2(const char* inputPath)
    {
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

        char chr;
        int currentLine = 0;
        for (int i = 0; i < lSize; i++)
        {
            fseek(pFile, i, SEEK_SET);
            fread(&chr, 1, 1, pFile);

            if (chr == '\n' || chr == EOF)//end of line
            {
                currentLine++;
            }
        }
    };

    void Problem1_2()
    {
        Run_Problem1_2(DATA_PROBLEM_2018_1_201);
    }
}