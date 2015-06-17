PREFIX =  /usr/local

INCLUDES = fs_clap.h fs_exception.h fs_formats.h fs_io.h fs_printing.h fs_string.h


make: 
	mkdir -p tmp/
	find scr/ -type f -iname '*.h' -exec cp -p  {} tmp/ \;
	find scr/ -type f -iname '*.cpp' -exec cp -p {} tmp/ \;
	cp makefiles/makefile tmp/
	make -C tmp/
 

install:
	make install -C tmp/
	cp -pR include/ $(PREFIX)/include/


uninstall:
	make uninstall -C tmp/
	find $(PREFIX)/include/ -type f -iname 'fs_*' -exec rm  {} \;
	

clean:
	rm -r tmp/