=====================================
epub::html::
=====================================

----------------------------------
epub::html::tidyhtml
----------------------------------

.. cpp:class:: epub::html::tidyhtml

    turns ugly mobi html into even uglier xhtml



variables
""""""""""""""

private
'''''''''''''''

.. cpp:member:: TidyDoc epub::html::tidyhtml::tdoc

    http://tidy.sourceforge.net/#docs





methods
"""""""""""""""""

public
'''''''''''''''''

.. cpp:function:: epub::html::tidyhtml::tidyhtml()

    sets up :cpp:member:`tdoc` and related options::

        tidyOptSetBool( tdoc, TidyXhtmlOut, yes);
        tidyOptSetBool( tdoc, TidyForceOutput, yes);
        tidyOptSetBool( tdoc, TidyShowWarnings, no);
        tidyOptSetBool( tdoc, TidyQuiet, yes);
        tidyOptSetInt( tdoc, TidyShowErrors, 0);
        tidySetCharEncoding(tdoc, "utf8");



.. cpp:function:: void parse(std::string html_code, std::string path)

    it doesn't only parse, but also writes to a file!
