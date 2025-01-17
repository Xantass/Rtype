##
## EPITECH PROJECT, 2023
## B-CPP-500-PAR-5-2-rtype-jules.gresset
## File description:
## Makefile
##

ifeq ($(OS), Windows_NT)
	CLIENT_NAME = r-type_client.exe
	SERVER_NAME = r-type_server.exe
	FLAPPY_NAME = flappy-bird.exe
	CLIENT_MAKE_RULE = cmake --build . --config Release && mv Release/$(CLIENT_NAME) ../../
	SERVER_MAKE_RULE = cmake --build . --config Release && mv Release/$(SERVER_NAME) ../../
	FLAPPY_MAKE_RULE = cmake --build . --config Release && mv Release/$(FLAPPY_NAME) ../../
else
	CLIENT_NAME = r-type_client
	SERVER_NAME = r-type_server
	FLAPPY_NAME = flappy-bird
	CLIENT_MAKE_RULE  = make && mv $(CLIENT_NAME) ../../
	SERVER_MAKE_RULE  = make && mv $(SERVER_NAME) ../../
	FLAPPY_MAKE_RULE  = make && mv $(FLAPPY_NAME) ../../
endif

.PHONY: all clean re client server flappy doc

all: client server

client:
	if [ ! -d "build" ]; then\
		mkdir build;\
	fi
	if [ ! -d "build/client/" ]; then\
		cd build && mkdir client;\
	fi
	cd build/client/ && cmake ../../client/ && $(CLIENT_MAKE_RULE)

server:
	if [ ! -d "build" ]; then\
		mkdir build;\
	fi
	if [ ! -d "build/server/" ]; then\
		cd build && mkdir server;\
	fi
	cd build/server/ && cmake ../../server/ && $(SERVER_MAKE_RULE)

flappy:
	if [ ! -d "build" ]; then\
		mkdir build;\
	fi
	if [ ! -d "build/flappy/" ]; then\
		cd build && mkdir flappy;\
	fi
	cd build/flappy/ && cmake ../../flappy/ && $(FLAPPY_MAKE_RULE)

clean:
	if [ -d "build" ]; then\
		rm -r build;\
	fi
	rm -f $(CLIENT_NAME)
	rm -f $(SERVER_NAME)

doc:
	doxygen docs/Doxyfile
	open docs/html/index.html

re: clean all
