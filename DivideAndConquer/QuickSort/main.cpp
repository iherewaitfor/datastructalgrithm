#include <iostream>
#include <vector>
using namespace std;
class QuickSort {
public:
    void quickSort(vector<int>& arr, int L, int R) {
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
    int partition(vector<int>& arr, int L, int R) {
        int x = arr[R]; //��Ԫ��
        int i = L - 1;
        for (int j = L; j < R; j++) {
            if (arr[j] < x) {
                i = i + 1;
                swap(arr, i, j);//exchange arr[i] and arr[j]
            }
        }        
        swap(arr, i + 1, R);// exchange arr[i+1] width arr[R]
        return i + 1;
    }
    void swap(vector<int>& arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
};
int main()
{
    vector<int> nums = { 5,4,3,5,683,86,3 };
    QuickSort quickSort;
    quickSort.quickSort(nums, 0, nums.size() - 1);
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    return 0;
}