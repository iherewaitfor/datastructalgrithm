- [DynamicProgramming 动态规划](#dynamicprogramming-动态规划)
- [钢条切割 CutRod](#钢条切割-cutrod)
- [最大连续子数组](#最大连续子数组)

# DynamicProgramming 动态规划

步骤
- 刻画一个最优解的的结构特征
- 递归地定义最优解的值
- 计算最优解的值，通常采用自底向上的方法
- 复用计算出的信息构造一个最优解。

状态步骤
- 设计状态
- 状态转移方程
- 设定初始状态
- 执行状态转移
- 返回最终解

# 钢条切割 CutRod

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

# 最大连续子数组
- 把原问题划分成独立的子问题
  - 以第i个元素结尾的子数组的最大子数组和为dp[i]
- 使用额外空间存储子问题的解，避免重复求解子问题。
  - 使用dp[nums.size()]存储子问题的解
- 使用子问题解组合成原问题解。
  - dp[i] = max(dp[i - 1] + nums[i], dp[i-1]);

最大连续子数组之和

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
