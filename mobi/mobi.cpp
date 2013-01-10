#include "mobi.hpp"

namespace mobi
{


bool strcmp_is_a_worthless_pos(char x[], const char y[], int len)
{
    for(int i=0;i<len;i++)
    {
        if(x[i] != y[i])
        return false;
    }
    return true;
}



st_c_section st_c_section::operator=(st_c_section st)
{
    this->size = st.size;
    this->content = new uint8[st.size];
    memcpy(this->content, st.content, st.size);

    return *this;
}



mobireader::mobireader():reader(0),file(0),title(0){}

mobireader::mobireader(std::string &input_file_name)\
:input_file_name(input_file_name),reader(0),file(0),title(0)

{
    try{
    this->load_file(input_file_name);
    }
    catch(no_such_file_exception){
        std::cout << "No such file\n";
        return;
    }
    try{
        this->parse_header();
    }
    catch(invalid_file_exception){
        std::cout << this->db_header.type << std::endl;
        std::cout << "Invalid file type\n"<< std::endl;
        return;
    }

    c_section.content = new uint8[8000];
    c_section.size = 8000; //tako rzecze specyfikacja.

}
mobireader::mobireader(const mobireader &m)
{
    *(this) = m; //TODO: is it a trap?

}
void mobireader::operator=(const mobireader &m)
{

    this->mobi_header_     = m.mobi_header_;
    this->header_offsets   = m.header_offsets;

    this->input_file_name  = m.input_file_name;
    this->load_file(this->input_file_name);

    this->pd_header = m.pd_header;
    this->db_header = m.db_header;
    this->set_compression();

    this->c_section = m.c_section;

    this->set_title(m.get_title());
    //this->title = new char[strlen(m.title)+1];
    //strcpy(this->title, m.title);

    
}

mobireader::~mobireader()
{
    delete reader;
    delete file;
    delete[] c_section.content;
    delete[] title;
}

void mobireader::parse_header()
{
    file->read((char *) &db_header, PALMDOC_DB_HEADER_LEN);
    unretardify_header(db_header);

  if(!strcmp_is_a_worthless_pos(db_header.type,MOBI_TYPE,8))
      throw invalid_file_exception();

    uint32 header_offset;
    for(int i=0;i<db_header.num_records;i++)
    {
        file->read((char *) &header_offset, sizeof(uint32));
        //file->read((char *) &header_offset_unk, sizeof(uint32_t));
        file->ignore(sizeof(uint32));
        bswap(header_offset);
        header_offsets.push_back(header_offset);
    }
    file->seekg(header_offsets[0]);

    file->read((char *) &pd_header, PALMDOC_HEADER_LEN);
    unretardify_header(pd_header);

    file->read((char *) &mobi_header_, MOBI_HEADER_LEN);
    unretardify_header(mobi_header_);

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
            file->seekg(header_offsets[0]+0x54);

            file->read((char *) &title_start, sizeof(uint32));
            bswap(title_start);
            file->read((char *) &title_len, sizeof(uint32));
            bswap(title_len);

            char _title[title_len+1];
            file->seekg(header_offsets[0]+title_start);
            file->read((char *) _title, title_len);
            _title[title_len] = '\0';

            this->set_title(_title);


        }


void mobireader::load_file(std::string &input_file_name)
{
    this->file = new std::ifstream(input_file_name.c_str());
    if(!file->good())
        throw no_such_file_exception();
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

std::string mobireader::get_section_uncompressed(int sec) const
{

    if(sec+1>=header_offsets.size() or sec<0)
        throw header_out_of_range_exception();

    size_t src_size = this->header_offsets[sec+1] - this->header_offsets[sec];

    file->seekg(header_offsets[sec]);
    file->read((char *) c_section.content, src_size);

    unsigned trash = c_section.content[src_size-1] & 127; 

    reader->uncompress(c_section.content, src_size-trash); //ommit unnecessary bytes
    return reader->output_raw();

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

        throw unsupported_compressiontype_exception();

    }
    else
    {
        throw invalid_compression_type_exception();
    }

}

}