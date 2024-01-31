PROGRAM = passgen

CXX = g++

C_SOURCES = $(PWD)/src/*.cpp

FLAGS = -std=c++17 -g -Wall -pedantic -lssl -lcrypto

INCLUDE_PATH = -I$(PWD)/inludes

OBJS = main.o password.o random.o

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) -o $(PROGRAM) $(OBJS) $(FLAGS)

dev:
	$(CXX) $(C_SOURCES) $(FLAGS) -o $(PROGRAM)

main.o: src/main.cpp
	$(CXX) -c $(FLAGS) src/main.cpp -o main.o

password.o: src/password.cpp
	$(CXX) -c $(FLAGS) src/password.cpp -o password.o

random.o: src/random.cpp
	$(CXX) -c $(FLAGS) src/random.cpp -o random.o

install:
	@install $(PROGRAM) /usr/local/bin/$(PROGRAM)

clean:
	rm -rf *.o *.txt *.txt.enc *.key $(PROGRAM)
