# GreedyAlgorithm 贪心算法

# 455. 分发饼干

[455. 分发饼干](https://leetcode.cn/problems/assign-cookies)

```C++
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int ans = 0;
        for(int i = g.size()-1, j = s.size()-1; i >=0 && j>=0;){
            if(s[j] >= g[i]){
                i--;
                j--;
                ans++;
            } else {
                i--;
            }
        }
        return ans;
    }
```