#include <vector>

namespace fugo
{

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

int gcd(int a, int b)
{
    if (!a) {
        return b;
    }
    return gcd(b % a, a);
}

} // namespace fugo
