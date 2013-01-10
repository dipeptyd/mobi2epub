#include "main.hpp"
int main(int argc, char **argv)
{

    optparse::Values options;
    try
    {
        options = op(argc, argv);
    }
    catch(no_file_name_exception)
    {
        return 1;
    }



    std::string dest;

    mobireader m(options["filename"]);
    mobi2epub e(m);
    try
    {
    if(options["output"].empty())
        e.save_to_directory();
    else
        e.save_to_directory(options["output"]);
    }
    catch(epub::user_wants_out_exception)
    {
        return 1;
    }

    e.directory_to_epub();
    return 0;
}
