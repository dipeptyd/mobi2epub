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
            //TODO: can i make this less repetitive.
            void read(st_palmdoc_db &db_header);
            void read(st_palmdoc &pd_header);
            void read(st_mobi &st_mobi_);
            void read(uint32_t &i);
            void read(char &i);
            void read(char *i, uint32_t n);
            void read(uint8_t *i, uint32_t n);
    };
}
