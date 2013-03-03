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

struct st_palmdoc_db;
struct st_palmdoc;
struct st_mobi;

#pragma pack(push)
#pragma pack(1)
struct st_palmdoc_db
{
    char   name[32];
    uint16_t flags;
    uint16_t version;
    uint32_t c_time;
    uint32_t m_time;
    uint32_t b_time;
    uint32_t mod_num;
    uint32_t app_info;
    uint32_t sort_info;
    char   type[8];
    //char creator[4];
    uint32_t u_id_seed;
    uint32_t next_record_list;
    uint16_t num_records;
};

struct st_palmdoc
{
    uint16_t compression;
    uint16_t garbage;
    uint32_t text_length;
    uint16_t record_count;
    uint16_t record_size;
    uint32_t current_pos;
};

struct st_mobi
{
  char   id[4];
  uint32_t header_len;
  uint32_t mobi_type;
  uint32_t text_encoding;
  uint32_t u_id;
  uint32_t file_version;
  uint32_t ortographic_index;            //0xFFFFFFFF
  uint32_t inflection_index;             //0xFFFFFFFF
  uint32_t index_names;
  uint32_t index_keys;
  uint32_t extra_index0;
  uint32_t extra_index1;
  uint32_t extra_index2;
  uint32_t extra_index3;
  uint32_t extra_index4;
  uint32_t extra_index5;
  uint32_t first_nonbook_index;
  uint32_t full_name_offset;
  uint32_t full_name_length;
  uint32_t locale;
  uint32_t input_language;
  uint32_t output_language;
  uint32_t min_version;
  uint32_t first_image_index;
  uint32_t huffman_record_offset;
  uint32_t huffman_record_count;
  uint32_t huffman_table_offset;
  uint32_t huffman_table_length;
  uint32_t exth_flags;                   //TODO: bitfield
  char   garbage[32];                  //0x000000000000000000000000.
  uint32_t drm_offset;
  uint32_t drm_count;
  uint32_t drm_size;
  uint32_t drm_flags;
  char   garbage2[12];
  uint16_t first_content_record_number;
  uint16_t last_content_record_number;
  uint32_t unknown;                      //0x00000001
  uint32_t fcis_record_number;
  uint32_t fcis_record_count;            //0x00000001
  uint32_t flis_record_number;
  uint32_t flis_record_count;            //0x00000001
  uint64_t unk0;                         //0x0000000000000000
  uint32_t unk1;                         //0xFFFFFFFF
  uint32_t unk2;                         //0x00000000
  uint32_t unk3;                         //0xFFFFFFFF
  uint32_t unk4;                         //0xFFFFFFFF
  uint32_t extra_record_data_flags;      //tldr http://wiki.mobileread.com/wiki/MOBI#MOBI_Header
  uint32_t indx_record_offset;           //(If not 0xFFFFFFFF)The record number of
                                       //the first INDX record created from an ncx file.
                                       //24B till exth
};


#pragma pack(pop)
static_assert((sizeof(st_palmdoc_db)==PALMDOC_DB_HEADER_LEN),"st_palmdoc_db");
static_assert((sizeof(st_palmdoc)==PALMDOC_HEADER_LEN),"st_palmdoc");
static_assert((sizeof(st_mobi)==MOBI_HEADER_LEN),"st_mobi");

void unretardify_header(st_palmdoc_db &x);
void unretardify_header(st_palmdoc &x);
void unretardify_header(st_mobi &x);



#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
inline void bswap(uint16_t &x){x = __builtin_bswap32(x << 16);}
inline void bswap(uint32_t &x){x = __builtin_bswap32(x);}
inline void bswap(uint64_t &x){x = __builtin_bswap64(x);}
inline void bswap(st_palmdoc_db &x){unretardify_header(x);}
inline void bswap(st_palmdoc &x)   {unretardify_header(x);}
inline void bswap(st_mobi &x)      {unretardify_header(x);}
#else
inline void bswap(uint16_t &x){}
inline void bswap(uint32_t &x){}
inline void bswap(uint64_t &x){}
#endif
