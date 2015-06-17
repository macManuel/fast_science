TARGET = libFastScience.dylib
PREFIX =  /usr/local

CC = g++
CFLAGS = -std=c++11 -Wall

HEADERS = exception.h string_functions.h print_functions.h format.h csvFormat.h gffFormat.h bedgraphFormat.h reader.h csvReader.h gffReader.h bedgraphReader.h wigReader.h writer.h csvWriter.h gffWriter.h bedgraphWriter.h wigWriter.h clapArgument.h clapSingleArgument.h clapMultiArgument.h commandlineParser.h

OBJECTS = exception.o string_functions.o print_functions.o format.o csvFormat.o gffFormat.o bedgraphFormat.o reader.o csvReader.o gffReader.o bedgraphReader.o wigReader.o writer.o csvWriter.o gffWriter.o bedgraphWriter.o wigWriter.o clapArgument.o clapSingleArgument.o clapMultiArgument.o commandlineParser.o



$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -dynamiclib -o $(TARGET) $(OBJECTS)


exception.o: exception.h exception.cpp
	$(CC) $(CFLAGS) -o exception.o -c exception.cpp

string_functions.o: string_functions.h string_functions.cpp
	$(CC) $(CFLAGS) -o string_functions.o -c string_functions.cpp

print_functions.o: print_functions.h print_functions.cpp
	$(CC) $(CFLAGS) -o print_functions.o -c print_functions.cpp


format.o: format.h format.cpp
	$(CC) $(CFLAGS) -o format.o -c format.cpp

csvFormat.o: format.h format.o csvFormat.h csvFormat.cpp 
	$(CC) $(CFLAGS) -o csvFormat.o -c csvFormat.cpp

gffFormat.o: format.h format.o gffFormat.h gffFormat.cpp
	$(CC) $(CFLAGS)  -o gffFormat.o -c gffFormat.cpp

bedgraphFormat.o: format.h format.o bedgraphFormat.h bedgraphFormat.cpp
	$(CC) $(CFLAGS)  -o bedgraphFormat.o -c bedgraphFormat.cpp

reader.o: reader.h reader.cpp
	$(CC) $(CFLAGS)  -o Reader.o -c Reader.cpp

csvReader.o: csvFormat.h csvFormat.o reader.h reader.o csvReader.h csvReader.cpp 
	$(CC) $(CFLAGS)  -o csvReader.o -c csvReader.cpp

gffReader.o: gffFormat.h gffFormat.o reader.h reader.o gffReader.h gffReader.cpp 
	$(CC) $(CFLAGS)  -o gffReader.o -c gffReader.cpp

bedgraphReader.o: bedgraphFormat.h bedgraphFormat.o reader.h reader.o bedgraphReader.h bedgraphReader.cpp 
	$(CC) $(CFLAGS)  -o bedgraphReader.o -c bedgraphReader.cpp

wigReader.o: bedgraphFormat.h bedgraphFormat.o reader.h reader.o wigReader.h wigReader.cpp 	
	$(CC) $(CFLAGS) -o wigReader.o -c wigReader.cpp

writer.o: writer.h writer.cpp
	$(CC) $(CFLAGS)  -o writer.o -c writer.cpp

csvWriter.o: csvFormat.h csvFormat.o writer.h writer.o csvWriter.h csvWriter.cpp 
	$(CC) $(CFLAGS)  -o csvWriter.o -c csvWriter.cpp

gffWriter.o: gffFormat.h gffFormat.o writer.h writer.o gffWriter.h gffWriter.cpp 
	$(CC) $(CFLAGS)  -o gffWriter.o -c gffWriter.cpp

bedgraphWriter.o: bedgraphFormat.h bedgraphFormat.o writer.h writer.o bedgraphWriter.h bedgraphWriter.cpp 
	$(CC) $(CFLAGS)  -o bedgraphWriter.o -c bedgraphWriter.cpp

wigWriter.o: bedgraphFormat.h bedgraphFormat.o writer.h writer.o wigWriter.h wigWriter.cpp 	
	$(CC) $(CFLAGS) -o wigWriter.o -c wigWriter.cpp


clapArgument.o: clapArgument.h clapArgument.cpp
	$(CC) $(CFLAGS) -o clapArgument.o -c clapArgument.cpp

clapSingleArgument.o : clapArgument.h clapArgument.o commandlineParser.h commandlineParser.o  clapSingleArgument.h clapSingleArgument.cpp
	$(CC) $(CFLAGS)  -o clapSingleArgument.o -c clapSingleArgument.cpp

clapMultiArgument.o :clapArgument.h clapArgument.o commandlineParser.h commandlineParser.o  clapMultiArgument.h clapMultiArgument.cpp	
	$(CC) $(CFLAGS)  -o clapMultiArgument.o -c clapMultiArgument.cpp

commandlineParser.o : clapArgument.h clapArgument.o commandlineParser.h commandlineParser.cpp
	$(CC) $(CFLAGS)  -o commandlineParser.o -c commandlineParser.cpp


install:
	mkdir -p  $(PREFIX)/lib/
	cp -p $(TARGET) $(PREFIX)/lib/

	mkdir -p $(PREFIX)/include/FastScience/
	cp -p  $(HEADERS) $(PREFIX)/include/FastScience/

uninstall:
	rm -r $(PREFIX)/include/FastScience/
	rm $(PREFIX)/lib/$(TARGET)