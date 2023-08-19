- [分治](#分治)
- [归并排序](#归并排序)
- [快速排序](#快速排序)
  - [原版本](#原版本)
  - [优化版本](#优化版本)
- [查找最大子数组](#查找最大子数组)
  - [分解](#分解)
  - [解决](#解决)
    - [递归结束条件](#递归结束条件)
    - [带限制条件最大子数组问题解决](#带限制条件最大子数组问题解决)
  - [合并](#合并)

# 分治
# 归并排序
# 快速排序
## 原版本
```C++
    void quickSort(vector<int>& arr, int L, int R) {
        if (L >= R) {
            //递归结束条件，只剩一个元素了，就是有序的。
            return;
        }
        //divide 分解:分成两个更小的子数组
        int q = partition(arr, L, R);
        //conquer 解决: 对子数组进行排序，递归调用。
        quickSort(arr, L, q-1);
        quickSort(arr, q + 1, R);
        //merge 合并
        //子数组分解后已是有序，无需合并操作。
    }
    //分解
    int partition(vector<int>& arr, int L, int R) {
        int x = arr[R]; //主元素
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
```
## 优化版本

- 随机选划分元素
  - 优化基本有序的情况
- 优化重复元素
  - 优化大部分是重复元素的情况。

```C++
    void quickSort(vector<int>& nums, int L, int R){
        if(L >= R){
            return;
        }
        int q = partion(nums, L, R);
        int lq = q - 1;
        int rq = q + 1;
        //优化重复元素
        while(lq > L && nums[lq] == nums[q]){
            lq --;
        }
        while(rq < R && nums[rq] == nums[q]){
            rq++;
        }
        quickSort(nums, L, lq);
        quickSort(nums, rq, R);
    }
    int partion(vector<int>& nums, int L, int R){
        int xIndex = (rand() % (R-L+1))+ L; //随机
        swap(nums, xIndex, R);
        int x = nums[R];
        int i = L - 1;
        for(int j = L; j < R; j++){
            if(nums[j] < x){
                i +=1;
                swap(nums, i, j);
            }
        }
        swap(nums,i+1, R);
        return i+1;
    }
    void swap(vector<int> & nums, int i, int j){
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
```

rand随机产生[L,R]范围内的整数。
```C++
(rand() % (R-L+1))+ L
```
rand 请参考[https://cplusplus.com/reference/cstdlib/rand/](https://cplusplus.com/reference/cstdlib/rand/)

# 查找最大子数组
- 股票买卖

## 分解
将问题分成3个子问题

int mid = (low+hight)/2

- [low, mid]  ，同类子问题
- [mid+1, high]， 同类子问题
- 肯定包含mid和mid+1的子数组。带条件的特定子问题。
## 解决

分别解决3个子问题
同类子问题，直接递归解决。
### 递归结束条件
子数组只剩一个元素。
### 带限制条件最大子数组问题解决
肯定包含mid和mid+1。

分别算左右，再相加。

low==high
## 合并
