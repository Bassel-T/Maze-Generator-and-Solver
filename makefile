run:
	g++ -std=c++11 main.cpp generator.h solver.h tile.h

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#