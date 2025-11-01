#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <unistd.h>
#include "engine_map_utils.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1


int main(){
    double windspeed = NAN;
    double current = NAN;

    printf("//////////////////////////////////////////\n"); 
    printf("//              ENGINE MAP              //\n");
    printf("//////////////////////////////////////////\n");
    printf("Welcome to the Engine Thurst Calculator!\n");
    printf("This program calculates the thrust produced by an engine based on the engine map, windspeed and current.\n");
    printf("There are two functions for this program:\n");
    printf("1. Clculate thrust for a specific set of windspeed and current, or\n");
    printf("2. Calculate thust for multiple sets of windspeed and current and export the results to thust_plot.txt\n");
    printf("You can also run an example case to see how the program works.\n\n");


    // EXAMPLE CASE
    // This is a simple example case that shows how the program works.
    // It calculates the thrust for two sets of windspeed and current and prints the results.
    char run_example = 'o';
    printf("Run example? (y/n): ");
    scanf(" %c", &run_example);
    printf("\n");
    if(run_example == 'y' || run_example == 'Y'){
        example();
        printf("\n");
    }

    // CREATE DATASET
    // This function culculates the thrust produced by the engine for a larger dataset of windspeed and current values and exports the results to thust_plot.txt.
    // It uses the engine_map function to calculate the thrust for each set of windspeed and current values.
    char create_dataset = 'o';
    printf("Create dataset? (y/n): ");
    scanf(" %c", &create_dataset);
    if(create_dataset == 'y' || create_dataset == 'Y'){
        printf("Exporting data to thrust_plot.txt...\n");
        sleep(1);
        int ct = output_data();
        if (ct == 1){
            perror("output_data() failed to export data\n");
            return EXIT_FAILURE;
        }
    }
    printf("\n");


    // EXIT PROGRAM
    char exit_program = 'o';
    printf("Exit program? (y/n): ");
    scanf(" %c", &exit_program);
    printf("\n");
    if(exit_program == 'y' || exit_program == 'Y'){
        return EXIT_SUCCESS;
    }

    // USER INPUT
    // This function takes user input for windspeed and current and calculates the thrust produced by the engine.
    // It uses the engine_map function to calculate the thrust for the given windspeed and current values.
    printf("/////////////////////////////////////////\n");
    printf("//            USER INPUT               //\n");
    printf("/////////////////////////////////////////\n");
    printf("Please enter the windspeed and current values to calculate the thrust produced by the engine.\n");
    printf("You can enter any value for windspeed and current.\n");
    
    
    printf("Windspeed (m/s): ");
    scanf("%lf", &windspeed);
    if(windspeed == NAN){
        perror("Invalid value for windspeed\n");
        return EXIT_FAILURE;
    }


    printf("Current (A): ");
    scanf("%lf", &current);
    if(current == NAN){
        perror("Invalid value for current\n");
        return EXIT_FAILURE;
    }

    double* thrust = engine_map(windspeed, current);
    if (thrust == NULL) {
        perror("engine_map() failed to calculate thrust\n");
        return EXIT_FAILURE;
    }

    printf("Thrust is: %lf\n N", *thrust);
    free(thrust);

    return EXIT_SUCCESS;
}


