#include "mobi_headers.hpp"

void unretardify_header(st_palmdoc_db &x)
{
    bswap(x.flags);
    bswap(x.version);
    bswap(x.c_time);
    bswap(x.m_time);
    bswap(x.b_time);
    bswap(x.mod_num);
    bswap(x.app_info);
    bswap(x.sort_info);
    bswap(x.u_id_seed);
    bswap(x.next_record_list);
    bswap(x.num_records);

}
void unretardify_header(st_palmdoc &x)
{
    bswap(x.compression);
    bswap(x.garbage);
    bswap(x.text_length);
    bswap(x.record_count);
    bswap(x.record_size);
    bswap(x.current_pos);

}
void unretardify_header(st_mobi &x)
{
    bswap(x.header_len);
    bswap(x.mobi_type);
    bswap(x.text_encoding);
    bswap(x.u_id);
    bswap(x.file_version);
    bswap(x.ortographic_index);
    bswap(x.inflection_index);
    bswap(x.index_names);
    bswap(x.index_keys);
    bswap(x.extra_index0);
    bswap(x.extra_index1);
    bswap(x.extra_index2);
    bswap(x.extra_index3);
    bswap(x.extra_index4);
    bswap(x.extra_index5);
    bswap(x.first_nonbook_index);
    bswap(x.full_name_offset);
    bswap(x.full_name_length);
    bswap(x.locale);
    bswap(x.input_language);
    bswap(x.output_language);
    bswap(x.min_version);
    bswap(x.first_image_index);
    bswap(x.huffman_record_offset);
    bswap(x.huffman_record_count);
    bswap(x.huffman_table_offset);
    bswap(x.huffman_table_length);
    bswap(x.exth_flags);
    bswap(x.drm_offset);
    bswap(x.drm_count);
    bswap(x.drm_size);
    bswap(x.drm_flags);
    bswap(x.first_content_record_number);
    bswap(x.last_content_record_number);
    bswap(x.unknown);
    bswap(x.fcis_record_number);
    bswap(x.fcis_record_count);
    bswap(x.flis_record_number);
    bswap(x.flis_record_count);
    bswap(x.unk0);
    bswap(x.unk1);
    bswap(x.unk2);
    bswap(x.unk3);
    bswap(x.unk4);
    bswap(x.extra_record_data_flags);
    bswap(x.indx_record_offset);
}
