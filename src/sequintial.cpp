
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

struct job
{
    int id;
    long long n;
};

bool is_prime(long long k)
{
    if (k < 2)
    {
        return false;
    }

    for (long long d = 2; d * d <= k; d++)
    {
        if (k % d == 0)
        {
            return false;
        }
    }

    return true;
}

long long count_primes(long long n)
{
    long long counter = 0;

    for (long long i = 2; i < n; i++)
    {
        if (is_prime(i))
        {
            counter++;
        }
    }

    return counter;
}

int main()
{
    ifstream file("jobs.txt");

    if (!file.is_open())
    {
        cerr << "Error Opening file!" << endl;
        return 1;
    }

    vector<job> jobs;
    string line;

    // Phase 1: Read, validate, and store jobs
    while (getline(file, line))
    {
        istringstream stt(line);
        job j{};

        if (stt >> j.id >> j.n)
        {
            if (j.id < 0 || j.n < 0)
            {
                cerr << "REJECTED! ID and N can't be negative. "
                     << "Error line: " << line << endl;
                continue;
            }

            jobs.push_back(j);
        }
        else
        {
            cerr << "Invalid Line: " << line << endl;
        }
    }

    file.close();

    auto start = chrono::steady_clock::now();

    for (const job &x : jobs)
    {
        long long result = count_primes(x.n);

        cout << x.id << " " << result << endl;
    }

    auto end = chrono::steady_clock::now();

    auto ms = chrono::duration_cast<chrono::milliseconds>(
                  end - start)
                  .count();

    cout << "----------------------------------------" << endl;
    cout << "Total execution time: " << ms << " ms" << endl;

    cout << "---------- Job Summary ----------" << endl;

    for (const job &x : jobs)
    {
        cout << "ID: " << x.id << ", N: " << x.n << endl;
    }

    return 0;
}
