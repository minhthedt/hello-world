#include "Common.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <chrono>
#include<iostream>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <functional>
using namespace std;

namespace Jam2019
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 signed long long
#define UINT64 unsigned long long
#define MAX_VALUE 200000


int CompareKey(const char* key1, const char* key2)
{
    if (strlen(key1) < strlen(key2))
    {
        return -1;
    }
    else if (strlen(key1) > strlen(key2))
    {
        return 1;
    }
    else
    {
        return strcmp(key1,key2);
    }
}

void BinarySearch(const std::vector<const char*>& keys, INT32 start, INT32 end, const char* key, int& out)
{
    //printf("start = %d, end = %d\n",start,end);
    if(end == -1) return;
    if(end - start <= 1)
    {
        if(CompareKey(key,keys[start]) == 0)
        {
            out = start;
            return;
        }else if(CompareKey(key,keys[end]) == 0)
        {
            out = end;
            return;
        }

    }else
    {
        INT32 middle = (start + end)/2;
        //printf("middle = %d\n",middle);
        int res = CompareKey(key,keys[middle]);

        if(res < 0)
        {
            BinarySearch(keys,start,middle,key,out);
        }else if(res > 0)
        {
            BinarySearch(keys,middle,end,key,out);
        }else{
            out = middle;
        }
    }
}


int findKey(const std::vector<const char*>& keys,const char* value)
{
    //        printf("array:\n");
    //        for(int i =0; i < keys.size();i++)
    //        {
    //            printf("%s ",keys[i]);
    //        }
    int index = -1;
    BinarySearch(keys,0,keys.size()-1,value,index);
    //        printf("\nkey = %s index = %d\n",value,index);
    return index;
}


struct Operation
{
    UINT8 cmd;
    const char* key;
    INT32 value;
    const char* key1;
    Operation():cmd(0),key(nullptr),value(-1),key1(nullptr){};
    Operation(UINT8 cmd,const char* key,INT32 value): cmd(cmd),key(key),value(value){};//add
    Operation(UINT8 cmd,const char* key,const char* key1): cmd(cmd),key(key),key1(key1){};//sum
    Operation(UINT8 cmd,const char* key): cmd(cmd),key(key){};//purge
    void setAdd(UINT8 cmd_,const char* key_,INT32 value_)
    {
        this->cmd = cmd_;
        this->key = key_;
        this->value = value_;
    }

    void setSum(UINT8 cmd_,const char* key_,const char* key1_)
    {
        this->cmd = cmd_;
        this->key = key_;
        this->key1 = key1_;
    }

    void setPurge(UINT8 cmd_,const char* key_)
    {
        this->cmd = cmd_;
        this->key = key_;
    }

};


struct Handler
{
    INT64 sum;
    INT64* arr;
    std::vector<const char*> keys;//was sort increase
    Handler() :sum(0),arr(nullptr) {
        //arr = new INT64[MAX_VALUE];
        //memset(arr,0,MAX_VALUE*sizeof(INT64));
    };
    ~Handler()
    {
        delete[] arr;
    }

    void Init(int n)
    {
        arr = new INT64[n*2];
        memset(arr,0,n*2*sizeof(INT64));
    }

    void Run(const Operation& op)
    {
        if(op.cmd == 1)
        {
            Addition(op.key,op.value);
        }else if(op.cmd == 2)
        {
            Sum(op.key,op.key1);
        }else if(op.cmd == 3)
        {
            Purge(op.key);
        }else{
            printf("ERROR Run...\n");
        }

    }
    private:
    INT32 GetIndexFromKey(const char* key)
    {
        return findKey(keys,key);
    }

    void Addition(const char* key, INT32 value)
    {
        INT32 index = GetIndexFromKey(key);
        arr[index] += value;
        sum += value;
        //cout << sum << " ";
        //printf("%lld ",sum);
    }

    void Purge(const char* key)
    {
        INT32 index = GetIndexFromKey(key);
        sum -= arr[index];
        arr[index] = 0;
        //cout << sum << " ";
        //printf("%lld ",sum);
    }

    void Sum(const char* key1, const char* key2)
    {
        INT32 index1 = GetIndexFromKey(key1);
        INT32 index2 = GetIndexFromKey(key2);
        INT32 min,max;
        if(index1 < index2 )
        {
            min = index1; max = index2;
        }else{
            min = index2; max = index1;
        }

        INT64 tong =0;
        for(INT32 i =min; i <= max; i++)
        {
            tong += arr[i];
        }
        //cout << tong << " ";
        //printf("%lld ",tong);
    }

};





    void Run_Problem1_6(const char* inputPath)
    {
       ios_base::sync_with_stdio(false);
        cin.tie(NULL);

        UINT32 n;//1 <= n <= 100,000
        Operation* list_operations = nullptr;
        char* buf_key = nullptr;
        char* start_buf_key = nullptr;

        Handler handler;
        std::vector<const char*>& keys = handler.keys;


        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {

            cin >> n;
            handler.Init(n);
            list_operations = new Operation[n];
            buf_key = new char[n*2*100];
            start_buf_key = buf_key;
            memset(buf_key,0,n*2*100);
            keys.reserve(n*2);
            //printf("%d\n",n);
            for (int i = 0; i < n; i++)
            {

                INT32 cmd;
                cin >> cmd;
                if (cmd == 1)//add
                {
                    char* key = buf_key;
                    INT32 value;// -10^9 and 10^9
                    cin >> buf_key;
                    cin >> value;
                    //printf("%d %s %d\n", cmd, key, value);
                    buf_key += 100;
                    list_operations[i].setAdd(cmd,key,value);

                    keys.push_back(key);

                }
                else if (cmd == 2)//sum
                {
                    char* key1 = buf_key;
                    cin >> key1;
                    buf_key += 100;
                    char* key2 = buf_key;
                    cin >> key2;
                    buf_key += 100;
                    //printf("%d %s %s\n", cmd, key1, key2);
                    list_operations[i].setSum(cmd,key1,key2);

                    keys.push_back(key1);
                    keys.push_back(key2);
                }
                else  if (cmd == 3)//Purge
                {
                    char* key = buf_key;
                    cin >> key;
                    buf_key += 100;
                    //printf("%d %s \n", cmd, key);
                    list_operations[i].setPurge(cmd,key);

                    keys.push_back(key);
                }


            }
            fclose(fi);
        }

        //sort all keys
        //printf("key.size = %d\n",keys.size());
        std::sort(keys.begin(),keys.end(),[](const char* key1, const char* key2) -> bool{

            if (CompareKey(key1, key2) < 0) return true;
            else return false;
        });
        std::vector<const char*> temp;
        temp.push_back(keys[0]);
        for(int i =1; i < keys.size();i++)
        {
            if(CompareKey(keys[i],temp[temp.size()-1]) != 0)
            {
                temp.push_back(keys[i]);
            }
        }
        keys.swap(temp);
        //printf("key.size = %d\n",keys.size());
        //        for(int i =0; i < keys.size();i++)
        //        {
        //            printf("%s ",keys[i].c_str());
        //        }
        for(INT32 i = 0; i < n;i++)
        {
            handler.Run(list_operations[i]);
        }

        //free memory
        delete[] list_operations;
        delete[] start_buf_key;

    };

    void Problem1_6()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem1_6("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round1\\F\\subtask2\\P6-data-020.in");
        //Run_Problem1_6("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round1\\problem6\\input001.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout <<"\n\n"<< ms << " ms" << endl;//2 ms
    }
}
