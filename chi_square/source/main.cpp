#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>

#include "RLogSU/logger.hpp"
#include "rnd_bit_generators/mrg32k3a.hpp"
#include "chi_sq_generator/chi_sq_generator.hpp"

int main(const int argc, const char* argv[]) try
{
    size_t k = 5;
    
    if (argc > 1)
    {
        k = std::atol(argv[1]);
    }

    rnd_generators::MRG32k3a       engine(42);
    rnd_generators::ChiSqGenerator dist(k);

    const std::string chi_sq_res = "tmp/chi_sq_res.txt";
    std::ofstream ostream(chi_sq_res);

    for (size_t i = 0; i < 5000; ++i)
    {
        ostream << dist(engine) << "\n";
    }

    std::string command = "env -i HOME=$HOME DISPLAY=$DISPLAY PATH=$PATH XDG_RUNTIME_DIR=$XDG_RUNTIME_DIR "
                          "gnuplot -p -e \"filename='" + chi_sq_res + "'; k=" + std::to_string(k) + "\" "
                          "source/chi_sq_generator/utils/plot_chi.gp";

    int result = std::system(command.c_str());
    
    if (result != 0)
    {
        RLSU_THROW<std::runtime_error>("system call fail");
    }
}

catch (std::runtime_error &e)
{
    RLSU_LOG_RUNTIME_ERR(e);
}
