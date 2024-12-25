#include <lang-model/utils/interpreter.hpp>

int main(int argc, char *argv[])
{
  Utils::Interpreter interpreter({ argc, argv });
  interpreter.run();
  return 0;
}
