TARGETS=threefry_ser threefry_par

all: $(TARGETS)

threefry_ser: 
	gcc -std=c99 -o threefry_ser threefry_ser.c

threefry_par:
	gcc -fopenmp -std=c99 -o threefry_par threefry_par.c


clean: 
	rm -f threefry_ser
	rm -f threefry_par
