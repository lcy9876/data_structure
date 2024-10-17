#include <iostream>
#include <assert.h>
#include "List.h" // 假设你的List类的头文件名为List.h

int main() {
    // 测试默认构造函数
    List<int> list1;
    assert(list1.size() == 0);
    std::cout << "默认构造函数测试通过!" << std::endl;

    // 测试初始化列表构造函数
    List<int> list2({1, 2, 3, 4, 5});
    assert(list2.size() == 5);
    assert(list2.front() == 1);
    assert(list2.back() == 5);

    const List<int> list2_const({1, 2, 3, 4, 5});
    assert(list2_const.size() == 5);
    assert(list2_const.front() == 1);
    assert(list2_const.back() == 5);

    std::cout << "初始化列表构造函数测试通过！" << std::endl;
    
    //测试拷贝构造函数
    List<int> list3(list2);
    assert(list3.size() == 5);
    assert(list3.front() == 1);
    assert(list3.back() == 5);
    std::cout << "测试拷贝构造函数测试通过！" << std::endl;

    // 测试赋值运算符
    List<int> list4 = list2;
    assert(list4.size() == 5);
    assert(list4.front() == 1);
    assert(list4.back() == 5);
    std::cout << "赋值运算符测试通过！" << std::endl;

    // 测试移动构造函数
    List<int> list5(std::move(list4));
    assert(list5.size() == 5);
    assert(list5.front() == 1);
    assert(list5.back() == 5);
    assert(list4.size() == 0); // 确保原列表被移动
    std::cout << "移动构造函数测试通过!" << std::endl;

    // 测试插入函数
    list1.push_back(100);
    list1.push_back(200);
    assert(list1.size() == 2);
    assert(list1.front() == 100);
    assert(list1.back() == 200);
    std::cout << "插入函数测试通过!" << std::endl;

    // 测试删除函数
    list1.pop_back();
    assert(list1.size() == 1);
    assert(list1.front() == 100);
    std::cout << "删除函数测试通过!" << std::endl;

    // 测试迭代器
    list1.push_back(200);
    list1.push_back(300);
    list1.push_back(400);
    list1.push_back(500);

    
    for (List<int>::iterator it = list1.begin(); it != list1.end(); ++it) {
        std::cout << "元素: " << *it << std::endl;
    }
 
    for (int elem : list1) {
        std::cout << "元素: " << elem << std::endl;
    }

    int expectedValues[] = {100, 200, 300, 400, 500};
    assert(std::equal(list1.begin(), list1.end(), expectedValues));

    const List<int> list6(list1);
    for (List<int>::const_iterator it = list6.begin(); it != list6.end(); ++it) {
        std::cout << "元素: " << *it << std::endl;
    }

    assert(std::equal(list6.begin(), list6.end(), expectedValues));
    
    std::cout << "迭代器测试通过！" << std::endl;

    // 测试清空函数
    list2.clear();
    assert(list2.size() == 0);
    assert(list2.empty() == true);
    std::cout << "清空函数测试通过！" << std::endl;

    // 测试赋值运算符
    list1 = list2;
    assert(list1.size() == 0);
    std::cout << "赋值运算符测试通过！" << std::endl;


    List<int> list7;
    list7.push_back(1);
    list7.push_back(2);
    list7.push_back(3);
    assert(list7.front() == 1);
    assert(list7.back() == 3);
    
    // 测试左值 push_front
    int value=10;
    list7.push_front(value);
    assert(list7.front() == 10); // 验证第一个元素

    // 测试右值 push_front
    list7.push_front(std::move(20));
    assert(list7.front() == 20); // 验证新的头部元素

    // 测试左值 push_back
    value=30;
    list7.push_back(value);
    assert(list7.back() == 30); // 验证最后一个元素

    // 测试右值 push_back
    value = 40;
    list7.push_back(std::move(value));
    assert(list7.back() == 40); // 验证新的尾部元素
    std::cout << "插入函数测试通过！" << std::endl;

    list7.pop_front();
    assert(list7.front() == 10); // 验证第一个元素

    list7.pop_back();
    assert(list7.back() == 30); // 验证第一个元素
    std::cout << "弹出函数测试通过！" << std::endl;

     List<int> list8;

    // 插入一些元素
    list8.push_front(10);
    list8.push_front(20);
    list8.push_front(30);

    // 测试插入左值
    auto itr = list8.begin();
    ++itr; // 移动到第二个元素
    value=40;
    auto insertedItr = list8.insert(itr, value);
    assert(*insertedItr == 40); // 验证插入的元素
    assert(*itr == 20); // 验证插入点后的元素

    // 测试插入右值
    itr = list8.begin();
    ++itr;
    insertedItr = list8.insert(itr, std::move(50));
    assert(*insertedItr == 50); // 验证插入的元素
    assert(*itr == 40); // 验证插入点后的元素
    std::cout << "插入指定位置测试通过！" << std::endl;

    // 删除测试
    list8.erase(list8.begin());
    list8.erase(list8.begin(), list8.end());
    assert(list8.size() == 0);
    std::cout << "删除测试通过！" << std::endl;

    std::cout << "所有测试通过！！!" << std::endl;
    return 0;
}