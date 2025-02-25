class Solution 
{
public:
    bool isMonotonic(vector<int>& nums) 
    {
        bool increasing = true, decreasing = true;//兩者狀態皆可能是monotonic array
        
        for (int i = 1; i < nums.size(); i++) 
        {
            if (nums[i] > nums[i - 1]) //兩數為遞增狀態
            {
                decreasing = false;//遞增狀態下如果遞減則不是monotonic array
            }
             if (nums[i] < nums[i - 1])//兩數為遞減狀態
             {
                increasing = false;//遞減狀態下如果遞增則也不是monotonic array
             }
        }
        return increasing || decreasing;
    }
};
