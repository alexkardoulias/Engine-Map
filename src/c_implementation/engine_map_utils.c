#include <stdio.h>

#include <stdlib.h>
#include <stdint.h>

#include <math.h>
#include <plot.h>


void example();
double* engine_map(double, double);
int output_data();


void example() {
    double * thrust = NULL;
    
    printf("//////////////////////////////////////\n");
    printf("//          EXAPMPLE CASE           //\n");
    printf("//////////////////////////////////////\n");

    printf("Exapmple 1:\n\n");
    printf("Windspeed = 20 m/s\n");
    printf("Current = 22 A\n");
    thrust = engine_map(20, 22);

    printf("Thrust is: %0.2lf N\n", *thrust);
    free(thrust);
    printf("--------------------------------------\n");
    
    printf("Exapmple 2:\n\n");
    printf("Windspeed = 20 m/s\n");
    printf("Current = 30 A\n");
    thrust = engine_map(20, 30);
    
    printf("Thrust is: %0.2lf N\n", *thrust);
    printf("--------------------------------------\n");

    free(thrust);

    return;
}

double* engine_map(double windspeed, double current) {
    // Engine Coefficients
    double ** p = (double**)malloc(3*sizeof(double**));
    if (p == NULL) {
        perror("NULL pointer (1)\n");
        
        return NULL;
    }

    for (int i=0; i<3; i++) {
        p[i] = (double*)malloc(3*sizeof(double*));
        
        if (p[i] == NULL) {
            perror("NULL pointer (2)");
            
            for (int j=0; j<i; j++) {
                free(p[j]);
            }

            return NULL;
        }
    }

    p[0][0] = 0.4304;
    p[1][0] = 0.4304;
    p[0][1] = 0.7532;
    p[2][0] = -0.003073;
    p[1][1] = -0.00794;
    p[0][2] = -0.005196;

    double x = windspeed;
    double y = current;
    
    // coefficients from matlab interpolation witn 95% confidence bounds
    double * thrust = (double*)malloc(sizeof(double*));
    *thrust = p[0][0] + p[1][0] * x + p[0][1] * y + p[2][0] * pow(x, 2) + p[1][1] * x * y + p[0][2] * pow(y, 2);

    // Free allocated memory
    for (int i = 0; i < 3; i++) {
        free(p[i]);
    }
    free(p);

    return thrust;
}

int output_data() {
    FILE *fp = fopen("thrust_data.txt", "w");
    if (fp == NULL) return 1;

    // Header for clarity
    fprintf(fp, "Current\tWindspeed\tThrust\n");

    // Generate data points
    double* thrust = NULL;
    for (double current = 10; current <= 30; current += 2) {
        for (double windspeed = 0; windspeed <= 25; windspeed += 0.5) {
            thrust = engine_map(windspeed, current);
            if (thrust == NULL) {
                perror("engine_map() failed to calculate thrust\n");
                fprintf(fp, "engine_map() failed to calculate thrust. Closing file.\n");
                fclose(fp);
                return 1;
            }

            fprintf(fp, "%.2lf\t%.2lf\t%.2lf\n", current, windspeed, *thrust);
            free(thrust);
        }
    }

    fclose(fp);

    return 0;
}
