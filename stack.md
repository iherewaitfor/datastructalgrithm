# stack

# 200. 岛屿数量
[https://leetcode.cn/problems/number-of-islands](https://leetcode.cn/problems/number-of-islands)
深度优先
- 所有结点先进栈
  - 四个方向：上下左右
  - 即四叉树。有四个孩子。
  - 使用grid本身的值做是否访问过的记录。
- 退栈时才访问
```C++
const vector<vector<int>> DIRECTORNS = {
    {1,  0},
    {-1, 0},
    {0,  1},
    {0, -1}
};
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size();
        if(0 == m){
            return 0;
        }
        int n = grid[0].size();
        int numIslands = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == '1'){
                    numIslands++;
                    dfsbyStack(i,j,grid);
                }
            }
        }
        return numIslands;
    }

    void dfsbyStack(int r,int c, vector<vector<char>>& grid){
        int m = grid.size();
        int n = grid[0].size();
        stack<vector<int>> s;
        s.push({r,c});
        while(!s.empty()){
            auto point = s.top();
            s.pop();
            grid[point[0]][point[1]] = '0';
            for(auto &direct : DIRECTORNS){
                int row = point[0] + direct[0];
                int col = point[1] + direct[1];
                if(row < 0 || row >=m ||col < 0 || col >= n || grid[row][col] != '1'){
                    continue;
                }
                s.push({row,col});
            }
        }
    }
};
```