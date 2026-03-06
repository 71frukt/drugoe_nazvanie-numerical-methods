#include <cstddef>
#include <iostream>
#include <string_view>
#include <memory>
#include <fstream>

struct AppSettings
{
public:
    bool parce(const int argc, const char *argv[]);

    std::ostream* ostream = nullptr;
    size_t gen_num = 10;

private:
    std::unique_ptr<std::ofstream> file_output_storage_;
};