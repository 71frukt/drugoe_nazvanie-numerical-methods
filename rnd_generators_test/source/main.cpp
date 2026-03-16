#include <cstddef>
#include <vector>
#include <boost/math/distributions/normal.hpp>
#include <random>

#include "RLogSU/logger.hpp"
#include "rnd_bit_generators/mrg32k3a.hpp"
#include "rnd_normal_generator/rnd_normal_generator.hpp"
#include "chi_sq_generator/chi_sq_generator.hpp"

#include "uniformity_tests/include/uniformity_tests/ks_uniformity_tester.hpp"
#include "two_level_test/two_level_tester.hpp"
#include "first_level_tests/disjoint_vectors.hpp"
#include "first_level_tests/fourier_tester.hpp" 


double RunTest(const std::vector<double>& u_data, const rnd_generators_test::IFirstLevelTester& lvl1)
{
    const size_t N = 100; 
    rnd_generators_test::TwoLevelTester lvl2tester(u_data);
    rnd_generators_test::KSTester u_tester;
    return lvl2tester.Run(lvl1, u_tester, N);
}

double UniformityDistrTest(const std::vector<double>& data, const rnd_generators_test::IFirstLevelTester& lvl1)
{
    return RunTest(data, lvl1);
}

double NormalDistrTest(const std::vector<double>& data, const rnd_generators_test::IFirstLevelTester& lvl1)
{
    if (data.empty())
        return 0.0;
    
    boost::math::normal_distribution<double> dist{0.0, 1.0};
    
    std::vector<double> u_data;
    u_data.reserve(data.size());
    
    for (double x : data)
        u_data.push_back(boost::math::cdf(dist, x));
    
    return RunTest(u_data, lvl1);
}

double ChiSquareDistrTest(const std::vector<double>& data, double df, const rnd_generators_test::IFirstLevelTester& lvl1)
{
    if (data.empty())
        return 0.0;
    
    boost::math::chi_squared_distribution<double> dist(df);
    
    std::vector<double> u_data;
    u_data.reserve(data.size());
    
    for (double x : data) u_data.push_back(boost::math::cdf(dist, x < 0 ? 0 : x));
        return RunTest(u_data, lvl1);
}


void PrintSuiteResults(const std::string& group_name,
                       const std::vector<double>& d_unif, 
                       const std::vector<double>& d_norm, 
                       const std::vector<double>& d_chi,
                       const rnd_generators_test::IFirstLevelTester& hyper,
                       const rnd_generators_test::IFirstLevelTester& fourier)
{
    RLSU_INFO("=== Results for {} ===", group_name);
    
    RLSU_INFO("--- Hypercube Test (2D) ---");
    RLSU_INFO("Unif: {}, Norm: {}, Chi: {}", 
              UniformityDistrTest(d_unif, hyper),
              NormalDistrTest(d_norm, hyper),
              ChiSquareDistrTest(d_chi, 3, hyper));

    RLSU_INFO("--- Fourier Test ---");
    RLSU_INFO("Unif: {}, Norm: {}, Chi: {}", 
              UniformityDistrTest(d_unif, fourier),
              NormalDistrTest(d_norm, fourier),
              ChiSquareDistrTest(d_chi, 3, fourier));
    RLSU_INFO("");
}

int main()
{
    const size_t num_blocks = 100;
    const size_t block_size = 4096; // 2^12 для стабильности Фурье
    const size_t total_size = num_blocks * block_size;

    size_t d_orig = std::max<size_t>(2, std::sqrt(total_size / 1000)); 
    rnd_generators_test::DisjointVectorsTester hypercube_test(2, d_orig);
    rnd_generators_test::FourierTester fourier_test(block_size);

    {
        std::vector<double> c_unif(total_size), c_norm(total_size), c_chi(total_size);
        rnd_generators::MRG32k3a gen_u(111), gen_n(444), gen_c(999);
        rnd_generators::NormalGenerator norm_gen;
        rnd_generators::ChiSqGenerator  chi_gen(3);

        for (size_t i = 0; i < total_size; i++) 
        {
            c_unif[i] = rnd_generators::NormalGenerator::ToCanonicalStrict(gen_u);
            c_norm[i] = norm_gen(gen_n);
            c_chi [i] = chi_gen (gen_c);
        }
        PrintSuiteResults("CUSTOM (MRG32k3a Source)", c_unif, c_norm, c_chi, hypercube_test, fourier_test);
    }

    {
        std::vector<double> m_unif(total_size), m_norm(total_size), m_chi(total_size);
        std::mt19937 mt_u(111), mt_n(444), mt_c(999);
        
        rnd_generators::NormalGenerator norm_gen;
        rnd_generators::ChiSqGenerator  chi_gen(3);

        std::uniform_real_distribution<double> dist_unif(0.0, 1.0);

        for (size_t i = 0; i < total_size; i++) 
        {
            m_unif[i] = dist_unif(mt_u);
            m_norm[i] = norm_gen(mt_n);
            m_chi [i] = chi_gen (mt_c);
        }
        PrintSuiteResults("MIXED (MT19937 Source + Custom Algos)", m_unif, m_norm, m_chi, hypercube_test, fourier_test);
    }

    {
        std::vector<double> s_unif(total_size), s_norm(total_size), s_chi(total_size);
        std::mt19937 engine(777);
        
        std::uniform_real_distribution<double> dist_u(0.0, 1.0);
        std::normal_distribution<double>      dist_n(0.0, 1.0);
        std::chi_squared_distribution<double> dist_c(3.0);

        for (size_t i = 0; i < total_size; i++) 
        {
            s_unif[i] = dist_u(engine);
            s_norm[i] = dist_n(engine);
            s_chi [i] = dist_c(engine);
        }
        PrintSuiteResults("STANDARD (MT19937 + STD Algos)", s_unif, s_norm, s_chi, hypercube_test, fourier_test);
    }

    return 0;
}