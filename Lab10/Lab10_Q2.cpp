#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int EMPTY = NULL; // 用 NULL 代表沒有節點

class TreeNode {
public:
    int value;            // 節點值
    TreeNode* left;       // 左子節點
    TreeNode* right;      // 右子節點

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {} // 初始化節點
};

class BinaryTree {
public:
    TreeNode* root;       // 樹根節點

    BinaryTree() : root(nullptr) {}

    TreeNode* buildTree(const vector<int>& arr) { // 建立樹
        if (arr.empty() || arr[0] == EMPTY) return nullptr;

        queue<TreeNode**> q;                 // 建立 queue 儲存待處理的節點指標
        root = new TreeNode(arr[0]);         // 建立根節點 (陣列第一個元素)
        q.push(&root);                       // 將根節點的指標加入 queue

        size_t i = 1;                        // 陣列索引
        while (!q.empty() && i < arr.size()) {
            TreeNode** nodePtr = q.front();  // 取出 queue 的第一個節點指標
            q.pop();                         // 將該節點從 queue 中刪除

            // 左子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->left = new TreeNode(arr[i]); // 添加左子節點
                    q.push(&((*nodePtr)->left));             // 將左子節點的指標加入 queue
                }
                i++;
            }

            // 右子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->right = new TreeNode(arr[i]); // 添加右子節點
                    q.push(&((*nodePtr)->right));             // 將右子節點的指標加入 queue
                }
                i++;
            }
        }
        return root;
    }

    void Depth_first_search(TreeNode* node) { // 深度優先搜尋
        if (node == nullptr) return;
        cout << node->value << " ";            // 訪問當前節點的值
        Depth_first_search(node->left);        // 遞迴遍歷左子樹
        Depth_first_search(node->right);       // 遞迴遍歷右子樹
    }

    void Breadth_first_search(TreeNode* root) { // 廣度優先搜尋
        if (root == nullptr) return;
        queue<TreeNode*> q;                    // 建立 queue 儲存待處理的節點指標
        q.push(root);                          // 將根節點的指標加入 queue

        while (!q.empty()) {
            TreeNode* current = q.front();     // 取出 queue 的第一個節點指標
            q.pop();                           // 將該節點從 queue 中刪除
            cout << current->value << " ";
            if (current->left) q.push(current->left);   // 加入左子節點
            if (current->right) q.push(current->right); // 加入右子節點
        }
    }

    // 用 DFS 尋找節點
    TreeNode* findNode(TreeNode* node, int target) {
        if (node == nullptr) return nullptr;              // 若節點為空，返回 nullptr
        if (node->value == target) return node;           // 若節點值符合，回傳節點
        TreeNode* leftResult = findNode(node->left, target); // 往左找
        if (leftResult) return leftResult;
        return findNode(node->right, target);             // 否則往右找
    }

    // 用 DFS 計算子樹的總和
    int calculateSubtreeSum(TreeNode* node) {
        if (node == nullptr) return 0;                    // 空節點總和為 0
        return node->value + calculateSubtreeSum(node->left) + calculateSubtreeSum(node->right);
    }

    // 比較目標節點的左/右子樹總和
    void compareLeftRight(TreeNode* root, int target) {
        TreeNode* node = findNode(root, target);          // 找到指定節點
        if (node == nullptr) {
            cout << "節點不存在於樹中" << endl;
            return;
        }

        if (node->left == nullptr && node->right == nullptr) {
            cout << "該節點為葉節點，沒有子樹" << endl;
            return;
        }

        int leftSum = calculateSubtreeSum(node->left);    // 左子樹總和
        int rightSum = calculateSubtreeSum(node->right);  // 右子樹總和

        cout << "左子樹總和：" << leftSum << endl;
        cout << "右子樹總和：" << rightSum << endl;

        if (leftSum > rightSum) {
            cout << "左子樹總和較大" << endl;
        } else if (rightSum > leftSum) {
            cout << "右子樹總和較大" << endl;
        } else {
            cout << "左右子樹總和相等" << endl;
        }
    }
};

int main() {
    BinaryTree tree;
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, NULL, NULL, 10, 11, NULL, NULL };
    tree.buildTree(arr);

    cout << "BFS Result: ";
    tree.Breadth_first_search(tree.root);
    cout << endl;

    // 輸入一個節點值，查詢其左右子樹總和
    int target;
    cout << "輸入欲檢查的節點值：";
    cin >> target;
    tree.compareLeftRight(tree.root, target);

    system("pause");
    return 0;
}
