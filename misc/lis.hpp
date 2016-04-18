#include <vector>

namespace fugo
{

// Finds array of Longest Increasing Subsequence length ending at i-th position.
template <typename T>
std::vector<int> findLIS(const std::vector<T>& a)
{
    std::vector<int> lengthEndingAt(a.size());
    auto INF = *max_element(a.begin(), a.end());
    std::vector<T> smallestEnd(a.size(), INF);

    int currentLength = 0;
    for (int i = 0; i < a.size(); ++i) {
        auto it = lower_bound(
            smallestEnd.begin(), smallestEnd.begin() + currentLength, a[i]);

        if (*it == INF) {
            ++currentLength;
        }
        *it = a[i];
        lengthEndingAt[i] = currentLength;
    }

    return lengthEndingAt;
}

} // namespace fugo
