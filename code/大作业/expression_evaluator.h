#include<iostream>
#include<algorithm>
#include<stack>
#include<stdlib.h>
#include<vector>
#include<string>
#include<cmath>
#include<stdexcept> //异常类
#include <sstream>

using namespace std;

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}


bool hasPrecedence(char op1, char op2) {
    if (op1 == '*' || op1 == '/') return true;
    if (op1 == '+' || op1 == '-') return false;
    return (op2 == '+' || op2 == '-');
}
inline int type(char ch)
{
    if(ch>='0'&&ch<='9') return 0;
    if(ch=='.') return 0;
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/') return 1;
    if(ch=='('||ch==')') return 2;
    return -1;
}

bool Check_and_Preprocessing(string st)	//1、检查是否合法
{
    int LeftBracketsCount=0;
    for(int i=0; i<st.length(); i++) //（2）检查括号是否匹配
    {
        if(st[i]=='(') LeftBracketsCount++;
        if(st[i]==')') LeftBracketsCount--;
        if(LeftBracketsCount<0) return false;
    }
    if(LeftBracketsCount) return false;

    string tmpst;
    for(int i=0; i<st.length(); i++) //（3）预处理负号
    {
        if(st[i]=='-')
        {
            if(!i) tmpst+='0'; //a. -...
            else if(st[i-1]=='(') tmpst+='0'; //b. ...(-x)...
        }
        tmpst+=st[i];
    }
    st=tmpst;

    if(type(st[0])==1||st[st.length()-1]==1 || type(st[0])==-1) return false; //（4）检查运算符是否合法
    for(int i=1; i<st.length(); i++)
    {
        if(type(st[i])==-1) return false; //a.出现非法符号
        if(type(st[i])==1) //b.运算符两侧不为数或括号
        {
            if(type(st[i-1])==1||type(st[i+1])==1) return false; //b i.+*
            if(st[i-1]=='('||st[i+1]==')') return false; //b ii.(+)
        }
    }

    return true; //（5）过关！
}

string format(string str) { //格式化四则运算式

    for(int i = 0; i < str.length(); i++) {
        if(str[i] == '-') {
            if(i == 0) {

                str.insert(0,1,'0'); //对于首位为负数，增加为0-
                //cout << "结果1:" << str << endl;
            } else if((str[i-1] == '(') ||(str[i-1] == '+')) {
                str.insert(i,1,'0'); //修正为0-
                //cout << "结果1:" << str << endl;
            }
        }
        if(str[i]=='e')     //对于科学计算法 将e转换为10的次方 再插入字符串中
        {
            str[i]='*';
            //i=i+1;
            //int xx=i+1;
            //int aa=atoi(str[xx]);
            //cout << "结果1:" << str << endl;

            std::string str2;
            str2=str[i+1];
            int aa=std::stoi(str2);
            int bb=std::pow(10,aa);
            std::string str1=std::to_string(bb);
            //cout << "结果2:" << str1 << endl;
            int dd=i+1;
            str.insert(dd,str1);
            //cout << "结果3:" << str << endl;
            int cc=str1.size();
            dd=i+cc+1;
            str.erase(dd,1);
            // cout << "结果4:" << str << endl;
            i=i+cc;
        }

    }
    return str;
}
int prior(char c) {
    if(c == '+' || c == '-') {
        return 1;
    } else if(c == '*' || c == '/') {
        return 2;
    } else {
        return 0;
    }

}
vector<string> hz(string str) {
    vector<string> vs;
    stack<char> st;
    for(int i = 0; i < str.length(); i++) {
        string tmp = "";
        switch(str[i]) {
        case '+':
        case '-':
        case '*':
        case '/':
            if(st.empty() || st.top() == '(') {
                st.push(str[i]);
            } else {
                while(!st.empty() && prior(st.top()) >= prior(str[i]) ) {
                    tmp += st.top();
                    vs.push_back(tmp);
                    st.pop();
                    tmp = "";
                }
                st.push(str[i]);
            }
            break;
        case '(':
            st.push(str[i]);
            break;
        case ')':
            while(st.top() != '(') {
                tmp += st.top();
                vs.push_back(tmp);
                st.pop();
                tmp = "";
            }
            st.pop();
            break;
        default:
            if((str[i]>='0' && str[i]<='9')) {
                tmp += str[i];
                while(i+1<str.size() && str[i+1]>='0' && str[i+1]<='9'||str[i+1] == '.')
                {
                    tmp += str[i+1];//若是连续数字
                    ++i;
                }
                vs.push_back(tmp);
            }
        }
    }
    while(!st.empty()) {
        string tmp = "";
        tmp += st.top();
        vs.push_back(tmp);
        st.pop();
    }
    return vs;
}
double result(vector<string> bh) {
    stack<double> st;
    double num,op1,op2;
    for(int i = 0; i < bh.size(); i++) {
        string tmp = bh[i];
        if(tmp[0] >= '0'&&tmp[0] <= '9') {
            num = atof(tmp.c_str());
            st.push(num);
        }
        else if(bh[i]=="+")
        {
            op2=st.top();
            st.pop();
            op1=st.top();
            st.pop();
            st.push(op1+op2);
        }
        else if(bh[i]=="-")
        {
            op2=st.top();
            st.pop();
            op1=st.top();
            st.pop();
            st.push(op1-op2);
        }
        else if(bh[i]=="*")
        {
            op2=st.top();
            st.pop();
            op1=st.top();
            st.pop();
            st.push(op1*op2);
        }
        else if(bh[i]=="/")
        {
            op2=st.top();
            // std::cout << "OP2=" << op2<<endl;
            st.pop();
            op1=st.top();
            st.pop();
            if(op2==0)
            {
                // std::cout << "除零错误" <<endl;
                return NAN; //除零错误 返回NAN
                //st.push(op1/op2);
            }
            else
            {
                st.push(op1/op2);
            };

        }
    }
    return st.top();
}
void solve(string str) {
    // str = format(str);
    // if (isInfixValid(str)) {
    //     std::cout << "表达式正确。" << std::endl;
    //  } else {
    //     std::cout << "表达式错误。" << std::endl;
    //    return;
    // }
    //str = format(str);
    vector<string> bh = hz(str);
    double k = result(bh);
    if((int)k == k) {
        cout << "计算结果:" << k << endl;
        // std::cout << "表达式1。" << std::endl;
        //cout<<k<<endl;
    } else {
        if(std::isnan(k))
        {
            std::cout << "ILLEAGL出现除零错误" << std::endl;
        }
        else
        {
            cout << "计算结果:" << k << endl;

        };


        // printf("%d",k);
        //cout<<endl;
    }

}
