#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

// 定義 Stack 的節點結構
struct Node {
    char data;  // 存儲字符 (運算子或括號)
    Node* next; // 指向下一個節點
};

// 使用 linked list 實作 Stack
class Stack {
private:
    Node* top; // 指向堆疊頂端
public:
    Stack() { top = nullptr; } // 初始化堆疊

    // Push 操作：將元素放入堆疊
    void push(char ch) {
        Node* newNode = new Node(); // 創建新節點
        newNode->data = ch;         // 設置節點數據
        newNode->next = top;        // 新節點指向當前堆疊頂端
        top = newNode;              // 更新堆疊頂端為新節點
    }

    // Pop 操作：移除並回傳頂端元素
    char pop() {
        if (top == nullptr) {
            return '\0'; // 如果堆疊是空的，回傳空字符
        }
        Node* temp = top;// 暫存目前堆疊的的頂端節點指標
        char poppedValue = top->data;// 儲存頂端節點的資料
        top = top->next;  // 更新堆疊頂端為下一個節點
        delete temp;      // 釋放原來頂端節點的記憶體
        return poppedValue;// 回傳原頂端節點的資料
    }

    // Peek 操作：取得頂端元素但不移除
    char peek() {
        if (top != nullptr) {
            return top->data;  //回傳頂端元素
        }
        return '\0';  // 堆疊空時回傳空字符
    }

    // 判斷堆疊是否為空
    bool isEmpty() {
        return top == nullptr;  // 若堆疊頂端為空，則堆疊為空
    }
};

// 判斷運算子(加減乘除) 的優先順序
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;  // 加減運算子的優先順序為 1
    }
    if (op == '*' || op == '/') {
        return 2;  // 乘除運算子的優先順序為 2(最優先)
    }
    return 0;  // 其他情況，默認優先順序為 0(最不優先)
}

// 將中序表達式 (infix) 轉換為後序表達式 (postfix)
void InfixToPostfix(const char* infix, char* postfix) {
    Stack s;
    int k = 0;  // 後序表達式的索引

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];// 逐字元讀取中序表達式的每一個符號

        // 如果是操作數，直接放入後序表達式
        if (isalnum(ch)) {
            postfix[k++] = ch;
        }
        // 如果是左括號，推入堆疊
        else if (ch == '(') {
            s.push(ch);
        }
        // 如果是右括號，彈出堆疊直到遇到左括號
        else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix[k++] = s.pop();// 將堆疊中的運算子加入後序表達式
            }
            s.pop();  // 彈出 '('
        }
        // 如果是運算子
        else {
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(ch)) {
                postfix[k++] = s.pop();// 將優先順序較高或相同的運算子彈出加入後序表達式
            }
            s.push(ch);// 將目前的運算子推入堆疊
        }
    }

    // 彈出堆疊中剩餘的運算子
    while (!s.isEmpty()) {
        postfix[k++] = s.pop();// 加入到後序表達式
    }
    postfix[k] = '\0';  // 添加字符串結束符
}

int main() {
    char infix[100], postfix[100];
    cout << "Enter an Infix expression: ";
    cin >> infix; // 輸入中序表達式

    InfixToPostfix(infix, postfix); // 轉換為後序表達式
    cout << "Postfix expression: " << postfix << endl; // 輸出後序表達式

    return 0;
}

