#include "compression.hpp"
namespace mobi
{
    std::string pd_compression::output_raw()
{
    return destination;
}



//TODO stringstream still would be cool.
void pd_compression::uncompress(uint8_t *src, size_t srcLen)
{
    if(!this->destination.empty())
        this->destination.clear();

    this->destination.reserve(srcLen*1.5);
    //

    uint8_t *srcEnd = src + srcLen;
    while (src < srcEnd ) 
    {

        unsigned c = *src++;

        if ((c >= 1) && (c <= 8)) 
        {
            while (c > 0) 
            {
                this->destination += *src++;
                --c;
            }
        } 
        else if (c < 128) 
        {

            if(c) {this->destination += c;} // !=0
        } 
        else if (c >= 192) 
        {
            this->destination  += ' ';
            this->destination  += c ^ 0x80;
        } 
        else 
        {
                c = (c << 8) | *src++;
                size_t back = (c >> 3) & 0x07ff;
                size_t n = (c & 7) + 3;
                std::string::iterator dst_back;
                if(src+n > srcEnd+8) //TODO: wat
                    throw not_palmdoc_compression_exception();
                dst_back = this->destination.end() - back;
                while (n > 0) 
                {
                    this->destination += *dst_back++;
                    --n;
                }
        }
    }
}


void no_compression::uncompress(uint8_t *src, size_t srcLen)
{
    if(!this->destination.empty())
        this->destination.clear();
    this->destination.append((char *)src, srcLen);
}


std::string no_compression::output_raw()
{
    return this->destination;
}
}
