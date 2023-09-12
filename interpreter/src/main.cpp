#include <boost/program_options.hpp>
//#include <interpreter.hpp>
#include <lang-model/promt.hpp>

int main(int argc, char *argv[])
{
    namespace opt = boost::program_options;
    opt::options_description desc("Interpreter options: ");
    desc.add_options()                                                  //
        ("file,-F", opt::value<std::string>(), "File with source code") //
        ("help,-H", "Show help message");                               //

    opt::variables_map vm;
    opt::store(opt::parse_command_line(argc, argv, desc), vm, /* utf8 = */ true);
    opt::notify(vm);

    // show help message
    if (vm.count("help"))
    {
        std::cout << desc << "\n";
    }
    // run file in interpreter
    else if (vm.count("file"))
    {
        std::string filepath(vm["file"].as<std::string>());
        // Debug purposes
        std::cout << filepath << '\n';
        // TODO: execute interpreter with selected file
    }
    // run promt
    else
    {
        tools::Promt promt;
        promt.run();
        // TODO: execute interpreter promt
    }

    return 0;
}
