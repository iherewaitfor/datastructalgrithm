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

# 四则运算

- 栈应用
- 优先级
  - 何时先计算栈内数据
    - 当前操作符为+或-
    - 栈顶操作符为*或/
- 边界
  - 最后一个操作数
    - 达到末尾字符时，把最后一个操作数入栈。

```C++
#include <iostream>
#include <stack>
using namespace std;
int calAB(int a, int b, char op) {
    int r = 0;
    if (op == '+') {
        r = a + b;
    }
    else if (op == '-') {
        r = a - b;
    }
    else if (op == '*') {
        r = a * b;
    }
    else if (op == '/') {
        r = a / b;
    }
    cout << "calAB:" << a << op << b << "=" << r << endl;
    return r;
}

int caldata(const string& str) {
    stack<int> datas;
    stack<char> ops;
    int opdata = 0;
    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        if (c >= '0' && c <= '9') {
            opdata = c - '0' + opdata * 10;
            if (i == str.size() - 1) {
                datas.push(opdata);
            }
        }
        else if(c == '+' || c=='-' || c=='*' || c=='/'){
            datas.push(opdata);
            opdata = 0;
            if (ops.size()>0 && (
                (c=='+' || c=='-')||
                (ops.top() == '*' || ops.top() == '/')
                )) {
                int b = datas.top();
                datas.pop();
                int a = datas.top();
                datas.pop();
                char opc = ops.top();
                ops.pop();
                int r = calAB(a, b, opc);
                datas.push(r);
            }
            ops.push(c);
        }
    }
    while (ops.size() > 0) {
        int b = datas.top();
        datas.pop();
        int a = datas.top();
        datas.pop();
        char opc = ops.top();
        ops.pop();
        int r = calAB(a, b, opc);
        datas.push(r);
    }
    return datas.top();
}
int main()
{
    //std::string str = "1+2";
    //std::string str = "11+22";
    //std::string str = "1+2-3";
    //std::string str = "1+2+3";
    //std::string str = "1+2*3";
    //string str = "11+10/5";
    string str = "11*10-20";
    int r = caldata(str);
    cout << "str:" << str << "=" << r << endl;
    cout << endl;
}
```

# 227. 基本计算器 II
[227. 基本计算器 II](https://leetcode.cn/problems/basic-calculator-ii)

- 用一个变量表示当前操作数的正负号。
- 把所有的数压入栈（带符号）
- 碰到乘除，先计算结果，再入栈
- 最后计算栈内的所有数之和
```C++
    int calculate(string s) {
        vector<int> stk;
        char presign = '+'; //当前操作数前面的操作符
        int64_t num = 0;
        int n = s.size();
        for(int i = 0; i < n ; i++){
            char c = s[i];
            if(c >= '0' && c <= '9'){
                num = num*10 + c-'0';
            }
            if(!(c >='0' && c <= '9') && c != ' ' || i == n-1){
                //即c为操作符+-*/
                //或者是最后一个数值
                //触发栈内操作数计算
                switch(presign){
                    case '+':
                        stk.push_back(num);
                        break;
                    case '-':
                        stk.push_back(-num);
                        break;
                    case '*':
                        stk.back() *= num;
                        break;
                    case '/':
                        stk.back() /= num;
                        break;
                }
                presign = c;//更新操作符
                num = 0;
            }
        }
        int sum = 0;
        for(auto v: stk){
            sum += v;
        }
        return sum;
    }
```
# 224. 基本计算器

解法一：使用后缀表达式。
关键数据结构
- 后缀表达式数组vector<string> rpn;
- 操作符栈stack<string> stk;

关键步骤
- 滤空
- 处理字符循环
  - 若为(
    - 直接入栈。注意是入符号栈。
  - 若为)
    - 把所有的操作符出栈，放到rpn，直到碰到(或者是空。
    - 然后把（出栈
  - 若为数值
    - 取出数值
    - 直接把数值放入到rpn
  - 最后为操作符
    - 先处理为-的情况
      - 需要额外加一个"0"到rpn。以例让运算符都保持是二元运算符。
        - i==s.size() 或s[i-1]为(
    - 根据优先级，处理需要出栈的操作符
      - 不是左括号的栈顶操作符，不比当前操作符小的操作符，都需要出栈，放入到rpn
      - 遇到左括号停止出栈
- 把栈内所有操作符出栈放到prn

```C++
#include<ctype.h>
class Solution {
public:
    int calculate(string s) {
        trim(s);
        vector<string> rpn;
        stack<string> stk;
        for(int i = 0; i < s.size(); i++){
            if(s[i] =='('){ 
                stk.push("(");
            } else if(s[i] == ')'){
                while(!stk.empty() && stk.top() != "("){
                    rpn.emplace_back(stk.top());
                    stk.pop();
                }
                stk.pop();//"("出栈
            } else if( isdigit(s[i])){
                string num;
                while(i < s.size() && isdigit(s[i])){
                    num.append(1,s[i++]);
                }
                i--;
                rpn.emplace_back(num);
            } else {
                if(s[i] == '-' && (i == 0 || s[i-1] == '(')){
                    rpn.emplace_back("0");
                }
                string op = s.substr(i,1);
                while(!stk.empty() && stk.top() != "(" && needpop(op, stk.top())){
                    rpn.emplace_back(stk.top());
                    stk.pop();
                }
                stk.push(op);
            }
        }
        while(!stk.empty()){
            rpn.emplace_back(stk.top());
            stk.pop();
        }
        // for(auto v: rpn){
        //     cout << v << " ";
        // }
        // cout << endl;
        return calrpn(rpn);
    }
private:
    bool isoperator(const string& s){
        return s =="+" || s=="-" || s=="*" || s=="/";
    }
    int calrpn(const vector<string> &rpn){
        stack<int> s;
        for(auto&v: rpn){
            if(isoperator(v)){
                int b = s.top();
                s.pop();
                int a = s.top();
                s.pop();
                s.push(calab(a,b,v));
            } else {
                s.push(stoi(v));
            }
        }
        return s.top();
    }
    int calab(int a, int b, const string& op){
        switch(op[0]){
            case '+':
                return a+b;
            case '-':
                return a-b;
            case '*':
                return a*b;
            case '/':
                return a/b;
        }
        return 0;
    }
    void trim(string& s){
        int j = 0;
        for(int i =0; i < s.size(); i++){
            if(s[i] != ' '){
                s[j++] = s[i];
            }
        }
        s.resize(j);
    }
    bool needpop(const string& op, const string& stktopop){
        static unordered_map<string,int> opmap = {
            {"+", 1},
            {"-", 1},
            {"*", 2},
            {"/", 2}
        };
        return opmap[stktopop] >= opmap[op];
    }
};
```

# 以词为单为翻转字符串

以词为单位翻转字符串(词之间以空格隔开)，以英文逗号为单位完成整段话的翻转。例如：

"how are you,I'm fine" -> "you are how,fine I'm"

"ab cde, fg,h jk" -> "cde ab,fg ,jk h"

```C++
#include <iostream>
using namespace std;
#include<stack>

std::string ReverseSentence(std::string input) {
    string ans; 
    stack<string> s;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == ','){
            while (!s.empty()) {
                ans.append(s.top());
                s.pop();
            }
            ans.append(1, input[i]);
        }
        else if (input[i] == ' ') {
            s.push(" ");
        }
        else {
            string word;
            while (input[i] != ',' && i < input.size() && input[i] != ' ') {
                word.append(1, input[i++]);
            }
            i--;
            s.push(word);
        }
    }
    while (!s.empty()) {
        ans.append(s.top());
        s.pop();
    }
    return ans;
}

int main()
{
    //string s = "how are you,I'm fine";
    string s = "ab cde, fg,h jk";
    cout << s << endl;
    string ans = ReverseSentence(s);
    cout << ans << endl;
    return 0;
}
```