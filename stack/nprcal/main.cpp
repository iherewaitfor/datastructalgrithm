#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;
class Solution {
public:
    void printstr(vector<string> words) {
        for (auto& w : words) {
            cout << w << " ";
        }
        cout << endl;
    }
    int calculate(string s) {
        vector<string> words;
        getwords(s, words);
        printstr(words);
        vector<string> rpn = getrpn(words);
        printstr(rpn);
        int r = calrpn(rpn);
        return r;


    }
    int calab(int a, int b, const string& opc) {
        int r = 0;
        if (opc == "+") {
            r = a + b;
        }
        else if (opc == "-") {
            r = a - b;
        }
        else if (opc == "*") {
            r = a * b;
        }
        else if (opc == "/") {
            r = a / b;
        }
        cout << "calab:" << a << opc << b << "=" << r << endl;
        return r;
    }
    int calrpn(const vector<string>& rpn) {
        stack<int> s;
        for (auto& v : rpn) {
            if (v == "+" || v == "-" || v == "*" || v == "/") {
                int b = s.top();
                s.pop();
                int a = s.top();
                s.pop();
                int r = calab(a, b, v);
                s.push(r);
            }
            else {
                s.push(stoi(v));
            }
        }
        return s.top();
    }
    vector<string> getrpn(const vector<string>& words) {
        vector<string> rpn;
        stack<string> s; //����ջ
        for (auto& v : words) {
            //���ȼ���������������ֱ�ӳ�ջ������Ƚ�
            //*/
            //+-
            //(
            if (v == "+" || v == "-") {
                //���ȼ��ϵ�,�ȼ���ջ���������������������(
                while (!s.empty() && (s.top() != "(")) {
                    rpn.emplace_back(s.top());
                    s.pop();
                }
                s.push(v);
            }
            else if (v == "*" || v == "/") {
                //���ȼ��ϸ�
                //ֻ��*��/���ȼ�����*/�ߡ�
                while (!s.empty() && (s.top() == "*" || s.top() == "/")) {
                    rpn.emplace_back(s.top());
                    s.pop();
                }
                s.push(v);
            }
            else if (v == ")") {
                //ֱ��ȡ��(
                while (s.top() != "(") {
                    rpn.emplace_back(s.top());
                    s.pop();
                }
                s.pop();
            }
            else if (v == "(") {
                s.push(v);
            }
            else {//��ֵ����ջ
                rpn.emplace_back(v);
            }
        }
        while (!s.empty()) {
            rpn.emplace_back(s.top());
            s.pop();
        }
        return rpn;
    }
    void getwords(const string& s, vector<string>& words) {
        string str;
        for (char c : s) {
            if (c != ' ') {
                str.append(1, c);
            }
        }
        string word;
        for (char c : str) {
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
                if (!word.empty()) {
                    words.push_back(word);
                    word = "";
                }
                word.append(1, c);
                words.push_back(word);
                word = "";
            }
            else {
                word.append(1, c);
            }
        }
        if (!word.empty()) {
            words.push_back(word);
            word = "";
        }
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
    slo.calculate("20*(10/2)");
}