CXX = g++
CXXFLAGS = -Wall

proj0: bingo.o 
	$(CXX) $(CXXFLAGS) bingo.o driver.cpp -o proj0

bingo.o: bingo.h bingo.cpp
	$(CXX) $(CXXFLAGS) -c bingo.cpp

clean:
	rm *.o*
	rm *~

run:
	./proj0