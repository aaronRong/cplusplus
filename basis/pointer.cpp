#include <iostream>
#include <stdlib.h>

using namespace std;
int main()
{
    auto p = new int(10);   // new一个单值，数组大小为1，初始化为10
    auto q = new int[10];   // new一个数组，没有初始化
    auto r = new int[10](); // new一个数组，并初始化为0
    return 0;
}