#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;
class FindMaxSubarray {
public:
    static vector<int> findMaxSubarray(vector<int>& arr, int low, int high) {
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
    
    static vector<int> findMaxCrossingSubarray(vector<int>& arr, int low, int mid, int high) {
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
};
int main()
{
    vector<int> nums = { 13, -3, -25, 20, -3, -16, -23,18, 20, -7, 12, -5, -22, 15, -4,7 }; // result:{7, 10, 43}
    //vector<int> nums = { 13 };
    //vector<int> nums = { -13 };
    vector<int> resuls = FindMaxSubarray::findMaxSubarray(nums, 0, nums.size() - 1);
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < resuls.size(); i++) {
        cout << resuls[i] << " ";
    }
    return 0;
}