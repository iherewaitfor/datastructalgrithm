#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;
class FindMaxSubarray {
public:
    vector<int> findMaxSubarray(vector<int>& arr, int low, int high) {
        //递归结束条件
        if (high == low) {
            return { low, high, arr[low] };
        }
        //分解:分解成更小的子问题
        int mid = (low + high) / 2;

        //解决:解决每个子问题
        vector<int> lefIndexs = findMaxSubarray(arr, low, mid);
        vector<int> rightIndexs = findMaxSubarray(arr, mid + 1, high);
        vector<int> crossIndexs = findMaxCrossingSubarray(arr, low, mid, high);
        
        //合并
        //0 low
        //1 high
        //2 sum
        if (lefIndexs[2] >= rightIndexs[2] && lefIndexs[2] >= crossIndexs[2]) {
            return lefIndexs;
        }
        else if (rightIndexs[2] >= lefIndexs[2] && rightIndexs[2] >= crossIndexs[2]) {
            return rightIndexs;
        }
        else {
            return crossIndexs;
        }
    }
    vector<int> findMaxCrossingSubarray(vector<int>& arr, int low, int mid, int high) {
        //一定包含mid和mid+1的情况
        int leftSum = INT_MIN;
        int sum = 0;
        int maxLeft = mid;
        for(int i = mid; i >=low; i--){
            sum = sum + arr[i];
            if (sum > leftSum) {
                leftSum = sum;
                maxLeft = i;
            }
        }
        int rightSum = INT_MIN;
        sum = 0;
        int maxRight = mid+1;
        for (int i = mid+1; i <= high; i++) {
            sum = sum + arr[i];
            if (sum > rightSum) {
                rightSum = sum;
                maxRight = i;
            }
        }
        return { maxLeft, maxRight, leftSum + rightSum };

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
        vector<int> results = findMaxSubarray(arr, 0, arr.size() - 1);
        if (results[2] <= 0) {
            return 0;
        }
        return results[2];
    }


    
    vector<int> maxSubarraySumbyDP(vector<int>&nums) {
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
            int leftIndex = dp[i - 1][0];//left
            
            if (dp[i][2] > dp[maxIndex][2]) {
                maxIndex = i;
            }
        }
        return dp[maxIndex];
    }
};

int main()
{
    vector<int> nums = { 13, -3, -25, 20, -3, -16, -23,18, 20, -7, 12, -5, -22, 15, -4,7 }; // result:{7, 10, 43}
    //vector<int> nums = { 13 };
    //vector<int> nums = { -13 };
    FindMaxSubarray maxSubarray;
    vector<int> resuls = maxSubarray.findMaxSubarray(nums, 0, nums.size() - 1);
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
    cout << "maxSubarray by Divide And Conquer " << endl;
    for (int i = 0; i < resuls.size(); i++) {
        cout << resuls[i] << " ";
    }
    cout << endl;
    vector<int> dpResults = maxSubarray.maxSubarraySumbyDP(nums);
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