-------------------------------
mobi::mobireader
-------------------------------

.. cpp:class:: mobi::mobireader

    Class for handling .mobi files

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

    .. cpp:member:: vector<uint32_t>  mobireader::section_offsets

        byte offset of every data section in the file


    .. cpp:member:: st_c_section  mobireader::c_section

        instance of :cpp:class:`mobi::st_c_section`


    .. cpp:member:: string mobireader::input_file_name

        name of the file, because ifstream is too cool to keep that by itself.

        .. note::

            Actually, it's the whole path used in the constructor


    .. cpp:member:: ifstream*  mobireader::file

        All it should do is to get passed to the :cpp:member:`handler`

    .. cpp:member:: compression*  mobireader::reader

        Pointer to a dynamic instance of :cpp:class:`mobi::compression`



    .. cpp:member:: header_handler* mobireader::handler

        pointer to a dynamic instance of :cpp:class:`header_handler`

    .. cpp:member:: char*  mobireader::title

        title of the book,
        set by 
        :cpp:func:`set_title` and :cpp:func:`set_default_title` methods


mobireader methods
-------------------------------

""""""""""""""""""""""""""
private
""""""""""""""""""""""""""

    .. cpp:function:: mobireader::void parse_header()

        loads up headers structures and fills the :cpp:member:`mobireader::section_offsets` vector

        if :cpp:member:`mobireader::db_header` type doesn't equal BOOKMOBI, throws
        :cpp:class:`mobi::invalid_file_exception`


    .. cpp:function:: mobireader::void set_compression()

        decides which one of the mobi::compression classes should :cpp:member:`mobireader::reader` point to

        throws unsupported_compressiontype_exception for dictionary compression.
        mainly because i haven't found it in any of my books.

    .. cpp:function:: std::string mobireader::get_section_uncompressed(unsigned s) const

        Handles uncompression and returns the uncompressed text.

        throws :cpp:class:`mobi::section_out_of_range_exception`
        when... the section is out of range


    .. cpp:function:: void mobireader::load_file(std::string &input_file_name)

        loads file from path in input_file_name string and sets up :cpp:member:`handler` and :cpp:member:`file` pointers.



"""""""""""""""""""""
public:
"""""""""""""""""""""

    .. cpp:function:: mobireader::mobireader(std::string &input_file_name)

        Does all the magic necessary, calls :cpp:func:`mobireader::load_file` for input_file_name


    .. cpp:function:: mobireader::mobireader(const mobireader &m)

        Copy constructor. Uses :cpp:func:`mobireader::operator=`


    .. cpp:function:: mobireader::mobireader()

        A Constructor that actually does nothing.



    .. cpp:function:: mobireader::~mobireader()

        Frees :cpp:member:`reader`, :cpp:member:`file`, :cpp:member:`title` and :cpp:member:`handler`


    .. cpp:function:: mobireader::void set_default_title()

        reads the default title from file and calls :cpp:func:`mobireader::set_title` with it as an argument.


    .. cpp:function:: char* mobireader::set_title(const char* s)

        Sets the char* s copy as the book title.

        Also handles deleting the old one.


    .. cpp:function:: char* mobireader::get_title() const

        returns current book :cpp:member:`title`.


    .. cpp:function:: std::string mobireader::get_html() const

        iterates :cpp:member:`mobireader::reader` over sections and returns html-like text.


    .. cpp:function:: std::string mobireader::get_file_name() const

        returns file name from :cpp:member:`mobireader::input_file_name`

        .. note::

            Actually this tends to be the full path used




    .. cpp:function:: void mobireader::operator=(const mobireader &m)

        obviously copies mobireader instance onto current one.
        calls :cpp:func:`load_file`

