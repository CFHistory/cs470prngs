#include <threefry.h>

/**
 *  Usage: ./threefry_ser unsigned long seed, unsigned long count
 */
int main(int argc, char* argv[]) {
    unsigned long seed;
    unsigned long count;    

    


    if(argc < 3){
        printf("USAGE: 3fry_ser seed(unsigned long) count(unsigned long)\n");
        exit(EXIT_FAILURE);
    } 

    seed = strtoul(argv[1]);
    count = strtoul(argv[2]);

    threefry2x64_key_t key = {{0,0}};
    threefry2x64_ctr_t ctr = {{0,0}};

    for(int i = 0; i < 5; i++){
        printf("Result: %d\n", threefry2x64(ctr, key));
    }
    

}
