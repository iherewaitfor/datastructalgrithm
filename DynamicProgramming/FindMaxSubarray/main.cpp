#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;
class FindMaxSubarray {
public:
    //求子数组和及下标
    vector<int> maxSubarray(vector<int>& nums) {
        if (nums.size() == 0) {
            return { 0,0,0 };
        }
        //0: left index
        //1: right index
        //2: sum
        vector<vector<int>> dp(nums.size(), { 0,0,0 });
        int maxIndex = 0;
        dp[0] = { 0,0,nums[0] };
        for (int i = 1; i < nums.size(); ++i) {
            if (dp[i - 1][2] + nums[i] > nums[i]) {
                dp[i][0] = dp[i - 1][0];
                dp[i][1] = i;
                dp[i][2] = dp[i - 1][2] + nums[i];
            }
            else {
                dp[i][0] = i;
                dp[i][1] = i;
                dp[i][2] = nums[i];
            }
            if (dp[i][2] > dp[maxIndex][2]) {
                maxIndex = i;
            }
        }
        return dp[maxIndex];
    }

    //求子数组和及下标
    vector<int> maxSubarrayWidthIndex(vector<int>& nums, int L, int R) {
        if(L>R){
            return { 0,0, 0}; 
        }
        int size = R - L + 1;
        //0: left index
        //1: right index
        //2: sum
        vector<vector<int>> dp(size, { 0,0,0 });
        int maxIndex = 0;
        dp[0] = { L,L,nums[L] };
        for (int i = 1,j = L+i; i < size; ++i,j++) {
            if (dp[i - 1][2] + nums[j] > nums[j]) {
                dp[i][0] = dp[i - 1][0];
                dp[i][1] = j;
                dp[i][2] = dp[i - 1][2] + nums[j];
            }
            else {
                dp[i][0] = j;
                dp[i][1] = j;
                dp[i][2] = nums[j];
            }
            if (dp[i][2] > dp[maxIndex][2]) {
                maxIndex = i;
            }
        }
        return dp[maxIndex];
    }
    //leecode 53. 最大子数组和
    //https://leetcode.cn/problems/maximum-subarray/

    int maxSubArray(vector<int>& nums) {
        //vector<int> r = maxSubarray(nums);
        //return r[2];
        int r = maxSubarraySum(nums);
        return r;
    }

    //只求和不求下标
    int maxSubarraySum(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        int maxValue = dp[0];
        for (int i = 1; i < nums.size(); ++i) {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            maxValue = max(maxValue, dp[i]);
        }
        return maxValue;
    }
    int max(int a, int b) {
        return a > b ? a : b;
    }
    //leecode 121
    //https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
    int maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) {
            return 0;
        }
        vector<int> arr(prices.size() - 1);
        for (int i = 1; i < prices.size(); i++) {
            arr[i - 1] = prices[i] - prices[i - 1];
        }
        vector<int> results = maxSubarray(arr);
        if (results[2] <= 0) {
            return 0;
        }
        return results[2];
    }
};

int main()
{
    vector<int> nums = { 13, -3, -25, 20, -3, -16, -23,18, 20, -7, 12, -5, -22, 15, -4,7 }; // result:{7, 10, 43}
    //vector<int> nums = { 13 };
    //vector<int> nums = { -13 };
    FindMaxSubarray maxSubarray;
    vector<int> dpResults = maxSubarray.maxSubarray(nums);
    cout << "maxSubarray by Dynamic Programming " << endl;
    for (int i = 0; i < dpResults.size(); i++) {
        cout << dpResults[i] << " ";
    }


    //test for 
    //https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
    cout << endl;
    vector<int> num2s = { 7,1,5,3,6,4 };
    FindMaxSubarray maxSubarray2;
    int r = maxSubarray2.maxProfit(num2s);
    cout << r;

    return 0;
}