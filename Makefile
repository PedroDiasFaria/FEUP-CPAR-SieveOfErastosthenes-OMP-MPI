all: matrizvector.cpp prodescalar.cpp
	mpiCC matrizvector.cpp -o matrizvector -l papi -fopenmp -O2
	mpiCC prodescalar.cpp -o prodescalar -l papi -fopenmp -O2

clean:
	rm -f *.o matrizvector prodescalar
