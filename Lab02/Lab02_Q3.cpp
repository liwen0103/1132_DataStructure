class Solution {
public:
    int findLucky(vector<int>& arr) {
        unordered_map<int, int> freq; //存數字出現的次數

        // 紀錄數字出現次數
        for (int num : arr) {
            freq[num]++;//出現一次計+1
        }

        int maxLucky = -1; //初始化最大幸運數字，-1表示沒有

        // 確認哪些數字是幸運數
        for (auto& pair : freq) {
            int num = pair.first;   // 數字
            int count = pair.second; // 數字出現的次數

            if (num == count) { // 如果數字跟出現的次數一樣
                maxLucky = max(maxLucky, num); // 就是最大幸運的數字
            }
        }

        return maxLucky; // 回傳最大幸運數字
    }
};

