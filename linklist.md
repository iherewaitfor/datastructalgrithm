# 链表
## 206反转链表
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
## 25. K个一组翻转链表
K个一组翻转链表。力扣25。

[https://leetcode.cn/problems/reverse-nodes-in-k-group](https://leetcode.cn/problems/reverse-nodes-in-k-group)

```
```


## 92. 反转链表 II
反转链表 II
[https://leetcode.cn/problems/reverse-linked-list-ii](https://leetcode.cn/problems/reverse-linked-list-ii)

```C++
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        int l = left;
        int r = right;
        ListNode * preHead = new ListNode(-1); //头结点的前一结点。只改next
        preHead->next = head;
        ListNode * pcur = head;          //找到left后，只改next
        ListNode * preSubHead = preHead; //找到left后，只改next
        int findLeft = 1;
        while(findLeft != left){
            pcur = pcur->next;
            preSubHead= preSubHead->next;
            findLeft++;
        }
        //反链表
        int len = right - left;
        while(len-- > 0){
            //1,2,3,4
            //临时指针
            ListNode* oldHead = preSubHead->next;
            preSubHead->next = pcur->next; //1指向3
            pcur->next = pcur->next->next; //2指向4
            preSubHead->next->next = oldHead;//3指向oldhead2
            //1,3,2,4
        }
        return preHead->next;
    }
```
