#include "Common.h"
#include <sstream> //string stream
#include <fstream> //file stream
#include <vector>
#include <chrono>
#include<iostream>
#include <stack>
using namespace std;
/*
[2018.08.25] created
http://simplecodecjava.blogspot.com/2015/09/thuat-toan-tim-uong-i-va-chu-trinh-euler.html
*/

namespace Algothirm
{
    class Euler
    {
        int vertices; // Số đỉnh trong đồ thị
        int** graph; // Đồ thị
        vector<int> list_vertices; // Danh sách các đỉnh tạo thành chu trình Euler
        int count_even_degree_vertex();
        int count_odd_degree_vertex();
        bool find_path();
    public:
        Euler() {};
        // Việc đọc file với các bạn có lẽ đã quá quen thuộc, cho nên mình xin phép không đề cập ở đây.
        Euler(string file_path);
        ~Euler() {};
        void get_path(string file_path);
    };
    // Có lẽ sẽ có bạn thắc mắc tại sao mình lại tạo 2 methods đếm đỉnh bậc chẵn và lẻ làm gì
    // Trong khi nếu ta lấy tổng số đỉnh trừ cho đỉnh bậc chẵn thì sẽ ra đỉnh bậc lẻ
    //
    // Mình muốn xét luôn cả trường hợp đỉnh cô lập nên sẽ tạo 2 methods để đảm bảo 😀
    Euler::Euler(string file_path)
    {
        int n;
        freopen(file_path.c_str(), "r", stdin);
        cin >> n;
        vertices = n;
        graph = new int*[n];
        for (int i = 0; i < n; i++)
        {
            graph[i] = new int[n];
        }

        cout << "So dinh do thi:" << n << endl;
        //nhập ma trận kề.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> graph[i][j];
            }
        }
    }
    int Euler::count_even_degree_vertex()
    {
        int total = 0;
        for (int i = 0; i < vertices; i++)
        {
            int count_neighbour = 0;
            for (int j = 0; j < vertices; j++)
            {
                if (graph[i][j] == 1) ++count_neighbour;
            }
            // Nếu có đỉnh lân cận
            // Thêm trường hợp count_neighbour > 0 để loại trừ đỉnh cô lập
            if (count_neighbour % 2 == 0 && count_neighbour > 0) ++total;
        }
        return total;
    }
    int Euler::count_odd_degree_vertex()
    {
        int total = 0;
        for (int i = 0; i < vertices; i++)
        {
            int count_neighbour = 0;
            for (int j = i + 1; j < vertices; j++)
            {
                if (graph[i][j] == 1) ++count_neighbour;
            }
            if (count_neighbour % 2 == 1) ++total;
        }
        return total;
    }

    bool Euler::find_path()
    {
        int even = count_even_degree_vertex();
        int odd = count_odd_degree_vertex();
        // Đỉnh bậc chẵn + bậc lẻ = tổng số đỉnh => Không có đỉnh cô lập
        if (even + odd == vertices && (even == vertices || odd == 2))
        {
            // Tìm đỉnh bắt đầu
            int start_vertex = -1;
            for (int i = 0; i < vertices; i++)
            {
                int count_degree = 0;
                for (int j = 0; j < vertices; j++)
                {
                    if (graph[i][j] == 1) count_degree++;
                }
                if (count_degree % 2 == 1)
                {
                    start_vertex = i;
                    break;
                }
            }
            // Nếu không tìm được đỉnh bậc lẻ nào => Toàn bộ đỉnh là bậc chẵn
            // Lấy đỉnh đầu tiên làm default
            if (start_vertex == -1) start_vertex = 0;
            stack<int> stack;
            stack.push(start_vertex);
            while (!stack.empty())
            {
                int current_vertex = stack.top();
                // Biến để kiểm tra xem đỉnh đang xét có đỉnh lân cận hay không
                bool has_neighbour = false;
                for (int i = 0; i < vertices; i++)
                {
                    if (graph[current_vertex][i] == 1)
                    {
                        has_neighbour = true;
                        graph[current_vertex][i] = graph[i][current_vertex] = 0;
                        stack.push(i);
                        break;
                    }
                }
                if (!has_neighbour)
                {
                    int vertex = stack.top();
                    stack.pop();
                    list_vertices.push_back(vertex);
                }
            }
            return true;
        }
        else return false;
    }

    void Euler::get_path(string file_path)
    {
        //bool is_found_path = this->find_path();
        //ofstream file_out(file_path);
        //if (is_found_path)
        //{
        //    for (int i = list_vertices.size() - 1; i > 0; i--)
        //    {
        //        file_out << list_vertices[i] << "->";
        //    }
        //    file_out << list_vertices[0];
        //}
        //else
        //{
        //    file_out << "Khong tim thay duong di!";
        //}
        //file_out.close();
        bool is_found_path = this->find_path();
        if (is_found_path)
        {
            for (int i = list_vertices.size() - 1; i > 0; i--)
            {
                cout << list_vertices[i] << "->";
            }
            cout << list_vertices[0];
        }
        else
        {
            cout << "Khong tim thay duong di!";
        }
      
    }

    void Run_Euler(const char* inputPath)
    {
        Euler a(inputPath);
        a.get_path("");
    };

    void Test_Euler()
    {
        Run_Euler(DATA_ALGOTHIRM_EULER);
    };
}