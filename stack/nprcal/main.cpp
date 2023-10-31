#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include<ctype.h>
#include<unordered_map>
using namespace std;

class Solution {
public:
    int calculate(string s) {
        trim(s);
        vector<string> rpn;
        stack<string> stk;//操作符栈
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                rpn.emplace_back("(");
            }
            else if (s[i] == ')') {
                while (!stk.empty() && stk.top() != "(") {
                    rpn.emplace_back(stk.top());
                    stk.pop();
                }
                stk.pop();//"("出栈
            }
            else if (isdigit(s[i])) {
                string num;
                while (i < s.size() && isdigit(s[i])) {
                    num.append(1, s[i++]);
                }
                i--;
                rpn.emplace_back(num);
            }
            else {
                if (s[i] == '-' && (i == 0 || s[i - 1] == '(')) {
                    rpn.emplace_back("0");
                }
                string op = s.substr(i, 1);
                while (!stk.empty() && stk.top() != "(" && needpop(op, stk.top())) {
                    rpn.emplace_back(stk.top());
                    stk.pop();
                }
                stk.push(op);
            }
        }
        while (!stk.empty()) {
            rpn.emplace_back(stk.top());
            stk.pop();
        }
         for(auto&v:rpn){
             cout << v << " ";
         }
         cout <<endl;
        return calrpn(rpn);
    }
private:
    bool isoperator(const string& op) {
        return op == "+" || op == "-" || op == "*" || op == "/";
    }
    int calab(int a, int b, string op) {
        switch (op[0]) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        }
        return 0;
    }
    int calrpn(vector<string>& rpn) {
        stack<int> s;
        for (auto& v : rpn) {
            if (isoperator(v)) {
                int b = s.top();
                s.pop();
                int a = s.top();
                s.pop();
                s.push(calab(a, b, v));
            }
            else {
                s.push(stoi(v));
            }
        }
        return s.top();
    }
    void trim(string& s) {
        int j = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != ' ') {
                s[j++] = s[i];
            }
        }
        s.resize(j);
    }
    bool needpop(const string& op, const string& stktopop) {
        static unordered_map<string, int> opmap = {
            {"+", 1},
            {"-", 1},
            {"*", 2},
            {"/", 2}
        };
        return opmap[stktopop] >= opmap[op];
    }
};
int main()
{
    Solution slo;
    //slo.calculate("2-1+2");
    //slo.calculate("(1+(4+5+2)-3)+(6+8)");    
    //slo.calculate("11+10");
    //slo.calculate("11+10*2");
    //slo.calculate("11+(20+10)*2");
    //slo.calculate("20*(10/2)");
    //string str = "1-(-2)";
    string str = "1+1";
    int r = slo.calculate(str); //1-(0-2)
    cout << str << "=" << r << endl;

    //slo.calculate("-1-(-2)"); //1-(0-2)
    
}