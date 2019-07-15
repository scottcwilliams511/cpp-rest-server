CC        = g++
SRC_DIR   = src
BUILD_DIR = build
INCLUDE   = -I include -I/usr/local/opt/openssl/include
OUTPUT    = server.exe

CC_FLAGS  = -g -Wall -Wextra -std=c++11
LIBS      = -L/usr/local/opt/openssl/lib -lcpprest -lssl -lcrypto -lboost_system -lboost_thread-mt -lboost_chrono-mt

SOURCES   = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS   = $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.cpp=.o)) $(BUILD_DIR)/Main.o

${OUTPUT}: ${OBJECTS}
	${CC} ${LIBS} ${OBJECTS} -o ${OUTPUT}

run: ${OUTPUT}
	./${OUTPUT}

$(BUILD_DIR)/Main.o: Main.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) -c $(CC_FLAGS) $(INCLUDE) $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) -c $(CC_FLAGS) $(INCLUDE) $< -o $@

clean:
	rm -f ${OUTPUT} ${OBJECTS}
