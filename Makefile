include Makefile.inc


mobitoepub: main.cpp mobi.o epub.o
	${CC} ${CCFLAGS}   -ltidy -lboost_program_options -lboost_filesystem -lboost_system mobi/mobi.o epub/epub.o main.cpp -o mobitoepub

mobi.o:
	$(MAKE) -C mobi/


epub.o:
	$(MAKE) -C epub/
