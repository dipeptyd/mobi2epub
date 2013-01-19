-------------------------------
mobi::header_handler
-------------------------------


.. cpp:class:: header_handler

    Handles reading data from the .mobi files, so the :cpp:class:`mobi::mobireader`
    methods can be a bit cleaner.

header_handler variables
-----------------------------


"""""""""""""""
private  
"""""""""""""""

header_handler methods
-----------------------------

    .. cpp:member:: std::ifstream* header_handler::file


"""""""""""""""
public:
"""""""""""""""
.. cpp:function:: header_handler(std::ifstream *file)

    Sets up :cpp:member:`file` pointer to 
    :cpp:member:`mobireader::file` 

.. cpp:function:: header_handler& header_handler::offset(unsigned offset)

    Sets offset in :cpp:member:`file`
    returns reference to self

.. cpp:function:: header_handler& header_handler::skip(unsigned skip)

    Skips n bytes in :cpp:member:`file`
    returns reference to self

.. cpp:function:: header_handler& header_handler::read(type &i)

    Reads sizeof i from :cpp:member:`file` and saves it to i

    returns reference to :cpp:class:`header_handler`

.. cpp:function:: header_handler& header_handler::read(type &i, unsigned n)

    Reads n times sizeof i from :cpp:member:`file` and saves it to i

    Should be overloaded for every necessary data type

    or just use templates, which i won't implement, because there's already 
    too much syntax noise as it is, without the chevron brackets.

    returns reference to self


