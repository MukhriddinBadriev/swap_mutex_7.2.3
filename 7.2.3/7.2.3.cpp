#include <iostream>

#include <thread>
#include <mutex>
#include <chrono>

class Data {
public:
    std::mutex m;
};

void lock_swap(Data* m1, Data* m2) {
    std::lock(m1, m2);
    std::swap(m1, m2);
}

void scoped_lock_swap(Data* m1, Data* m2) {
    std::scoped_lock s_l{ m1,m2 };
    std::swap(m1, m2);
}

void unique_lock_swap(Data* m1, Data* m2) {

    std::swap(m1, m2);
}

int main()
{
    return 0;
}