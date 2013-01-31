#pragma once
#include "compression_exceptions.hpp"
#include <string>
#include <cstdint>

namespace mobi
{
class compression 
{
    compression(compression &c);
    compression &operator=(compression &c);
    protected:
        std::string destination;
    public:
    compression(){}
        virtual void uncompress(uint8_t *src, size_t srcLen) = 0;
        virtual std::string output_raw();
};
class no_compression:public compression
{
    public:
    void uncompress(uint8_t *src, size_t srcLen);

};

class hd_compression:public compression
{
    public:
    void uncompress(uint8_t *src, size_t srclen) {}
    hd_compression() { throw foo();}

};


class  pd_compression:public compression
{

    public:
    void uncompress(uint8_t *src, size_t srcLen);

};

}

