#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int EMPTY = NULL; // 用 NULL 代表沒有節點

class TreeNode {
public:
    int value; // 節點值
    TreeNode* left; // 左子節點
    TreeNode* right; // 右子節點

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {} // 初始化節點
};

class BinaryTree {
public:
    TreeNode* root; // 樹根節點

    BinaryTree() : root(nullptr) {}

    TreeNode* buildTree(const vector<int>& arr) { // 建立樹
        if (arr.empty() || arr[0] == EMPTY) return nullptr;

        queue<TreeNode**> q; // 建立queue儲存待處理的節點指標
        root = new TreeNode(arr[0]); // 建立根節點 (陣列第一個元素)
        q.push(&root); // 將根節點的指標加入queue

        size_t i = 1; // 陣列索引
        while (!q.empty() && i < arr.size()) {
            TreeNode** nodePtr = q.front(); // 取出queue的第一個節點指標
            q.pop(); // 將該節點從queue中刪除

            // 左子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->left = new TreeNode(arr[i]); // 添加左子節點
                    q.push(&((*nodePtr)->left)); // 將左子節點的指標加入queue
                }
                i++;
            }
            // 右子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->right = new TreeNode(arr[i]); // 添加右子節點
                    q.push(&((*nodePtr)->right)); // 將右子節點的指標加入queue
                }
                i++;
            }
        }
        return root;
    }

    void Breadth_first_search(TreeNode* root) {
        if (root == nullptr) return;
        queue<TreeNode*> q; // 建立queue儲存待處理的節點指標
        q.push(root); // 將根節點的指標加入queue

        while (!q.empty()) {
            TreeNode* current = q.front(); // 取出queue的第一個節點指標
            q.pop(); // 將該節點從queue中刪除
            cout << current->value << " ";
            if (current->left) q.push(current->left);  // 將左子節點的指標加入queue
            if (current->right) q.push(current->right); // 將右子節點的指標加入queue
        }
    }

    // 輸入層級（從第 0 層開始），回傳該層所有節點值的總和
    // 如果輸入的層數超出實際樹高，則顯示「層數過高」的警告訊息
    int sumAtLevel(int level) {
        if (root == nullptr) return 0;

        queue<TreeNode*> q; // 建立 queue 進行層級遍歷
        q.push(root);
        int currentLevel = 0; // 當前層級

        while (!q.empty()) {
            int levelSize = q.size(); // 當前層的節點數

            // 當前層等於要查的層，開始加總
            if (currentLevel == level) {
                int levelSum = 0;
                for (int i = 0; i < levelSize; ++i) {
                    TreeNode* node = q.front();
                    q.pop();
                    levelSum += node->value; // 加總該層節點值
                }
                return levelSum; // 回傳總和
            }

            // 還沒到指定層就繼續往下層擴展
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = q.front();
                q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }

            currentLevel++; // 前進到下一層
        }

        // 若迴圈結束還沒到指定層，表示層級超出
        cout << "層數過高" << endl;
        return -1; // 警告回傳值
    }
};

int main() {
    BinaryTree tree;
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, NULL, NULL, 10, 11, NULL, NULL };
    tree.buildTree(arr);

    cout << "BFS Result: ";
    tree.Breadth_first_search(tree.root);
    cout << endl;

    int level;
    cout << "請輸入要查詢的層數：";
    cin >> level;

    int result = tree.sumAtLevel(level); // 執行層級查詢

    if (result != -1) {
        cout << "第 " << level << " 層的節點總和為：" << result << endl;
    }

    system("pause");
    return 0;
}

