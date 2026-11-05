#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

std::atomic<int> counter = 0;
void work(std::atomic<int> &c)
{
    for (int i = 0; i < 1000000; i++)
    {
        c++;
    }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1(work, std::ref(counter));
    std::thread t2(work, std::ref(counter));

    t1.join();
    t2.join();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
    std::cout << counter << std::endl;
}