#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// 從文件中讀取數據並存入向量
vector<int> readFromFile(const string& filename) {
    vector<int> arr;
    ifstream file(filename);

    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return arr;
    }

    string line;
    while (getline(file, line)) { // 持續讀取整行內容
        stringstream ss(line);    // 創建字符串流
        string value;
        while (getline(ss, value, ',')) { // 用逗號分隔值
            try {
                arr.push_back(stoi(value)); // 將字符串轉換為整數並存入向量
            }
            catch (exception& e) {
                cerr << "Invalid number format in file: " << value << endl;
            }
        }
    }

    file.close();
    return arr;
}

class MinHeap {
public:
    vector<int> heap; // 儲存Min Heap的元素

    // 建立Min Heap
    void buildMinHeap(vector<int>& arr) {  //建立Min Heap
        heap = arr;

        for (int i = (heap.size() / 2) - 1; i >= 0; i--) { // 從最後一個非葉子節點開始向上執行Min Heap
            heapify(i);
        }
    }

    void heapify(int i) { // 堆化函式（確保以 i 為根的子樹符合Min Heap性質）
        int smallest = i;          // 假設當前節點是最小的
        int left = 2 * i + 1;     // 左子節點索引
        int right = 2 * i + 2;    // 右子節點索引

        // 檢查左子節點是否比當前節點小
        if (left < heap.size() && heap[left] < heap[smallest]) {
            smallest = left;
        }

        // 檢查右子節點是否比當前節點小
        if (right < heap.size() && heap[right] < heap[smallest]) {
            smallest = right;
        }

        // 如果最小的不是父節點，交換並繼續堆化
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest); // 遞迴處理受影響的子樹
        }
    }

    // 顯示Heap的內容(使用BFS)
    void printHeap() {
        for (int val : heap) {
            cout << val << " "; // 輸出每個元素
        }
        cout << endl;
    }
};

int main() {
    // 從文件讀取輸入元素
    string filename = "input.txt"; // 請確保你的 input.txt 檔案在同一資料夾
    vector<int> arr = readFromFile(filename); // 讀取數據

    if (arr.empty()) { // 如果數據為空
        cerr << "No valid data found in file." << endl; // 輸出錯誤信息
        return -1;
    }

    cout << "Input Array: "; // 輸出讀取的數據
    for (int val : arr) {
        cout << val << " "; // 輸出每個元素
    }
    cout << endl;

    MinHeap minHeap; // 創建Min Heap對象
    minHeap.buildMinHeap(arr); // 建立Min Heap

    // 輸出Min Heap的內容
    cout << "Min Heap(By BFS): ";
    minHeap.printHeap();
    cout << endl;

    system("pause");
    return 0;
}
