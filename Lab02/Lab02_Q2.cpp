class Solution {
public:
vector<int> runningSum(vector<int>& nums) 
{
int n =nums.size();//nums的長度
vector<int> result(n);
result[0]=nums[0];//第一個數直接輸出

   //第二個數開始跟前面的數都相加
   for(int i=1; i<n; i++)
   {
   result[i]=result[i-1]+nums[i];//輸出的值是前面的累加，加上當前位置本身的值
   }
   return result;//回傳累加的結果
 }
};

