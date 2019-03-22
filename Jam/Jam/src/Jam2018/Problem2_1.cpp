#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <chrono>
using namespace std;

namespace Jam2018
{

	constexpr int inf = 123;
	//hàm này sẽ đếm số case thỏa mã với đầu vào đc chia thành các bộ
	int count(vector<int> cards) {
	    int ans = 0;
	    while (true) {
	        int three = 0;
	        //check xem có bao nhiêu bộ 3, bởi vì cần pải có bộ này để nhóm đủ 5 card theo yêu cầu
	        //tư tưởng là tìm só bộ 3 trước để ghép đôi với bộ 2
	        //nếu hết bộ 3 và chỉ còn bộ 4 thì lấy bộ 4 ghép bộ 2
	        //nếu chỉ còn bộ 4 thì lấy bộ 4 ghép bộ 4
	        if (cards[3])
	            three = 3;
	        else if (cards[4])
	            three = 4;
	        else
	            break;//nếu ko còn bộ 3 hoặc 4 thỉ break

	        int two = 0;
	        if (cards[2])
	            two = 2;
	        else if (cards[4] > 1 || (cards[4] && three != 4))
	        //else if ((three == 4 && cards[4] > 1) || (cards[4] && three == 3))//dễ hiểu hơn
	            two = 4;
	        else if (cards[3] > 1 || (cards[3] && three != 3))//có >= 2 bộ 3
	        //else if ((three == 3 && cards[3] > 1) || (cards[3] && three == 4))//dễ hiểu hơn
	            two = 3;
	        else
	            break;//nếu còn bộ 3,4 nhưng ko còn bộ 2

	        //đoạn này là lấy ra 5 card thỏa mãn
	        --cards[three], ++cards[three-3];//sau khi lấy đi 1 bộ 3 thì còn dư three -3
	        --cards[two], ++cards[two-2];
	        ++ans;
	    }
	    return ans;
	}

	static inline int minhouse(int remove, int n, vector<int> &cards) {
	    if (remove == 0)//sau khi điền hết card vào các bộ 0->4 thì bắt đầu tính có bao nhiêu trường hợp thỏa mãn
	        return count(cards);
	    if (remove < 0 || n < 1)
	        return inf;
	    int ans = inf;
	    for (int i = 0; i <= cards[4]; ++i) {
	    	//tư tưởng là cột 4 sẽ chia sẻ sang các cột còn lại sao cho remove = 0
	        cards[4] -= i, cards[4-n] += i;
	        ans = min(ans, minhouse(remove - i * n, n - 1, cards));
	        cards[4] += i, cards[4-n] -= i;
	    }
	    return ans;
	}
	//[2019.03.21] the.vu create minhouse_1
	int minhouse_1(int remove)
	{
		printf("remove = %d\n",remove);
		vector<int> cards { 0, 0, 0, 0 };
		int ans = 8;

		for(int i1 =0; i1 <=13;i1++)
		{
			for(int i2 =0; i2 <=13; i2++)
			{
				for(int i3 =0; i3 <=13;i3++)
				{
					for(int i4 =0; i4 <=13;i4++)
					{
						int total_cards = i1 * 1 + i2 * 2 + i3 * 3 + i4 * 4 ;
						int total_cases = i1 + i2 + i3 + i4;
						if(total_cards  == 52 - remove && total_cases <= 13)
						{
							//printf("%d %d %d %d %d \n",i1,i2,i3,i4);
							vector<int> cards = {0,i1,i2,i3,i4};
							int m = count(cards);
							//printf("m = %d\n",m);
							ans = min(ans, m);

						}
					}
				}

			}

		}



		return ans;
	}

	int minhouse(int remove) {
	    vector<int> cards { 0, 0, 0, 0, 13 };//brute force cho trường hợp đầu tiên (gồm 13 bộ 4)
	    return minhouse(remove, 4, cards);
	}

	int maxhouse(int remove) {
	    return min(8, (52 - remove) / 5);
	}

    void Run_Problem2_1(const char* inputPath)
    {

		FILE* file = freopen(inputPath, "r", stdin);
		if(file)
		{
			int n;
			cin >> n;

			auto begin = chrono::high_resolution_clock::now();
			cout <<  minhouse_1(n) << ' ' << maxhouse(n) << endl;
			auto end = chrono::high_resolution_clock::now();
			auto dur = end - begin;
			auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
			cout << ms <<" ms: minhouse_1"<< endl;

			begin = chrono::high_resolution_clock::now();
			cout << minhouse(n) << ' ' << maxhouse(n) << endl;
			end = chrono::high_resolution_clock::now();
			dur = end - begin;
			ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
			cout << ms <<" ms: minhouse"<< endl;
			fclose (stdin);
		}
    }
    
    void Problem2_1()
    {
//        Run_Problem2_1(DATA_PROBLEM_2018_2_101);
//        Run_Problem2_1(DATA_PROBLEM_2018_2_110);
//        Run_Problem2_1(DATA_PROBLEM_2018_2_111);
//        Run_Problem2_1(DATA_PROBLEM_2018_2_112);
          Run_Problem2_1("D:\\Training\\github\\data\\2018_round2\\A\\subtask1\\A-data-019.in");
       
    }
}
