#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <chrono>
#include <math.h>
#include <algorithm>
using namespace std;

namespace Jam2016
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 signed long long
#define UINT64 unsigned long long
#define PI  3.1415926535897932384626344
#define MAXN    100000



    bool isEven(char cnt[])
    {
        for (int i = 0; i < 26; i++)
        {
            if (cnt[i] & 1 )//cnt[i] đến số lượng ký tự i trong chuỗi
            {
                return false;
            }
        }
        return true;
    };
    //Độ phức tạp O(n^2)
    void Run_Problem1_3_SubTask1(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
         if(fi)
         {
            UINT32 T;
            cin >> T;
            char cnt[26];
            for (int i = 0; i < T; i++)
            {
                char* gs = new char[MAXN];
                memset(gs, 0, MAXN);
                cin >> gs;
                //printf("%s\n", gs);

                int size = strlen(gs);
                int ans = 0;
                //O(n^2) = ((N+1)*N/2)/2
                //duyệt tất cả các sub string có size chẵn
                //string sau được tính từ string trước
                for (int i = 0; i < size - 1; i++)
                {
                    memset(cnt, 0, 26);
                    for (int j = i; j < size - 1; j+=2)
                    {
                        cnt[gs[j] - 'a']++;
                        cnt[gs[j+1] - 'a']++;
                        if (isEven(cnt))ans++;
                    }
                }

                cout << ans << std::endl;
            }
            fclose(fi);
        }
        else
        {
            printf("FAIL open %s\n",inputPath);
        }

    }
    //Độ phức tạp O(nlogn) (độ phức tập hàm xắp xếp, quicksort)
    void Run_Problem1_3_SubTask2(const char* inputPath)
    {
        //ý tưởng rất hay, đầu tiên gán mỗi ký tự với 1 số integer : 1 << (word [i] - 'a')
        //Tính XOR toàn ký tự trọng 1 substring -> nếu XOR = 0 =>  substring này thỏa mản
        //Hay ho ở chỗ, ta sẽ tính giá trị XOR (1:K) (k chạy từ 1 -> N)
        //Ta sẽ có N kết quả => sắp xếp tăng dần, trong N kết quả sẽ có giá trị = nhau
        //ví dụ XOR(1:a) = XOR(1:b) => substring[a+1:b] thỏa mãn
        //Giả sử có Y giá trị XOR giống nhau -> có Y*(Y-)/2 cặp XOR = số substring thỏa mã
        FILE* fi = freopen(inputPath, "r", stdin);
         if(fi)
         {
            UINT32 T;
            cin >> T;

            for (int i = 0; i < T; i++)
            {
                //chứa chuỗi ký tự đầu vào
                char* gs = new char[MAXN];
                memset(gs, 0, MAXN);
                cin >> gs;
                //printf("%s\n", gs);
                //tính size của chuỗi ký tự
                int size = strlen(gs);
                //tạo mảng chưa giá trị XOR
                INT32* xors = new INT32[size];
                memset(xors, 0, size*sizeof(INT32));
                //
                INT32 org = 0x00;
                for (int i = 0; i < size; i++)
                {
                    //convert ky tu gs[i] thanh integer de su dung XOR (mỗi ký tự biểu diễn 1 bit trong 32 bit của integer)
                    INT32 temp = 1 << (gs[i] - 'a');
                    //printf("0x%x \n",temp);
                    //dich sang trai
                    if(i ==0)
                    {
                        xors[i] = org ^ temp;
                    }else{
                        xors[i] = xors[i-1] ^ temp;
                    }

                }
                sort(xors, xors+size);//O (n log n).
                int ans = 0;
                int numsub =0;
                for(int i =0; i < size; i++)
                {
                    //printf("0x%x ",xors[i]);
                    if(i == 0) numsub = 1;

                    if(xors[i] == 0) { ans++;}

                    if(i > 0)
                    {
                        if(xors[i] != xors[i-1])
                        {
                            //check số phần tử = lien tiep
                            if(numsub > 1)
                            {
                                //printf("numsub = %d\n",numsub);
                                ans += numsub*(numsub-1)/2;
                            }
                            //bắt đầu chuỗi = mới
                            numsub=1;

                        }else{
                            numsub++;
                        }
                    }

                }
                cout << ans << std::endl;


            }
            fclose(fi);
        }
        else
        {
            printf("FAIL open %s\n",inputPath);
        }

    }

     //Độ phức tạp O(n) (độ phức tập hàm xắp xếp, quicksort)
    void Run_Problem1_3_SubTask3(const char* inputPath)
    {
        //ý tưởng rất hay, đầu tiên gán mỗi ký tự với 1 số integer : 1 << (word [i] - 'a')
        //Tính XOR toàn ký tự trọng 1 substring -> nếu XOR = 0 =>  substring này thỏa mản
        //Hay ho ở chỗ, ta sẽ tính giá trị XOR (1:K) (k chạy từ 1 -> N)
        //Ta sẽ có N kết quả => sắp xếp tăng dần, trong N kết quả sẽ có giá trị = nhau
        //ví dụ XOR(1:a) = XOR(1:b) => substring[a+1:b] thỏa mãn
        //Giả sử có Y giá trị XOR giống nhau -> có Y*(Y-)/2 cặp XOR = số substring thỏa mã
        FILE* fi = freopen(inputPath, "r", stdin);
         if(fi)
         {
            UINT32 T;
            cin >> T;
            // coi moi gia tri xor là 1 index của mảng, thì mảng cần tạo có độ lớn là 2^26 x 4 = 256MB
            UINT32* gN = new UINT32[1 << 26];

            for (int i = 0; i < T; i++)
            {
                 //memset(gN,0,sizeof(UINT32)*(1<<26));
                //mảng chứa các giá trị xor
                std::vector<UINT32> xors;
                //chứa chuỗi ký tự đầu vào
                char* gs = new char[MAXN];
                memset(gs, 0, MAXN);
                cin >> gs;
                //printf("%s\n", gs);
                //tính size của chuỗi ký tự
                int size = strlen(gs);
                //tạo mảng chưa giá trị XOR
                INT32 aaa = 0x00;
                int ans = 0;
                //
                INT32 org = 0x00;
                for (int i = 0; i < size; i++)
                {
                    //convert ky tu gs[i] thanh integer de su dung XOR (mỗi ký tự biểu diễn 1 bit trong 32 bit của integer)
                    INT32 temp = 1 << (gs[i] - 'a');
                    //printf("0x%x \n",temp);
                    //dich sang trai
                    if(i ==0)
                    {
                        aaa = org ^ temp;
                    }else{
                        aaa ^= temp;
                    }

                    if(aaa == 0) ans++;

                    gN[aaa]++;
                    if(gN[aaa] == 1)xors.push_back(aaa);
                    //printf("aaa = 0x%x \n",aaa);
                }


                for(int i =0; i < xors.size();i++)
                {
                    int aaa_ = xors[i];
                    ans += gN[aaa_] * (gN[aaa_] - 1) /2;
                    gN[aaa_] = 0;
                }
                cout << ans << std::endl;


            }
            fclose(fi);
        }
        else
        {
            printf("FAIL open %s\n",inputPath);
        }

    }



    void Problem1_3()
    {
        auto begin = chrono::high_resolution_clock::now();
        //Run_Problem1_3_SubTask1("D:\\Training\\github\\hello-world\\reference\\Sample\\2016\\round1\\Problem3_set4\\inputL001.txt");//224030 ms
        //Run_Problem1_3_SubTask2("D:\\Training\\github\\hello-world\\reference\\Sample\\2016\\round1\\Problem3_set4\\inputL001.txt");//918ms
        Run_Problem1_3_SubTask3("D:\\Training\\github\\hello-world\\reference\\Sample\\2016\\round1\\Problem3_set4\\inputL001.txt");//918ms
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
