- [链表](#链表)
- [206反转链表](#206反转链表)
- [25. K个一组翻转链表](#25-k个一组翻转链表)
- [92. 反转链表 II](#92-反转链表-ii)
- [21. 合并两个有序链表](#21-合并两个有序链表)
- [707. 设计链表](#707-设计链表)
- [328. 奇偶链表](#328-奇偶链表)
- [146. LRU 缓存](#146-lru-缓存)
- [707. 设计链表（单链表）](#707-设计链表单链表)
- [707. 设计链表（双向链表）](#707-设计链表双向链表)

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


# 21. 合并两个有序链表

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

# 328. 奇偶链表
[https://leetcode.cn/leetbook/read/linked-list](https://leetcode.cn/leetbook/read/linked-list)

```C++
    ListNode* oddEvenList(ListNode* head) {
        if(nullptr == head || nullptr == head->next ||nullptr == head->next->next){
            return head;
        }
        ListNode* preHead1 = new ListNode(-1);
        preHead1->next = head;
        ListNode* pTail1 = head;
        ListNode* preHead2 = new ListNode(-2);//开始是空链表
        ListNode* pTail2 = preHead2;
        int index = 1;
        while(pTail1->next){
            if(index++ % 2 == 0){ 
                //说明要放到队列1的尾部
                pTail1 = pTail1->next;   
            } else {
                //要放到队列2
                pTail2->next = pTail1->next;
                pTail2 = pTail2->next;
                pTail1->next = pTail1->next->next;
            }
        }
        pTail1->next = preHead2->next;
        pTail2->next =nullptr;
        return preHead1->next;
    }
```


# 146. LRU 缓存
[https://leetcode.cn/problems/lru-cache](https://leetcode.cn/problems/lru-cache)

```C++
struct DListNode{
    int key;
    int val;
    DListNode* next;
    DListNode* pre;
    DListNode(int k, int v):key(k),val(v),next(nullptr),pre(nullptr){}
};
class LRUCache {
private:
    const int m_capacity;
    int m_size;
    vector<DListNode*> m_keymap;//结点的值为key, 
    DListNode* m_keyListHead;
    DListNode* m_keyListTail;
public:
    LRUCache(int capacity):m_capacity(capacity),m_size(0)
        ,m_keymap(vector<DListNode*>(10001,nullptr)){
        //使用了伪头结点和伪尾结点，简单操作逻辑
        m_keyListHead = new DListNode(-1,-1);
        m_keyListTail = new DListNode(-1,-1);
        m_keyListHead->next = m_keyListTail;
        m_keyListTail->next = m_keyListHead;//结点操作，前后都有非空结点
    }
    
    int get(int key) {
        if(m_keymap[key] == nullptr){
            return -1;
        }
        DListNode* keyNode = m_keymap[key];
        moveToHead(keyNode);
        return keyNode->val;
    }
    
    void put(int key, int value) {
        if(m_keymap[key] != nullptr){
            //已经包含该key了，不影响 大小 ，只移动key结点到链头
            DListNode* keyNode = m_keymap[key];
            keyNode->val = value;
            moveToHead(keyNode);
            return;
        }
        //空的情况
        //先插入新key
        DListNode* newNode = new DListNode(key, value);
        m_keymap[key] = newNode;
        addToHead(newNode);
        m_size++;
        if(m_size > m_capacity){
            //删掉队尾元素
            DListNode* removedNode = removeTail();
            m_keymap[removedNode->key] = nullptr;
            delete removedNode;
            m_size--;
        }
    }
private:
    void removeNode(DListNode* node) {
        node->pre->next = node->next; //前指向后
        node->next->pre = node->pre;  //后指向前
    }
    void addToHead(DListNode* node) {
        node->pre = m_keyListHead;     //先处理新结点
        node->next = m_keyListHead->next;
        m_keyListHead->next->pre = node;
        m_keyListHead->next = node;
    }
    void moveToHead(DListNode* node) {
        removeNode(node);
        addToHead(node);
    }
    DListNode* removeTail() {
        DListNode* node = m_keyListTail->pre;
        removeNode(node);
        return node;
    }
};
```

```C++
struct DListNode{
    int val;
    DListNode* next;
    DListNode* pre;
    DListNode(int v):val(v),next(nullptr),pre(nullptr){}
};
class LRUCache {
public:
    LRUCache(int capacity):m_capacity(capacity),m_size(0)
        ,m_keymap(vector<DListNode*>(10001,nullptr))
        ,m_dataMap(vector<int>(100001)){
        m_keyListHead = new DListNode(-1);
        m_keyListTail = new DListNode(-1);
        m_keyListHead->next = m_keyListTail;
        m_keyListTail->next = m_keyListHead;
    }
    
    int get(int key) {
        if(m_keymap[key] == nullptr){
            return -1;
        }
        DListNode* keyNode = m_keymap[key];
        moveToHead(keyNode);
        return m_dataMap[keyNode->val];
    }
    
    void put(int key, int value) {
        if(m_keymap[key] != nullptr){
            //已经包含该key了，不影响 大小 ，只移动key结点到链头
            DListNode* keyNode = m_keymap[key];
            m_dataMap[key] = value;
            moveToHead(keyNode);
            return;
        }
        //空的情况
        //先插入新key
        DListNode* newNode = new DListNode(key);
        m_keymap[key] = newNode;
        m_dataMap[key] = value;
        addToHead(newNode);
        m_size++;
        if(m_size > m_capacity){
            //删掉队尾元素
            DListNode* removedNode = removeTail();
            m_keymap[removedNode->val] = nullptr;
            delete removedNode;
            m_size--;
        }
    }
private:
    void removeNode(DListNode* node) {
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }
    void addToHead(DListNode* node) {
        node->pre = m_keyListHead;
        node->next = m_keyListHead->next;
        m_keyListHead->next->pre = node;
        m_keyListHead->next = node;
    }
    void moveToHead(DListNode* node) {
        removeNode(node);
        addToHead(node);
    }
    DListNode* removeTail() {
        DListNode* node = m_keyListTail->pre;
        removeNode(node);
        return node;
    }
private:
    const int m_capacity;
    int m_size;
    vector<DListNode*> m_keymap;//结点的值为key, 
    vector<int> m_dataMap;
    DListNode* m_keyListHead;
    DListNode* m_keyListTail;
};
```

# 707. 设计链表（单链表）
[https://leetcode.cn/problems/design-linked-list](https://leetcode.cn/problems/design-linked-list)

```C++
class MyLinkedList {
private:
    ListNode* preHead;
    int m_size;
public:
    MyLinkedList():m_size(0) {
        preHead = new ListNode(-1);
    }
    
    int get(int index) {
        if(m_size == 0 || index < 0 || index >m_size -1){
            return -1;
        }
        int i = 0;
        ListNode* pcur = preHead->next;
        while(i++ != index){
            pcur = pcur->next;
        }
        return pcur->val;
    }
    
    void addAtHead(int val) {
        addAtIndex(0, val);
    }
    
    void addAtTail(int val) {
        addAtIndex(m_size, val);
    }
    
    void addAtIndex(int index, int val) {
        if(index < 0 || index >m_size){
            return;
        }
        int i = 0;
        ListNode* pre = preHead;
        while(i++ != index){
            pre = pre->next;
        }
        ListNode * node = new ListNode(val);
        node->next = pre->next;
        pre->next = node;
        m_size++;
    }
    
    void deleteAtIndex(int index) {
        if(m_size == 0 || index < 0 || index >m_size-1){
            return;
        }
        int i = 0;
        ListNode* pre = preHead;
        while(i++ != index){
            pre = pre->next;
        }
        pre->next = pre->next->next;
        m_size--;
    }
};
```

# 707. 设计链表（双向链表）
[https://leetcode.cn/problems/design-linked-list](https://leetcode.cn/problems/design-linked-list)

```C++
struct DListNode{
    int val;
    DListNode* next;
    DListNode* prev;
    DListNode(int v):val(v),next(nullptr),prev(nullptr){}
};
class MyLinkedList {
private:
    DListNode* m_head;
    DListNode* m_tail;
    int m_size;
public:
    MyLinkedList():m_size(0) {
        m_head = new DListNode(-1);
        m_tail = new DListNode(-2);
        m_head->next = m_tail;
        m_tail->prev = m_head;
    }
    
    int get(int index) {
        if(index < 0 || index > m_size - 1  || 0 == m_size){
            return -1;
        }
        DListNode* pcur = m_head->next;
        int target = 0;
        while(target++ != index){
            pcur = pcur->next;
        }
        return pcur->val;
    }
    
    void addAtHead(int val) {
        DListNode* node = new DListNode(val);
        node->next = m_head->next;
        node->prev = m_head;
        m_head->next->prev = node;
        m_head->next = node;
        m_size++;
    }
    
    void addAtTail(int val) {
        DListNode* node = new DListNode(val);
        node->next = m_tail;
        node->prev = m_tail->prev;
        m_tail->prev->next = node;
        m_tail->prev = node;
        m_size++;
    }
    
    void addAtIndex(int index, int val) {
        if(index < 0 || index > m_size){
            return ;
        }
        if(index == m_size){
            addAtTail(val);
            return;
        }
        DListNode* pre = m_head;
        int target = 0;
        while(target++ != index){
            pre = pre->next;
        }
        DListNode* node = new DListNode(val);
        node->next = pre->next;
        node->prev = pre;
        pre->next->prev = node;
        pre->next = node;
        m_size++;
    }
    
    void deleteAtIndex(int index) {
        if(0 == m_size || index < 0 || index > m_size-1){
            return ;
        }
        DListNode* pcur = m_head->next;
        int target = 0;
        while(target++ != index){
            pcur = pcur->next;
        }
        pcur->prev->next = pcur->next;
        pcur->next->prev = pcur->prev;
        m_size--;
    }
};
```