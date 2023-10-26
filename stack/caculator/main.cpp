#include <iostream>
#include <stack>
using namespace std;

int calAB(int a, int b, char op) {
    int r = 0;
    if (op == '+') {
        r = a + b;
    }
    else if (op == '-') {
        r = a - b;
    }
    else if (op == '*') {
        r = a *b;
    }
    else if (op == '/') {
        r = a / b;
    }
    cout << "calAB: " << a << op << b <<"="<<r << endl;
    return r;
}

int caldata(const string& str) {
    stack<int> datas;
    stack<char> ops;
    int opdata = 0;
    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        if (c >= '0' && c <= '9') {
            opdata = c - '0' + opdata * 10;
            if (i == str.size() - 1) {
                datas.push(opdata);
            }
        }
        else if (c == '*' || c == '/' || c == '+' || c == '-') {
            datas.push(opdata);
            opdata = 0;
            //2*  直接push
            //2*3*  //先计算2*3
            //1+2*3//直接push
            if (ops.size() > 0 &&(
                ( ops.top() == '*' || ops.top() == '/')||
                  (c == '+' || c=='-')
                )) {
                //操作栈非空，何时需要先计算栈内操作符
                //(1)当前操作符为+-时 。1+2+    或1*2+ 或 2/1*3
                //或(2)栈顶操作符为*/时， 1*2+ 或1*2*
                int b = datas.top();
                datas.pop();
                int a = datas.top();
                datas.pop();
                char opc = ops.top();
                ops.pop();
                int r = calAB(a, b, opc);
                datas.push(r);
            }
            ops.push(c);
        }
    }
    //1+2*3
    while (ops.size() > 0) {
        int b = datas.top();
        datas.pop();
        int a = datas.top();
        datas.pop();
        char opc = ops.top();
        ops.pop();
        int r = calAB(a, b, opc);
        datas.push(r);
    }
    return datas.top();
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
    int r = caldata(str);
    cout << "str:" << str << "=" << r << endl;
    cout << endl;
}