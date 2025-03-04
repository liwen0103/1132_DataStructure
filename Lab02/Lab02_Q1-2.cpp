// Method 2
class Solution 
{
  public:
  vector<int> smallerNumbersThanCurrent(vector<int>& nums)
  {
    vector<int> result; // 存結果
    int count; // 計數器
    
    // 外層迴圈遍歷 nums 陣列中的每個元素
    //count=1(for a loop)
    for (int i = 0; i < nums.size(); i++) 
    {
    //count=1(assignment)
    count = 0; // 每次重新計算當前元素的較小數量
    
    // 內層迴圈再次遍歷 nums 陣列,統計比 nums[i] 小的元素數量
    //count=1(for a loop)
      for (int j = 0; j < nums.size(); j++) 
      {
      //count=1(comparisons)
      if (nums[j] < nums[i]) { count++; } // 如果 nums[j] 比
      
      nums[i] 小,則計數器 +1
      
      }
       result.push_back(count); // 將計算出的數量存入 result
    }
    //count=1(for return)
    return result;
  }
};
//total operations:=2n^2+1
// Therefore, O(n^2) complexity

