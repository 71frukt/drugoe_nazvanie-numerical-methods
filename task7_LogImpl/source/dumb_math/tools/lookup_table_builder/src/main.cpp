#include <iostream>

#include "cmd_options/cmd_options.hpp"

int main(const int argc, const char* argv[])
{
    lookup_table_builder::AppSettings settings;
    settings.parce(argc, argv);

    
}