#pragma once
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include "mobi_exceptions.hpp"
#include "mobi_headers.hpp"
#include "compression/compression.hpp"
namespace mobi
{
bool strcmp_is_a_worthless_pos(char x[], const char y[], int len);

struct st_c_section
{
    uint8 *content;
    unsigned size;
    st_c_section operator=(st_c_section st);
};

class mobireader{

    //#########################
    //####DEM HEADERS##########
    palmdoc_db_header db_header;
    palmdoc_header    pd_header;
    mobi_header       mobi_header_;
    std::vector<uint32>    header_offsets;
    st_c_section c_section;

    std::string input_file_name;

    //#########################
    //#########################
    compression *reader;
    std::ifstream *file;
    char *title;

    void parse_header();
    void set_compression();

    std::string get_section_uncompressed(int sec) const;
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
