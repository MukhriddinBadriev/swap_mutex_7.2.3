#include <iostream>

#include <thread>
#include <mutex>
#include <chrono>

class Data {
public:
    std::mutex m;
    int a;
};

void lock_swap(Data* m1, Data* m2) {
    std::lock(m1, m2);
    std::lock_guard lg1{ m1,std::adopt_lock };
    std::lock_guard lg2{ m1,std::adopt_lock };
    std::swap(m1->a, m2->a);
}

void scoped_lock_swap(Data* m1, Data* m2) {
    std::scoped_lock s_l{ m1,m2 };
    std::swap(m1->a, m2->a);
}

void unique_lock_swap(Data* m1, Data* m2) {
    Data data;
    std::unique_lock<std::mutex> ul1{ m1,std::defer_lock };
    std::unique_lock<std::mutex> ul2{ m1,std::defer_lock };
    std::lock(ul1, ul2); 
    std::swap(m1->a, m2->a);
}

int main()
{
    Data data;
    data.a = 22;
    auto& m1 = data.m;
    auto& m2 = data.m;

    std::thread t1(lock_swap, m1, m2);
    std::thread t2(scoped_lock_swap, m1, m2);
    std::thread t3(unique_lock_swap, m1, m2);
    
    t1.join();
    t2.join();
    t3.join();

    return 0;
}