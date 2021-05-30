CXX = g++
CXXFLAGS 	= -Wall -std=c++14
EXE = pcts
DEPS = main.o cards.o
INCLUDES = -I includes
OPTS = -pthread

$(EXE): $(DEPS)
	$(CXX) -g $^ -o $@ $(OPTS)

%.o: src/%.cpp
	$(CXX) -c $(INCLUDES) $(CXXFLAGS) $< $(OPTS)

.PHONY: clean

clean:
	rm -f *.o $(EXE)
