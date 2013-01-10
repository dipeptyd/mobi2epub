include ../Makefile.inc

epub.o: a.o b.o
	ld -r a.o b.o -o epub.o

a.o: epub.cpp 
	${CC} ${CCFLAGS} -c epub.cpp -o a.o

b.o: tidyhtml_wrapper.cpp
	${CC} ${CCFLAGS} -c tidyhtml_wrapper.cpp -o b.o
