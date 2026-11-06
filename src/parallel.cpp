#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <atomic>

struct job
{
    int id;
    long long n;
};

bool is_prime(long long k)
{
    if (k < 2)
        return false;

    for (long long d = 2; d * d <= k; d++)
    {
        if (k % d == 0)
            return false;
    }

    return true;
}

long long count_primes(long long n)
{
    long long counter = 0;

    for (long long i = 2; i < n; i++)
    {
        if (is_prime(i))
            counter++;
    }

    return counter;
}

int main()
{
    // Reading Jobs
    std::ifstream file("jobs.txt");

    if (!file.is_open())
    {
        std::cerr << "Error Opening File!" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<job> jobs;

    while (getline(file, line))
    {
        std::istringstream stt(line);
        job j{};

        if (stt >> j.id >> j.n)
        {
            if (j.id < 0 || j.n < 0)
            {
                std::cerr << "Invalid Job: " << line << std::endl;
                continue;
                return 1;
            }

            jobs.push_back(j);
        }
        else
        {
            std::cerr << "Error Reading Line: " << line << "\n";
            continue;
        }
    }

    file.close();
    // Parallel Processing
    std::atomic<size_t> next{0};

    std::vector<long long> results(jobs.size());

    std::vector<std::thread> workers;

    auto start = std::chrono::steady_clock::now();

    // Creating 4 Workers
    for (int t = 0; t < 4; t++)
    {
        workers.emplace_back([&]()
                             {
            while (true)
            {
                // Get next Job
                size_t i = next.fetch_add(1);

                // Check if Jobs are finished
                if (i >= jobs.size())
                    break;

                // Process Job
                results[i] = count_primes(jobs[i].n);
            } });
    }

    auto end = std::chrono::steady_clock::now();

    // Printing Results
    for (size_t i = 0; i < jobs.size(); i++)
    {
        std::cout << "Job ID: " << jobs[i].id
                  << " | N: " << jobs[i].n
                  << " | Prime Count: " << results[i]
                  << std::endl;
    }

    // Execution Time
    auto duration = std::chrono::duration<double>(end - start);

    std::cout << "\nExecution Time: "
              << duration.count() << " seconds\n";

    return 0;
}