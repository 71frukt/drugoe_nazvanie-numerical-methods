#include "two_level_test/two_level_tester.hpp"
#include "first_level_tests/disjoint_vectors.hpp"
#include "uniformity_tests/include/uniformity_tests/ks_uniformity_tester.hpp"
#include <vector>
#include <random>

#include "RLogSU/logger.hpp"

#include "rnd_bit_generators/mrg32k3a.hpp"

int main()
{
    std::vector<double> data(10000);
    
    rnd_generators::MRG32k3a gen;

    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (double& val : data) {
        val = dist(gen);
    }

    rnd_generators_test::TwoLevelTester lvl2tester(data);
    rnd_generators_test::DisjointVectorsTester lvl1test(10);
    rnd_generators_test::KSTester u_tester;

    double res = lvl2tester.Run(lvl1test, u_tester, 100);

    RLSU_INFO("test result = {}\n", res);
}