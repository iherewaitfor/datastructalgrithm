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

# 133. 克隆图
[https://leetcode.cn/problems/clone-graph](https://leetcode.cn/problems/clone-graph)

```C++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        unordered_map<Node*,Node*> visited;
        return dfsbyStack(node, visited);
        // unordered_map<Node*,Node*> visited;
        // return dfs(node, visited);
        
    }
    Node * dfsbyStack(Node* node, unordered_map<Node*,Node*> &visited){
        if(NULL == node){
            return NULL;
        }
        Node* cNode = new Node(node->val);
        visited[node] = cNode;
        //深度优先
        stack<Node*> s;
        s.push(node);
        while(!s.empty()){
            Node * source = s.top();
            s.pop();
            for(auto neighbor:source->neighbors){
                if(visited.count(neighbor) < 1){
                    //建副本结点
                    Node* cneighbor = new Node(neighbor->val);
                    visited[neighbor] = cneighbor;
                    s.push(neighbor);
                }
                visited[source]->neighbors.push_back(visited[neighbor]);
            }
        }
        return cNode;
    }

        //递归
    Node * dfs(Node* node, unordered_map<Node*,Node*> &visited){
        if(NULL == node){
            return NULL;
        }
        if(visited.find(node) != visited.end()){
            return visited[node];
        }
        //所有的方向 
        Node* cNode = new Node(node->val);
        visited[node] = cNode;
        for(auto neighbor:node->neighbors){
            cNode->neighbors.push_back(dfs(neighbor,visited ));
        }
        return cNode;
    }
};
```