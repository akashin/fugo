#include <vector>
#include <numeric>

namespace fugo {

template<typename T>
std::vector<int> prefixFunction(T begin, T end)
{
    int n = std::distance(begin, end);
    std::vector<int> p(n, 0);
    int k = 0;

    for (int i = 1; i < n; ++i) {
        while (k > 0 && *(begin + k) != *(begin + i)) {
            k = p[k - 1];
        }
        if (*(begin + k) == *(begin + i)) {
            ++k;
        }
        p[i] = k;
    }

    return p;
}

template<typename T>
std::vector<int> findMatches(T sBegin, T sEnd, T tBegin, T tEnd)
{
    int n = std::distance(tBegin, tEnd);
    int m = std::distance(sBegin, sEnd);
    std::vector<int> matches;

    if (m == 0) {
        matches.resize(n);
        iota(matches.begin(), matches.end(), 0);
        return matches;
    }

    auto p = prefixFunction(sBegin, sEnd);

    int k = 0;
    for (int i = 0; i < n; ++i)
    {
        while (k > 0 && *(tBegin + i) != *(sBegin + k)) {
            k = p[k - 1];
        }
        if (*(tBegin + i) == *(sBegin + k)) {
            ++k;
        }
        if (k == m) {
            matches.push_back(i - m + 1);
            k = p[k - 1];
        }
    }
    return matches;
}

} // namespace fugo
