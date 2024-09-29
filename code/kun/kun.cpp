#include <iostream> // 引入输入输出流库
#include <cstring>  // 引入字符串处理库

// 定义一个名为Chicken（鸡）的类
class Chicken
{
    private: // 私有成员
        int age = 24; // 年龄属性，默认值为24
        char *name = nullptr; // 名字属性，初始化为nullptr（空指针）
    public: // 公有成员
        // 默认构造函数
        Chicken() {};

        // 带年龄参数的构造函数
        Chicken(int _age) : age(_age) {};

        // 带年龄和名字参数的构造函数
        Chicken(int _age, const char *_name) : age(_age) 
        {
            int len = strlen(_name) + 1; // 计算名字的长度（包括结束符）
            name = new char[len]; // 动态分配内存来存储名字
            for (int i = 0; i < len; i++) // 将名字复制到成员变量
                name[i] = _name[i]; // 逐字符复制
        };

        // 复制构造函数
        Chicken(const Chicken &other) : age(other.age) 
        {
            if (other.name != nullptr) // 检查其他对象的名字是否为空
            {
                int len = strlen(other.name) + 1; // 计算名字的长度
                name = new char[len]; // 动态分配内存来存储名字
                for (int i = 0; i < len; i++) // 将其他对象的名字复制到当前对象
                    name[i] = other.name[i]; // 逐字符复制
            }
        };

        // 赋值运算符重载
        Chicken& operator=(const Chicken &other) 
        {
            if (this != &other) // 检查自赋值
            {
                delete[] name; // 释放当前对象的名字内存
                age = other.age; // 复制年龄
                // 复制名字
                if (other.name != nullptr) // 检查其他对象的名字是否为空
                {
                    int len = strlen(other.name) + 1; // 计算名字长度
                    name = new char[len]; // 动态分配内存来存储名字
                    for (int i = 0; i < len; i++) // 将其他对象的名字复制到当前对象
                        name[i] = other.name[i]; // 逐字符复制
                }
                else
                {
                    name = nullptr; // 如果其他对象的名字为空，则将当前对象的名字也设置为nullptr
                }
            }
            return *this; // 返回当前对象的引用
        }

        // 析构函数，释放动态分配的内存
        ~Chicken()
        {
            if (name != nullptr) // 如果名字不为空
                delete[] name; // 释放名字所占的内存
        }

        // 设置年龄的成员函数
        void setAge(int _age)
        {
            age = _age; // 将输入的年龄值赋给成员变量age
        }

        // 设置名字的成员函数
        void setName(const char *_name)
        {
            delete[] name; // 释放原来的名字内存
            int len = strlen(_name) + 1; // 计算输入名字的长度（包括结束符）
            name = new char[len]; // 动态分配内存来存储新的名字
            for (int i = 0; i < len; i++) // 将新的名字复制到成员变量
                name[i] = _name[i]; // 逐字符复制
        }

        // 获取名字的成员函数
        const char *getName() const
        {
            return name; // 返回名字指针
        }

        // 获取年龄的成员函数
        const int &getAge() const
        {
            return age; // 返回年龄的引用
        }
};

// 主函数，程序的入口点
int main()
{
    Chicken c(24, "Kunkun"); // 创建Chicken对象c，年龄为24，名字为"Kunkun"
    std::cout << "Hi, everyone! My name is " << c.getName() << ", I am " << c.getAge() << " years old." << std::endl; // 输出鸡的名字和年龄

    Chicken c2 = c; // 使用复制构造函数创建对象c2
    std::cout << "Hi, everyone! My name is " << c2.getName() << ", I am " << c2.getAge() << " years old." << std::endl; // 输出c2的名字和年龄

    Chicken c3; // 创建一个默认构造的对象c3
    c3 = c; // 使用赋值运算符重载进行赋值
    std::cout << "Hi, everyone! My name is " << c3.getName() << ", I am " << c3.getAge() << " years old." << std::endl; // 输出c3的名字和年龄
    
    return 0; // 返回0，表示程序正常结束
}