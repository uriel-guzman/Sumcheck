# Sum-check protocol C++ implementation
This is my implementation of the sum-check protocol described here: https://people.cs.georgetown.edu/jthaler/ProofsArgsAndZK.pdf. This implementation assumes that the prover is not malicious since it's just an educational exercise to demonstrate the understanding of the algorithm.

# Running
For MacOS/Linux, just run the following line in your terminal. You will need g++ installed in your computer first.

    g++ --std=c++17 main.cpp && ./a.out

For Windows, you might want to take a look at this: https://stackoverflow.com/questions/11365850/run-c-in-command-prompt-windows.

Note: Since the prover is always honest in this example, the accuracy will always be 100%. I am still trying to understand how the prover could trick the verifier (eg. how does the protocol check that the prover is actually correctly evaluating a polynomial? Can the prover send more than one polynomial?) in order to account for the soundness of the protocol.


