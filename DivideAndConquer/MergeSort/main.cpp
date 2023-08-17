#include <iostream>
#include <vector>
using namespace std;
class MergeSort {
public:
    //���ι���
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
        //���ø����ռ�
        vector<int> help = vector<int>(R - L + 1);
        int i = 0;
        int p1 = L;
        int p2 = M + 1;
        //�ж�����ֵ�Ƿ�Խ��
        while (p1 <= M && p2 <= R) {
            //����ߵ�ֵ<�ұߵ�ֵ  ����ߵ�ֵ������help��ȥ
            //�����ұߵ�ֵ������help��ȥ
            help[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
        }
        //���p1û��Խ�磬��ô��p1ʣ�µĶ���ȫ��������help��ȥ
        while (p1 <= M) {
            help[i++] = arr[p1++];
        }
        //���p2û��Խ�磬��ô��p2ʣ�µĶ���ȫ��������help��ȥ
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