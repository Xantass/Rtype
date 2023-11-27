##
## EPITECH PROJECT, 2023
## B-CPP-500-PAR-5-2-rtype-jules.gresset
## File description:
## Makefile
##

.PHONY: all clean re client server doc

all: client server

client:
	@if [ ! -d "build" ]; then\
		mkdir build;\
	fi
	@if [ ! -d "build/client/" ]; then\
		cd build && mkdir client;\
	fi
	cd build/client/ && cmake ../../client/ && make && mv r-type_client ../../

server:
	@if [ ! -d "build" ]; then\
		mkdir build;\
	fi
	@if [ ! -d "build/server/" ]; then\
		cd build && mkdir server;\
	fi
	cd build/server/ && cmake ../../server/ && make && mv r-type_server ../../

clean:
	@if [ -d "build" ]; then\
		rm -r build;\
	fi
	rm -f r-type_client
	rm -f r-type_server

doc:
	doxygen doc/Doxyfile
	open doc/html/index.html

re: clean all
