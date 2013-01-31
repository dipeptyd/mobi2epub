#pragma once
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>   //precompiled headers?
#include <vector>
#include "mobi_exceptions.hpp"
#include "mobi_headers.hpp"
#include "mobi_headers_handler.hpp"
#include "compression/compression.hpp"
namespace mobi
{

typedef std::vector<uint32_t> tdf_vector_32;
typedef std::string tdf_string;

struct st_c_section
{
    uint8 *content;
    unsigned size;
    st_c_section &operator=(st_c_section st);
    st_c_section():content(NULL){};
    ~st_c_section(){delete[] content;};
    st_c_section(unsigned x);
};

class mobireader{

    //#########################
    //####DEM HEADERS##########
    st_palmdoc_db db_header;
    st_palmdoc    pd_header;
    st_mobi     mobi_header;
    tdf_vector_32    section_offsets;
    st_c_section c_section;

    tdf_string input_file_name;

    //#########################
    //#########################
    compression *reader;
    std::ifstream *file;
    header_handler *handler;
    char *title;

    void load_file(std::string const &input_file_name);
    void parse_header();
    void set_compression();

    tdf_string get_section_uncompressed(unsigned sec) const;
public:
    mobireader(std::string const &input_file_name);
    mobireader(const mobireader &m);
    mobireader();
    ~mobireader();


    void set_default_title();
    void set_title(const char *);

    const char *get_title() const;


    tdf_string get_html() const;
    tdf_string get_file_name() const;


    void operator=(const mobireader &m);

};


}
