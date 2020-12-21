FLAGS = -std=c++17 -masm=intel -fconcepts -pthread -fopenacc -fopenmp -ggdb3 -Wpedantic -Wall -Wextra -Wconversion -Winline -Wsign-conversion -Weffc++ -Wstrict-null-sentinel -Wold-style-cast -Wnoexcept -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wsuggest-final-types -Wsuggest-final-methods  -Wsuggest-override -lquadmath
all: main

main: Cont_Test.cpp
	g++ $(FLAGS) Cont_Test.cpp -o main
