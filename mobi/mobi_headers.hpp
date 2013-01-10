#pragma once
#define PALMDOC_DB_HEADER_LEN 78
#define PALMDOC_HEADER_LEN 16
#define MOBI_HEADER_LEN 232
#define COMPRESSION_NONE 1
#define COMPRESSION_PALM 2
#define COMPRESSION_HUFFDIC 17480
#define MOBI_TYPE "BOOKMOBI"

#include <cstdint>
#include <iostream>
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

inline void bswap(uint16 &x){x = __builtin_bswap32(x << 16);}
inline void bswap(uint32 &x){x = __builtin_bswap32(x);}
inline void bswap(uint64 &x){x = __builtin_bswap64(x);}


struct palmdoc_db_header;
struct palmdoc_header;
struct mobi_header;
struct rec_headers;
struct image_data;
#pragma pack(push)
#pragma pack(1)
struct palmdoc_db_header
{
    char   name[32];
    uint16 flags;
    uint16 version;
    uint32 c_time;
    uint32 m_time;
    uint32 b_time;
    uint32 mod_num;
    uint32 app_info;
    uint32 sort_info;
    char   type[8];
    //char creator[4];
    uint32 u_id_seed;
    uint32 next_record_list;
    uint16 num_records;
};

struct palmdoc_header
{
    uint16 compression;
    uint16 garbage;
    uint32 text_length;
    uint16 record_count;
    uint16 record_size;
    uint32 current_pos;
};

struct mobi_header
{
  //palmdoc_header s_palmdoc_header;
  char   id[4];
  uint32 header_len;
  uint32 mobi_type;
  uint32 text_encoding;
  uint32 u_id;
  uint32 file_version;
  uint32 ortographic_index;            //0xFFFFFFFF
  uint32 inflection_index;             //0xFFFFFFFF
  uint32 index_names;
  uint32 index_keys;
  uint32 extra_index0;
  uint32 extra_index1;
  uint32 extra_index2;
  uint32 extra_index3;
  uint32 extra_index4;
  uint32 extra_index5;
  uint32 first_nonbook_index;
  uint32 full_name_offset;
  uint32 full_name_length;
  uint32 locale;
  uint32 input_language;
  uint32 output_language;
  uint32 min_version;
  uint32 first_image_index;
  uint32 huffman_record_offset;
  uint32 huffman_record_count;
  uint32 huffman_table_offset;
  uint32 huffman_table_length;
  uint32 exth_flags;                   //TODO: bitfield
  char   garbage[32];                  //0x000000000000000000000000.
  uint32 drm_offset;
  uint32 drm_count;
  uint32 drm_size;
  uint32 drm_flags;
  char   garbage2[12];
  uint16 first_content_record_number;
  uint16 last_content_record_number;
  uint32 unknown;                      //0x00000001
  uint32 fcis_record_number;
  uint32 fcis_record_count;            //0x00000001
  uint32 flis_record_number;
  uint32 flis_record_count;            //0x00000001
  uint64 unk0;                         //0x0000000000000000
  uint32 unk1;                         //0xFFFFFFFF
  uint32 unk2;                         //0x00000000
  uint32 unk3;                         //0xFFFFFFFF
  uint32 unk4;                         //0xFFFFFFFF
  uint32 extra_record_data_flags;      //tldr http://wiki.mobileread.com/wiki/MOBI#MOBI_Header
  uint32 indx_record_offset;           //(If not 0xFFFFFFFF)The record number of
                                       //the first INDX record created from an ncx file.
                                       //24B till exth
};

struct rec_headers
{
    uint32   offset;
    uint8    deleted   : 1;
    uint8    dirty     : 1;
    uint8    busy      : 1;
    uint8    secret    : 1;
    uint8    category  : 4;
    char     uniqueID[3];
};



struct image_data
{
    char  *data;
    size_t len;
    char  *type;
};


#pragma pack(pop)
static_assert((sizeof(palmdoc_db_header)==PALMDOC_DB_HEADER_LEN),"palmdoc_db_header");
static_assert((sizeof(palmdoc_header)==PALMDOC_HEADER_LEN),"palmdoc_header");
static_assert((sizeof(mobi_header)==MOBI_HEADER_LEN),"mobi_header");

//extern struct palmdoc_db_header db_header;


void unretardify_header(palmdoc_db_header &x);
void unretardify_header(palmdoc_header &x);
void unretardify_header(mobi_header &x);
void print_header(const mobi_header &x);
void print_header(const palmdoc_db_header &x);
void print_header(const palmdoc_header &x);
