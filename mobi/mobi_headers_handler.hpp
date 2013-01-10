#pragma once
#include "mobi_headers.hpp"
#include <fstream>

namespace mobi
{
    class header_handler
    {
        std::ifstream *file;

        void operator=(header_handler &x);
        header_handler(header_handler &x);
        public:
            header_handler offset(unsigned offset);
            header_handler(std::ifstream *file);
            void read(palmdoc_db_header &db_header);
            void read(palmdoc_header &pd_header);
            void read(mobi_header &mobi_header_);
            void read(uint32_t &i);
            void read(char &i);
            void read(char *i, uint32_t n);
            void read(uint8_t *i, uint32_t n);
    };
}
