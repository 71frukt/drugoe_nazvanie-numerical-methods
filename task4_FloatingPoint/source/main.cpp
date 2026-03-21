#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <random>
#include <string>
#include <iomanip>

#include "dispersia_calculator.hpp"
#include "norm_distr_gen.hpp"
#include "cmd_options/cmd_options.hpp"

namespace {

template <std::floating_point T>
void TestVariance(std::ostream& output, size_t gen_num, std::mt19937& generator)
{
    for (size_t i = 1; i < gen_num; i++)
    {
        T mid = static_cast<T>(std::pow(10, i));
        T std_dev = 1.0f / mid;

        std::vector<T> norm_distr = BuildNormDistr(1000, mid, std_dev, generator);

        T var_fast    = VarianceiaFast   <T>(norm_distr);
        T var_twopass = VarianceiaTwoPass<T>(norm_distr);
        T var_onepass = VarianceiaOnePass<T>(norm_distr);

        output << std::left 
               << std::setw(10) << mid 
               << std::setw(10) << std_dev 
               << "| "
               << std::setw( 2) << " "
               << std::setw(15) << var_fast 
               << std::setw(15) << var_twopass 
               << std::setw(15) << var_onepass 
               << "\n";
    }
    
    output << std::string(70, '-') << "\n";
}

} // namespace

int main(const int argc, const char* argv[])
{
    std::cout << sizeof(float) << " "  << sizeof(double) << " "  << sizeof(long double) << " \n";

    AppSettings settings = {};
    if (settings.parce(argc, argv) == false)
        return 0;

    std::random_device rd;
    std::mt19937 generator(rd());

    *settings.ostream << std::left 
                      << std::setw(10) << "mid" 
                      << std::setw(10) << "deviation" 
                      << "| "
                      << std::setw( 2) << " "
                      << std::setw(15) << "Fast" 
                      << std::setw(15) << "TwoPass" 
                      << std::setw(15) << "OnePass" 
                      << "\n";

    *settings.ostream << std::string(30, '-') << " float "       <<  std::string(33, '-') << "\n";
    TestVariance<float>(*settings.ostream, settings.gen_num, generator);

    *settings.ostream << std::string(30, '-') << " double "      <<  std::string(32, '-') << "\n";
    TestVariance<double>(*settings.ostream, settings.gen_num, generator);

    *settings.ostream << std::string(30, '-') << " long double " <<  std::string(27, '-') << "\n";
    TestVariance<long double>(*settings.ostream, settings.gen_num, generator);

    return 0;
}