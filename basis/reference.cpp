#include <iostream>
#include <stdlib.h>
#include <memory>

using namespace std;

int num = 10;

int &func(void) {
    return num;
}

int main() {
    cout << "Result: " << endl;
    cout << "[before].num: " << num << endl;
    func() = 20;
    cout << "[after].num: " << num << endl;
    return 0;
}

// Result:
// [before].num: 10
// [after].num: 20