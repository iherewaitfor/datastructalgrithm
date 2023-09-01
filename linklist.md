# 链表
# 206反转链表
力扣206[https://leetcode.cn/problems/reverse-linked-list/](https://leetcode.cn/problems/reverse-linked-list/)

原题
```
```
使用preHead简化逻辑
```C++
    ListNode* reverseList(ListNode* head) {
        if(NULL == head){
            return head;
        }
        ListNode* preHead = new ListNode(-1);
        preHead->next = head;
        ListNode* pcur = head;
        while(pcur->next != NULL){
            ListNode* tempOldHead = preHead->next;//保存旧头部,一会新头需要指向该结点
            preHead->next = pcur->next;     //新头部
            pcur->next = pcur->next->next;  //当前结点往前走一个结点
            preHead->next->next = tempOldHead; //新头部的next指向旧头部
        }
        return preHead->next;
    }
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
# 25. K个一组翻转链表
K个一组翻转链表。力扣25。

[https://leetcode.cn/problems/reverse-nodes-in-k-group](https://leetcode.cn/problems/reverse-nodes-in-k-group)

```
```


# 92. 反转链表 II
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


## 21. 合并两个有序链表

[https://leetcode.cn/problems/merge-two-sorted-lists](https://leetcode.cn/problems/merge-two-sorted-lists)

```C++
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* preHead3 = new ListNode(-3); //合并链表preHead
        ListNode* pcur1 = list1;
        ListNode* pcur2 = list2;
        ListNode* pcur3 = preHead3;
        while(nullptr != pcur1 && nullptr != pcur2){
            if(pcur1->val < pcur2->val){
                pcur3->next = pcur1;
                pcur1 = pcur1->next;
                pcur3 = pcur3->next;
                pcur3->next = nullptr;
            } else {
                pcur3->next = pcur2;
                pcur2 = pcur2->next;
                pcur3 = pcur3->next;
                pcur3->next = nullptr;
            }
        }
        while(nullptr != pcur1){
            pcur3->next = pcur1;
            pcur1 = pcur1->next;
            pcur3 = pcur3->next;
            pcur3->next = nullptr;
        }
        while(nullptr != pcur2){
            pcur3->next = pcur2;
            pcur2 = pcur2->next;
            pcur3 = pcur3->next;
            pcur3->next = nullptr;
        }
        return preHead3->next;
    }
```

# 707. 设计链表

[https://leetcode.cn/problems/design-linked-list/](https://leetcode.cn/problems/design-linked-list/)

- 注意合理使用preHead结点
  - preHead = new ListNode(-1);
  - 能简化边界处理逻辑
- 

```C++
struct LinkNode{
    int val;
    LinkNode* next;
    LinkNode(int v):val(v),next(nullptr){}
};
class MyLinkedList {
public:
    MyLinkedList():head(nullptr),preHead(new LinkNode(-1)),size(0){

    }
    
    int get(int index) {
        if(index < 0 || index > size -1){
            return -1;
        }
        LinkNode * pcur = preHead;
        int i = -1;
        while(i++ != index){
            pcur = pcur->next;
        }
        return pcur->val;
    }
    
    void addAtHead(int val) {
        LinkNode* newNode = new LinkNode(val);
        newNode->next = head;
        preHead->next = newNode;
        head = preHead->next;
        size++;
    }
    
    void addAtTail(int val) {
        LinkNode * newNode = new LinkNode(val);
        LinkNode * pcur = preHead;
        //找队尾
        while(nullptr != pcur->next){
            pcur = pcur->next;
        }
        pcur->next = newNode;
        size++;
    }
    
    void addAtIndex(int index, int val) {
        LinkNode * newNode = new LinkNode(val);
        LinkNode * pre = preHead; 
        if(index < 0 || index > size ){
            //非法下标
            return ;
        }
        int i = 0;
        while(i++ != index){
            pre = pre->next;
        }
        newNode->next = pre->next;
        pre->next = newNode;
        size++;
    }
    
    void deleteAtIndex(int index) {
        LinkNode * pre = preHead; 
        if(index < 0 || index > size-1 ){
            //非法下标
            return ;
        }
        int i = 0;
        while(i++ != index){
            pre = pre->next;
        }
        pre->next = pre->next->next;
        size--;
    }
private:
    LinkNode* head;
    LinkNode* preHead;
    int size;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
```