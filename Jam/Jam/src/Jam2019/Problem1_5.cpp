#include "Common.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <chrono>
#include<iostream>
#include <algorithm>
#include <stack>
using namespace std;

namespace Jam2019
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 long long int
#define UINT64 unsigned long long 

    std::vector<std::string> fake;
    struct Element
    {
        INT32 index;//0 -> R*C-1
        INT32 row;//0 -> R-1
        INT32 col;//0 -> C -1
        Element() :row(-1), col(-1), index(-1){};
        void RelateTo(const Element& other)
        {
            if (row == other.row)
            {
                if (col == other.col + 1)
                {
                    printf("L");
                    fake.push_back("L");
                }
                else if (col == other.col - 1)
                {
                    printf("R");
                    fake.push_back("R");
                }
                else
                {
                    printf("***1***");
                }
            }
            else  if (col == other.col)
            {
                if (row == other.row + 1)
                {
                    printf("U");
                    fake.push_back("U");
                }
                else if (row == other.row - 1)
                {
                    printf("D");
                    fake.push_back("D");
                }
                else
                {
                    printf("***2***");
                }
            }
            else
            {
                printf("***3***");
            }
            
        }
    };

    struct Rectangle
    {
        Element** arr;
        INT32 R;
        INT32 C;
        Rectangle(INT32 R, INT32 C):R(R),C(C)
        {
            arr = new Element*[R];
            for (int i = 0; i < R; i++)
            {
                arr[i] = new Element[C];
                for (int j = 0; j < C; j++)
                {
                    arr[i][j].row = i;
                    arr[i][j].col = j;
                    arr[i][j].index = C * i + j;
                    //printf(" %d [%d,%d]\n", arr[i][j].index, arr[i][j].row, arr[i][j].col);
                }
            }
        }

        ~Rectangle()
        {
            for (int i = 0; i < R; i++)
            {
                delete[] arr[i];
            }
        }
    };
    
    void printResult(const std::vector<Element*>& stack, INT32 r, INT32 c)
    {
        int find = -1;
        for (int k = 0; k < stack.size(); k++)
        {
            int rr = stack[k]->row;
            int cc = stack[k]->col;
            if (rr == r)
            {
                if (cc == c)
                {
                    find = k;
                    break;
                }

            }
        }

        Element* p = nullptr;
        for (int i = find; i <= stack.size(); i++)
        {
            if (!p) p = stack[i];
            if (i + 1 < stack.size())
            {
                p->RelateTo(*stack[i + 1]);
                p = stack[i + 1];
            }
        }

        for (int i = 0; i < find; i++)
        {
            if (!p) p = stack[i];
            p->RelateTo(*stack[i]);
            p = stack[i];
        }
    }

    //check if R%2 == 0
    void Check1(const Rectangle& rect, INT32 r, INT32 c)
    {
        Element** arr  = rect.arr;
        const INT32 R = rect.R;
        const INT32 C = rect.C;
        std::vector<Element*> stack;

        if (R == 1 )
        {
            if (c == C - 1)
            {
                for (int col = C - 1; col >= 0; col--)
                {
                    stack.push_back(&arr[0][col]);
                }
            }
            else if (c == 0)
            {
                for (int col = 0; col < C; col++)
                {
                    stack.push_back(&arr[0][col]);//row 0
                }
            }
            else
            {
                cout << "IMPOSSIBLE\n";
            }
            
        }
        else
        {
            for (int col = 0; col < C; col++)
            {
                stack.push_back(&arr[0][col]);//row 0
            }
            for (int col = C - 1; col >= 0; col--)
            {
                if (col % 2 == 1)
                {
                    for (int row = 1; row < R; row++)
                    {
                        stack.push_back(&arr[row][col]);
                    }
                }
                else
                {
                    for (int row = R - 1; row >= 1; row--)
                    {
                        stack.push_back(&arr[row][col]);
                    }
                }
            }
        }
        

        
        printResult(stack,r,c);
        

        printf("\n");
       
    };

    void Check2(const Rectangle& rect, INT32 r, INT32 c)
    {
        Element** arr = rect.arr;
        const INT32 R = rect.R;
        const INT32 C = rect.C;
        std::vector<Element*> stack;

        if (C == 1)
        {
            if (r == R - 1)
            {
                for (int row = R - 1; row >= 0; row--)
                {
                    stack.push_back(&arr[row][0]);
                }
            }
            else if (r == 0)
            {
                for (int row =0; row < R; row++)
                {
                    stack.push_back(&arr[row][0]);
                }
            }
            else
            {
                cout << "IMPOSSIBLE\n";
            }
        }
        else
        {
            for (int row = 0; row < R; row++)
            {
                stack.push_back(&arr[row][0]);//colum 0
            }
            for (int row = R - 1; row >= 0; row--)
            {
                if (row % 2 == 1)
                {
                    for (int col = 1; col < C; col++)
                    {
                        stack.push_back(&arr[row][col]);
                    }
                }
                else
                {
                    for (int col = C - 1; col >= 1; col--)
                    {
                        stack.push_back(&arr[row][col]);
                    }
                }
            }
        }

        

        printResult(stack, r, c);

        printf("\n");

    };

    enum COLOR
    {
        BLACK = 0,
        WHITE
    };
    COLOR getColor(int r,int c)
    {
        if (r % 2 == 0 && c % 2 == 0)
        {
            return BLACK;
        }
        else  if (r % 2 == 1 && c % 2 == 1)
        {
            return BLACK;
        }
        else
        {
            return WHITE;
        }
      
    }

    void ChanChan_TR_TL(int R,int C)
    {
        Rectangle rect(R, C);
        Element** arr = rect.arr;
        std::vector<Element*> stack;
        for (int col = C - 1; col >= 0; col --)
        {
            if (col % 2 == 1)
            {
                for (int row = 0; row < R ; row++)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
            else
            {
                for (int row = R - 1; row >= 0; row--)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
        }
        if (stack.size() != R * C)
        {
            printf("stack error\n");
        }
        printResult(stack, 0, C-1);
    }

    void ChanChan_BL_TL(int R, int C)
    {
        Rectangle rect(R, C);
        Element** arr = rect.arr;
        std::vector<Element*> stack;
        for (int row = R - 1; row >= 0; row--)
        {
            if (row % 2 == 1)
            {
                for (int col = 0; col < C; col++)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
            else
            {
                for (int col = C - 1; col >= 0; col--)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
        }
        if (stack.size() != R * C)
        {
            printf("stack error\n");
        }
        printResult(stack, R-1, 0);
    }

    void ChayDuongThang(INT32 C)
    {
        Rectangle rect(1, C);
        Element** arr = rect.arr;
        std::vector<Element*> stack;
        for (int col = 0; col < C; col++)
        {
            stack.push_back(&arr[0][col]);
        }
        if (stack.size() !=  C)
        {
            printf("stack error\n");
        }
        printResult(stack, 0, 0);
    }

    void LeLe_TL_BR(int R, int C)
    {
        Rectangle rect(R, C);
        Element** arr = rect.arr;
        std::vector<Element*> stack;
        for (int row = 0; row < R; row++)
        {
            if (row % 2 == 0)
            {
                for (int col = 0; col < C; col++)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
            else
            {
                for (int col = C - 1; col >= 0; col--)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
        }
        if (stack.size() != R * C)
        {
            printf("stack error\n");
        }
        printResult(stack, 0, 0);
    }

    void LeLe_TR_LR(int R, int C)
    {
        Rectangle rect(R, C);
        Element** arr = rect.arr;
        std::vector<Element*> stack;
        //printf("0x%x\n",stack.data());
        for (int row = 0; row < R; row++)
        {
            int col= C - 1;//final colum
            stack.push_back(&arr[row][ col]);
        }

        //bottom right -> top left (le,chan)
        for (int row = R - 1; row >= 0; row--)
        {
            if (row % 2 == 0)
            {
                for (int col = C - 2; col >= 0;col --)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
            else
            {
                if (C - 1 > 0)
                {
                    for (int col = 0; col <= C - 2; col++)
                    {
                        stack.push_back(&arr[row][col]);
                    }
                }

            }
        }
        
        if (stack.size() != R * C)
        {
            printf("stack error\n");
        }
        printResult(stack, 0, C-1);
    }

    void ChanLe_BL_TR(int R, int C)
    {
        Rectangle rect(R, C);
        Element** arr = rect.arr;
        std::vector<Element*> stack;
        for (int col = 0; col < C ; col++)
        {
            if (col % 2 == 0)
            {
                for (int row = R - 1; row >= 0; row--)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
            else
            {
                for (int row = 0; row < R; row++)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
        }
        if (stack.size() != R * C)
        {
            printf("stack error\n");
        }
        printResult(stack, R-1, 0);
    }

    void LeChan_TL_BL(int R, int C)
    {
        Rectangle rect(R, C);
        Element** arr = rect.arr;
        std::vector<Element*> stack;
        for (int row = 0; row < R; row++)
        {
            if (row % 2 == 0)
            {
                for (int col = 0; col < C; col++)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
            else
            {
                for (int col = C-1; col >= 0; col--)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
        }
        if (stack.size() != R * C)
        {
            printf("stack error\n");
        }
        printResult(stack, 0, 0);
    }
    void LeLe_TR_BR(int R, int C)
    {
        Rectangle rect(R, C);
        Element** arr = rect.arr;
        std::vector<Element*> stack;
        for (int col = C-1; col >= 0; col--)
        {
            int row = 0;//final row
            stack.push_back(&arr[row][col]);
        }

        //colum left->right
        for (int col = 0; col < C; col++)
        {
            if (col % 2 == 0)
            {
                for (int row = 1; row < R; row++)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
            else
            {
                if (R > 1)
                {
                    for (int row = R - 1; row > 0; row--)
                    {
                        stack.push_back(&arr[row][col]);
                    }
                }

            }
        }


        if (stack.size() != R * C)
        {
            printf("stack error\n");
        }
        printResult(stack, 0, C - 1);
    }

    void Lechan_BL_TR(int R, int C)
    {
        Rectangle rect(R, C);
        Element** arr = rect.arr;
        std::vector<Element*> stack;
        for (int row = R-1; row >= 0; row--)
        {
            if (row % 2 == 0)
            {
                for (int col = 0; col < C; col++)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
            else
            {
                for (int col = C -1; col >= 0; col--)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
        }
        if (stack.size() != R * C)
        {
            printf("stack error\n");
        }
        printResult(stack, R-1, 0);
    }

    void LeChan_TL_RL(int R, int C)
    {
        Rectangle rect(R, C);
        Element** arr = rect.arr;
        std::vector<Element*> stack;
        for (int col = 0; col < C; col++)
        {
            if (col % 2 == 0)
            {
                for (int row = 0; row < R; row++)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
            else
            {
                for (int row = R-1; row >=0; row--)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
        }

        if (stack.size() != R * C)
        {
            printf("stack error\n");
        }
        printResult(stack, 0, 0);
    }

    void ChanChan_BR_TR(int R, int C)
    {
        Rectangle rect(R, C);
        Element** arr = rect.arr;
        std::vector<Element*> stack;
        for (int row = R-1; row >= 0; row--)
        {
            if (row % 2 == 1)
            {
                for (int col = C -1; col >= 0; col--)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
            else
            {
                for (int col = 0; col < C; col++)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
        }

        if (stack.size() != R * C)
        {
            printf("stack error\n");
        }
        printResult(stack, R-1, C-1);
    }

    void LeChan_TL_TR(int R, int C)
    {
        Rectangle rect(R, C);
        Element** arr = rect.arr;
        std::vector<Element*> stack;
        for (int col = 0; col < C; col++)
        {
            if (col % 2 == 0)
            {
                for (int row = 0; row < R; row++)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
            else
            {
                for (int row = R - 1; row >= 0; row--)
                {
                    stack.push_back(&arr[row][col]);
                }
            }
        }

        if (stack.size() != R * C)
        {
            printf("stack error\n");
        }
        printResult(stack, 0, 0);
    }

    void Check3(const Rectangle& rect, INT32 r, INT32 c)
    {
        //ChanChan_TR_TL(4,4);
        //ChanChan_BL_TL(4,4);
        //ChanChan_BR_TR(4,2);
        //ChayDuongThang(4);
        //LeLe_TL_BR(5,3);
        //LeLe_TR_LR(5,5);
        //LeLe_TR_BR(5,3);
        //ChanLe_BL_TR(4,3);
        //LeChan_TL_BL(5,4);
        //Lechan_BL_TR(5,4);
        //LeChan_TL_RL(3,4);
        //LeChan_TL_TR(3,2);

        
        Element** arr = rect.arr;
        const INT32 R = rect.R;
        const INT32 C = rect.C;
        std::vector<Element*> stack;
        //kiem tra xem toa do (r,c) co trung voi mau cua (0,0) ?
        Element* org = &arr[r][c];
        COLOR color_0 = getColor(0,0);
        COLOR color_org = getColor(r,c);
        if (color_0 != color_org)
        {
            cout << "IMPOSSIBLE\n";
            return;
        }

        int pR = R - r;
        int pC = c+1;
       
        if (pC % 2 == 0 && pR % 2 == 0)
        {
            //chay tu goc topright -> left right (chan,chan)
            ChanChan_TR_TL(pR, pC);

            if (R - pR > 1)//R - pR = 2,4,6...
            {
                //Up
                cout << "U";
                fake.push_back("U");
                //chay tu bottomleft -> top left (chan chan)
                ChanChan_BL_TL(R - pR -1, pC);
                //Up
                cout << "U";
                fake.push_back("U");
                //chay duong thang
                ChayDuongThang(pC);

            }else if (R - pR == 1)
            {
                //Up
                cout << "U";
                fake.push_back("U");
                //chay duong thang
                ChayDuongThang(pC);
            }

            if (pC < C)
            {
                //Right
                cout << "R";
                fake.push_back("U");
                //chay tu topleft -> bottom right (le,le)
                LeLe_TL_BR(R,C - pC);
            }

        }
        else if (pC % 2 == 1 && pR % 2 == 1)
        {
           
            //xet bien
            if (pR == R)//5 5 1 3, nam tren row =0
            {
                if (R == 1 && c != C - 1& c != 0)
                {
                    cout << "IMPOSSIBLE\n";
                }
                else
                {
                    //LeLe_TL_BR(R, C);
                    LeLe_TR_BR(pR, pC);

                    if (pC < C)
                    {
                        //right
                        cout << "R";
                        fake.push_back("R");
                        //
                        Lechan_BL_TR(R, C - pC);
                    }
                }
                
            }
            else if (pC == 1)//xet bien, nam tren col =0
            {
                if (C > pC)
                {
                    //toplef->topright (le,chan)
                    LeChan_TL_TR(pR,pC+1);
                    if (pR < R)
                    {
                        //Up
                        cout << "U";
                        fake.push_back("U");
                        //bottomright ->topright(chan chan)
                        ChanChan_BR_TR(R-pR,pC+1);
                        if (pC < C)
                        {
                            //Right
                            cout << "R";
                            fake.push_back("R");
                            //topleft -> bottomright(le,le)
                            LeLe_TL_BR(R, C-pC-1);
                        }
                    }
                    
                    
                   
                }
                else
                {
                    if (pR == 1)//r=R,c=C=1
                    {
                        for (int i = 0; i < R-1; i++)
                        {
                            cout << "U";
                            fake.push_back("U");
                        }
                    }
                    else
                    {
                       
                        cout << "IMPOSSIBLE\n";
                    }
                   
                }
            }
            else
            {
                //chay tu topright -> leftright (Le,Le)
                LeLe_TR_LR(pR, pC);
                //up
                if (pR < R)
                {
                    cout << "U";
                    fake.push_back("U");
                    //chay tu bottomleft -> top right (chan,le)
                    ChanLe_BL_TR(R - pR, pC);

                    if (pC < C)
                    {
                        //Right
                        cout << "R";
                        fake.push_back("R");
                        //chay tu topleft -> bottomleft (le,chan)
                        LeChan_TL_BL(R, C - pC);
                    }

                }
            }
            
        }
        else
        {
            printf("Error\n");
        }

       
        printf("\n");

    };



    void Run_Problem1_5(const char* inputPath)
    {
        FILE* fi = freopen(inputPath, "r", stdin);
        if (fi)
        {
            UINT32 T;//1 <= T <= 100
            UINT32 R, C, r, c;//1 <= R, C <= 100
            cin >> T;
            //printf("%d\n",T);
            for (int i = 0; i < T; i++)
            {
                //fake.clear();
                cin >> R; cin >> C; cin >> r; cin >> c;
                //printf("%d %d %d %d\n", R,C,r,c);
                Rectangle rect(R,C);

                if (C % 2 == 0)
                {
                    Check1(rect, r - 1, c - 1);
                }
                else if (R % 2 == 0)
                {
                    Check2(rect, r - 1, c - 1);
                }
                else if (C % 2 == 1 && R % 2 == 1)
                {
                    Check3(rect, r - 1, c - 1);
                }
               

                //if (fake.size() == R * C - 1)
                //{


                //    //verify result
                //    std::vector<Element*> tmp;
                //    Element* org = &rect.arr[r-1][c-1];
                //    tmp.push_back(org);
                //    int t_r = r-1;
                //    int t_c = c-1;
                //    for (int i = 0; i < fake.size(); i++)
                //    {
                //        if (fake[i].compare("R") == 0)
                //        {
                //            t_c++;

                //        }
                //        else if (fake[i].compare("L") == 0)
                //        {
                //            t_c--;
                //        }
                //        else if (fake[i].compare("U") == 0)
                //        {
                //            t_r--;
                //        }
                //        else if (fake[i].compare("D") == 0)
                //        {
                //            t_r++;
                //        }
                //        else
                //        {
                //            printf("Error fake 111\n");
                //        }
                //        tmp.push_back(&rect.arr[t_r][t_c]);
                //    }

                //    bool OK = true;
                //    for (int i = 0; i < R*C; i++)
                //    {
                //        bool existed = false;
                //        for (int j = 0; j < tmp.size(); j++)
                //        {
                //            if (i == tmp[j]->index)
                //            {
                //                existed = true;
                //                break;
                //            }
                //        }

                //        if (!existed)
                //        {
                //            OK = false;
                //            break;
                //        }
                //    }

                //    printf("\nOK = %s\n", OK ? "true" : "flase");
                //}
                //else
                //{
                //    printf("Error fake\n");
                //}
                
            }
            fclose(fi);
        }
        
    };

    void Problem1_5()
    {
        Run_Problem1_5("D:\\Training\\github\\hello-world\\reference\\Exam\\2019\\round1\\problem5\\input001.txt");
    }
}