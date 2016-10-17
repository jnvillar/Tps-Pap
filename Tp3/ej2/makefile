TARGETS=ej2
FLAGS= -std=c++0x
make: $(TARGETS)
ej2: ej2.cpp p2.cpp
	g++ $^ -g -O0 -o $@ $(FLAGS)
clean: 
	rm -f *.o *~ $(TARGETS)