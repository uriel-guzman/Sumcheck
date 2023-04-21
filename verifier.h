#include "prover.h"

struct Verifier {
  bool accept(Prover& prover) {
    for (int i = 0; i < prover.numVariables; i++) {
      int cursum = (prover.s(0, true) + prover.s(1, true)) % F;

      if (i == 0) {
        // First round: s[0](0) + s[0](1) must be equal to H
        if (cursum != prover.H) {
          return false;
        }
      } else {
        // Remaining rounds: s[i](0) + s[i](1) must be equal to s[i - 1](r[i])
        if (cursum != prover.s(prover.r.back(), false)) {
          return false;
        }
      }

      // send to the prover a random field element of size F
      prover.r.push_back(random(0, F - 1));
    }

    // Final check: previous g(r[0], r[1], ..., r[n - 1]) must be equal to s[n -
    // 1](r[n - 1])
    if (prover.s(prover.r.back(), false) != prover.eval(prover.r)) {
      return false;
    }

    return true;
  }
};

