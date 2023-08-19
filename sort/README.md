- [排序](#排序)
- [归并排序](#归并排序)
- [快速排序](#快速排序)
- [堆排序](#堆排序)
- [计算排序](#计算排序)

# 排序
# 归并排序
# 快速排序
[DivideAndConquer/README.md#快速排序](https://github.com/iherewaitfor/datastructalgrithm/blob/main/DivideAndConquer/README.md#%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F)
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

自适应mapsize，有可能能省一点内存。
```C++
    void countSort(vector<int> & nums){
        if(nums.size() <=1){
            return;
        }
        int maxNum = nums[0];
        int minNum = nums[0];
        for(int i = 0; i < nums.size(); i++){
            if(maxNum < nums[i]){
                maxNum = nums[i];
            }
            if(minNum > nums[i]){
                minNum = nums[i];
            }
        }
        int mapsize = maxNum - minNum + 1;
        // num - offset = index  of countMap. start from 0.
        // minMum - offset = 0
        int offset  = minNum; 

        vector<int> countMap(mapsize,0);
        for(int i = 0; i < nums.size(); i++){
            nums[i] -= offset;
            countMap[nums[i]] += 1;
        }
        for(int i = 0,index = 0; i < countMap.size(); i++){
            while(countMap[i] > 0){
                nums[index++] = i + offset;
                countMap[i]--;
            }
        }
    }
```