#include <iostream>
#include <vector>
#include <random>
#include <chrono>

#include "interval_tree.hpp"

using namespace std;

template<typename T>
class SimpleRangeSum
{
public:
    SimpleRangeSum(int size) {
        values.assign(size, 0);
    }

    void incOne(int pos, T value)
    {
        values[pos] += value;
    }

    T getSum(int L, int R) {
        T sum = 0;
        for (int i = L; i < R; ++i) {
            sum += values[i];
        }
        return sum;
    }

private:
    vector<T> values;
};

using fugo::SumIntervalTree;

mt19937 gen(42);

int randomInt(int L, int R) {
    return uniform_int_distribution<int>(L, R)(gen);
}

void test(int iterations, int size)
{
    SumIntervalTree<long long> intervalTree(size);
    SimpleRangeSum<long long> simpleRangeSum(size);

    for (int i = 0; i < iterations; ++i) {
        int t = randomInt(0, 1);
        if (t == 0) {
            // Add new value
            int pos = randomInt(0, size - 1);
            int value = randomInt(0, 1e9);
            intervalTree.incOne(pos, value);
            simpleRangeSum.incOne(pos, value);
        } else {
            // Query for sum
            int R = randomInt(1, size - 1);
            int L = randomInt(0, R - 1);

            auto itSum = intervalTree.getSum(L, R);
            auto simpleSum = simpleRangeSum.getSum(L, R);
            if (itSum != simpleSum) {
                cout << "Error on query getSum(" << L << ", " << R << ")\n";
                cout << "itervalTree sum: " << itSum << "\n";
                cout << "simpleRangeSum sum: " << simpleSum << "\n";
                return;
            }
        }
    }
    cerr << "Test completed" << endl;
}

void benchmark(int iterations, int size)
{
    SumIntervalTree<long long> intervalTree(size);

    vector<pair<int, int>> queries(iterations);
    for (int i = 0; i < iterations; ++i) {
        queries[i] = make_pair(randomInt(0, size - 1), randomInt(0, 1e9));
    }

    chrono::high_resolution_clock clock;
    auto startTime = clock.now();
    for (int i = 0; i < iterations; ++i) {
        intervalTree.incOne(queries[i].first, queries[i].second);
    }
    auto finishTime = clock.now();
    auto elapsed = finishTime - startTime;
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(elapsed);
    cout << elapsed_ms.count() << endl;
}

int main()
{
    test(100000, 100000);
    benchmark(2000000, 10000000);
    return 0;
}

