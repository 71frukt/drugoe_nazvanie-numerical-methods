#include "cmd_options/cmd_options.hpp"
#include "cxxopts.hpp"
#include "RLogSU/logger.hpp"
#include <string>

bool AppSettings::parce(const int argc, const char *argv[])
{
    cxxopts::Options options("tenpiler");

    options.add_options()
        ("o,output" , "Path to output"                                          , cxxopts::value<std::string>())
        ("n,gen_num", "number of generated arrays for each type, each algorithm", cxxopts::value<std::size_t>())
        ("h,help"   , "SOS")
        ;

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return false;
    }

    //-------------------------output-----------------------------------------------------------

    if (result.count("output"))
    {
        std::string output_filename = result["output"].as<std::string>();

        file_output_storage_ = std::make_unique<std::ofstream>(output_filename);

        if (!file_output_storage_->is_open())
        {
            throw std::runtime_error("Could not open file: '" + output_filename + "'");
        }
        
        ostream = file_output_storage_.get();
    }

    else
    {
        ostream = &std::cout;
    }



    //-------------------------gen_num-------------------------------------------------------------
    if (result.count("gen_num"))
    {
        gen_num = result["gen_num"].as<size_t>();
    }

    return true;
}
