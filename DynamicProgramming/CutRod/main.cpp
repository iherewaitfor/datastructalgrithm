#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;
class ExtendButtomUpCutRod {
public:
    void cut(vector<int>& arr, int n, vector<int> &result,vector<int> &scut ) {
        //����ռ����������Ľ⣬
        vector<int> r(n+1);
        vector<int> s(n+1); // the first cut index  of the max.
        r[0] = 0; //�������������⡣
        for (int j = 1; j <= n; j++) {
            //������������
            int q = INT_MIN;
            for (int i = 1; i <= j; i++) {
                // max(pn,R1+Rn-1, R2+Rn-2... Rn-1+R1)
                //ͨ������������Ž���ϳ�ԭ����⡣
                if (q < arr[i] + r[j - i]){
                    q = arr[i] + r[j - i];
                    s[j] = i;
                }
            }
            r[j] = q;
        }
        result.resize(n+1);
        scut.resize(n+1);
        std::copy(r.begin(), r.end(), result.begin());
        std::copy(s.begin(), s.end(), scut.begin());
    }
    void  printCutRod(vector<int>& arr, int n) {
        vector<int> result;
        vector<int> scut;
        cut(arr, n, result, scut);
        int i = n;
        while (i > 0) {
            cout<< scut[i] << " ";
            i = i - scut[i];
        }
    }
};
int main()
{
    vector<int> nums = {0,1,5,8,9,10,17,17,20,24,30 };
    ExtendButtomUpCutRod cutRod;
    cutRod.printCutRod(nums, 8);
    return 0;
}