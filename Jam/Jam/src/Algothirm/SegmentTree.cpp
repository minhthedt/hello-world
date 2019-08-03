#include<iostream> 
#include <list> 
#include <vector>
using namespace std;
//https://www.hackerearth.com/fr/practice/data-structures/advanced-data-structures/segment-trees/tutorial/
//Segment Trees giống như binary tree, mỗi node chứa 1 tập hợp phần tử, các phần tử của các node ko bị trùng lặp
//Node gốc là 1 mảng A[0 -> N]
//Node1,2 là 2 mảng A[0->i] và A[i+1 > N]
namespace Algothirm
{
    namespace SegmentTree
    {
#define A_SIZE 10
        std::vector<int> A(A_SIZE, 0);//cho dãy A có 100 phần tử
        std::vector<int> tree(32, -1); //là dãy chứa các  Node của SegmentTrees
        //Thực tế chiều cao của tree là log2(N) có N nút lá tương ứng N element của array
        //còn lại N -1 nút => tổng số nút của cây là 2N -1 
        //cần xây dựng tree có độ dài 2* 2^k sao cho 2^k >= N và 2^(k-1) < N
        

        //cho trước một mảng A
        //xây dựng một segment tree = binary tree cân bằng từ mảng A
        //Mỗi Node có giá trị = tổng 2 node lá
        //Phải set node >= 1, nếu node = 0 sẽ sai tính toán, node =2 thì cần mảng dài hơn node = 1
        void build(int node, int start, int end)
        {
            if (start == end)
            {
                // Leaf node will have a single element
                tree[node] = A[start];
            }
            else
            {
                int mid = (start + end) / 2;
                // Recurse on the left child
                build(2 * node , start, mid);
                // Recurse on the right child
                build(2 * node + 1, mid + 1, end);
                // Internal node will have the sum of both of its children
                tree[node] = tree[2 * node] + tree[2 * node + 1];
            }
        }

       
        //Khi update một phần tử A[idx], ta tiến hành update lại giá trị của các node liên quan đên A[idx]
        void update(int node, int start, int end, int idx, int val)
        {
            if (start == end)
            {
                // Leaf node
                A[idx] += val;
                tree[node] += val;//update nút lá rồi backtrack lại các nút cha
            }
            else
            {
                int mid = (start + end) / 2;
                if (start <= idx and idx <= mid)
                {
                    // If idx is in the left child, recurse on the left child
                    update(2 * node, start, mid, idx, val);
                }
                else
                {
                    // if idx is in the right child, recurse on the right child
                    update(2 * node + 1, mid + 1, end, idx, val);
                }
                // Internal node will have the sum of both of its children
                tree[node] = tree[2 * node] + tree[2 * node + 1];
            }
        }

        //dựa vào segment tree để tính tổng cá phần tử từ l -> r
        int query(int node, int start, int end, int l, int r)
        {
            if (r < start or end < l)
            {
                // range represented by a node is completely outside the given range
                return 0;
            }
            if (l <= start and end <= r)
            {
                // range represented by a node is completely inside the given range
                return tree[node];
            }
            // range represented by a node is partially inside and partially outside the given range
            int mid = (start + end) / 2;
            int p1 = query(2 * node, start, mid, l, r);
            int p2 = query(2 * node + 1, mid + 1, end, l, r);
            return (p1 + p2);
        }

        int main()
        {
            int start = 0;
            int end = A.size() - 1;
            int ROOT = 1;
            int idx = 0;
            int val = 15;
            for (int i = 0; i < A.size(); i++) A[i] = i;
            printf("A[10] =");
            for (int i = 0; i < A.size(); i++) printf("%d ", A[i]);
            printf("\n");
            //xây dựng segmentree từ mảng A
            auto& debug = tree;
            build(ROOT, start, end);
            printf("tree[32] =");
            for (int i = 0; i < tree.size(); i++) printf("%d ", tree[i]);
            printf("\n");
            printf("the number of nodes = %d",2 * A.size() -1);
            //update phần tử idx của A => update lại giá trị các node của segmentree
            update(1, start, end, idx, val);
            //tính tổng các phần tử
            int sum = query(ROOT, start, end, 0, 2);

            return 0;
        }

    }

    void Test_SegmentTrees()
    {
        (void)SegmentTree::main();
    }
}