openmp:
	g++ openmp.cpp -o openmp -lm -fopenmp -O2

mpi:
	mpic++ -fopenmp mpi.cpp -o mpi -lm -O2

hybrid:
	make mpi

all:
	make clean
	make openmp
	make mpi

clean:
	rm -rf openmp
	rm -rf mpi
	rm -rf hybrid
