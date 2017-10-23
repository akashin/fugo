namespace fugo {

template <typename T>
T mulMod(T a, T b, T mod)
{
    return (a * 1ll * b) % mod;
}

template <typename T>
T addMod(T a, T b, T mod)
{
    return ((a + b) % mod + mod) % mod;
}

template <typename T>
T divMod(T a, T b, T mod)
{
    while (a % b != 0) {
        a += mod;
    }
    a /= b;
    a %= mod;
    return a;
}

template <typename T>
void iMulMod(T& a, T b, T mod)
{
    a = mulMod(a, b, mod);
}

template <typename T>
void iAddMod(T& a, T b, T mod)
{
    a = addMod(a, b, mod);
}

template <typename T>
T fastPow(T base, T degree, T mod)
{
    T result = 1;
    while (degree) {
        if (degree & 1) {
            iMulMod(result, base, mod);
        }
        iMulMod(base, base, mod);
        degree >>= 1;
    }
    return result;
}

long long fastPow(int base, int degree)
{
    long long result = 1;
    while (degree) {
        if (degree & 1) {
            result *= base;
        }
        base *= base;
        degree >>= 1;
    }
    return result;
}

template <typename T>
T invMod(T value, T mod)
{
    return fastPow(value, mod - 2, mod);
}

template <typename T>
long long fact(T n, T mod)
{
    long long result = 1;
    for (T i = 1; i <= n; ++i) {
        result = (result * i) % mod;
    }
    return result;
}

} // namespace fugo
