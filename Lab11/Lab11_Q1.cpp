#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

// 商品類別
class Product {
private:
    string name;     // 商品名稱
    int expiry;      // 有效期限（剩餘天數）
    int popularity;  // 熱銷程度（1~10）

public:
    // 建構子
    Product(string n, int e, int p) : name(n), expiry(e), popularity(p) {}

    // 取得商品名稱
    string getName() const { return name; }

    // 取得有效期限
    int getExpiry() const { return expiry; }

    // 取得熱銷程度
    int getPopularity() const { return popularity; }

    // 比較規則
    static bool compare(const Product &a, const Product &b) {
        if (a.expiry != b.expiry)
            return a.expiry < b.expiry;  // 有效期限短者優先
        return a.popularity > b.popularity;  // 熱銷高者優先
    }

    // 顯示商品資訊
    void print() const {
        cout << name << " " << expiry << " " << popularity << endl;
    }
};

// 合併排序用 merge 函式
void merge(vector<Product> &arr, int left, int mid, int right) {
    vector<Product> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<Product> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < leftArr.size() && j < rightArr.size()) {
        if (Product::compare(leftArr[i], rightArr[j]))
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }
    while (i < leftArr.size()) arr[k++] = leftArr[i++];
    while (j < rightArr.size()) arr[k++] = rightArr[j++];
}

// 合併排序主函式
void mergeSort(vector<Product> &arr, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {
    ifstream file("input.txt"); // 固定讀取 input.txt
    if (!file.is_open()) {
        cerr << "無法開啟 input.txt 檔案" << endl;
        return 1;
    }

    int N;
    file >> N;
    file.ignore(); // 忽略讀完 N 後的換行

    vector<Product> products;

    // 每行完整讀取並解析
    for (int i = 0; i < N; ++i) {
        string line;
        getline(file, line);
        istringstream iss(line);
        string word, name = "";
        int expiry, popularity;

        // 組合商品名稱直到遇到數字
        while (iss >> word) {
            if (isdigit(word[0])) {
                expiry = stoi(word);
                break;
            }
            if (!name.empty()) name += " ";
            name += word;
        }

        // 讀取熱銷程度
        iss >> popularity;

        // 新增商品到容器中
        products.emplace_back(name, expiry, popularity);
    }
    file.close();

    // 執行排序
    mergeSort(products, 0, products.size() - 1);

    // 輸出結果
    for (const auto &product : products) {
        product.print();
    }

    return 0;
}
