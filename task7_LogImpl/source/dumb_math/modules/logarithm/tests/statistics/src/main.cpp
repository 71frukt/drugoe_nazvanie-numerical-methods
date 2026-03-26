#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>

#include "stat_generator.hpp"
#include "RLogSU/logger.hpp"

const std::string OFolderName = CURRENT_SRC_DIR "/data/";

namespace {
    template <typename T>
    void MakeStat(const std::string& type_name, const std::string& ofolder)
    {
        std::string stat_1toInf_name = ofolder + "stat_1toInf_" + type_name + ".txt";
        std::string stat_near1_name  = ofolder + "stat_near1_"  + type_name + ".txt";

        std::ofstream stat_1toInf(stat_1toInf_name);
        std::ofstream stat_near1 (stat_near1_name);

        if (!stat_1toInf.is_open())
            RLSU_THROW<std::runtime_error>(RLSU_FORMAT("file '{}' is not open!", stat_1toInf_name));

        if (!stat_near1.is_open())
            RLSU_THROW<std::runtime_error>(RLSU_FORMAT("file '{}' is not open!", stat_near1_name));

        std::cout << "cur file = " << ofolder + "stat_1toInf_" + type_name + ".txt" << std::endl;
        
        dumb_math::logarithm::tests::GenerateLnErrorUlpData_1toInf<T>(stat_1toInf);
        dumb_math::logarithm::tests::GenerateLnErrorUlpData_near1 <T>(stat_near1 );
    }
}


int main(const int argc, const char* argv[]) try
{
    ::MakeStat<float>      ("float",       OFolderName);
    ::MakeStat<double>     ("double",      OFolderName);
    ::MakeStat<long double>("long_double", OFolderName);
}

catch (std::runtime_error e)
{
    RLSU_LOG_RUNTIME_ERR(e);
}