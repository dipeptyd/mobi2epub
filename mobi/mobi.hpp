#pragma once
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include "mobi_exceptions.hpp"
#include "mobi_headers.hpp"
#include "mobi_headers_handler.hpp"
#include "compression/compression.hpp"
namespace mobi
{
bool strcmp_is_a_worthless_pos(char x[], const char y[], int len);

struct st_c_section
{
    uint8 *content;
    unsigned size;
    st_c_section operator=(st_c_section st);
    st_c_section(){};
    st_c_section(unsigned x);
};

class mobireader{

    //#########################
    //####DEM HEADERS##########
    st_palmdoc_db db_header;
    st_palmdoc    pd_header;
    st_mobi     mobi_header;
    std::vector<uint32>    header_offsets;
    st_c_section c_section;

    std::string input_file_name;

    //#########################
    //#########################
    compression *reader;
    std::ifstream *file;
    header_handler *handler;
    char *title;

    void parse_header();
    void set_compression();

    std::string get_section_uncompressed(unsigned sec) const;
public:
    mobireader(std::string &input_file_name);
    mobireader(const mobireader &m);
    mobireader();
    ~mobireader();


    void set_default_title();
    void set_title(const char *);

    const char *get_title() const;


    std::string get_html() const;
    std::string get_file_name() const {return input_file_name;}


    void load_file(std::string &input_file_name);
    void operator=(const mobireader &m);

};


}
