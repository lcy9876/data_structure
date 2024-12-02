#include<iostream>
#include<algorithm>
#include<stack>
#include<stdlib.h>
#include<vector>
#include<string>
#include<cmath>
#include<stdexcept> //异常类
#include <sstream>
#include "expression_evaluator.h"
using namespace std;



int main() {
    string str;

    while(true) {
        cout << "输入等式:";
        std::getline(std::cin,str);

        str = format(str);
        if(!Check_and_Preprocessing(str))
        {
            printf("ILLEAGL运算式格式错误\n");

        }
        else {

            solve(str);
        }


    }

    return 0; // 程序正常结束返回0
}
