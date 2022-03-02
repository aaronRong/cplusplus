#include <iostream>
#include <stdlib.h>
#include <memory>

using namespace std;

template <int32_t num>  // 为什么不用函数参数
void func_non_standard() {
    cout << "num: " << num << endl;
}

int main() {
    func_non_standard<5>();
    return 0;
}