#include <stdio.h>
#include <stdlib.h>

/**
* @author Andrei Ciobanu
* @date 9 DEC, 2010
*/

long long *sieve(size_t a_size);
void show_primes(long long max_size);

/**
* Returns the Eratostene Sieve in array form .
* This function is needed for the show_primes function .
* @param a_size The size of the sieve .
* @return A pointer to an array of shorts allocated on the heap .
*/
long long *sieve(size_t a_size)
{
	size_t i, j;
	long long *res = NULL;
	res = malloc(a_size * sizeof(*res));

	if (NULL == res) {
		printf("Memory allocation failed. n");
		abort();
	}

	for (i = 0; i < a_size; ++i) {
		res[i] = 1;
	}

	for (i = 2; i * i < a_size ; ++i) {
		if(res[i] == 1) {
			for (j = 2; j * i < a_size ; ++j) {
				res[i*j] = 0;
			}
		}
	}

	return (res);
}

/**
* Prints on the screen all the prime numbers in between the interval
* [0..max_size) .
* @param The maximum number for the primes interval .
*/
void show_primes(long long max_size) {
	int i;
	long long *sv = sieve(max_size);
	long long count = 0;
	for (i = 2	; i < max_size; ++i) {
		if (sv[i]) {
			printf("%d ", i);
			count++;
		}
	}
	printf("COUNT: %lld\n", count);
	printf("n");
	free(sv);
}

int main(int argc, char *argv[])
{
	printf("Showing primes < 33554432:n");
	show_primes(33554432);
	return (0);
}
