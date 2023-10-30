#include <iostream>
#include <vector>
using namespace std;
int calculate(string s) {
    vector<int> stk;
    char preSign = '+';
    int64_t num = 0;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            num = num * 10 + c - '0';
        }
        if (!(c >= '0' && c <= '9') && c != ' ' || i == n - 1) {
            switch (preSign) {
            case '+':
                stk.push_back(num);
                break;
            case '-':
                stk.push_back(-num);
                break;
            case '*':
                stk.back() *= num;
                break;
            default:
                stk.back() /= num;
            }
            preSign = c;
            num = 0;
        }
    }
    int sum = 0;
    for (int v : stk) {
        sum += v;
    }
    return sum;
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
    int r = calculate(str);
    cout << "str:" << str << "=" << r << endl;
    cout << endl;
}