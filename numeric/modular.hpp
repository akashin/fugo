namespace fugo
{

int mulMod(int a, int b, int mod)
{
    return (a * 1ll * b) % mod;
}

void iMulMod(int& a, int b, int mod)
{
    a = mulMod(a, b, mod);
}

int fastPow(int base, int degree, int mod)
{
    int result = 1;
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


} // namespace fugo
