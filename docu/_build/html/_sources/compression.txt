-------------------------------
mobi::compression
-------------------------------

.. cpp:class:: mobi::compression

    abstract class, provides base for :cpp:class:`pd_compression`, :cpp:class:`no_compression`
    and :cpp:class:`hd_compression`

compression variables
-----------------------------

"""""""""""""""
private  
"""""""""""""""

    .. cpp:member:: std::string destination


compression methods
-----------------------------

"""""""""""""""
public:
"""""""""""""""

.. cpp:function:: void compression::uncompress(uint8_t *src, size_t srcLen) =0

    .. note::

        pure virtual function

    Should be overloaded with::

        if(!this->destination.empty())
            this->destination.clear();
        (decompression algorithm that appends stuff to this->destination)
        return;

.. cpp:function:: std::string compression::output_raw() 

    .. note::

        virtual function

    Usually should just::

        return this->destination;


.. cpp:class:: mobi::pd_compression

    inherits from :cpp:class:`compression`

    Uses PalmDoc algorithm:

       1. Read a byte from the compressed stream. If the byte is 
       2. 0x00: "1 literal" copy that byte unmodified to the decompressed stream.
       3. 0x09 to 0x7f: "1 literal" copy that byte unmodified to the decompressed stream.
       4. 0x01 to 0x08: "literals": the byte is interpreted as a count from 1 to 8, and that many literals are copied unmodified from the compressed stream to the decompressed stream.
       5. 0x80 to 0xbf: "length, distance" pair: the 2 leftmost bits of this byte ('10') are discarded, and the following 6 bits are combined with the 8 bits of the next byte to make a 14 bit "distance, length" item. Those 14 bits are broken into 11 bits of distance backwards from the current location in the uncompressed text, and 3 bits of length to copy from that point (copying n+3 bytes, 3 to 10 bytes).
       6. 0xc0 to 0xff: "byte pair": this byte is decoded into 2 characters: a space character, and a letter formed from this byte XORed with 0x80.
       7. Repeat from the beginning until there is no more bytes in the compressed f

    Except it doesn't copy 0x00. Because who in the right mind would want to do that?

    throws :cpp:class:`mobi::not_palmdoc_compression_exception`
    from check at stage 5.





.. cpp:class:: mobi::no_compression

    inherits from :cpp:class:`compression`

    It's just::

        if(!this->destination.empty())
            this->destination.clear();
        this->destination.append((char *)src, srcLen);

    in :cpp:func:`compression::uncompress`




.. cpp:class:: mobi::hd_compression

    inherits from :cpp:class:`compression`\

    currently not implemented, because none of the books i've found use it.

