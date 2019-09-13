#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <chrono>
#include <math.h>
using namespace std;
//[2019-09-13] chưa hiểu rõ lời giải: kiểu quy hoạch động + phân chia nhiều trường hợp
namespace Jam2016
{
#define MAX_N 2000
#define max(a, b) ((a > b) ? a : b)
    int power[MAX_N];
    int female[MAX_N];
    int N;
    int chk_cal[MAX_N + 1][MAX_N];
    int next_fe[MAX_N];
    inline int mul_p(int a, int b)
    {
        if (female[a] != female[b])
            return power[a] * power[b];
        return 0;
    }
    int find_max_power(void)
    {
        int i, k;
        int st, ed, len;
        int p;
        int max_p = 0;

        for (i = 0, k = i; i < N; i++) {
            if (female[i])
                while (k <= i)
                    next_fe[k++] = i;
        }
        while (k < N)
            next_fe[k++] = MAX_N + 1;

        for (i = 0; i < N - 1; i++) {
            chk_cal[i][i + 1] = mul_p(i, i + 1);
        }
        for (len = 3; len <= N; len++) {
            for (st = 0; st < N - len + 1; st++) {
                ed = st + len - 1;
                int n_st = next_fe[st];
                int n_ed = next_fe[ed];

                max_p = max(chk_cal[st][ed - 1], chk_cal[st + 1][ed]);
                p = mul_p(st, ed) + chk_cal[st + 1][ed - 1];
                max_p = max(p, max_p);
                if (female[st] == 0) {
                    for (k = n_st; k < n_ed; k = next_fe[k + 1]) {
                        p = chk_cal[st][k] + chk_cal[k + 1][ed];
                        max_p = max(p, max_p);
                    }
                }
                else if (female[st] == 1 && female[ed] == 0) {
                    for (k = n_st; k < n_ed; k = next_fe[k + 1]) {
                        p = chk_cal[st][k - 1] + chk_cal[k][ed];
                        max_p = max(p, max_p);
                    }
                }
                else { /* (female[st] == 1 && female[ed] == 1) */
                    for (k = st + 1; k < ed - 1; k++) {
                        p = chk_cal[st][k] + chk_cal[k + 1][ed];
                        max_p = max(p, max_p);
                    }
                }
                chk_cal[st][ed] = max_p;
            }
        }
        return max_p;
    }

    void Run_Problem1_5(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            int i, t;
            int max;
            //scanf("%d", &t);
            cin >> t;
            while (t--) {
                //scanf("%d", &N);
                cin >> N;
                memset(chk_cal, 0, sizeof(chk_cal));
                memset(next_fe, 0, sizeof(next_fe));
                for (i = 0; i < N; i++) {
                    //scanf("%d", &power[i]);
                    cin >> power[i];
                }
                for (i = 0; i < N; i++) {
                    //scanf("%d", &female[i]);
                    cin >> female[i];
                }
                max = find_max_power();
                printf("%d\n", max);
            }

            fclose(fi);

        }
    };

    void Problem1_5()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem1_5("D:\\Training\\github\\hello-world\\reference\\Sample\\2016\\round1\\Problem5_set1\\input000.txt");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//2 ms
    }
}
