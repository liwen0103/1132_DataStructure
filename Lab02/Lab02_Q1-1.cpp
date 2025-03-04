// Method 1
class Solution 
{
public:
vector<int> smallerNumbersThanCurrent(vector<int>& nums)
  {
   //count=1(assignment)
  int count[101]={0};//計數陣列,範圍 0-100
   
  //count=1(assignment)
  int n=num.size();//陣列長度
  vector<int> result(n); //vector<int>是動態陣列,在執行分配記憶體時,可以根據 num.size()自動調整大小
   //計算每個數字的出現次數,此迴圈遍歷 nums,並統計每個數字 num 出現的次數
   
  //count=1(addition)
  for(int num:nums){ count[num]++;}
   //計算比當前數字小的數量
   //count=1(for a loop)
    
    for(int i=1; i<101; i++)
    {
      //count=1(addition)
      count[i]+=count[i-1];
    }//計算 result 陣列
      
    //count=1(for a loop)
    for(int i=0; i<n; i++)
    {
      //count=1(assignment)
      result[i]=(nums[i]==0)?0:count[nums[i]-1];
      //count[nums[i]-1]代表比 nums[i]小的數的數量,nums[i]==0 時則 直接返回 0
    }
    
        //count=1(for return)
        return result;
  }
}
//total operations:5n+3
// Therefore, O(n) complexity

