#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <chrono> // 包含时间测量功能
#include <algorithm> // 包含 std::sort_heap，仅供测试
#include "heapsort.h"
using namespace std;


int main() {

    // 创建一个包含1000000个整数的vector，并初始化为正序序列
    std::vector<int> positive_sequence(1000000);
    //int positive_sequence(1000000);

    for (int i = 0; i < 1000000; ++i) {
        positive_sequence[i] = i;
    }
    std::cout << "The vector 未排序前的前9个数" << std::endl;
    printlist(positive_sequence,0,9);
    std::cout << std::endl;
    make_heap(positive_sequence.begin(),positive_sequence.end());
    //获取开始时间
    auto start = std::chrono::high_resolution_clock::now();
    heapSort(positive_sequence);
    // 使用 std::sort_heap对 vector 进行排序对比测试
   // std::sort_heap(positive_sequence.begin(), positive_sequence.end());
    // 获取结束时间点
    auto end = std::chrono::high_resolution_clock::now();
    // 计算持续时间（以微秒为单位）
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // 输出所用时间
    std::cout << "正序序列排序耗时 " << duration.count() << " 微秒." << std::endl;
    if (check(positive_sequence)) {
        std::cout << "The vector 是正确升序，前9个数示例" << std::endl;
        printlist(positive_sequence,0,9);
    } else {
        std::cout << "The vector 是错误升序." << std::endl;
    }

    printf("\n");
    //逆序排序测试
    std::reverse(positive_sequence.begin(), positive_sequence.end());
    std::cout << "The vector 未排序前的前9个数" << std::endl;
    printlist(positive_sequence,0,9);
    std::cout << std::endl;
    make_heap(positive_sequence.begin(),positive_sequence.end());
    //获取开始时间
    auto start1= std::chrono::high_resolution_clock::now();
    heapSort(positive_sequence);
    // 使用 std::sort_heap对 vector 进行排序对比测试
   // std::sort_heap(positive_sequence.begin(), positive_sequence.end());
    // 获取结束时间点
    auto end1 = std::chrono::high_resolution_clock::now();
    // 计算持续时间（以微秒为单位）
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);

    // 输出所用时间
    std::cout << "逆序序列排序耗时 " << duration1.count() << " 微秒." << std::endl;
    if (check(positive_sequence)) {
        std::cout << "The vector 是正确升序，前9个数示例" << std::endl;
        printlist(positive_sequence,0,9);
    } else {
        std::cout << "The vector 是错误升序." << std::endl;
    }
    printf("\n");
    //乱序序列测试
    // 初始化随机数生成器

    std::random_device rd;  // 用于获取随机数种子
    std::mt19937 gen(rd()); // 以rd()作为种子的Mersenne Twister伪随机数生成器
    std::uniform_int_distribution<> dis(0, 1000000); // 创建一个[0, 1000000]的均匀分布

    // 创建一个包含1000000个随机整数的vector
    std::vector<int> random_numbers(1000000);
    for (int& num : random_numbers) {
        num = dis(gen); // 使用分布对象dis和生成器对象gen来生成随机数
    }

    // 输出前个随机数作为示例（可选）
    std::cout << "The vector 未排序前的前9个数" << std::endl;
    printlist(random_numbers,0,9);
    std::cout << std::endl;
    make_heap(random_numbers.begin(),random_numbers.end());
    //获取开始时间
    auto start2 = std::chrono::high_resolution_clock::now();
    heapSort(random_numbers);
    // 使用 std::sort_heap对 vector 进行排序对比测试
    //std::sort_heap(random_numbers.begin(), random_numbers.end());
    // 获取结束时间点
    auto end2= std::chrono::high_resolution_clock::now();
    // 计算持续时间（以微秒为单位）
    auto duration2= std::chrono::duration_cast<std::chrono::microseconds>(end2- start2);
    std::cout << "乱序序列排序耗时 " << duration2.count() << " 微秒." << std::endl;
    if (check(random_numbers)) {
        std::cout << "The vector 是正确升序，，前9个数示例" << std::endl;
        printlist(random_numbers,0,9);
    } else {
        std::cout << "The vector 是错误升序." << std::endl;
    }

    printf("\n");
    //部分重复序列测试
    //创建一个部分重复序列
    for (int i = 0; i < random_numbers.size(); ++i) {
        if (i % 10 == 0) {
            random_numbers[i] = -1; // 每10个元素中的第一个设置为-1（重复值）
        } else {
            random_numbers[i] = std::rand() % 100; // 其他元素设置为0到99之间的随机数
        }
    }
    std::cout << "The vector 未排序前的前9个数" << std::endl;
    printlist(random_numbers,0,9);
    std::cout << std::endl;
    make_heap(random_numbers.begin(),random_numbers.end());
    //获取开始时间
    auto start3 = std::chrono::high_resolution_clock::now();
     heapSort(random_numbers);
    // 使用 std::sort_heap对 vector 进行排序对比测试
   // std::sort_heap(random_numbers.begin(), random_numbers.end());
    // 获取结束时间点
    auto end3= std::chrono::high_resolution_clock::now();
    // 计算持续时间（以微秒为单位）
    auto duration3= std::chrono::duration_cast<std::chrono::microseconds>(end3- start3);
    std::cout << "部分重复序列排序耗时 " << duration2.count() << " 微秒." << std::endl;
    if (check(random_numbers)) {
        std::cout << "The vector 是正确升序，，前9个数示例" << std::endl;
        printlist(random_numbers,0,9);
    } else {
        std::cout << "The vector 是错误升序." << std::endl;
    }

    printf("\n测试结束\n");






    return 0;
}
