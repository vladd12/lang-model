#include <filesystem>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>

namespace ast
{
namespace generator
{

  struct field
  {
    std::string_view type;
    std::string_view name;
  };

  struct class_definition
  {
    std::string_view name;
    std::vector<field> fields;
  };

  static void define_type()
  {
  }

  static void define_class(                  //
    std::ofstream &output_file,              //
    const std::string_view &basename,        //
    const class_definition &class_definition //
  )
  {
    output_file << "class " << class_definition.name    //
                << basename << " : public " << basename //
                << "\n{\n"
                << "}\n\n";
  }

  static void define_ast(                        //
    std::filesystem::path &output_path,          //
    const std::string_view &basename,            //
    const std::vector<class_definition> &classes //
  )
  {
    output_path += fmt::format("{}.hpp", basename);
    if (std::filesystem::exists(output_path))
      std::filesystem::remove(output_path);

    std::ofstream output_file { output_path.c_str() };
    output_file <<                 //
      "namespace AST\n{\n\nclass " //
                << basename <<     //
      "\n{\n}\n\n";                //

    for (const auto &class_definition : classes)
    {
      define_class(output_file, basename, class_definition);
    }

    output_file << "}\n";
    output_file.close();
  }

} // namespace generator
} // namespace ast

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: ast_generator <output directory>\n";
    return 1;
  }
  std::string_view dir_path_str { argv[1] };
  std::filesystem::path dir_path { dir_path_str };
  if (!std::filesystem::is_directory(dir_path))
  {
    std::cerr << "Error: argument must be directory\n";
    return 2;
  }
  try
  {
    ast::generator::define_ast(dir_path, "Expression", //
      {
        { "Binary", { { "Expression", "left" }, { "Expression", "right" }, { "Token", "operator" } } },
        { "Grouping", { { "Expression", "expression" } } },
        { "Literal", { { "std::variant<std::string, unsigned long long, double, char>", "value" } } },
        { "Unary", { { "Expression", "right" }, { "Token", "operator" } } },
      } //
    );
  } catch (const std::exception &err)
  {
    std::cerr << "Catch exception: " << err.what() << '\n';
    return 3;
  }
  return 0;
}
