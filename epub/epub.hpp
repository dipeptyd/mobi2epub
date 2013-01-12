#pragma once
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sstream>
#include <boost/format.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/algorithm/string.hpp>
#include "../mobi/mobi.hpp"
#include "epub_exceptions.hpp"
#include "tidyhtml_wrapper.hpp"


namespace epub
{
    extern std::string container_xml;
    extern std::string mimetype;
    extern std::string content_opf;
    extern std::string itemid;
    extern std::string itemref;


class mobi2epub
{
        
    boost::filesystem::path base;
    mobi::mobireader m;

    mutable bool safe;
    mutable bool no_cleanup;
    mutable bool vanilla_base;

    void directory_structure() const;
    void cleanup() const;

    void gen_content_opf(std::stringstream &itemids, std::stringstream &itemrefs) const;
    void operator=(mobi2epub &m);
    mobi2epub(mobi2epub &m);

    void set_base(std::string &s);
public:
    mobi2epub(const mobi::mobireader &m, bool safe=false, bool no_cleanup=false);
    void save_to_directory() const;
    void save_to_directory(std::string s);
    void directory_to_epub() const;
    void directory_to_epub(std::string s);

};


}
