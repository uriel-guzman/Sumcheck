#include "util.h"

struct Prover {
  // Note: g is private, this emphasizes that only the prover knows how g looks
  // like
  private:
    Poly g;

  public:
    int64_t H;
    vector<int64_t> r;
    int numVariables;

    Prover(const Poly& g, int64_t H) {
      this->g = g;
      numVariables = g.numVariables;
      this->H = H;
    }

    int64_t eval(const vector<int64_t>& x) {
      return g.eval(x);
    }

    int64_t s(int x, bool current) {
      // s(x) = g(r[0], r[1], ..., r[i - 1], x, x[i + 1], x[i + 2], ..., x[n - 1])

      // Note: If current equals false, then s[i](x) is actually s[i - 1](x)
      // by removing the previous random field element r[i], this is important
      // because that's how the Verifier alternates between these two functions
      int64_t sum = 0;
      int variablesLeft = numVariables - int(r.size()) - current;

      // Generates all possible [0, 1] combinations for the remaining variables
      // x[i]
      for (int mask = 0; mask < (1 << variablesLeft); mask++) {
        vector<int64_t> input = r;

        if (!current) {
          input.pop_back();
        }

        input.push_back(x);

        for (int i = 0; i < variablesLeft; i++) {
          input.push_back((mask >> i) & 1);
        }

        sum += g.eval(input);
        sum %= F;
      }

      return sum;
    }
};

