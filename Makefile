CXX = clang++
EXE = pcts
DEPS = main.o cards.o
INCLUDES = -I includes
LIBS = -lboost_thread
OPTS = -pthread

$(EXE): $(DEPS)
	$(CXX) -g $^ $(LIBS) -std=c++14 -o $@ $(OPTS)

%.o: src/%.cpp
	$(CXX) -c $(INCLUDES) $<

.PHONY: clean

clean:
	rm -f *.o $(EXE)
