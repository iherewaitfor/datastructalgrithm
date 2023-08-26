- [二叉树](#二叉树)
- [前序遍历](#前序遍历)
  - [递归遍历](#递归遍历)
  - [迭代 by Stack](#迭代-by-stack)
- [中序遍历](#中序遍历)
  - [递归](#递归)
  - [迭代 byStack](#迭代-bystack)
- [后序遍历](#后序遍历)
  - [递归](#递归-1)
  - [迭代 byStack](#迭代-bystack-1)
- [层次遍历](#层次遍历)
- [中序后序遍历序列构造树](#中序后序遍历序列构造树)

# 二叉树

最基本的结构定义
```C++
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
};
```
# 前序遍历
## 递归遍历
```C++
    void preOrder(TreeNode* root, vector<int>& res) {
        if (root == nullptr) {
            return;
        }
        res.push_back(root->val);
        preOrder(root->left, res);
        preOrder(root->right, res);
    }
```
## 迭代 by Stack
```C++
    void preOrderByStack(TreeNode * root, vector<int>&res){
        stack<TreeNode*> treeStack;
        treeStack.push(root);
        while(!treeStack.empty()){
            TreeNode* node = treeStack.top();
            treeStack.pop();
            if(node == NULL){
                continue;;
            }
            //根结点和左孩子结点，直接给出结束。
            //右孩子结点，只进栈，不输出结。
            //右孩子需要等从栈里出来，才输出结果（先进后出）
            res.push_back(node->val);
            treeStack.push(node->right); //先进后出
            TreeNode * pLeft = node->left;
            while(pLeft){
                res.push_back(pLeft->val);
                treeStack.push(pLeft->right);//先进后出
                pLeft = pLeft->left;
            }
        }
    }
```
# 中序遍历
## 递归
```C++
    void inOrder(TreeNode* root, vector<int> &res){
        if(root == NULL){
            return;
        }
        inOrder(root->left, res);
        res.push_back(root->val);//中序
        inOrder(root->right, res);
    }
```
## 迭代 byStack
```C++
    void inorderByStack(TreeNode* root, vector<int> & res) {
        stack<TreeNode*> tStack;
        tStack.push(root);
        //根结点已在栈里。左孩子后入栈，（后进先出），先出栈先被访问。
        TreeNode * pLeft = NULL;
        if(root){
            pLeft = root->left;
        }
        while(pLeft){
                tStack.push(pLeft);
                pLeft = pLeft->left;
        }
        while(!tStack.empty()){
            TreeNode* node = tStack.top();
            tStack.pop(); //出栈
            if(node == NULL){
                continue;
            }
            res.push_back(node->val);//访问根
            tStack.push(node->right);//根结点访问后（出栈），才访问右结点。
            if(node->right){
                pLeft = node->right->left;
            }
            while(pLeft){
                tStack.push(pLeft);
                pLeft = pLeft->left;
            }
        }
    }
```
# 后序遍历
左右根

## 递归

```C++
    void postOrder(TreeNode* root, vector<int>&res){
        if(root == NULL){
            return;
        }
        postOrder(root->left, res);
        postOrder(root->right, res);
        res.push_back(root->val);
    }
```

## 迭代 byStack

通过unordered_set记录已经访问过的结点，判断出栈逻辑。

```C++
    void postOrderByStackAndSet(TreeNode* root, vector<int>&res){
        stack<TreeNode*> tStack;
        if(!root){
           return; 
        }
        //后序：左右根
        tStack.push(root);//根
        unordered_set<TreeNode*> visitedNodes; //记录已访问过的结点
        while(!tStack.empty()){
            TreeNode* node = tStack.top();
            if(node==NULL){
                tStack.pop();
                continue;
            }
            //根结点在左右都被访问过,才能出栈
            //左孩子已处理
            if(node->left == NULL || visitedNodes.count(node->left)){
                //右孩子已处理
                if(node->right == NULL || visitedNodes.count(node->right)){
                    tStack.pop();
                    res.push_back(node->val);
                    visitedNodes.insert(node);
                    continue;
                } else {
                    //处理右孩子。
                    tStack.push(node->right);
                }
            } else {
                //处理左孩子。
                tStack.push(node->left);
            }
        }
    }
```

非优化版本。通过pLastvisi及穷举，判断左右孩子是否已被访问。

```C++
    void postOrderByStack(TreeNode* root, vector<int>&res){
        stack<TreeNode*> tStack;
        if(!root){
           return; 
        }
        //后序：左右根
        tStack.push(root);//根
        TreeNode * pLastvisi  = NULL; //上一个被访问的结点。
        while(!tStack.empty()){
            TreeNode* node = tStack.top();
            if(node==NULL){
                tStack.pop();
                pLastvisi = NULL;
                continue;
            }
            //根结点在左右都被访问过,才能出栈
            //左右为空
            if(node->left == NULL && node->right == NULL){
                //出栈。
                tStack.pop();
                res.push_back(node->val);
                pLastvisi = node;
                continue;
            }

            if(node->left == NULL && node->right != NULL){
                //右孩子访问就可以出栈，否则入栈右孩子。
                //确认左孩子已访问
                if(pLastvisi == node->right){
                    tStack.pop();
                    res.push_back(node->val);
                    pLastvisi = node;
                } else {
                    tStack.push(node->right);
                }
                continue;
            }

            if(node->right == NULL && node->left != NULL){
                if(pLastvisi == node->left){
                    tStack.pop();
                    res.push_back(node->val);
                    pLastvisi = node;
                } else {
                    tStack.push(node->left);
                }
                continue;
            }

            if(node->right != NULL && node->left != NULL){
                if(pLastvisi == node->right){
                    tStack.pop();
                    res.push_back(node->val);
                    pLastvisi = node;
                } else if(pLastvisi == node->left){
                    tStack.push(node->right);
                } else{
                    tStack.push(node->left);
                }
                continue;
            }        
        }
    }
```

# 层次遍历
使用队列做存储。

- 如何判断一层
  - levelLastNode记录一层的最后一个结点
  - 如果队列为空，没有下一层，结束。

- 易错点
  - 空结点不入队
  - 给新层次添加结果存储行

```C++
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> tQueue;
        vector<vector<int>> res;
        if(NULL != root){
            tQueue.push(root);
        }
        while(!tQueue.empty()){
            int size = tQueue.size();
            res.push_back(vector<int>());
            while(size-- > 0){
                TreeNode* node = tQueue.front();
                tQueue.pop();
                res.back().push_back(node->val);
                if(node->left){
                    tQueue.push(node->left);
                }
                if(node->right){
                    tQueue.push(node->right);
                }
            }
        }
        return res;
    }
```

```C++
    void levelOrderByQueue(TreeNode* root, vector<vector<int>>& res){
        if(root == NULL){
            return;
        }
        queue<TreeNode*> tQueue;
        tQueue.push(root);
        int indexOfLevel = 0;
        TreeNode* levelLastNode = root;
        res.clear();
        res.push_back(vector<int>());
        //如何判断一个层次开始 或结束
        //层次的结束结点知道:
        //第一层为根结点
        //其他层为，上一层最后一个结点时，队列中的最后一个非空结点。
        while(!tQueue.empty()){
            TreeNode* node = tQueue.front();
            tQueue.pop();//出队
            if(node == NULL){
                continue;
            }
            res[indexOfLevel].push_back(node->val);
            if(node->left){
                tQueue.push(node->left);
            }
            if(node->right){                
                tQueue.push(node->right);
            }
            //是否为层次最后一个结点
            if(node == levelLastNode){
                //下一层没数据了直接结束
                if(tQueue.empty()){
                    break;
                }
                //有数据为新一层做数据准备
                res.push_back(vector<int>());
                indexOfLevel++;
                levelLastNode = tQueue.back();
            }
        }
    }
```

无注解
```C++
    void leveOrderByQueue(TreeNode * root, vector<vector<int>> & res){
        if(NULL == root){
            return;
        }
        queue<TreeNode*> tQueue;
        TreeNode* levelLastNode = root;
        res.clear();
        res.push_back(vector<int>());
        int levelIndex = 0;
        tQueue.push(root);
        while(!tQueue.empty()){
            TreeNode* node = tQueue.front();
            tQueue.pop();
            if(node == NULL){
                continue;
            }
            res[levelIndex].push_back(node->val);
            if(node->left){
                tQueue.push(node->left);
            }
            if(node->right){
                tQueue.push(node->right);
            }
            if(node == levelLastNode){
                if(tQueue.empty()){
                    break;
                }
                levelLastNode = tQueue.back();
                res.push_back(vector<int>());
                levelIndex++;
            }
        }
    }
```

# 中序后序遍历序列构造树

leecode 106. 从中序与后序遍历序列构造二叉树
[https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal](https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal)


```C++
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int postIdx = postorder.size() - 1;
        unordered_map<int,int> inIdx_map;
        for(int i = 0; i < inorder.size(); i++){
            inIdx_map[inorder[i]] = i;
        }
        return buildTree(inorder, 0, inorder.size() - 1, inIdx_map, postorder, postIdx);
    }
    TreeNode * buildTree(vector<int>inorder, int L, int R, unordered_map<int,int> &inIdx_map,
                vector<int>& postorder,int &postIdx){
        if(L > R){
            return NULL;
        }
        int nodeVal = postorder[postIdx];
        postIdx--;
        TreeNode * node = new TreeNode(nodeVal);
        int inIdx = inIdx_map[nodeVal];
        //左右根--->根右左
        node->right = buildTree(inorder, inIdx + 1, R, inIdx_map, postorder, postIdx);
        node->left = buildTree(inorder, L, inIdx - 1, inIdx_map, postorder, postIdx);
        return node;
    }
```