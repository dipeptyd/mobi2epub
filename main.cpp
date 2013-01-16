#include "main.hpp"
int main(int argc, char **argv)
{

    po::variables_map vm;
    try {
    vm = op(argc, argv);
    }
    catch( no_file_name_exception& c)
    {
        std::cout << c.imdoingitwrong() << std::endl;
        return 1;
    }
    std::string filename = vm["input-file"].
        as <std::vector <std::string> >().front();


    std::string output;
    if(vm.count("output-file"))
    {
        output = vm["output-file"].
            as <std::vector <std::string> >().front();
    }

    mobireader m(filename);
    mobi2epub e(m);
    try
    {
    if(!output.empty())
        e.save_to_directory(output);
    else
        e.save_to_directory();
    }
    catch(epub::user_wants_out_exception)
    {
        return 1;
    }

    e.directory_to_epub();
    return 0;
}


po::variables_map op(int &ac, char **av)
{
    po::variables_map vm;
    po::options_description desc("mobitoepub input file [output file] [options]");
    desc.add_options()
    ("help,h", "produce help message")
    ("input-file,i", po::value< std::vector <std::string>  >(), "input file")
    ("output-file,o", po::value< std::vector <std::string>  >(), "output file");
;
    po::positional_options_description p;
    p.add("input-file", 1);
    p.add("output-file", 1);


        po::store(po::command_line_parser(ac, av).
        options(desc).positional(p).run(), vm);

    po::notify(vm);

    if (vm.count("help")) {
            throw no_file_name_exception(desc);//FIXME
    }


    if(vm.count("input-file"))
    {
        std::vector<std::string> ifile = vm["input-file"].as<std::vector <std::string> >();
        if (ifile.size() == 1)
            return vm;
        else
        {
            throw no_file_name_exception(desc);
        }
    }
    else
    {
    throw no_file_name_exception(desc);
    }
            return vm;
}
