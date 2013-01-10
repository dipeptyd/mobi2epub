include ../Makefile.inc

mobi.o: a.o b.o c.o compression.o
	ld -r a.o b.o c.o compression/compression.o -o mobi.o

a.o: mobi.cpp
	${CC} ${CCFLAGS} -c mobi.cpp -o a.o

b.o: mobi_headers.cpp
	${CC} ${CCFLAGS} -c mobi_headers.cpp -o b.o

c.o: mobi_headers_handler.cpp
	${CC} ${CCFLAGS} -c mobi_headers_handler.cpp -o c.o



compression.o:
	$(MAKE) -C compression/
