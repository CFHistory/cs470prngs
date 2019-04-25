<<<<<<< HEAD
TARGETS=middlesquare_ser middlesquare_par lcg_ser lcg_par monteStock darts
=======
TARGETS=middlesquare_ser middlesquare_par lcg monteStock
>>>>>>> 85566e4d40cacc91fd85016fc88b286d96b9aad6

all: $(TARGETS)

middlesquare_ser: 
	gcc -std=c99 -o middlesquare_ser middlesquare_ser.c

middlesquare_par:
	gcc -fopenmp -std=c99 -o middlesquare_par middlesquare_par.c
  
lcg_ser:
	gcc -std=c99 -o lcg_ser lcg_ser.c

lcg_par:
	gcc -fopenmp -std=c99 -o lcg_par lcg_par.c

monteStock:
	gcc -std=c99 -o monteStock monteCarloStock.c -lm

clean: 
	rm -f middlesquare_ser
	rm -f middlesquare_par
	rm -f lcg
	rm -f lcg_ser
	rm -f lcg_par
	rm -f monteStock
	rm -f darts
