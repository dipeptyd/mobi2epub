#include "mobi_headers_handler.hpp"
//#include "mobi_headers.hpp"
//#include <fstream>
namespace mobi
{

    header_handler::header_handler(std::ifstream *file)
    {
        this->file = file;

    }

    header_handler &header_handler::offset(unsigned offset)
    {
        this->file->seekg(offset);
        return *this;
    }
    header_handler &header_handler::skip(unsigned skip)
    {
        this->file->ignore(skip);
        return *this;
    }


    //template<typename type> //clearly too sober.
    //header_handler &header_handler::read(type &t)
    //{
        //file->read((char *) &t, sizeof(t));
        //bswap(t);
        //return *this;
    //}
    
    header_handler &header_handler::read(st_palmdoc_db &db_header)
    {
        file->read((char *) &db_header, sizeof(db_header));
        bswap(db_header);
        return *this;
    }
    header_handler &header_handler::read(uint32_t &i)
    {
        file->read((char *) &i, sizeof(uint32));
        bswap(i);
        return *this;
    }
    header_handler &header_handler::read(char &i)
    {
        file->read((char *) &i, 1);
        return *this;
    }
    header_handler &header_handler::read(st_palmdoc &pd_header)
    {
        file->read((char *) &pd_header, sizeof(pd_header));
        bswap(pd_header);
        return *this;
    }
    header_handler &header_handler::read(st_mobi &st_mobi_)
    {
        file->read((char *) &st_mobi_, MOBI_HEADER_LEN);
        bswap(st_mobi_);
        return *this;
    }
    
    header_handler &header_handler::read(char *i, uint32_t n)
    {
        file->read((char *) i, n);
        return *this;
    }
    header_handler &header_handler::read(uint8_t *i, uint32_t n)
    {
        file->read((char *) i, n);
        return *this;

    }
}
