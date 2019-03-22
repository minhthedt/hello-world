#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

namespace Jam2018
{
#define uint32 unsigned int

	struct CAS
	{
		int Z;
		int sum;
		CAS(int Z, int sum):Z(Z),sum(sum){};
	};
	int Brute_Force(int R,int C, int D, int W, int** arr)
	{
		int total_blocks = R*C;
		int cost = 0;
		std::map<int,int,std::less<int> >  p_map;
		for(int i = 0; i < R; i++)
		{
			for(int j = 0; j < C; j++)
			{
				if(p_map.find(arr[i][j]) == p_map.end())
				{
					p_map[arr[i][j]] = 1;
				}else
				{
					p_map[arr[i][j]]++;
				}
			}
		}

		int num_skyscraper = 0;
		std::vector<CAS> cases;
		std::map<int,int>::iterator it;
		for(it = p_map.begin(); it != p_map.end();it++)
		{
			printf("%d %d \n",it->first,it->second);
			//kiểm tra số block là chẵn
			num_skyscraper += it->second;
			int num_block_parks = total_blocks - num_skyscraper;
			if(num_block_parks %2 == 0)
			{
				printf("Pass %d %d \n",it->first,it->second);
				//tính cost nếu xây dựng thành công
				int Z = it->first;
				int num_parks  = num_block_parks / 2;
				int sum = Z * W + num_parks * D;
				cases.push_back(CAS(Z,sum));
			}
		}

		std::sort(cases.begin(), cases.end(), [](const CAS& t1,const CAS& t2) -> bool
			{
				return t1.sum < t2.sum;
			}
		);

		for(int i =0; i< cases.size();i++)
		{
			printf("%d %d \n",cases[i].Z,cases[i].sum);
		}
		return cost;

	}
    void Run_Problem2_4(const char* inputPath)
    {
    	FILE* file = freopen(inputPath, "r", stdin);
		if(file)
		{
			int R,C,D,W;
			cin >> R >> C >> D >> W;
            printf("%d %d %d %d\n",R,C,D,W);
            int** arr = new int*[R];
            for(int j =0; j < R; j++)
            {
            	arr[j] = new int[C];
            }

            for(int i = 0; i < R ; i++)
            {
            	for(int j =0 ; j < C; j++)
            	{
            		cin >> arr[i][j];
            		printf("%d ",arr[i][j] );
            	}
            	printf("\n");
            }

            //TOFO
            int cost = Brute_Force(R,C,D,W,arr);


			fclose (stdin);
		}


    }


    void Problem2_4()
    {
        //Run_Problem2_4(DATA_PROBLEM_2018_2_401);
        //Run_Problem2_4(DATA_PROBLEM_2018_2_410);
        //Run_Problem2_4(DATA_PROBLEM_2018_2_411);
        Run_Problem2_4("D:\\Training\\github\\data\\2018_round2\\D\\sample-1.in");
        //Run_Problem2_4(DATA_PROBLEM_2018_2_413);

    }
}
