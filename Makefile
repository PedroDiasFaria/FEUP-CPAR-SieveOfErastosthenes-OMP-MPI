all: matrizvector.cpp prodescalar.cpp
	mpiCC.openmpi -o matrizvector matrizvector.cpp -O2
	mpiCC.openmpi -o prodescalar prodescalar.cpp -O2

clean:
	rm -f *.o matrizvector prodescalar
