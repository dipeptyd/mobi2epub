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


