#include <bits/stdc++.h>
using namespace std;

// Local debugging file. Not important
#ifdef LOCAL
#include "/home/uriel/ICPC/debug.h"
#else
#define debug(...)
#endif

// Finite field size
const int64_t F = 1e9 + 7;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Random number generator in the range [l, r]
int64_t random(int64_t l, int64_t r) {
  return uniform_int_distribution<int64_t>(l, r)(rng);
}

// Fast exponentiation modulo F
int64_t fpow(int64_t x, long long n) {
  int64_t r = 1;

  for (; n > 0; n >>= 1) {
    if (n & 1) {
      r = (r * x) % F;
    }

    x = (x * x) % F;
  }

  return r;
}

// Multivariable Polynomial class
struct Poly : map<vector<int64_t>, int64_t> {
  vector<int64_t> deg;
  int numVariables;

  Poly() {}

  Poly(vector<int64_t> deg) {
    this->deg = deg;
    numVariables = deg.size();
  }

  // int64_try every possible degree combination
  int64_t eval(const vector<int64_t>& x) {
    assert(x.size() == numVariables);
    int64_t sum = 0;

    for (const auto& [exp, coef] : *this) {
      int64_t termVal = coef;

      for (int i = 0; i < exp.size(); i++) {
        termVal *= fpow(x[i], exp[i]);
        termVal %= F;
      }

      sum += termVal;
      sum %= F;
    }

    return sum;
  }
};

