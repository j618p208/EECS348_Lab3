#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MONTHS 12

float *min(float *a, float *b) {    //Minimum function that takes and returns pointers
    return (*a < *b) ? a:b;
}

float *max(float *a, float *b) {    //Maximum function that takes and returns pointers
    return (*a > *b) ? a:b;
}

float *read_data_from(char *filename) {
    float *month_sales_data = (float*)malloc(sizeof(float)*MONTHS);
    FILE *fp = fopen(filename, "r+");       //reads from the file
    if (fp == NULL) {printf("fp is null\n");}
    for (int i=0; i<MONTHS; i++) {
        fscanf(fp, "%f\n", &month_sales_data[i]);
    }
    return month_sales_data;        //Returns sales
}

float *average(const float *sales, int num_months) {    //Average function for sales
    float *value = (float*)malloc(sizeof(float));
    *value = 0;
    for (int i=0; i<num_months; i++) {
        *value = *value + *(sales+i);
    }
    *value /= num_months;
    return value;
}

float *minimum(const float *sales) {        //Minimum function for sales
    float *value = &sales[0];
    for (int i=1; i<MONTHS; i++) {
        value = min(value, &sales[i]);
    }
    return value;
}

float *maximum(const float *sales) {        //Maximum function for sales
    float *value = &sales[0];
    for (int i=1; i<MONTHS; i++) {
        value = max(value, &sales[i]);
    }
    return value;
}

void print_data(const char *months[], const float *sales, const float *min, const float *max, const float *ave) { //prints the data in desired format
    printf("%-12s %-10s\n", "Month", "Sales");
    for (int i=0; i<MONTHS; i++) {
        printf("%-12s $%10f\n", months[i], sales[i]);
    }

    char *char_min;
    char *char_max;
    for (int i=0; i<MONTHS; i++) {
        if (*min == sales[i]) {
            char_min = months[i];
        } else if (*max == sales[i]) {
            char_max = months[i];
        }
    }
    printf("\nSales summary:\n");
    printf("Minimum sales:  $%10f  (%s)\n", *min, char_min);
    printf("Maximum sales:  $%10f  (%s)\n", *max, char_max);
    printf("Average sales:  $%10f\n", *ave);

    printf("\nSix-Month Moving Average\n");
    for (int i=0; i<=6; i++) {
        printf("%-12s - %-12s $%10f\n", months[i], months[i+5], *average(&*(sales+i), 6));
    }

    
    printf("\nSales Report (Highest to Lowest):\n");
    printf("%-12s %-10s\n", "Month", "Sales");
    char *month;
    float *value;
    for (int i=0; i<MONTHS; i++) {
        value = maximum(sales);         //Finds the maximum value
        for (int i=0; i<MONTHS; i++) {
            if (*value == sales[i]) {   //Gets the correct Month
                month = months[i];
            }
        }
        printf("%-12s $%10f\n", month, *value);
        *value = 0;             //Final use of sales in the program so it can be modified
    }
}

int main() {
    float *sales = read_data_from("Cprogram1/data.txt");
    const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    float *ave = average(sales, MONTHS);
    float *min = minimum(sales);
    float *max = maximum(sales);
    
    print_data(months, sales, min, max, ave);
    return 0;
}