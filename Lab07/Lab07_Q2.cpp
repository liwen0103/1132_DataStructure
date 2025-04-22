#include <iostream>
#include <queue>
#include <vector>
#include <climits> // 為了使用 INT_MIN
using namespace std;

// 樹的節點
class TreeNode {
public:
    int value;             // 節點的值
    TreeNode* left;        // 左子節點
    TreeNode* right;       // 右子節點

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {} // 初始化節點
};

// 樹結構
class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {} // 初始化樹

    // 用陣列構建二元樹
    TreeNode* buildTree(vector<int>& arr) {
        if (arr.empty()) return nullptr;

        queue<TreeNode*> q;// 建立queue儲存待處理的節點
        root = new TreeNode(arr[0]);// 建立根節點 (陣列第一個元素)
        q.push(root);// 將根節點加入queue

        size_t i = 1;// 陣列索引
        while (!q.empty()) {//&& i < arr.size()
            TreeNode* current = q.front();// 取出queue中的節點
            q.pop();
            
            // 添加左子節點
            if (i < arr.size()) {
                current->left = new TreeNode(arr[i]);
                q.push(current->left);// 將左子節點加入queue
                i++;
            }
            // 添加右子節點
            if (i < arr.size()) {
                current->right = new TreeNode(arr[i]);
                q.push(current->right);// 將右子節點加入queue
                i++;
            }
        }

        return root;
    }

    // 中序遍歷
    void inorderTraversal(TreeNode* node) {
        if (node == nullptr) return;// 如果節點為空，忽略

        inorderTraversal(node->left);// 遍歷左子樹
        cout << node->value << " ";// 訪問當前節點
        inorderTraversal(node->right);// 遍歷右子樹
    }

    // 找出以某節點為根的子樹中最大值
    int findMax(TreeNode* node) {
         if (node == nullptr) return INT_MIN; // 如果節點是空的，回傳最小整數（表示沒有值）
        
        // 遞迴找出左右子樹的最大值
        int leftMax = findMax(node->left);
        int rightMax = findMax(node->right);
        
        // 回傳當前節點值、左子樹最大值、右子樹最大值三者中的最大值
        return max(node->value, max(leftMax, rightMax));
    }
};


int main() {
    BinaryTree tree;// 宣告二元樹
    // 輸入陣列用於構建樹，NULL 表示空子節點
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7 };
    tree.buildTree(arr);
    // 中序遍歷輸出
    cout << "Inorder Traversal: ";
    tree.inorderTraversal(tree.root);
    cout << endl;

    if (tree.root != nullptr) {
        
        // 找出左子樹中的最大值
        int leftMax = tree.findMax(tree.root->left);
        // 找出右子樹中的最大值
        int rightMax = tree.findMax(tree.root->right);
        
        // 輸出左右子樹的最大值
        cout << "Left Subtree Max: " << leftMax << endl;
        cout << "Right Subtree Max: " << rightMax << endl;
    }

    return 0;
}
