CC        = g++
CC_FLAGS  = -g -Wall -Wextra -std=c++11 -I/usr/local/opt/openssl/include
LD_FLAGS  = -L/usr/local/opt/openssl/lib -lcpprest -lssl -lcrypto -lboost_system -lboost_thread-mt -lboost_chrono-mt
OUTPUT    = server.exe
SOURCES   = Main.cpp Server.cpp
OBJECTS   = $(SOURCES:.cpp=.o)

${OUTPUT}: ${OBJECTS}
	${CC} ${LD_FLAGS} ${CC_FLAGS} ${OBJECTS} -o ${OUTPUT}

run: ${OUTPUT}
	./${OUTPUT}

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f ${OUTPUT} ${OBJECTS}
