# 链表
## 反转链表
力扣206[https://leetcode.cn/problems/reverse-linked-list/](https://leetcode.cn/problems/reverse-linked-list/)

原题
```
```

答题
```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* newFirst = NULL;
        ListNode* oldFirst = head;
        while(oldFirst != NULL){
            ListNode* tempNewFirst = newFirst;  //临时保存新队头
            ListNode* tempOldFirst = oldFirst->next;  //临时保存旧队头的下一个节点
            newFirst = oldFirst;  //旧队头变成新队头
            newFirst->next = tempNewFirst;  //新队头的下一个节点为临时新队头。
            oldFirst = tempOldFirst; //旧队头指向临时旧队头
        }
        return newFirst;
    }
};
```