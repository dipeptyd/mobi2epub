#include "mobi_headers.hpp"
void unretardify_header(palmdoc_db_header &x)
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
void unretardify_header(palmdoc_header &x)
{
    bswap(x.compression);
    bswap(x.garbage);
    bswap(x.text_length);
    bswap(x.record_count);
    bswap(x.record_size);
    bswap(x.current_pos);

}
void unretardify_header(mobi_header &x)
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


void print_header(const mobi_header &x)
{

    std::cout<< "mobi_header                 "   << "\n\n";
    std::cout<< "id:                         "   << x.id << std::endl;
    std::cout<< "header_len:                 "   << x.header_len << std::endl;
    std::cout<< "mobi_type:                  "   << x.mobi_type << std::endl;
    std::cout<< "text_encoding:              "   << x.text_encoding << std::endl;
    std::cout<< "u_id:                       "   << x.u_id << std::endl;
    std::cout<< "file_version:               "   << x.file_version << std::endl;
    std::cout<< "ortographic_index:          "   << x.ortographic_index << std::endl;
    std::cout<< "inflection_index:           "   << x.inflection_index << std::endl;
    std::cout<< "index_names:                "   << x.index_names << std::endl;
    std::cout<< "index_keys:                 "   << x.index_keys << std::endl;
    std::cout<< "extra_index0:               "   << x.extra_index0 << std::endl;
    std::cout<< "extra_index1:               "   << x.extra_index1 << std::endl;
    std::cout<< "extra_index2:               "   << x.extra_index2 << std::endl;
    std::cout<< "extra_index3:               "   << x.extra_index3 << std::endl;
    std::cout<< "extra_index4:               "   << x.extra_index4 << std::endl;
    std::cout<< "extra_index5:               "   << x.extra_index5 << std::endl;
    std::cout<< "first_nonbook_index:        "   << x.first_nonbook_index << std::endl;
    std::cout<< "full_name_offset:           "   << x.full_name_offset << std::endl;
    std::cout<< "full_name_length:           "   << x.full_name_length << std::endl;
    std::cout<< "locale:                     "   << x.locale << std::endl;
    std::cout<< "input_language:             "   << x.input_language << std::endl;
    std::cout<< "output_language:            "   << x.output_language << std::endl;
    std::cout<< "min_version:                "   << x.min_version << std::endl;
    std::cout<< "first_image_index:          "   << x.first_image_index << std::endl;
    std::cout<< "huffman_record_offset:      "   << x.huffman_record_offset << std::endl;
    std::cout<< "huffman_record_count:       "   << x.huffman_record_count << std::endl;
    std::cout<< "huffman_table_offset:       "   << x.huffman_table_offset << std::endl;
    std::cout<< "huffman_table_length:       "   << x.huffman_table_length << std::endl;
    std::cout<< "exth_flags:                 "   << x.exth_flags << std::endl;
    std::cout<< "garbage:                    "   << x.garbage << std::endl;
    std::cout<< "drm_offset:                 "   << x.drm_offset << std::endl;
    std::cout<< "drm_count:                  "   << x.drm_count << std::endl;
    std::cout<< "drm_size:                   "   << x.drm_size << std::endl;
    std::cout<< "drm_flags:                  "   << x.drm_flags << std::endl;
    std::cout<< "garbage2:                   "   << x.garbage2 << std::endl;
    std::cout<< "first_content_record_number:"   << x.first_content_record_number << std::endl;
    std::cout<< "last_content_record_number: "   << x.last_content_record_number << std::endl;
    std::cout<< "unknown:                    "   << x.unknown << std::endl;
    std::cout<< "fcis_record_number:         "   << x.fcis_record_number << std::endl;
    std::cout<< "fcis_record_count:          "   << x.fcis_record_count << std::endl;
    std::cout<< "flis_record_number:         "   << x.flis_record_number << std::endl;
    std::cout<< "flis_record_count:          "   << x.flis_record_count << std::endl;
    std::cout<< "unk0:                       "   << x.unk0 << std::endl;
    std::cout<< "unk1:                       "   << x.unk1 << std::endl;
    std::cout<< "unk2:                       "   << x.unk2 << std::endl;
    std::cout<< "unk3:                       "   << x.unk3 << std::endl;
    std::cout<< "unk4:                       "   << x.unk4 << std::endl;
    std::cout<< "extra_record_data_flags:    "   << x.extra_record_data_flags << std::endl;
    std::cout<< "indx_record_offset:         "   << x.indx_record_offset << std::endl;
}
void print_header(const palmdoc_db_header &x)
{

    std::cout <<"palmdoc_db_header           " << "\n\n" << std::endl;
    std::cout << "name[32]:                  " <<   x.name<< std::endl;
    std::cout << "flags:                     " <<   x.flags<< std::endl;
    std::cout << "version:                   " <<   x.version<< std::endl;
    std::cout << "c_time:                    " <<   x.c_time<< std::endl;
    std::cout << "m_time:                    " <<   x.m_time<< std::endl;
    std::cout << "b_time:                    " <<   x.b_time<< std::endl;
    std::cout << "mod_num:                   " <<   x.mod_num<< std::endl;
    std::cout << "app_info:                  " <<   x.app_info<< std::endl;
    std::cout << "sort_info:                 " <<   x.sort_info<< std::endl;
    std::cout << "type[8]:                   " <<   x.type<< std::endl;
    std::cout << "u_id_seed:                 " <<   x.u_id_seed<< std::endl;
    std::cout << "next_record_list:          " <<   x.next_record_list<< std::endl;
    std::cout << "num_records:               " <<   x.num_records<< std::endl;

}
void print_header(const palmdoc_header &x)
{
    std::cout << "palmdoc_header              " << "\n\n";

    std::cout << "compression:                "  << x.compression << std::endl;
    std::cout << "garbage:                    "  << x.garbage << std::endl;
    std::cout << "text_length:                "  << x.text_length << std::endl;
    std::cout << "record_count:               "  << x.record_count << std::endl;
    std::cout << "record_size:                "  << x.record_size << std::endl;
    std::cout << "current_pos:                "  << x.current_pos << std::endl;

}
