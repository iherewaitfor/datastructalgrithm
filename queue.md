# 队列
# 广度优先搜索

# 279. 完全平方数
[https://leetcode.cn/problems/perfect-squares](https://leetcode.cn/problems/perfect-squares)

## 广度优先搜索从n开始
```C++
    int bsfFromN(int n){
        queue<int> q;
        q.push(n);
        int step = 1;
        while(!q.empty()){
            int size = q.size();
            while(size--){
                int num = q.front();
                q.pop();
                for(int i = 1; i*i <= num; i++){
                    if(i*i == num){
                        return step;
                    }
                    q.push(num-i*i);
                }
            }
            step++;
        }
        return step;
    }
```
## 广度优先搜索从0开始
```C++
    int bsfFrom0(int n){
        queue<int>q;
        q.push(0);
        int step = 1;
        while(!q.empty()){
            int size = q.size();
            while(size--){
                int num = q.front();
                q.pop();
                for(int i = 1; i*i <= n-num; i++){
                    if(i*i + num == n){
                        return step;
                    }
                    q.push(num+i*i);
                }
            }
            step++;
        }
        return step;
    }
```
## 使用动态规划方法
```C++
    int numSquaresByDp(int n) {
        static int sqMap[10001] = {0};
        if(sqMap[1] < 1){ 
            for(int i = 1; i <=100; i++){
                sqMap[i*i] = 1;
            }
        }
        if(sqMap[n] > 0){
            return sqMap[n];
        }
        //dp[i]表示i，完全平方数的最少数量。
        vector<int> dp(n+1,0);
        for(int i = 1; i <= n; i++){
            if(sqMap[i] > 0){
                dp[i] = sqMap[i];
                continue;
            }
            dp[i] = i;
            for(int j = 1; j *j <= i ; j++){
                dp[i] = min(dp[i], dp[i-j*j]+1);
            }
            sqMap[i] = dp[i];
        }
        return dp[n];
    }
```