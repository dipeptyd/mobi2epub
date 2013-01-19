-------------------------------
separate mobi::functions
-------------------------------


.. cpp:function:: mobi::strcmp_is_a_worthless_pos(char *x, char *y, int *n)

    compares x and y arrays up to n.
    returns true if they match


.. cpp:function:: void bswap(uint16_t &x)
.. cpp:function:: void bswap(uint32_t &x)
.. cpp:function:: void bswap(uint64_t &x)

    switch variable endianess on little endian architecture.

.. cpp:function:: void unretardify_header(st_palmdoc_db &x)
.. cpp:function:: void unretardify_header(st_palmdoc &x)
.. cpp:function:: void unretardify_header(st_mobi &x)

    bswap every value in those structures.


.. cpp:type:: st_palmdoc_db

    Should be equal to 78 bytes.
    ::

        char   name[32];
        uint16_t flags;
        uint16_t version;
        uint32_t c_time;
        uint32_t m_time;
        uint32_t b_time;
        uint32_t mod_num;
        uint32_t app_info;
        uint32_t sort_info;
        char   type[8]; //BOOKMOBI
        uint32_t u_id_seed;
        uint32_t next_record_list;
        uint16_t num_records;



.. cpp:type:: st_palmdoc

    Should be equal to 16 bytes.

    ::

        uint16_t compression
        uint16_t garbage
        uint32_t text_length
        uint16_t record_count
        uint16_t record_size
        uint32_t current_pos


.. cpp:type:: st_mobi

    Should be equal to 232 bytes.
    ::

        char   id[4]
        uint32_t header_len
        uint32_t mobi_type
        uint32_t text_encoding
        uint32_t u_id
        uint32_t file_version
        uint32_t ortographic_index
        uint32_t inflection_index
        uint32_t index_names
        uint32_t index_keys
        uint32_t extra_index0
        uint32_t extra_index1
        uint32_t extra_index2
        uint32_t extra_index3
        uint32_t extra_index4
        uint32_t extra_index5
        uint32_t first_nonbook_index
        uint32_t full_name_offset
        uint32_t full_name_length
        uint32_t locale
        uint32_t input_language
        uint32_t output_language
        uint32_t min_version
        uint32_t first_image_index
        uint32_t huffman_record_offset
        uint32_t huffman_record_count
        uint32_t huffman_table_offset
        uint32_t huffman_table_length
        uint32_t exth_flags
        char   garbage[32]
        uint32_t drm_offset
        uint32_t drm_count
        uint32_t drm_size
        uint32_t drm_flags
        char   garbage2[12]
        uint16_t first_content_record_number
        uint16_t last_content_record_number
        uint32_t unknown
        uint32_t fcis_record_number
        uint32_t fcis_record_count
        uint32_t flis_record_number
        uint32_t flis_record_count
        uint64_t unk0
        uint32_t unk1
        uint32_t unk2
        uint32_t unk3
        uint32_t unk4
        uint32_t extra_record_data_flags
        uint32_t indx_record_offset

