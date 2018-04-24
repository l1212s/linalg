all:
	g++ -std=c++11 test.cpp  -o blas

vim:
	vim matrix.h

run:
	./blas

clean:
	rm blas
