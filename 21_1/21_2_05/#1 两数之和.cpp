//用哈希表
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        map<int,int> m;
        for(int i = 0; i < nums.size(); i++)
        {
            map<int,int>::iterator it = m.find(target - nums[i]);
            if(it != m.end())
            {
                return {it->second,i};
            }
            m.insert(pair<int,int>(nums[i],i));
        }
       return {0,0};
    }
};