TARGETS=middlesquare_ser middlesquare_par

all: $(TARGETS)

middlesquare_ser: 
	gcc -o middlesquare_ser middlesquare_ser.c

middlesquare_par:
	gcc -fopenmp -o middlesquare_par middlesquare_par.c
  
clean: 
	rm -f middlesquare_ser
	rm -f middlesquare_par
