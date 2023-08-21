- [DynamicProgramming 动态规划](#dynamicprogramming-动态规划)
- [钢条切割 CutRod](#钢条切割-cutrod)
- [最大连续子数组之和](#最大连续子数组之和)
- [最大连续子数组](#最大连续子数组)
- [买卖股票的最佳时期3](#买卖股票的最佳时期3)
- [打家劫舍](#打家劫舍)
- [编辑距离 leecode 72](#编辑距离-leecode-72)

# DynamicProgramming 动态规划
动态归划，与分治策略类似
- 相同
  - 分解：划分原问题为若干子问题
    - 同类问题，规模更小
    - 新的的问题，但可单独求解
  - 解决
    - 同类问题，求解规模更小的子问题
      - 递归结束：规模最小的同类子问题 可直接得出。
      - 归并：只剩一个元素
      - 快排：只剩一个元素
      - 最大子数组之和：只剩一个元素
    - 不同的问题，单独求解
    - 合并：组合子问题的解，求解原问题
      - 归并：全并操作
      - 最大子数组之和：找出最大值。
- 不同
  - 分治策略：互不相交的子问题。如归并排序、快排、最大子数组之和。
    - 使用递归
  - 动态规划：大量重复的子问题。如钢条切割，最大子数组之各。
    - 使用额外存储空间存储子问题答案，避免重复求解
    - 一般 自底向上
    - 一般不使用递归。使用状态转移方程解决子问题。

状态转移解法步骤
- 设计状态
- 状态转移方程
- 设定初始状态
- 执行状态转移
- 返回最终解


《算法导论》步骤
- 刻画一个最优解的的结构特征
- 递归地定义最优解的值
- 计算最优解的值，通常采用自底向上的方法
- 利用计算出的信息构造一个最优解。

# 钢条切割 CutRod

状态步骤
- 设计状态
  - 分治：划分子问题。子问题是同类问题，或可单独求解。
  - 长度为i的最大值为dp[i],i=[0,n-1]
  - 这些子问题的解可以组合出原问题的解。
- 状态转移方程
  - 切割[0,i-1]
    - 不切割
  - dp[i] = max(nums[i],dp[i-1]+ dp[1], dp[i-2] + dp[2], ..., d[1]+ dp[i-1] );
  - (递归定义子问题解)
- 设定初始状态
  - dp[0] = 0;
  - dp[1] = nums[1];
  - 递归结束条件。
- 执行状态转移
  - 求解子问题解，从1到n
  - 自底向上求解
- 返回最终解
  - 组合子问题的解，求解原问题的解
  - 该题中，子问题的定义就是原问题
  - result = dp[n];
  

- 最优解的结构特征
  - Rn = max(Pn, R1+Rn-1, R2+Rn-2,...,Rn-2+R2,Rn-1+R1)
- 递归地定义最优解的值
- 自底向上
  - 从0开始计算子问题的值
- 构造一个最优解

动态规划核心思想：
- 把原问题划分成独立的子问题。
- 使用额外空间存储子问题的解，避免重复求解子问题。
- 使用子问题解组合成原问题解。

# 最大连续子数组之和

- 把原问题划分成独立的子问题
  - 以第i个元素结尾的子数组的最大子数组和为dp[i]
    - 与第i子元素相连   
      - dp[i-1] + nums[i];
    - 与第i个元素不相连
      - nums[i]
- 使用额外空间存储子问题的解，避免重复求解子问题。
  - 使用dp[nums.size()]存储子问题的解
  - 求解子问题
    - dp[0] = nums[0];//初始状态 ，递归结束条件。
    - dp[i] = max(dp[i - 1] + nums[i], nums[i]);
- 使用子问题解组合成原问题解。
  - max(dp[0], dp[1], dp[2], ... , dp[n-2],dp[n-1]);

[https://leetcode.cn/problems/maximum-subarray/](https://leetcode.cn/problems/maximum-subarray/)

nums[n];
状态步骤
- 设计状态
  - 分治：划分子问题。子问题是同类问题，或可单独求解。
  - 以第i个元素为结尾的子数组的最大子数组和为dp[i],i=[0,n-1]
  - 这些子问题的解可以组合出原问题的解。
- 状态转移方程
  - 与i元素相连 dp[i-1] + nums[i]
  - 与i元素不相连nums[i]
  - dp[i] = max(dp[i-1]+nums[i],nums[i])
  - (递归定义子问题解)
- 设定初始状态
  - dp[0] = nums[0]
  - 递归结束条件。
- 执行状态转移
  - 求解子问题解，从0到n-1
- 返回最终解
  - 组合子问题的解，求解原问题的解
  - result = max(dp[0], dp[1], d[2], ..., dp[n-2], d[n-1]);


```C++
    int maxSubarraySum(vector<int>& nums){
        if(nums.size() == 0){
            return 0;
        }
        vector<int> dp(nums.size());
        int maxValue = nums[0];
        dp[0] = nums[0];
        for(int i = 1; i < nums.size(); ++i){
            dp[i] = max(dp[i-1] + nums[i], nums[i]);
            maxValue = max(maxValue, dp[i]);
        }
        return maxValue;
    }
    int max(int a, int b){
        return a > b ? a : b;
    }
```

# 最大连续子数组

返回和以及子数组下标

# 买卖股票的最佳时期3


未优化版本
```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() <= 1){
            return 0;
        }
        vector<int> arr(prices.size()-1);
        for(int i = 1; i <= prices.size() -1; i++){
            arr[i-1] = prices[i] - prices[i -1 ];
        }
        int r = max2SubArraySum(arr);
        return r > 0 ? r : 0;
    }
    int max2SubArraySum(vector<int>&nums){
        if(nums.size() == 0){
            return 0;
        }
        //至多两笔交易，第一笔在i点卖出。
        vector<int> dp2(nums.size(), {0});
        //求左右 子数组最大值之和
        dp2[0] = maxSum(nums[0], maxSubarray(nums, 1, nums.size() - 1)[2]);
        int maxValue = dp2[0];
        for(int i = 1; i < nums.size(); i++){
            dp2[i] = maxSum(maxSubarray(nums,0, i)[2], maxSubarray(nums,i+1, nums.size()-1)[2]);
            maxValue = dp2[i] > maxValue ? dp2[i] : maxValue;
        }
        return maxValue;
    }
    int maxSum(int a, int b){
        if( a > 0 ){
            return  b > 0 ? (a+b) : a;
            
        } else {
            return b > 0 ? b : 0;
        }
    }

    //求子数组和及下标
    vector<int> maxSubarray(vector<int>& nums, int L, int R) {
        if(L>R){
            return { 0,0, 0}; 
        }
        int size = R - L + 1;
        //0: left index
        //1: right index
        //2: sum
        vector<vector<int>> dp(size, { 0,0,0 });
        int maxIndex = 0;
        dp[0] = { L,L,nums[L] };
        for (int i = 1,j = L+i; i < size; ++i,j++) {
            if (dp[i - 1][2] + nums[j] > nums[j]) {
                dp[i][0] = dp[i - 1][0];
                dp[i][1] = j;
                dp[i][2] = dp[i - 1][2] + nums[j];
            }
            else {
                dp[i][0] = j;
                dp[i][1] = j;
                dp[i][2] = nums[j];
            }
            if (dp[i][2] > dp[maxIndex][2]) {
                maxIndex = i;
            }
        }
        return dp[maxIndex];
    }
};
```

# 打家劫舍
leecode 198

[https://leetcode.cn/problems/house-robber](https://leetcode.cn/problems/house-robber)

```C++
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n == 1){
            return nums[0];
        }
        vector<int> dp(n);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for(int i = 2; i < n; i++){
            dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
        }
        return dp[n- 1];
    }
```

# 编辑距离 leecode 72


leecode 72 [https://leetcode.cn/problems/edit-distance](https://leetcode.cn/problems/edit-distance)

找最小路径和。
```C++
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        //dp[i][j] 表示
        //word1的前i子串 转换成
        //word2的前j子串 所需的最小步数
        vector<vector<int>> dp(m+1, vector<int>(n+1));

        //dp[i-1][j-1]  
        //dp[i-1][j]   从word1插入一个字符dp[i][j]
        //dp[i][j-1]   从word2插入一个字条dp[i][j]
        
        // 可以从以上3个状态，转换到dp[i][j].
        //对应二维图，dp[i][j]的 左上方、上方、左方三个格子
        //可以转换为，二维图的路径，怎么走代价最小。

        //第一行
        for(int j = 1; j <= n; j++){
            dp[0][j] = dp[0][j-1] + 1; //全插入。由空串变成word2前j。
        }
        //第一列
        for(int i = 1; i <= m; i++){
            dp[i][0] = dp[i-1][0] + 1; //全删除。由word1变成空串。
        }

        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(word1[i-1] == word2[j-1]){
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = min(min(dp[i-1][j-1], dp[i][j-1]),
                        dp[i-1][j]) + 1;
                }
            }
        }
        return dp[m][n];
    }
```

leecode 64. 最小路径和的逻辑是很类似的。
[https://leetcode.cn/problems/minimum-path-sum](https://leetcode.cn/problems/minimum-path-sum)

只是走法不一样。
- leecode 64. 最小路径 只有两种走法
  - 向右
  - 向下
- leecode 72. 编辑距离 有三种走法
  - 向右
  - 向下
  - 斜角右下

把整体思路变成找最小路径和，就很清晰了。




