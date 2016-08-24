TARGETS= p1
FLAGS= -std=c++0x
make: $(TARGETS)
p1: main.cpp p1.cpp
	g++ $^ -o $@ $(FLAGS)
clean: 
	rm -f *.o *~ $(TARGETS)