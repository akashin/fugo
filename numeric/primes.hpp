#include <vector>

namespace fugo {

std::vector<int> findDivisors(int x)
{
    std::vector<int> divisors;
    for (int i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            divisors.push_back(i);
            if (i != x / i) {
                divisors.push_back(x / i);
            }
        }
    }
    return divisors;
}

std::vector<std::pair<int, int>> factorize(int x)
{
    std::vector<std::pair<int, int>> factors;
    for (int i = 2; i * i <= x; ++i) {
        int degree = 0;
        while (x % i == 0) {
            x /= i;
            ++degree;
        }
        if (degree > 0) {
            factors.push_back(std::make_pair(i, degree));
        }
    }
    if (x != 1) {
        factors.push_back(std::make_pair(x, 1));
    }
    return factors;
}

template <typename T>
bool isPrime(T x) {
    if (x == 1 || x == 2 || x == 3) {
        return true;
    }
    if (x % 2 == 0 || x % 3 == 0) {
        return false;
    }

    for (T i = 1; (i * 6 - 1) * (i * 6 - 1) <= x; ++i) {
        if (x % (6 * i - 1) == 0) {
            return false;
        }
        if (x % (6 * i + 1) == 0) {
            return false;
        }
    }
    return true;
}

template <typename T>
T gcd(T a, T b)
{
    if (!a) {
        return b;
    }
    return gcd(b % a, a);
}

} // namespace fugo
