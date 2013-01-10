#include "compression_exceptions.hpp"
#include <string>
#include <cstdint>

namespace mobi
{
class compression 
{
    protected:
        std::string destination;
    public:
        virtual void uncompress(uint8_t *src, size_t srcLen) = 0;
        virtual std::string output_raw() = 0;
        //compression(){}
        //virtual compression clone() = 0;
};
class no_compression:public compression
{
    public:
    void uncompress(uint8_t *src, size_t srcLen);
    //compression(){}
    std::string output_raw(); //TODO

};

class hd_compression:public compression
{

};


class  pd_compression:public compression
{

    public:
    void uncompress(uint8_t *src, size_t srcLen);
    std::string output_raw();

};

}

