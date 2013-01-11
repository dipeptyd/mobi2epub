#include "mobi/mobi.hpp"
#include "epub/epub.hpp"
//#include "optparse/OptionParser.h"
#include <boost/program_options.hpp>
#include <string>
//using optparse::OptionParser;
using mobi::mobireader;
using epub::mobi2epub;
using namespace std;
using namespace boost;
namespace po = boost::program_options;

class no_file_name_exception:public std::exception{
        po::options_description desc;
    public:
        no_file_name_exception(po::options_description desc):desc(desc){}
        po::options_description imdoingitwrong(){return desc;}

 };


po::variables_map op(int &ac, char **av);
