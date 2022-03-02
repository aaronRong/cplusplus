#include <iostream>
#include <stdlib.h>
#include <memory>

using namespace std;
struct Family {
    string father = "father";
    string mother = "nother";
    string son = "son";
};

void shared_func(shared_ptr<Family> family) {
    cout << "function: " << __FUNCTION__ << ", family count: " << family.use_count() << endl;
}

void weak_func(weak_ptr<Family> family) {
    cout << "function: " << __FUNCTION__ << "family count: " << family.use_count() << endl;
}

void unique_func(unique_ptr<Family> family) {   // 如果实参不用std::move包裹，那么此处需要用引用
    cout << "function: " << __FUNCTION__ /*<< "family count: " << family.use_count()*/ << endl;
}

int main()
{
    shared_ptr<Family> ptr1(new Family());
    shared_ptr<Family> ptr2(ptr1);
    cout << "Result: " << endl;
    cout << "line: " << __LINE__
         << ", ptr1.use_count(): " << ptr1.use_count()
         << ", ptr2.use_count(): " << ptr2.use_count()
         << ", ptr2->son: " << ptr2->son << endl;

    shared_func(ptr2);  // 进入函数后，由于函数参数拷贝特性，count+1,如果是引用仍然不变
    weak_func(ptr2);    // 不管是不是引用，都不会增加

    weak_ptr<Family> ptr3(ptr2);    // ptr2为shared_ptr
    cout << "line: " << __LINE__
         << ", ptr1.use_count(): " << ptr1.use_count()
         << ", ptr2.use_count(): " << ptr2.use_count()
         << ", ptr3.use_count(): " << ptr3.use_count()
         << ", ptr3.lock()->son: " << ptr3.lock()->son << endl; // 注意访问方式

    Family family;
    shared_ptr<Family> ptr7 = make_shared<Family>(family);
    cout << "line: " << __LINE__
         << ", make_shared ptr7.use_count(): " << ptr7.use_count() << endl;

    unique_ptr<Family> ptr4(new Family());
    unique_func(std::move(ptr4));

    unique_ptr<Family> ptr5(new Family());
    shared_ptr<Family> ptr6(std::move(ptr5));   // unique_ptr初始化shared_ptr
    cout << "line: " << __LINE__ << ", ptr6->son: " << ptr6->son << endl;

    // 错误用法：
    // std::weak_ptr<int> w_ptr(new int(20)); 不可对weak_ptr直接普通指针初始化
    return 0;
}

// Result:
// line: 24, ptr1 count: 2, ptr2 count: 2, ptr2.son: son
// family count: 3
// family count: 2
// line: 34, ptr1 count: 2, ptr2 count: 2, ptr3 count: 2, ptr3.son: son

// -- 关于weak_ptr
// . lock().如果当前 weak_ptr 已经过期，则该函数会返回一个空的 shared_ptr 指针；反之，该函数返回一个和当前 weak_ptr 指向相同的 shared_ptr 指针。
// . expired().判断当前 weak_ptr 指针为否过期（指针为空，或者指向的堆内存已经被释放）。
// . use_count().查看指向和当前 weak_ptr 指针相同的 shared_ptr 指针的数量。
// . reset().将当前 weak_ptr 指针置为空指针。