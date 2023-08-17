#include <iostream>
#include <vector>
using namespace std;
class MergeSort {
public:
    //分治过程
    static void mergeSort(vector<int>& arr, int L, int R) {
        if (L >= R) {
            return;
        }
        int mid = (L+R)/2;
        mergeSort(arr, L, mid);
        mergeSort(arr, mid + 1, R);
        merge(arr, L, mid, R);
    }

    static void merge(vector<int>& arr, int L, int M, int R) {
        //设置辅助空间
        vector<int> help = vector<int>(R - L + 1);
        int i = 0;
        int p1 = L;
        int p2 = M + 1;
        //判断两边值是否越界
        while (p1 <= M && p2 <= R) {
            //当左边的值<右边的值  将左边的值拷贝到help里去
            //否则将右边的值拷贝到help里去
            help[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
        }
        //如果p1没有越界，那么将p1剩下的东西全部拷贝到help中去
        while (p1 <= M) {
            help[i++] = arr[p1++];
        }
        //如果p2没有越界，那么将p2剩下的东西全部拷贝到help中去
        while (p2 <= R) {
            help[i++] = arr[p2++];
        }

        for (i = 0; i < help.size(); i++) {
            arr[L + i] = help[i];
        }
    }
};
int main()
{ 
    vector<int> nums = { 5,4,3,5,683,86,3 };
    MergeSort::mergeSort(nums,0,nums.size()-1);
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    return 0;
}