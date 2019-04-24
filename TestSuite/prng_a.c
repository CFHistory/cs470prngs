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
#define MAXVALS 5000
//Define the number of buckets for the chisquared
#define BUCKETCT 10
//#define DEBUG

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
    
    char retval[500000] = "[ ";
    char temp[500000] = "";
    for(int i = 0; i < data.numvals; i++){ 
        sprintf(temp, "%.3f ", data.values[i]);
        strcat(retval, temp);
    }
    strcat(retval, "]");
    strcpy(returnto, retval);
}

void* report_analysis(randomdata data){
    
}

void chisquared(randomdata data, analysis results){
    //perform the chi squared test in here
    //define constant p = 0.05 (could be lower)
    //
    // divide the range of data by 10 (could go for smaller buckets)
    // count the number of values in each bucket
    // determine how many 'should' be in each bucket (total/# buckets)
    // subtract expected from actual, square it, divide by expected
    // add up the resulting values
    //
    // p value needs to be looked up on a table, unfortunately
    // so, do we calcluate p value?

    //check for results to have been defined

    //define data structure of buckets- each of the
    int buckets[BUCKETCT];
    double chiscore[BUCKETCT];
    double chisum = 0.0;
    for(int j = 0; j < BUCKETCT; j++){
        buckets[j] = 0;
    }    

    double range = (results.max - results.min);
    double bucketsize = range/BUCKETCT;
    double desiredspread = (data.numvals/BUCKETCT);
    for(int i = 0; i < data.numvals; i++){
        buckets[(int)((data.values[i] - results.min)/bucketsize)] += 1; 
    }


    for(int k = 0; k < BUCKETCT; k++){
        printf("Bucket %i (%.2f to %.2f): %d\n", k, (results.min + (bucketsize * k)), (results.min + (bucketsize * (k + 1))), buckets[k]);
        //subtract expected from actual
        chiscore[k] = buckets[k] - desiredspread;
        //square it
        chiscore[k] *= chiscore[k];
        //divide by expected
        chiscore[k] = chiscore[k]/desiredspread;
        //add up results         
        chisum += chiscore[k];
    }
    
    for( int c = 0; c < BUCKETCT; c++){
        printf("Bucket %i chi: %.2f\n", c, chiscore[c]);
    }    
    printf("Chiscore overall is %.3f\n", chisum);
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

    for(int j = 0; j < data.numvals; j++) {
        std_deviation += (pow(data.values[j] - mean, 2)/data.numvals);
    }
    results->sum = sum;
    results->mean = mean;
    results->min = min;
    results->max = max;
    results->std_deviation = sqrt(std_deviation);
}


//period identification function 
void repeats(randomdata data){

}

//main

int main(int argc, char* argv[]){
    //for now, create a randomdata struct manually and send to spread and send to the functions
    
    randomdata testdata;
    #ifdef DEBUG
    randomdata data;

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
    #endif    

    if(argc < 2){
        printf("ERROR: Please provide an infile.\n");
        exit(EXIT_FAILURE);
    }

    unsigned long buffer = 0;
    FILE* datafile = fopen(argv[1], "r");
    
    //Hard code certain things for now
    testdata.alg = LCG;
    testdata.numvals = 0;
    while((fscanf(datafile, "%lu", &buffer) > 0) && testdata.numvals < MAXVALS){
        float tempVal = (float) buffer;
        testdata.values[testdata.numvals] = tempVal;
        testdata.numvals++;
    }
    fclose(datafile);
    analysis testdata_a; 
    char newvals[50000];

    values_tostring(testdata, newvals);
    spread(testdata, &testdata_a);
    #ifdef DEBUG
    printf("Values of this array: %s\n", newvals);
    #endif
    printf("STANDARD DEVIATION: %.3f\n", testdata_a.std_deviation);
    float range = (testdata_a.max - testdata_a.min);
    printf("RANGE: %.3f\n", range);
    printf("MEAN: %.3f\n", testdata_a.mean);
    printf("~~~~~~~~~~~~~~~~~~~~~\n");
    chisquared(testdata, testdata_a);
    float tempSD = ((testdata_a.std_deviation)/range) * 100;
    printf("Standard Deviation is %.2f percent of range\n", tempSD);
    printf("The minimum value is %.2f standard deviations away from the mean\n", ((testdata_a.mean - testdata_a.min)/testdata_a.std_deviation));
    printf("The maximum value is %.2f standard deviations away from the mean\n", ((testdata_a.max - testdata_a.mean)/testdata_a.std_deviation));


}
