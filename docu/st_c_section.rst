----------------------------------
mobi::st_c_section
----------------------------------
.. cpp:class:: mobi::st_c_section

    Container used for simpler management of Content array by passing it's
    size along with it


st_c_section variables
-------------------------------

""""""""""""""""
public
""""""""""""""""
    .. cpp:member:: uint8* st_c_section::content
    .. cpp:member:: unsigned st_c_section::size

st_c_section methods
-------------------------------

""""""""""""""""
public
""""""""""""""""

    .. cpp:function:: st_c_section()

    .. cpp:function:: st_c_section(unsigned x)

        sets up :cpp:member:`st_c_section::content` to uint8[x]
        
        and :cpp:member:`st_c_section::size` to x
