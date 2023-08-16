#include <iostream>
#include <thread>
using namespace std;

void thread_func_1(int v)
{

    for (int i = 0; i < 5; i++)
    {
        std::cout << v << " thread_func_1 i:" << i << endl;
    }
}

void thread_func_2(int v)
{

    for (int i = 0; i < 5; i++)
    {
        std::cout << v << " thread_func_2 i:" << i << endl;
    }
}

int main()
{
    thread t1(thread_func_1, 1);
    thread t2(thread_func_2, 3);

    t1.join();
    t2.join();

    return 0;
}
