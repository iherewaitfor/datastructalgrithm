# 数组和字符串

# 28. 找出字符串中第一个匹配项的下标
[leecode 28. 找出字符串中第一个匹配项的下标](https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/)

使用KMP算法。
- next数组
 - 由子串独立生成
 - 长度为子串的长度
 - 表示以当前下标元素为结尾的子串，前后缀相同的最大长度。
 - 
    |0|1|2|3|4|5|6|7|
    |:----|:----|:----|:----|:----|:----|:----|:----|
    |A|B|A|C|A|B|A|B|
    |0|0|1|0|1|2|3|2|
- 

```C++
    int strStr(string haystack, string needle) {
        int n = haystack.size();
        int m = needle.size();
        if(m == 0){
            return -1;
        }
        vector<int> next(m);
        for(int i = 1, j= 0; i < m; i++){
            if(j > 0 && needle[i] != needle[j]){
                j = next[j-1];
            }
            if(needle[i] == needle[j]){
                j++;
            }
            next[i] = j;
        }
        for(int i = 0, j = 0; i < n; i++){
            while(j > 0 && haystack[i] != needle[j]){
                j = next[j-1];
            }
            if(haystack[i] == needle[j]){
                j++;
            }
            if(j==m){
                return i - m+1;
            }
        }
        return -1;
    }
```