#include<iostream> 
#include <list> 
#include <vector>
using namespace std;
//https://www.geeksforgeeks.org/convert-normal-bst-balanced-bst/
//BST (Binary Search Tree): cây tìm kiếm nhị phân
//Cây nhị phân mà mỗi gốc có tối đa 2 lá -> BST là cây nhị phân thỏa mãn lá trái < gôc và lá phải > gốc
//Cây nhị phân cân bằng là cây nhị phân mà tại mỗi nút chiều cao của 2 cây con sai khác nhau không quá 1
//Bài toán này hướng dẫn chuyển 1 BST-unbalanced  thành BTS-balanced
//Ý tưởng rất đơn giản: lấy toàn bộ các node của BST-unbalanced lưu vào 1 mảng theo thứ tự tăng dần
//Dùng Binary Search để tạo ra BTS-balanced
namespace BST
{
    struct Node
    {
        int data;
        Node* left, *right;
    };

    /* This function traverse the skewed binary tree and
    stores its nodes pointers in vector nodes[] */
    void storeBSTNodes(Node* root, vector<Node*> &nodes)
    {
        // Base case 
        if (root == NULL)
            return;

        // Store nodes in Inorder (which is sorted 
        // order for BST) 
        storeBSTNodes(root->left, nodes);
        nodes.push_back(root);
        storeBSTNodes(root->right, nodes);
    }

    /* Recursive function to construct binary tree */
    Node* buildTreeUtil(vector<Node*> &nodes, int start,
        int end)
    {
        // base case 
        if (start > end)
            return NULL;

        /* Get the middle element and make it root */
        int mid = (start + end) / 2;
        Node *root = nodes[mid];

        /* Using index in Inorder traversal, construct
        left and right subtress */
        root->left = buildTreeUtil(nodes, start, mid - 1);
        root->right = buildTreeUtil(nodes, mid + 1, end);

        return root;
    }

    // This functions converts an unbalanced BST to 
    // a balanced BST 
    Node* buildTree(Node* root)
    {
        // Store nodes of given BST in sorted order 
        vector<Node *> nodes;
        storeBSTNodes(root, nodes);

        // Constucts BST from nodes[] 
        int n = nodes.size();
        return buildTreeUtil(nodes, 0, n - 1);
    }

    // Utility function to create a new node 
    Node* newNode(int data)
    {
        Node* node = new Node;
        node->data = data;
        node->left = node->right = NULL;
        return (node);
    }

    /* Function to do preorder traversal of tree */
    void preOrder(Node* node)
    {
        if (node == NULL)
            return;
        printf("%d ", node->data);
        preOrder(node->left);
        preOrder(node->right);
    }

    // Driver program 
    int main()
    {
        /* Constructed skewed binary tree is
                10
               /
              8
             /
            7
           /
          6
         /
        5   */

        Node* root = newNode(10);
        root->left = newNode(8);
        root->left->left = newNode(7);
        root->left->left->left = newNode(6);
        root->left->left->left->left = newNode(5);

        root = buildTree(root);

        printf("Preorder traversal of balanced "
            "BST is : \n");
        preOrder(root);

        return 0;
    }
}