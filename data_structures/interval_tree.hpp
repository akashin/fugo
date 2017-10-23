#include <vector>
#include <iostream>

namespace fugo {

template<typename T>
class SumIntervalTree
{
public:
    SumIntervalTree(int size) {
        size_ = size;
        int pow2 = 1;
        while (pow2 < size * 2) {
            pow2 *= 2;
        }
        nodes_.resize(pow2);
    }

    void incOne(int pos, T value)
    {
        //incOne(0, 0, size_, pos, value);
        incOneNonRecursive(pos, value);
    }

    T getSum(int L, int R)
    {
        return getSum(0, 0, size_, L, R);
    }

private:
    struct Node {
        T sum = 0;
    };

    void recalc(int v, int L, int R) {
        nodes_[v].sum = nodes_[v * 2 + 1].sum + nodes_[v * 2 + 2].sum;
    }

    void incOneNonRecursive(int pos, T value)
    {
        int L = 0;
        int R = size_;
        int v = 0;
        while (L + 1 != R) {
            int M = (L + R) / 2;
            nodes_[v].sum += value;
            if (pos < M) {
                R = M;
                v = v * 2 + 1;
            } else {
                L = M;
                v = v * 2 + 2;
            }
        }
        nodes_[v].sum += value;
    }

    void incOne(int v, int L, int R, int pos, T value)
    {
        if (L + 1 == R) {
            nodes_[v].sum += value;
            return;
        }

        int M = (L + R) / 2;
        if (pos < M) {
            incOne(v * 2 + 1, L, M, pos, value);
        } else {
            incOne(v * 2 + 2, M, R, pos, value);
        }
        recalc(v, L, R);
    }

    T getSum(int v, int L, int R, int QL, int QR) {
        if (L == QL && R == QR) {
            return nodes_[v].sum;
        }

        int M = (L + R) / 2;
        if (QR <= M) {
            return getSum(v * 2 + 1, L, M, QL, QR);
        } else if (QL >= M) {
            return getSum(v * 2 + 2, M, R, QL, QR);
        } else {
            return getSum(v * 2 + 1, L, M, QL, M) + getSum(v * 2 + 2, M, R, M, QR);
        }
    }

    int size_;
    std::vector<Node> nodes_;

};

} // namespace::fugo
