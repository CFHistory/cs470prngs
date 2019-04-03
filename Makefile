TARGETS=middlesquare_ser middlesquare_par lcg monteStock

all: $(TARGETS)

middlesquare_ser: 
	gcc -std=c99 -o middlesquare_ser middlesquare_ser.c

middlesquare_par:
	gcc -fopenmp -std=c99 -o middlesquare_par middlesquare_par.c
  
lcg:
	gcc -std=c99 -o lcg lcg.c

monteStock:
	gcc -std=c99 -o monteStock monteCarloStock.c -lm

clean: 
	rm -f middlesquare_ser
	rm -f middlesquare_par
	rm -f lcg
	rm -f monteStock
