#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include <chrono>
#include <math.h>
using namespace std;


namespace Jam2018
{
#define uint32 unsigned int
    namespace BruteForce
    {
        struct CAS
        {
            int Z;
            int sum;
            CAS(int Z, int sum) :Z(Z), sum(sum) {};
        };

        void CanBuidParks(int R, int C, int** arr, int Z, bool& pass)
        {
            bool existedEmptyBlock = false;
            for (int i = 0; i < R; i++)
            {
                for (int j = 0; j < C; j++)
                {
                    //duyệt những block dùng cho xây dựng công viên
                    if (arr[i][j] > Z)
                    {
                        existedEmptyBlock = true;
                        //kiểm tra xem có block liền kề có trống không
                        //nếu đã tìm đc trường hợp thỏa mãn (pass = true) thì không cần check các trường hợp còn lại
                        if (!pass)
                        {
                            std::vector<int*> childrens;

                            if (i + 1 < R && arr[i + 1][j] > Z)
                            {
                                childrens.push_back(&arr[i + 1][j]);
                            }

                            if (i - 1 >= 0 && arr[i - 1][j] > Z)
                            {
                                childrens.push_back(&arr[i - 1][j]);
                            }

                            if (j + 1 < C && arr[i][j + 1] > Z)
                            {
                                childrens.push_back(&arr[i][j + 1]);
                            }

                            if (j - 1 >= 0 && arr[i][j - 1] > Z)
                            {
                                childrens.push_back(&arr[i][j - 1]);
                            }

                            for (int k = 0; k < childrens.size(); k++)
                            {
                                int old1 = arr[i][j];
                                int old2 = *childrens[k];
                                arr[i][j] = Z;//bỏ qua việc check 2 blocks
                                *childrens[k] = Z;
                                CanBuidParks(R, C, arr, Z, pass);
                                arr[i][j] = old1;
                                *childrens[k] = old2;
                            }
                        }



                    }
                }
            }

            if (!existedEmptyBlock)
            {
                pass = true;
            }
        }

        int Caculate(int R, int C, int D, int W, int** arr)
        {
            int total_blocks = R * C;
			//map.first là độ cao, map.second là số block có cùng độ cao
            std::map<int, int, std::less<int> >  p_map;
            for (int i = 0; i < R; i++)
            {
                for (int j = 0; j < C; j++)
                {
                    if (p_map.find(arr[i][j]) == p_map.end())
                    {
                        p_map[arr[i][j]] = 1;
                    }
                    else
                    {
                        p_map[arr[i][j]]++;
                    }
                }
            }

            int num_skyscraper = 0;
            //tìm danh sách độ cao Z có thể xây dựng skycraper + matching parks
            //1 CAS sẽ chưa độ cao Z và sum là tổng chi phí nếu xây dựng thành công
            std::vector<CAS> cases;
            std::map<int, int>::iterator it;
            for (it = p_map.begin(); it != p_map.end(); it++)
            {
                printf("%d %d \n",it->first,it->second);
                //kiểm tra số block là chẵn
                num_skyscraper += it->second;
                int num_block_parks = total_blocks - num_skyscraper;
                if (num_block_parks % 2 == 0)//check xem có khả năng matching ko
                {
                    //printf("Pass %d %d \n",it->first,it->second);
                    //tính cost nếu xây dựng thành công
                    int Z = it->first;
                    int num_parks = num_block_parks / 2;
                    int sum = Z * W + num_parks * D;
                    cases.push_back(CAS(Z, sum));
                }
            }
            //bổ sung thêm trường hợp toàn bộ block là parks, tương đương trường hợp Z =0
            if(R*C %2 == 0)cases.push_back(CAS(0, 0.5 * R*C* D));

            //xắp xếp lại danh sách theo chi phí tăng dần
            std::sort(cases.begin(), cases.end(), [](const CAS& t1, const CAS& t2) -> bool
            {
                return t1.sum < t2.sum;
            }
            );

            //duyệt danh sách xem có xây dựng đc matching-parks không
            for (int i = 0; i< cases.size(); i++)
            {
                printf("Z = %d sum = %d \n",cases[i].Z,cases[i].sum);
                bool pass = false;
                CanBuidParks(R, C, arr, cases[i].Z, pass);
                if (pass)
                {
                    printf("PASS: %d %d \n", cases[i].Z, cases[i].sum);
                    //printf("%d\n", cases[i].sum);
                    return cases[i].sum;
                }
            }
            return 0;

        }
        void Run_Problem2_4(const char* inputPath)
        {
            FILE* file = freopen(inputPath, "r", stdin);
            if (file)
            {
                int R, C, D, W;
                cin >> R >> C >> D >> W;
                printf("%d %d %d %d\n", R, C, D, W);
                int** arr = new int*[R];
                for (int j = 0; j < R; j++)
                {
                    arr[j] = new int[C];
                }

                for (int i = 0; i < R; i++)
                {
                    for (int j = 0; j < C; j++)
                    {
                        cin >> arr[i][j];
                        printf("%d ", arr[i][j]);
                    }
                    printf("\n");
                }

                //TOFO
                auto begin = chrono::high_resolution_clock::now();
                int cost = Caculate(R, C, D, W, arr);
                printf("cost = %d\n",cost);
                auto end = chrono::high_resolution_clock::now();
                auto dur = end - begin;
                auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
                cout << ms << " ms" << endl;
                fclose (stdin);
            }

        }
    }

    namespace MaximumBipartiteMatching
    {
        enum E_COLOR
		{
        	none =0,
			black,
			white
		};
    	struct Block
		{
    		int i,j;
    		int z;
    		E_COLOR color;
    		bool visisted;
    		Block* parent;
    		Block(): i(-1),j(-1),z(-1),color(E_COLOR::none),visisted(false),parent(nullptr){};
    		Block(int i,int j):i(i),j(j){};
		};

		 struct CAS
        {
            int Z;
            int sum;
            CAS(int Z, int sum) :Z(Z), sum(sum) {};
        };

        //Đọc dữ liệu từ file đầu vào
        bool ReadDataFile(const char* inputPath,Block** &arr,int& R, int& C, int& D, int& W )
        {
            FILE* file = freopen(inputPath, "r", stdin);

			if (file)
			{
				cin >> R >> C >> D >> W;
				printf("%d %d %d %d\n", R, C, D, W);
				arr = new Block*[R];
				for (int i = 0; i < R; i++)
				{
					arr[i] = new Block[C];
				}

				for (int i = 0; i < R; i++)
				{
					for (int j = 0; j < C; j++)
					{
						int z;
						cin >> z;
						arr[i][j].i = i;
						arr[i][j].j = j;
						arr[i][j].z = z;

						if(i%2 == 0)//điền màu cho các ô
						{
							if(j%2 == 0) arr[i][j].color = E_COLOR::white;
							else arr[i][j].color = E_COLOR::black;
						}else
						{
							if(j%2 == 0) arr[i][j].color = E_COLOR::black;
							else arr[i][j].color = E_COLOR::white;
						}
						//printf("%d ", arr[i][j].color);
						printf("%d ", z);
					}
					printf("\n");
				}
				fclose (stdin);
				return true;
			}

			return false;
        }

        //kiểm tra xem số block dành build parks, black == white ?
        //Z là level của skyscraper
        bool CheckEqualBlackWhile(Block** arr, int R, int C, int Z)
        {
            int nblacks =0;
            int nwhites = 0;
            for(int i =0; i < R;i++)
            {
                for(int j =0; j < C;j++)
                {
                    if(arr[i][j].z > Z)//các block này dùng build Parks
                    {
                        if(arr[i][j].color == E_COLOR::black) nblacks++;
                        else if(arr[i][j].color == E_COLOR::white) nwhites++;
                        else printf("ERROR data \n");
                    }

                }
            }

            return (nblacks == nwhites) ? true : false;
        }

        //Maximum Bipartite Matching
        bool CheckAdjacent(Block* a,Block* b)
        {
            if(std::abs(a->i - b->i) == 1 && a->j == b->j) return true;
            if(std::abs(a->j - b->j) == 1 && a->i == b->i) return true;
            return false;
        }
        //DFS
        //https://www.geeksforgeeks.org/maximum-bipartite-matching/
        bool bmp(Block* black,const std::vector<Block*>& whites)
        {
            for(int i =0; i < whites.size();i++)
            {
                Block* white = whites[i];
                if(CheckAdjacent(black,white) && white->visisted == false)
                {
                    white->visisted = true;
                    if(white->parent == nullptr || bmp(white->parent,whites))
                    {
                        white->parent = black;
                        return true;
                    }
                }

            }

            return false;

        }

        bool CheckMatchingBiprate(Block** arr, int R, int C, int Z)
        {
            bool res = true;
            std::vector<Block*> blacks;
            std::vector<Block*> whites;
            for(int i =0; i < R; i++)
            {
                for(int j =0; j <C ;j++)
                {
                    if(arr[i][j].z > Z)
                    {
                        if(arr[i][j].color == E_COLOR::black) blacks.push_back(&arr[i][j]);
                        else if(arr[i][j].color == E_COLOR::white) whites.push_back(&arr[i][j]);
                        else printf("ERROR data \n");
                        //printf("%d ",arr[i][j].z);
                    }else{
                        //printf(". ");
                    }
                }
                //printf("\n");
            }
            printf("nblacks = %d nwhites = %d\n",blacks.size(),whites.size());
            int max_flow = 0;
            for(int i =0; i < blacks.size();i++)
            {
                 //reset visited về giá trị mặc định
                for(int i =0; i < R; i++)
                {
                    for(int j =0; j < C; j++)
                    {
                        arr[i][j].visisted = false;
                    }
                }

                if(bmp(blacks[i],whites) == false)
                {
                    res = false;
                    break;
                }else
                {
                    //printf("max_flow = %d\n",i);
                }
            }

            //for(int i =0; i < whites.size();i++)
            //{
            //    if(whites[i]->parent)
            //        printf("%d-%d --> %d-%d \n",whites[i]->i,whites[i]->j,whites[i]->parent->i,whites[i]->parent->j);
            //}



            return res;
        }



    	void Run_Problem2_4(const char* inputPath)
    	{

            Block** arr ;
			int R, C, D, W;
			if(!ReadDataFile(inputPath,arr,R,C,D,W))
            {
                printf("Can not read file %s\n",inputPath);
                return;
            }

            //map.first là độ cao, map.second là số block có cùng độ cao
            std::map<int, int, std::less<int> >  p_map;
            p_map[0] = 0; //bổ sung thêm trường hợp toàn bộ block là parks, tương đương trường hợp Z =0
            for (int i = 0; i < R; i++)
            {
                for (int j = 0; j < C; j++)
                {
                    int z = arr[i][j].z;
                    if (p_map.find(z) == p_map.end())
                    {
                        p_map[z] = 1;
                    }
                    else
                    {
                        p_map[z]++;
                    }
                }
            }
            //loại bỏ các Z không thỏa mãn matching-parks
            int num_skyscraper = 0;
            int total_blocks = R * C;
            std::vector<CAS> cases;
            std::map<int, int>::iterator it;
            printf("checking ...\n");
            for (it = p_map.begin(); it != p_map.end(); it++)
            {
                //printf("%d %d \n",it->first,it->second);
                //kiểm tra số block là chẵn
                num_skyscraper += it->second;
                int num_block_parks = total_blocks - num_skyscraper;
                if (num_block_parks % 2 == 0)//check xem có khả năng matching ko
                {
                    //check xem số lượng block back và white có băng nhau không
                   if(CheckEqualBlackWhile(arr,R,C,it->first))
                   {
                        //printf("Pass %d %d \n",it->first,it->second);
                        //tính cost nếu xây dựng thành công
                        int Z = it->first;
                        int num_parks = num_block_parks / 2;
                        int sum = Z * W + num_parks * D;
                        cases.push_back(CAS(Z, sum));
                   }

                }
            }

            //xắp xếp lại danh sách theo chi phí tăng dần
            std::sort(cases.begin(), cases.end(), [](const CAS& t1, const CAS& t2) -> bool
            {
                return t1.sum < t2.sum;
            }
            );

            int cost = -1;
            //duyệt danh sách xem có xây dựng đc matching-parks không
            for (int k = 0; k< cases.size(); k++)
            {
                for(int i =0; i < R; i++)
                {
                    for(int j =0; j < C; j++)
                    {
                        arr[i][j].parent = nullptr;
                        arr[i][j].visisted = false;
                    }
                }

                printf("Z = %d sum = %d \n",cases[k].Z,cases[k].sum);
                if(CheckMatchingBiprate(arr,R,C,cases[k].Z))
                {
                    cost = cases[k].sum;
                    break;
                }

            }

            printf("cost = %d",cost);
    	}
    }

    void Problem2_4()
    {
        auto begin = chrono::high_resolution_clock::now();

        //Run_Problem2_4(DATA_PROBLEM_2018_2_401);
        //Run_Problem2_4(DATA_PROBLEM_2018_2_410);
        //Run_Problem2_4(DATA_PROBLEM_2018_2_411);
        //BruteForce::Run_Problem2_4("D:\\Training\\github\\data\\2018_round2\\D\\sample-2.in");
        //BruteForce::Run_Problem2_4("D:\\Training\\github\\data\\2018_round2\\D\\subtask2\\D-data-new-040.in");
    	MaximumBipartiteMatching::Run_Problem2_4("D:\\Training\\github\\data\\2018_round2\\D\\subtask2\\D-data-new-040.in");

        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout <<"\n\n"<< ms << " ms" << endl;//2 ms

    }
}
