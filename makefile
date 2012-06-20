EXE = Kinect-Client
LIBS = -pthread
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(EXE)

$(EXE): $(OBJ)
	g++ $(LIBS) -o $@ $^

%.o: %.cpp
	g++ -c $^

.PHONY: clean mrproper

clean:
	rm *.o

mrproper: clean
	rm $(EXE)
