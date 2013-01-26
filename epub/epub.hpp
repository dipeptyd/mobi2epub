#pragma once
#include "epub_pre.hpp"
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
        
    boost::filesystem::path path_out;
    boost::filesystem::path path_tmp;
    mobi::mobireader m;

    mutable bool safe;
    mutable bool no_cleanup;
    mutable bool vanilla_out;

    void directory_structure() const;
    void cleanup() const;

    void gen_content_opf(std::stringstream &itemids, std::stringstream &itemrefs) const;
    void operator=(mobi2epub &m);
    mobi2epub(mobi2epub &m);

    void lin_zip() const;
    void win_zip() const; //TODO: externalize somehow?

    void set_out(std::string &s);
public:
    mobi2epub(const mobi::mobireader &m, bool safe=false, bool no_cleanup=false);
    void save_to_directory() const;
    void save_to_directory(std::string s);
    void directory_to_epub() const;
    void directory_to_epub(std::string s);

};


}
