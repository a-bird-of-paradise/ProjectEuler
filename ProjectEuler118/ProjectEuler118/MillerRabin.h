#pragma once
// Miller-Rabin stuff
typedef uint64_t ULL;
typedef int64_t LL;

LL MultiplyMod(LL a, LL b, LL mod) { //computes a * b % mod
    ULL r = 0;
    a %= mod, b %= mod;
    while (b) {
        if (b & 1) r = (r + a) % mod;
        b >>= 1, a = ((ULL) a << 1) % mod;
    }
    return r;
}

template<typename T>
T PowerMod(T a, T n, T mod) {  //computes a^n % mod
    T r = 1;
    while (n) {
        if (n & 1) r = MultiplyMod(r, a, mod);
        n >>= 1, a = MultiplyMod(a, a, mod);
    }
    return r;
}

template<typename T>
bool isprime(T n) { //determines if n is a prime number
    const int pn = 5, p[] = { 2, 3, 5, 7, 11 }; //, 13, 17, 19, 23 }; // speed up: don't use too many primes
    for (int i = 0; i < pn; ++i)
        if (n % p[i] == 0) return n == p[i];
    if (n < p[pn - 1]) return 0;
    T s = 0, t = n - 1;
    while (~t & 1)
        t >>= 1, ++s;
    for (int i = 0; i < pn; ++i) {
        T pt = PowerMod<T> (p[i], t, n);
        if (pt == 1) continue;
        bool ok = 0;
        for (int j = 0; j < s && !ok; ++j) {
            if (pt == n - 1) ok = 1;
            pt = MultiplyMod(pt, pt, n);
        }
        if (!ok) return 0;
    }
    return 1;
}

