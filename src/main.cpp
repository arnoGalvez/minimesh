#include "options.hpp"
#include "viewer.hpp"
#include "import.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

void print_usage()
{
    std::cout << "A VTK-focused unstructured mesh manipulation mini-app\n";
    std::cout << "Usage:\n";
    std::cout << "  minimesh [OPTION...]\n";
    std::cout << "\n";
    std::cout << "  -v, --view Mesh file            View a mesh\n";
    std::cout << "  -t, --transform Transform file  Transform (merge, translate) a mesh\n";
    std::cout << "  -h, --help                      Print help\n";
}

int main( int argc, char **argv )
{
    std::string command;
    std::string file_name;

    if ( argc > 1 ) { command = argv[1]; }

    if ( ( argc <= 1 ) || command == "-h" || command == "--help" )
    {
        print_usage();
        return EXIT_SUCCESS;
    }

    if ( command == "-v" || command == "--view" )
    {
        if ( argc < 3 )
        {
            std::cerr << "Error: missing file\n";
            print_usage();
            return EXIT_FAILURE;
        }
        file_name = argv[2];
        auto &viewer = Viewer::Instance();
        viewer.View(file_name);
    }
    else if ( command == "-t" || command == "--transform" )
    {
        if ( argc < 3 )
        {
            std::cerr << "Error: missing file\n";
            print_usage();
            return EXIT_FAILURE;
        }
        file_name = argv[2];
        OptionsParser op( file_name );
        auto params = op.parse();
        params->Execute();
        
    }
    /*else if (command == "-c" || command == "--concatenate")
    {
        std::vector<std::string>(argc - 2);
        for (int i = 2; i < argc; ++i)
        {
            std::string file(argv[i]);

        }
    }*/
    else
    {
        std::cerr << "Error: unknown command\n";
        print_usage();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
