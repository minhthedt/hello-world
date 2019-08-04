#include "Common.h"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <array>
#include <chrono>
using namespace std;
//[2019.08.04] Chưa thực sự hiểu rõ lời giải bài toán
namespace Jam2019
{
#define UINT8 unsigned char
#define INT16 short int
#define UINT32 unsigned int
#define INT32  int
#define INT64 long long int
#define UINT64 unsigned long long 

#define MAX_M 10000
#define MAX_K 1000000

    std::string bitString;
    constexpr int MAX_NUM = 1'048'576;
    constexpr int ROOT = 1;
    constexpr int MAX_QUERIES = 10'000;
    int N, M, K;

    std::array<int, MAX_NUM> sources;
    std::array<int, MAX_NUM * 2> segmentTree;
    std::array<int, MAX_QUERIES> begins;
    std::array<int, MAX_QUERIES> ends;

    // build binary segment tree
    void buildTree(int node, int left, int right) {
        segmentTree[node] = right - left + 1;
        if (left == right) {
            return;
        }
        int mid = left + (right - left) / 2;
        buildTree(node * 2, left, mid); // left subtree
        buildTree(node * 2 + 1, mid + 1, right); // right subtree
    }
    int searchFromTree(int node, int left, int right, int key) {
        if (segmentTree[node] < key) {
            return right + 1;
        }
        if (left == right) {
            return right;
        }
        int mid = left + (right - left) / 2;
        if (segmentTree[node * 2] >= key) {
            return searchFromTree(node * 2, left, mid, key);
        }
        else {
            return searchFromTree(node * 2 + 1, mid + 1, right, key - segmentTree[node * 2]);
        }
    }
    int removeFromTree(int node, int left, int right, int key) {
        if (segmentTree[node] < key) {
            return right + 1;
        }
        segmentTree[node]--;
        if (left == right) {
            return right;
        }
        int mid = left + (right - left) / 2;
        if (segmentTree[node * 2] >= key) {
            return removeFromTree(node * 2, left, mid, key);
        }
        else {
            return removeFromTree(node * 2 + 1, mid + 1, right, key - segmentTree[node * 2]);
        }
    }
    void solve() {
        sources.fill(0);
        buildTree(ROOT, 1, K);
        for (int i = M - 1; i >= 0; i--) {
            int length = ends[i] - begins[i] + 1;
            for (int curr = begins[i], j = 1; j <= length && ends[i] < segmentTree[ROOT]; j++, curr++) {
                int source = removeFromTree(ROOT, 1, K, ends[i] + 1);
                if (source > K) {
                    break;
                }
                sources[source] = searchFromTree(ROOT, 1, K, curr);
            }
        }
        int idx = 0;
        std::string result;
        for (int i = 0; i < K; i++) {
            int source = sources[i + 1] - 1;
            if (source >= 0) {
                result += result[source] == '0' ? '1' : '0';
            }
            else {
                result += bitString[idx++];
            }
        }
        std::cout << result << '\n';
    }


    void Run_Problem2_6(const char* inputPath)
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);

        FILE* fi = freopen(inputPath, "r", stdin);

        UINT32 T;//number of testcase
        UINT32 n;//size of original string 1 ≤ n ≤ 10^6
        UINT32 m;//number of operation 1 ≤ m ≤ 10^4
        UINT32 k;//size of output 1 ≤ k ≤ 10^6
        UINT8* str = new UINT8[MAX_K + 1];//buffer contain string
        UINT32 x, y;

        if (fi)
        {
            std::ios_base::sync_with_stdio(false);
            cin.tie(nullptr);
            std::cout.tie(nullptr);
            int TC = 1;
            cin >> TC;
            for (int i = 0; i < TC; i++) {
                cin >> N >> M >> K;
                cin >> bitString;
                for (int j = 0; j < M; j++) {
                    cin >> begins[j] >> ends[j];
                }
                solve();
            }

            fclose(fi);
        }

       
    }

    void Problem2_6()
    {
        auto begin = chrono::high_resolution_clock::now();
        Run_Problem2_6("D:\\Training\\github\\hello-world\\reference\\Sample\\2019\\round2\\2nd_F\\subtask2\\P6-data-big-001.in");
        auto end = chrono::high_resolution_clock::now();
        auto dur = end - begin;
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        cout << "\n\n" << ms << " ms" << endl;//3249 ms
    }
}