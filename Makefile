TARGETS=middlesquare_ser middlesquare_par

all: $(TARGETS)

middlesquare_ser: 
	gcc -std=c99 -o middlesquare_ser middlesquare_ser.c

middlesquare_par:
	gcc -fopenmp -std=c99 -o middlesquare_par middlesquare_par.c
  
clean: 
	rm -f middlesquare_ser
	rm -f middlesquare_par
