#include <boost/program_options.hpp>
#include <interpreter.hpp>

namespace opt = boost::program_options;

int main(int argc, char *argv[])
{
    opt::options_description desc("Interpreter options: ");
    desc.add_options()("file", opt::value<std::string>()->required(), "File with source code");
    return 0;
}
