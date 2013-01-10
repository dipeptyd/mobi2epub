#include "mobi/mobi.hpp"
#include "epub/epub.hpp"
#include "optparse/OptionParser.h"
#include <string>
using optparse::OptionParser;
using mobi::mobireader;
using epub::mobi2epub;

class no_file_name_exception:public std::exception{};

optparse::Values  op(int &argc, char **argv)
{


OptionParser parser = OptionParser() \
                      .usage("\%prog filename [options]");

//parser.add_option("-d", "--debug")
                  //.action("store_false") .dest("debug") .set_default("0")
                  //.help("print debug information"); //TODO:

parser.add_option("-o", "--output") .dest("output") .action("store")
                  .help("output to FILE") .set_default("");


optparse::Values options = parser.parse_args(argc, argv);
std::vector<std::string> args = parser.args();


if(args.size()!=1)
{
    parser.print_help();
    throw no_file_name_exception();
}

options["filename"] = args[0];
return options;

}
