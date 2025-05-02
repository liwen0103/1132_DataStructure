#include <iostream>     
#include <stack>        
#include <string>       
#include <sstream>      // 分割字串
#include <cctype>       // 字元判斷
#include <cmath>        // 數學運算
using namespace std;

// link list做stack
struct Node {
    string data;       // 存放資料
    Node* next;        // 指向下一個節點
    Node(string val) : data(val), next(nullptr) {} // 初始化
};

class Stack {
private:
    Node* top;         // 指向stack最上層
public:
    Stack() : top(nullptr) {} // 初始化 top 為空

    void push(string val) {    // 堆入一個新元素
        Node* newNode = new Node(val); // 新節點
        newNode->next = top;           // 新節點指向原本的 top
        top = newNode;                 // top 更新成新節點
    }
    
    string pop() {            // 移除最上層元素並回傳
        if (!top) return "";   // 如果堆疊是空的
        Node* temp = top;      
        string val = temp->data; // 取出資料
        top = top->next;         // top 往下一個
        delete temp;             // 釋放記憶體
        return val;              // 回傳取出的資料
    }
    
    string peek() {            // 查看最上層元素但不移除
        return top ? top->data : "";
        //如果 Stack內有東西，就回傳最上層的值，否則回傳空字串
    }
    
    bool isEmpty() {           // 判斷堆疊是否為空
        return top == nullptr;
    }
};

// 判斷運算子優先順序
int precedence(string op) {
    if (op == "^") return 3;                  // 次方最優先
    if (op == "*" || op == "/" || op == "%") return 2;  // 乘除取餘次優先
    if (op == "+" || op == "-") return 1;      // 加減優先度最低
    return 0;                                  // 其他不重要
}

// 判斷是否為運算子
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%';
}

// 中序轉後序 
string infixToPostfix(string infix) {
    Stack s;                // 使用link list做的stack
    string postfix;         // 存放轉換結果
    string number;          // 暫存數字（可能是多位數或小數）

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];//每次處理一個字元
        
        //判斷是不是數字或小數點
        if (isdigit(c) || c == '.') {  
            number += c;               // 加到 number 裡
        } else {
            if (!number.empty()) {     // 如果 number 裡有東西
                postfix += number + " "; // 加到後序表示式
                number = "";             // 清空 number
            }

            if (c == '(') {              // 左括號
                s.push("(");
            } else if (c == ')') {        // 右括號
                while (!s.isEmpty() && s.peek() != "(") {//配對到右括號
                    postfix += s.pop() + " ";  // 把括號內的運算子都加到後序
                }
                s.pop(); // 拿掉左括號
            } else if (isOperator(c)) {   // 是運算子
                string op(1, c);          // 把 char 轉成 string
                
                // 當堆疊不為空，且stack頂端的運算子優先順序 >= 當前運算子
                while (!s.isEmpty() && precedence(s.peek()) >= precedence(op)) {
                    postfix += s.pop() + " "; 
                    // 就把stack頂端的運算子取出，加到後序表示式
                }
                s.push(op);// 把新的運算子放進stack
            }
        }
    }

    if (!number.empty()) {  // 如果迴圈還有數字
        postfix += number + " ";//加到後序表示式
    }

    while (!s.isEmpty()) {  // 把stack剩下的運算子都拿出來
        postfix += s.pop() + " ";//加到後序表示式
    }

    return postfix;// 回傳完整的後序表示式
}

// 計算後序表示式
double evaluatePostfix(string postfix) {
    stack<double> s;           
    istringstream iss(postfix); // 把後序字串用空白分割為一個一個的 token
    string token;

    while (iss >> token) {     // 逐個取出字串
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            // 如果是數字或負數
            s.push(stod(token));  // 轉成 double 並推進 stack
        } else {
            // 是運算子，從 stack 拿出兩個數字(n1 n2 op)
            double b = s.top(); s.pop();// 第二個數字（右邊）
            double a = s.top(); s.pop();// 第一個數字（左邊）
            
            //根據運算子執行對應的運算，結果再堆入stack
            if (token == "+") s.push(a + b);
            else if (token == "-") s.push(a - b);
            else if (token == "*") s.push(a * b);
            else if (token == "/") s.push(a / b);
            else if (token == "%") s.push(fmod(a, b)); 
            else if (token == "^") s.push(pow(a, b));  
        }
    }

    return s.top();// 最後 stack 只剩答案
}

// 主程式
int main() {
    string input;
    cout << "請輸入一個算式: ";
    getline(cin, input);       // 讀取整行輸入（支援空白）

    string postfix = infixToPostfix(input);   // 轉成後序表示式
    double result = evaluatePostfix(postfix); // 計算後序表示式

    cout << "後序表示式: " << postfix << endl;
    cout << "結果: " << result << endl;
    
    return 0;
}
