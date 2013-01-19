-------------------------------
mobi::mobireader
-------------------------------

.. cpp:class:: mobi::mobireader

    Opens .mobi files and reads as 

    .. code-block:: cpp

        std::string  foo = "foo.mobi";

        mobi::mobireader bar(foo);

        std::cout << bar.get_title();



mobireader variables
-------------------------------

""""""""""""""""
private
""""""""""""""""


    .. cpp:member:: st_palmdoc_db  mobireader::db_header

    .. cpp:member:: st_palmdoc    mobireader::pd_header

    .. cpp:member:: st_mobi  mobireader::mobi_header

    .. cpp:member:: vector  mobireader::section_offsets

        byte offset of every data section in file


    .. cpp:member:: st_c_section  mobireader::c_section


    .. cpp:member:: string mobireader::input_file_name

        name of the file, because ifstream is too cool to keep that.


    .. cpp:member:: ifstream*  mobireader::file

        All it should do is get passed to the :cpp:member:`handler`

    .. cpp:member:: compression*  mobireader::reader

        Pointer to new instance of :cpp:class:`mobi::compression`



    .. cpp:member:: header_handler* mobireader::handler

        pointer to new instance of :cpp:class:`header_handler`

    .. cpp:member:: char*  mobireader::title

        title of the book
        set by 
        :cpp:func:`set_title` and :cpp:func:`set_default_title` methods


mobireader methods
-------------------------------

""""""""""""""""""""""""""
private
""""""""""""""""""""""""""

    .. cpp:function:: mobireader::void parse_header()

        loads up headers structures and section vector

        if :cpp:member:`mobireader::db_header`   type doesn't equal BOOKMOBI, throws
        :cpp:class:`mobi::invalid_file_exception`


    .. cpp:function:: mobireader::void set_compression()

        decides which one of the mobi::compression classes should \*reader point to

        throws unsupported_compressiontype_exception for dictionary compression.
        mainly because i haven't found it in any of my books.

    .. cpp:function:: std::string mobireader::get_section_uncompressed(unsigned s) const

        Handles uncompressing and returning section from a valid range of 
        section_offsets vector

        header_out_of_range_exception


    .. cpp:function:: void mobireader::load_file(std::string &input_file_name)

        loads file from string and sets up :cpp:member:`handler` and :cpp:member:`file` pointers.



"""""""""""""""""""""
public:
"""""""""""""""""""""

    .. cpp:function:: mobireader::mobireader(std::string &input_file_name)


    .. cpp:function:: mobireader::mobireader(const mobireader &m)


    .. cpp:function:: mobireader::mobireader()


    .. cpp:function:: mobireader::~mobireader()


    .. cpp:function:: mobireader::void set_default_title()

        reads the default title from file


    .. cpp:function:: char* mobireader::set_title(const char *s) const


    .. cpp:function:: char* mobireader::get_title() const

        returns current book :cpp:member:`title`.


    .. cpp:function:: std::string mobireader::get_html() const

        iterates \*reader over sections and returns html-like text.


    .. cpp:function:: std::string mobireader::get_file_name() const

        returns file name from :cpp:member:`mobireader::input_file_name`




    .. cpp:function:: void mobireader::operator=(const mobireader &m)

        obviously copies mobireader class onto another instance.
        calls :cpp:func:`load_file` to check if the file is still ok.

