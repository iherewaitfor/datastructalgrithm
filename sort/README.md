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
    void countSort(vector<int> & nums){
        const int MAP_SIZE = 100010;
        const int OFFSET = 50000;
        vector<int> mapArr(MAP_SIZE);
        for(int i = 0; i < mapArr.size(); i++){
            mapArr[i] = 0;
        }
        for(int i = 0; i < nums.size(); i++){
            nums[i] += OFFSET;
            mapArr[nums[i]] += 1;
        }
        int index = 0;
        for(int i = 0; i < mapArr.size(); i++){
            while(mapArr[i] > 0){
                nums[index++] = i;
                mapArr[i]--;
            }
        }
        for(int i = 0; i < nums.size(); i++){
            nums[i] -= OFFSET;
        }
    }
```