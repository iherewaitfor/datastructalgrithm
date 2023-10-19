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
# 860. 柠檬水找零
[860. 柠檬水找零](https://leetcode.cn/problems/lemonade-change/description/)
```C++
    bool lemonadeChange(vector<int>& bills) {
        int five = 0;
        int ten = 0;
        for(auto b : bills){
            if(b == 5){
                five++;
            } else if(b == 10){
                if(five <= 0){
                   return false; 
                }
                five--;
                ten++;
            } else if(b == 20){
                if(five > 0 && ten >0){
                    five--;
                    ten--;
                } else if(five >=3){
                    five -=3;
                } else {
                    return false;
                }
            }
        }
        return true;;
    }
```

# 435. 无重叠区间
[435. 无重叠区间](https://leetcode.cn/problems/non-overlapping-intervals)

```C++
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const auto& u, const auto& v)->bool {
            return u[1] < v[1];
        });
        int right = intervals[0][1];
        int count = 1;
        for(int i = 1; i < intervals.size(); i++){
            if(intervals[i][0] >= right){
                right = intervals[i][1];
                count++;
            }
        }
        return intervals.size() - count; 
    }
```