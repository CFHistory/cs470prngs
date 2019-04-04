/**
 * This c program is intended to take in text files that correspond to the results of running a pseuod-random number generator algorithm and analyze the contents of those files.
 *
 *
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Define the maximum number of values in the randomdata.values array
#define MAXVALS 50

//Enum that defines what prng algorithm was used to generate these values
enum algorithm{MiddleSquare, LCG, ThreeFry};



//define the struct here
typedef struct {
    enum algorithm alg;          //The algorithm used to generate these values
    double time;            //The wall time for when these values were generated
    int cores;              //How many cores were used to generate these values 
                            //  (serial versions should specify 0 cores)
    int numvals;         //How many values were generated 
    double values[MAXVALS]; //Uninitialized array of the values generated by this algorithm. 
                     
} randomdata;

typedef struct {
    float sum;
    float mean;
    float std_deviation;
    double min;
    double max;
    
} analysis;



void* values_tostring(randomdata data, char* returnto){
    
    char retval[50000] = "[ ";
    char temp[50000] = "";
    for(int i = 0; i < data.numvals; i++){ 
        sprintf(temp, "%.3f ", data.values[i]);
        strcat(retval, temp);
    }
    strcat(retval, "]");
    strcpy(returnto, retval);
}

void* report_analysis(randomdata data){
    
}

//standard deviation function 
void* spread(randomdata data, analysis* results){
    float sum = 0.0;
    float mean;
    float std_deviation = 0.0;
    float min;
    float max = 0.0; 

    //Loop through the entire set of values, getting sum, min and max values
    for(int i = 0; i < data.numvals; i++){
        sum += data.values[i];
        if(i == 1 || data.values[i] < min){
            min = data.values[i];
        }
        if(data.values[i] > max){
            max = data.values[i];
        }
    }
    mean = sum/data.numvals;

    for(int j = 0; j < data.numvals; j++){
        std_deviation += pow(data.values[j] - mean, 2);
 
    }
    results->sum = sum;
    results->mean = mean;
    results->min = min;
    results->max = max;
    results->std_deviation = sqrt(std_deviation/data.numvals);
    printf("Done!\n");
}


//period identification function 
void repeats(randomdata data){

}

//main

int main(int argc, char* argv[]){
    //for now, create a randomdata struct manually and send to spread and send to the functions
	
    randomdata data;
    randomdata testdata;

    data.alg = LCG;
    data.time = 4.555;
    data.cores = 0;
    data.numvals = 5;
    data.values[0] = 123; 
    data.values[1] = 234; 
    data.values[2] =  345; 
    data.values[3] =  456; 
    data.values[4] =  567; 
     
    char arrayvals[500];
    values_tostring(data, arrayvals);
    analysis data_a;
    spread(data, &data_a);

    printf("Values of this array: %s\n", arrayvals);
    printf("Standard Deviation of the test struct is %f\n", data_a.std_deviation);
    //in the future, parse in data and send it out to these functions to get values back
    
    if(argc < 2){
        printf("ERROR: Please provide an infile.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[100];
    FILE* datafile = fopen(argv[1], "r");
    
    //Hard code certain things for now
    testdata.alg = LCG;
    testdata.numvals = 0;
    while((fscanf(datafile, "%s", buffer) > 0) && testdata.numvals < MAXVALS){
        testdata.values[testdata.numvals] = atof(buffer);
        testdata.numvals++;
    }
    fclose(datafile);
    analysis testdata_a; 
    char newvals[50000];

    values_tostring(testdata, newvals);
    spread(testdata, &testdata_a);
    printf("Values of this array: %s\n", newvals);
    printf("Standard deviation of data: %f\n", testdata_a.std_deviation);


}
