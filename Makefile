CXX = g++
CXXFLAGS 	= -Wall -std=c++14
EXE = pcts
DEPS = main.o cards.o progbar.o
INCLUDES = -I includes
OPTS = -pthread

all: $(EXE)

$(EXE): $(DEPS)
	$(CXX) -g $^ -o $@ $(OPTS)

%.o: src/%.cpp
	$(CXX) -c $(INCLUDES) $(CXXFLAGS) $< $(OPTS)

%.o: src/aux/%.cpp
	$(CXX) -c $(INCLUDES) $(CXXFLAGS) $< $(OPTS)

.PHONY: clean

clean:
	rm -f *.o $(EXE)
