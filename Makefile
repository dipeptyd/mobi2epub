include Makefile.inc


mobitoepub: main.cpp mobi.o optparse.o epub.o
	${CC} ${CCFLAGS}   -ltidy -lboost_filesystem -lboost_system optparse/OptionParser.o mobi/mobi.o epub/epub.o main.cpp -o mobitoepub

mobi.o:
	$(MAKE) -C mobi/

optparse.o:
	$(MAKE) -C optparse/

epub.o:
	$(MAKE) -C epub/
