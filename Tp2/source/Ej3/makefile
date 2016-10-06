TARGETS= ej3
FLAGS= -std=c++0x
make: $(TARGETS)
ej3: main.cpp ej3.cpp
	g++ $^ -o $@ $(FLAGS)
clean: 
	rm -f *.o *~ $(TARGETS)