- [二叉树](#二叉树)
- [前序遍历](#前序遍历)
  - [递归遍历](#递归遍历)
  - [迭代 by Stack](#迭代-by-stack)

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