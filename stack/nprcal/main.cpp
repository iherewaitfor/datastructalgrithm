#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;
vector<string> getrnp(const string& str, vector<string>& exps) {
    string temp;
    for (char c : str) {
        if (c != ' ') {
            temp.append(1, c);
        }
    }
    string word;
    for (char c : temp) {
        if (c == '(' || c == ')' || c == '*' || c == '/' || c == '+' || c == '-') {
            if (!word.empty()) {
                exps.emplace_back(word);
                word = "";
            }
            word.append(1, c);
            exps.emplace_back(word);
            word = "";
        }
        else {
            word.append(1, c);
        }
    }
    if (!word.empty()) {
        exps.emplace_back(word);
    }

    //ȡ�沨�����ʽ
    vector<string> nrp;
    stack<string> s;
    for (auto word : exps) {
        if (word == "+" || word == "-" || word == "(" ) {
            //��ջ
            if (!s.empty() &&(s.top() == "*" || s.top() == "/")) {
                //ȫ����ջ��* /�����ȼ����ߡ��ȼ���ջ�ڵĲ�����
                while (!s.empty()) {
                    nrp.emplace_back(s.top());
                    s.pop();
                }
            }
            s.push(word);//��ջ
        }
        else if (word == ")") {
            //��ջ��ֱ������"("
            while (s.top() != "(") {
                nrp.emplace_back(s.top());
                s.pop();
            }
            s.pop();//(��ջ
        }
        else if (word == "*" || word == "/") {
            s.push(word);
        }
        else {
            //��ֵ
            nrp.emplace_back(word);
        }
    }
    while (!s.empty()) {
        nrp.emplace_back(s.top());
        s.pop();
    }
    return nrp;
}
int calab(int a, int b, string c) {
    int r = 0;
    if (c == "+") {
        r = a + b;
    }
    else if (c == "-") {
        r = a - b;
    }
    else if (c == "*") {
        r = a * b;
    }
    else if (c == "/") {
        r = a / b;
    }
    cout << "calab:" << a << c << b << "=" << r << endl;
    return r;
}
int calnrp(vector<string>& nrp) {
    stack<int> s;
    for (auto& word : nrp) {
        if (word == "+" || word == "-" || word == "*" || word == "/") {
            int b = s.top();
            s.pop();
            int a = s.top();
            s.pop();
            int r = calab(a, b, word);
            s.push(r);
        }
        else {
            s.push(stoi(word));
        }
    }
    return s.top();
}
int main()
{
    vector<string> exps;
    vector<string> npr;
    //string nstr = "1+2";
    //string nstr = " 1 +2 ";
    string nstr = "9+(3-1)*3+10/2";
    npr = getrnp(nstr, exps);
    cout << nstr << endl;
    for (auto& s : exps) {
        cout << s;
    }
    cout << endl;

    for (auto& s : npr) {
        cout << s << " ";
    }
    cout << endl;
    cout << calnrp(npr) << endl;
}