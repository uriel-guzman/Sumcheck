#include "verifier.h"

int64_t booleanHypercubeSum(Poly& g) {
  int64_t sum = 0;

  for (int mask = 0; mask < (1 << g.numVariables); mask++) {
    vector<int64_t> x;

    for (int i = 0; i < g.numVariables; i++) {
      x.push_back((mask >> i) & 1);
    }

    sum += g.eval(x);
    sum %= F;
  }

  return sum;
}

pair<bool, bool> predict(Poly& g, int64_t H) {
  Prover prover(g, H);
  int64_t sum = booleanHypercubeSum(g);
  Verifier verifier;
  return {verifier.accept(prover), sum == H};
}

void exampleTest() {
  // Let g(x1, x2, x3) = 2 * x1^3 + x1 * x3 + x2 * x3
  // x1 is of degree 4, x2 and x3 are of degree 2
  Poly g(vector<int64_t>{4, 2, 2});
  g[{3, 0, 0}] = 2;
  g[{1, 0, 1}] = 1;
  g[{0, 1, 1}] = 1;
  auto [veredict, expectedVeredict] = predict(g, 12);
  cout << "Example test\n";
  cout << "Veredict: " << veredict << '\n';
  cout << "Expected veredict: " << expectedVeredict << '\n';
}

pair<Poly, int64_t> createTestCase(int maxTerms = 10,
                                   int maxNumVariables = 10,
                                   int64_t maxDeg = 10,
                                   int64_t maxCoef = 10) {
  int numVariables = random(1, maxNumVariables);
  vector<int64_t> deg(numVariables);

  for (auto& d : deg) {
    d = random(1, maxDeg);
  }

  int numTerms = random(
      1,
      min<int64_t>(
          maxTerms,
          accumulate(deg.begin(), deg.end(), int64_t(1), [&](int i, int j) {
            return i * j;
          })));

  Poly g(deg);

  auto genTerm = [&]() {
    vector<int64_t> term;

    for (int i = 0; i < numVariables; i++) {
      term.push_back(random(0, deg[i] - 1));
    }

    return term;
  };

  for (int i = 0; i < numTerms; i++) {
    vector<int64_t> term;

    do {
      term = genTerm();
    } while (g.count(term));

    g[term] = random(0, maxCoef);
  }

  // Random H, but not so random
  int64_t H = booleanHypercubeSum(g) + random(-5, +5);
  H += F;
  H %= F;
  return {g, H};
}

void runRandomizedTests(int numTests = 1000) {
  int confusionMatrix[2][2] = {};

  for (int it = 0; it < numTests; it++) {
    auto [g, H] = createTestCase();
    auto [veredict, expectedVeredict] = predict(g, H);
    confusionMatrix[veredict][expectedVeredict]++;
  }

  cout << setprecision(2) << fixed;
  cout << "True positives: " << (1.0 * confusionMatrix[1][1] / numTests * 100)
       << '\n';
  cout << "False positives: " << (1.0 * confusionMatrix[1][0] / numTests * 100)
       << '\n';
  cout << "True negatives: " << (1.0 * confusionMatrix[0][0] / numTests * 100)
       << '\n';
  cout << "False negatives: " << (1.0 * confusionMatrix[0][1] / numTests * 100)
       << '\n';
  cout << "Accuracy: "
       << (1.0 * confusionMatrix[0][0] + confusionMatrix[1][1]) / numTests * 100
       << '\n';
}

int main() {
  exampleTest();
  cout << '\n';
  runRandomizedTests();
  return 0;
}
