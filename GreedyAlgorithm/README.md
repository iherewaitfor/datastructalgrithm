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
# 452. 用最少数量的箭引爆气球
[452. 用最少数量的箭引爆气球](https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons)
```C++
    int findMinArrowShots(vector<vector<int>>& points) {
        if(points.empty()){
            return 0;
        }
        sort(points.begin(), points.end(), [](const vector<int>&u, const vector<int>&v){
            return u[1] < v[1];
        });
        int arrow = points[0][1];
        int count = 1;
        for(auto& point:points){
            if(point[0] > arrow){
                arrow = point[1];
                ++count;
            }
        }
        return count;
    }
```
# 56. 合并区间
[56. 合并区间](https://leetcode.cn/problems/merge-intervals)
```C++
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;
        for(auto & interval: intervals){
            int L = interval[0];
            int R = interval[1];
            if(merged.size() == 0 || merged.back()[1] < L){
                merged.push_back(interval);
            } else {
                merged.back()[1] = max(merged.back()[1], R);
            }
        }
        return merged;
    }
```

# 55. 跳跃游戏
[55. 跳跃游戏](https://leetcode.cn/problems/jump-game)
```C++
    bool canJump(vector<int>& nums) {
        int rightmost = 0;
        for(int i = 0; i < nums.size(); i++){
            if(i > rightmost){
                return false;
            }
            rightmost = max(rightmost, i+nums[i]);
            if(rightmost >= nums.size()-1){
                return true;
            }
        }
        return true;
    }
```