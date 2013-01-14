#pragma once
#include "mobi_headers.hpp"
#include <fstream>

namespace mobi
{
    class header_handler
    {
        std::ifstream *file;

        header_handler operator=(header_handler &x){};
        header_handler(header_handler &x){};
        public:
            header_handler &offset(unsigned offset);//TO
            header_handler(std::ifstream *file);
            header_handler &skip(unsigned skip);
            //TODO: can i make this less repetitive.
            header_handler &read(st_palmdoc_db &db_header);
            header_handler &read(st_palmdoc &pd_header);
            header_handler &read(st_mobi &st_mobi_);
            header_handler &read(uint32_t &i);
            header_handler &read(char &i);
            header_handler &read(char *i, uint32_t n);
            header_handler &read(uint8_t *i, uint32_t n);
    };
}
