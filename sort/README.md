- [排序](#排序)
- [归并排序](#归并排序)
- [快速排序](#快速排序)
- [堆排序](#堆排序)
- [计算排序](#计算排序)

# 排序
# 归并排序
# 快速排序

# 堆排序
[sort/HeapSort](https://github.com/iherewaitfor/datastructalgrithm/tree/main/sort/HeapSort)
# 计算排序

力扣912
[https://leetcode.cn/problems/sort-an-array/](https://leetcode.cn/problems/sort-an-array/)

```C++
    void couterSort(vector<int>& nums){
        const int MAP_SIZE = 100010;
        const int OFFSET = 50000;
        vector<int> countMap(MAP_SIZE,0);
        for(int i = 0; i < nums.size(); i++){
            nums[i] += OFFSET;
            countMap[nums[i]]++;
        }
        int index = 0;
        for(int i = 0; i < countMap.size(); i++){
            while(countMap[i] > 0){
                nums[index++] = i - OFFSET;
                countMap[i]--;
            }
        }
    }
```