=====================================
epub::
=====================================

.. toctree::

    tidyhtml.rst

Namespace for classes that read .epub, write .epub and convert to .epub


.. cpp:member:: std::string container_xml

    http://wiki.mobileread.com/wiki/EPUB#container.xml

    ::

        <?xml version=\"1.0\"?>\n\
        <container version=\"1.0\" xmlns=\"urn:oasis:names:tc:opendocument:xmlns:container\">\n\
        <rootfiles>\n\
            <rootfile full-path=\"OEBPS/content.opf\" media-type=\"application/oebps-package+xml\"/>\n\
            \n\  
        </rootfiles>\n\
        </container>"

.. cpp:member:: std::string mimetype

    http://wiki.mobileread.com/wiki/EPUB#mimetype

    ::

        "application/epub+zip";



.. cpp:member:: std::string content_opf

    http://wiki.mobileread.com/wiki/EPUB#OPF

    ::

        <?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>\n\
        <package xmlns=\"http://www.idpf.org/2007/opf\" unique-identifier=\"BookId\" version=\"2.0\">\n\
            <metadata xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:opf=\"http://www.idpf.org/2007/opf\">\n\
                <dc:title>%1%</dc:title> \n\
            </metadata>\n\
            <manifest>\n\n\
        \
        %2%\n\   //itemid
        \
            </manifest>\n\
            <spine toc=\"ncx\">\n\n\
        \
        %3%\n\ //itemref
        \
            </spine>\n\
        </package>\n\

    title string comes from :cpp:func:`mobireader::get_title()`

.. cpp:member:: std::string itemid

        format string for :cpp:member:`content_opf`

.. cpp:member:: std::string itemref

        format string for :cpp:member:`content_opf`

-------------------------------
epub::mobi2epub
-------------------------------

.. cpp:class:: epub::mobi2epub

    Class converting .mobi files to .epub 
    
    and because of lame
    .zip support  writes them on the disk immediately.

    :sub:`actually it's still in ram, thanks to tmpfs, nonetheless, could be better`


""""""""""""""""""""""""""
mobi2epub variables
""""""""""""""""""""""""""
private
-------------------------------
.. cpp:member:: boost::filesystem::path path_out

    Path to the output file *obviously including file name*

    Used in :cpp:func:`mobi2epub::directory_to_epub`

    Set in :cpp:func:`mobi2epub::mobi2epub`

    

.. cpp:member:: boost::filesystem::path path_tmp

    Path to the temporary directory, used to save the entire uncompressed file structure

    Set in :cpp:func:`mobi2epub::mobi2epub`

    .. note:: 

        Currently supports only unix

.. cpp:member:: mobi::mobireader m

    instance of :cpp:class:`mobi::mobireader` copied in :cpp:func:`mobi2epub::mobi2epub`


.. cpp:member:: mutable bool safe

    Tells if it's ok to wipe the user's drive ^W^W^W^W run :cpp:func:`mobi2epub::directory_structure`


.. cpp:member:: mutable bool no_cleanup

    Makes :cpp:func:`mobi2epub::cleanup` exit immediately

.. cpp:member:: mutable bool vanilla_out

    Checks if :cpp:func:`mobi2epub::set_out` was called and :cpp:member:`path_out`
    isn't default anymore.



""""""""""""""""""""""""""
mobi2epub methods
""""""""""""""""""""""""""

private
-------------------------------

.. cpp:function:: void mobi2epub::directory_structure() const


    Creates the static part of every .epub file::

       path_tmp/
                OEBPS/
                OEBPS/text/
                OEBPS/META-INF/
                META-INF/container.xml
                mimetype


    checks if already exists, if so ask to whether :cpp:func:`remove <mobi2epub::cleanup>`
    or set to :cpp:member:`safe` and continue

.. cpp:function:: void mobi2epub::cleanup() const

    .. warning::

        Removes recursively every file in :cpp:member:`path_tmp` without asking if :cpp:member:`safe` is set to **True** 

        should be handled with caution.

    :cpp:member:`no_cleanup` decides whether it should return instantly 

    Throws :cpp:class:`epub::user_wants_out_exception` if the user decides to quit

.. cpp:function:: void mobi2epub::gen_content_opf(std::stringstream &itemids, std::stringstream &itemrefs) const

    Generates :cpp:member:`content_opf` and saves it to::

        OEBPS/content.opf

.. cpp:function:: void mobi2epub::operator=(mobi2epub &m)

    Makes the class uncopyable

.. cpp:function:: mobi2epub::mobi2epub(mobi2epub &m)

    Makes the class uncopyable even more


.. cpp:function::   void mobi2epub::set_out(std::string &s)

    Sets :cpp:member:`vanilla_out` to **False**, then
    changes :cpp:member:`path_tmp` to 

public
-------------------------------

.. cpp:function:: mobi2epub::mobi2epub(const mobi::mobireader &m,\
    bool safe=false, bool no_cleanup=false)

.. cpp:function:: void mobi2epub::save_to_directory() const

    Calls :cpp:func:`mobi2epub::directory_structure` and :cpp:func:`mobireader::get_html`

    splits the html on every new chapter mark::

        <mbp:pagebreak/>

    then iterates over them to:
    

    1. convert to xhtml with :cpp:class:`epub::html::tidyhtml`
    2. save xhtml to :cpp:member:`path_tmp` /OEBPS/text
    3. build up :cpp:member:`itemid` and :cpp:member:`itemref` lists, which get passed to :cpp:func:`mobi2epub::gen_content_opf` later on



.. cpp:function:: void mobi2epub::save_to_directory(std::string s)

    calls :cpp:func:`mobi2epub::set_out` and 
    then proceeds to :cpp:func:`mobi2epub::save_to_directory`

.. cpp:function:: void mobi2epub::directory_to_epub() const

    calls zip executable to compress everything in :cpp:member:`path_tmp`
    and save it to :cpp:member:`path_out`

    .. note::

        if it somehow compiles on windows and nothing fails up to this point, should throw :cpp:class:`epub::terrible_operating_system_exception` 


    throws :cpp:class:`epub::zip_exit_status_exception` if the zip exit code isn't equal to 0.



.. cpp:function:: void mobi2epub::directory_to_epub(std::string s)

    Calls :cpp:func:`mobi2epub::set_out` before calling actual :cpp:func:`mobi2epub::directory_to_epub`


