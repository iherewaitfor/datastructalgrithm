#include <iostream>
#include <stack>
#include <string>
#include <list>
using namespace std;
class Solution {
public:
    void printstr(list<string> words) {
        for (auto& w : words) {
            cout << w << " ";
        }
        cout << endl;
    }
    int calculate(string s) {
        list<string> words;
        getwords(s, words); //���˿��ַ�
        //printstr(words);
        handlsub(words);    //ת������Ϊ0-
        //printstr(words);
        list<string> rpn = getrpn(words); //ȡ�ú�׺���ʽ
        //printstr(rpn);
        int r = calrpn(rpn); //�����׺���ʽ
        return r;
    }
    void handlsub(list<string>& words) {
        if (words.front() == "-") {
            words.push_front("0");
        }
        //1-(-2)ת��Ϊ1-(0-2)
        //-1-(-2)ת��Ϊ0-1-(0-2)
        auto it = words.begin();
        it++;
        for (; it != words.end(); ++it) {
            if (*(it) == "-") {
                --it;
                if (*(it) == "(") {
                    ++it;
                    words.insert(it, "0");
                }
                ++it;
            }
        }
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
    int calrpn(const list<string>& rpn) {
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
    list<string> getrpn(const list<string>& words) {
        list<string> rpn;
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
    void getwords(const string& s, list<string>& words) {
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
    //slo.calculate("20*(10/2)");
    slo.calculate("1-(     -2)"); //1-(0-2)
    slo.calculate("-1-(     -2)"); //1-(0-2)
    
}