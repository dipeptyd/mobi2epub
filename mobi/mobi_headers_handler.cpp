#include "mobi_headers_handler.hpp"
namespace mobi
{

    header_handler::header_handler(std::ifstream *file)
    {
        this->file = file;

    }

    void header_handler::read(palmdoc_db_header &db_header)
    {
        file->read((char *) &db_header, PALMDOC_DB_HEADER_LEN);
        unretardify_header(db_header);
    }
    header_handler header_handler::offset(unsigned offset)
    {
        this->file->seekg(offset);
        return *this;
    }

    void header_handler::read(palmdoc_header &pd_header)
    {
        file->read((char *) &pd_header, PALMDOC_HEADER_LEN);
        unretardify_header(pd_header);
    }
    void header_handler::read(mobi_header &mobi_header_)
    {
        file->read((char *) &mobi_header_, MOBI_HEADER_LEN);
        unretardify_header(mobi_header_);
    }
    void header_handler::read(uint32_t &i)
    {
        file->read((char *) &i, sizeof(uint32));
        bswap(i);
    }
    void header_handler::read(char &i)
    {
        file->read((char *) &i, 1);
    }
    void header_handler::read(char *i, uint32_t n)
    {
        file->read((char *) i, n);
        i[n+1] = '\0';
    }
    void header_handler::read(uint8_t *i, uint32_t n)
    {
        file->read((char *) i, n);

    }
}
