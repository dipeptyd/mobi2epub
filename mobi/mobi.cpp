#include "mobi.hpp"

namespace mobi
{
std::ostream& errdbg = std::cout;

st_c_section::st_c_section(unsigned x)
{
    this->size = x;
    this->content = new uint8_t[x];
}
st_c_section &st_c_section::operator=(st_c_section st)
{
    this->size = st.size;
    this->content = new uint8[st.size];
    memcpy(this->content, st.content, st.size);

    return *this;
}



mobireader::mobireader():reader(0),file(0),title(0){}

mobireader::mobireader(std::string const &input_file_name)\
:c_section(8000),input_file_name(input_file_name),reader(0),file(0)\
    ,title(0)

{
    this->load_file(this->input_file_name);
    this->parse_header();

}
mobireader::mobireader(const mobireader &m)
{
    *(this) = m; //TODO: is this a trap?

}
void mobireader::operator=(const mobireader &m)
{

    this->mobi_header     = m.mobi_header;
    this->section_offsets   = m.section_offsets;

    this->input_file_name  = m.input_file_name;
    this->load_file(this->input_file_name);

    this->pd_header = m.pd_header;
    this->db_header = m.db_header;
    this->set_compression();

    this->c_section = (m.c_section);

    this->set_title(m.get_title());

    
}

mobireader::~mobireader()
{
    delete reader;
    delete file;
    delete[] title;
    delete handler;
}

void mobireader::parse_header()
{

    this->handler->read(db_header);

  if(strncmp(db_header.type,MOBI_TYPE,8)!=0)
      throw invalid_file_exception();

    uint32 section_offset;
    for(int i=0;i<db_header.num_records;i++)
    { //TODO
        this->handler->read(section_offset).skip(sizeof(uint32_t));
        section_offsets.push_back(section_offset);
    }
    this->handler->offset(section_offsets[0]).read(pd_header);
    this->handler->read(mobi_header);
    this->set_compression();
    this->set_default_title();

}

void mobireader::set_title(const char *s)
{
    if(title != NULL)
    {
        delete[] title;
    }

    this->title = new char[strlen(s)+1];
    strcpy(title, s);

}

const char *mobireader::get_title() const
{
    return title;
}


void mobireader::set_default_title()
        {
            uint32 title_start;
            uint32 title_len;
            this->handler->offset(section_offsets[0]+0x54)\
                .read(title_start);

            this->handler->read(title_len);

            char *_title = new char[title_len];

            handler->offset(section_offsets[0]+title_start-1)\
                .read(_title,title_len);

            this->set_title(_title);
            delete[] _title;
        }


void mobireader::load_file(std::string const &input_file_name)
{
    this->file = new std::ifstream(input_file_name.c_str());

    if(!file->good())
        throw no_such_file_exception();
    this->handler = new header_handler(this->file);
}


std::string mobireader::get_html() const
{
    std::stringstream out;
    for(int i=1; i<=pd_header.record_count; i++)
    {
        out << this->get_section_uncompressed(i);
    }
    return out.str();

}

std::string mobireader::get_section_uncompressed(unsigned sec) const
{

    if(sec+1>=section_offsets.size())
        throw section_out_of_range_exception();

    size_t src_size = this->section_offsets[sec+1] - this->section_offsets[sec];

    unsigned short last_seven_bits = 127;
    handler->offset(section_offsets[sec]).read(c_section.content, src_size);
    unsigned trash = c_section.content[src_size-1] & last_seven_bits; 

    reader->uncompress(c_section.content, src_size-trash); //ommit unnecessary bytes
    return reader->output_raw();

}


std::string mobireader::get_file_name() const
{
    return input_file_name;
}


void mobireader::set_compression()
{
    if(this->pd_header.compression == COMPRESSION_PALM)
    {
         reader = new pd_compression;
    }

    else if(this->pd_header.compression == COMPRESSION_NONE)
    {
        reader = new no_compression;
    }
    else if(this->pd_header.compression == COMPRESSION_HUFFDIC)
    {
        reader = new hd_compression;
    }
    else
    {
        throw invalid_compression_type_exception();
    }

}

}
