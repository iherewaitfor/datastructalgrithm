#include <iostream>
#include <vector>
using namespace std;
class QuickSort {
public:
    static void quickSort(vector<int>& arr, int L, int R) {
        if (L >= R) {
            //�ݹ����������ֻʣһ��Ԫ���ˣ���������ġ�
            return;
        }
        //divide �ֽ�:�ֳ�������С��������
        int q = partition(arr, L, R);
        //conquer ���: ��������������򣬵ݹ���á�
        quickSort(arr, L, q-1);
        quickSort(arr, q + 1, R);
        //merge �ϲ�
        //������ֽ��������������ϲ�������
    }
    //�ֽ�
    static int partition(vector<int>& arr, int L, int R) {
        int x = arr[R]; //��Ԫ��
        int i = L - 1;
        for (int j = L; j < R; j++) {
            if (arr[j] < x) {
                i = i + 1;
                //exchange arr[i] and arr[j]
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        // exchange arr[i+1] width arr[R]
        int t = arr[i + 1];
        arr[i + 1] = arr[R];
        arr[R] = t;
        return i + 1;
    }
};
int main()
{
    vector<int> nums = { 5,4,3,5,683,86,3 };
    QuickSort::quickSort(nums, 0, nums.size() - 1);
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    return 0;
}