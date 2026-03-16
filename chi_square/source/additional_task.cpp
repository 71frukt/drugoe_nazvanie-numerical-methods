#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

#include "RLogSU/logger.hpp"
#include "bivariate_normal_generator/bivariate_normal_generator.hpp"
#include "rnd_bit_generators/mrg32k3a.hpp"

double CalculatePearsonCorrelation(const std::vector<std::pair<double, double>>& data)
{
    double sum_x  = 0.0;
    double sum_y  = 0.0;
    double sum_xy = 0.0;
    double sum_x2 = 0.0;
    double sum_y2 = 0.0;
    
    size_t n = data.size();

    for (const auto& p : data)
    {
        sum_x  += p.first;
        sum_y  += p.second;
        sum_xy += p.first  * p.second;
        sum_x2 += p.first  * p.first;
        sum_y2 += p.second * p.second;
    }

    double numerator = n * sum_xy - sum_x * sum_y;
    double denominator = std::sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_y2 - sum_y * sum_y));
    
    return (denominator == 0.0) ? 0.0 : numerator / denominator;
}

static std::string to_fixed(double val, int precision = 2)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << val;
    return ss.str();
}

void TestAndPlotBivariate(double target_rho, const std::string& filename, const std::string& title)
{
    const size_t num_samples = 10000;

    const double mu_x    = 0.0;
    const double mu_y    = 0.0;
    const double sigma_x = 1.0;
    const double sigma_y = 1.0;

    rnd_generators::MRG32k3a engine(42); 
    rnd_generators::BivariateNormalGenerator biv_gen(mu_x, mu_y, sigma_x, sigma_y, target_rho);

    std::vector<std::pair<double, double>> data;
    data.reserve(num_samples);

    std::ofstream out(filename);

    for (size_t i = 0; i < num_samples; ++i)
    {
        auto [x, y] = biv_gen(engine);
        data.push_back({x, y});
        out << x << " " << y << "\n";
    }
    out.close();

    double emp_rho = CalculatePearsonCorrelation(data);
    std::cout << "Target rho: " << target_rho 
              << " | Empirical rho: " << emp_rho 
              << " | Error: " << std::abs(target_rho - emp_rho) << "\n";

    std::string t_rho_str = to_fixed(target_rho);
    std::string e_rho_str = to_fixed(emp_rho);

    std::string gnuplot_cmd = 
        "env -u LD_LIBRARY_PATH -u GTK_PATH -u QT_PLUGIN_PATH /usr/bin/gnuplot -p -e \""
        "set title '" + title +
        "\nTheoretical rho = " + t_rho_str + 
        "\nEmpirical   rho = " + e_rho_str + "'; "
        "set xlabel 'X'; set ylabel 'Y'; "
        "set grid; "
        "set size ratio -1; "
        "plot '" + filename + "' using 1:2 with points pt 7 ps 0.1 lc rgb 'blue' title 'Data'\"";

    int result = std::system(gnuplot_cmd.c_str());

    if (result != 0)
    {
        RLSU_THROW<std::runtime_error>("system call fail");
    }
}

int main()
{
    std::cout << "Starting bivariate normal generation tests...\n\n";

    TestAndPlotBivariate(0.0, "tmp/biv_rho_0.txt", "Independent Normal Variables");

    TestAndPlotBivariate(0.8, "tmp/biv_rho_pos.txt", "Positive Correlation");

    TestAndPlotBivariate(-0.8, "tmp/biv_rho_neg.txt", "Negative Correlation");

    return 0;
}