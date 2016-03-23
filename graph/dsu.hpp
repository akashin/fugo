#include <vector>
#include <numeric>
#include <cstdlib>

namespace fugo {

class DSU
{
public:
    DSU()
    { }

    DSU(int size)
    {
        resize(size);
    }

    void resize(int size)
    {
        parent.resize(size);
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int v)
    {
        if (v != parent[v]) {
            parent[v] = find(parent[v]);
        }
        return parent[v];
    }

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);

        if (a == b) {
            return false;
        }

        if (std::rand() & 1) {
            std::swap(a, b);
        }

        parent[a] = b;
        return true;
    }

private:
    std::vector<int> parent;

};

} // namespace fugo
