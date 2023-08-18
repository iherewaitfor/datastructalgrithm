#include <iostream>
#include <vector>
using namespace std;
class HeadSort {
public:
    void sort(vector<int>& arr) {
        buildMaxHeap(arr);
        for (int i = arr.size()-1; i > 0; i--) {
            swap(arr, 0, i); // �Ѹ���㣬�ŵ������
            maxHeapify(arr, 0, i); // the new heap size is i;
        }
    }
private:

    void buildMaxHeap(vector<int>& arr) {
        for (int i = arr.size() / 2 - 1; i >= 0; i--) {
            maxHeapify(arr, i, arr.size());
        }
    }

    void maxHeapify(vector<int>& arr, int i, int heapSize) {
        int l = left(i);  //��������
        int r = right(i); //�Һ�������
        int largest = i;  //���ֵ����
        if (l < heapSize && arr[l] > arr[largest]) {
            largest = l;
        }
        if (r < heapSize && arr[r] > arr[largest]) {
            largest = r;
        }
        if (largest != i) {
            swap(arr, i, largest);
            maxHeapify(arr, largest, heapSize);
        }
    }

    int parent(int i) {
        return (i-1)/2;
    }
    int left(int i) {
        return i * 2+1;
    }
    int right(int i) {
        return i * 2 + 2;
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
    HeadSort heapSort;
    heapSort.sort(nums);
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    return 0;
}