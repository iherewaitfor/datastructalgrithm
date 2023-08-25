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
    void inOrderByStack(TreeNode* root, vector<int> &res){
        stack<TreeNode*> tStack;
        tStack.push(root); //入栈。先入后出。出栈时再输出。左根右
        if(root){
            TreeNode * pLeft = root->left;;
            while(pLeft!=NULL){
                tStack.push(pLeft);
                pLeft = pLeft->left;
            }
        }
        while(!tStack.empty()){
            TreeNode* node = tStack.top();
            tStack.pop();//出栈
            if(node == NULL){
                continue;
            }
            //只在出栈时输出。
            res.push_back(node->val);
            //右孩子入栈：先进后出
            tStack.push(node->right);
            //右孩子的所有左孩子入栈。
            TreeNode * pLeft = NULL;
            if(node->right){
                pLeft = node->right->left;
            }
            while(pLeft != NULL){
                tStack.push(pLeft);//先进后出。出来时输出
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
        TreeNode * pLastvisi  = NULL; //上一个被访问的结点。
        unordered_set<TreeNode*> visitedNodes; //记录已访问过的结点
        while(!tStack.empty()){
            TreeNode* node = tStack.top();
            if(node==NULL){
                tStack.pop();
                pLastvisi = NULL;
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
                    pLastvisi = node;
                    continue;
                } else {
                    //处理左孩子。
                    tStack.push(node->right);
                }
            } else {
                //处理左孩子。
                tStack.push(node->left);
            }
        }
    }

```

非优化版本。通过穷举，判断左右孩子是否已被访问。

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