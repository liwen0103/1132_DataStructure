class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1; // nums1 的最後一個元素
        int j = n - 1; // nums2 的最後一個元素
        int k = m + n - 1; // 合併後最後的位置

        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k--] = nums1[i--];
            } else {
                nums1[k--] = nums2[j--];
            }
        }

        // 如果nums2還有元素，繼續放入nums1
        while (j >= 0) {
            nums1[k--] = nums2[j--];
        }
    }
};
