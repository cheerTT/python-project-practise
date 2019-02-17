#include "src/NumCpp.hpp"

#include <iostream>

using namespace std;

int main() {

    // 1 实训一个类似ndarray的N维数组对象，实现基础的N维数据存储和管理
    nc::NdArray<int> a1 = {{1, 1}, {1, 2}, {1, 3}};

    // 2 实现算法对数组执行元素级的计算和直接对数组执行数学运算功能
    nc::NdArray<int> a2 = {{-1, 1}, {1, -2}, {1, -3}};

    cout << a1 + 1 << endl;
    cout << a1 * 2 << endl;

    cout << a1.max(nc::Axis::ROW) << endl;
    cout << a1.min(nc::Axis::COL) << endl;

    cout << a1.argmax() << endl;
    cout << a1.argmin() << endl;

    // 3 提供一组对象方法，实现数组之间的计算功能：包括并不限于，数组拷贝，替换和矩阵相乘等
    nc::NdArray<int> a3 = {{1, 1}, {1, 1}};
    nc::NdArray<int> a4 = {{1, 1}, {1, 1}};
    cout << a3 * a4 << endl;  // 对应元素相乘
    cout << a3 + a4 << endl;  // 对应元素相加
    cout << nc::dot(a3, a4) << endl; // 矩阵乘法

    auto a5 = nc::copy(a3);
    cout << a5 << endl; // 数组拷贝

    auto a6 = nc::sin(a3); // 数学运算
    cout << a6 << endl;


    nc::NdArray<int> a7 = {{1, 1}, {1, 1}}; // 4 提供数组在磁盘上的读写操作
    cout << a7;

    // 5 包括并不限于实现线性代数运算，随机数生成等其他常用数学运算功能

    // 求行列式
    nc::NdArray<int> b1 = {{1, 2}, {3, 4}};
    cout << nc::linalg::det(b1) << endl;

    // 矩阵转置
    const nc::NdArray<int> b3 = {{1, 1, 1}, {2, 2, 2}, {3, 3, 3}};
    cout << nc::linalg::inv(b3) << endl;

    return 0;
}