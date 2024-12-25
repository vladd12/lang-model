#include <lang-model/tools/interpreter.hpp>

int main(int argc, char *argv[])
{
    tools::Interpreter interpreter(tools::CommandLineArguments { argc, argv });
    interpreter.run();
    return 0;
}
