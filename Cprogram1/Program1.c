#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MONTHS 12

float *min(float *a, float *b) {
    return (*a < *b) ? a:b;
}

float *max(float *a, float *b) {
    return (*a > *b) ? a:b;
}

float *read_data_from(char *filename) {
    float *month_sales_data = (float*)malloc(sizeof(float)*MONTHS);
    FILE *fp = fopen(filename, "r+");       //reads from the file
    if (fp == NULL) {printf("fp is null\n");}
    for (int i=0; i<MONTHS; i++) {
        fscanf(fp, "%f\n", &month_sales_data[i]);
    }
    return month_sales_data;
}

float *average(const float *sales, int num_months) {
    float *value = (float*)malloc(sizeof(float));
    *value = 0;
    for (int i=0; i<num_months; i++) {
        *value = *value + *(sales+i);
    }
    *value /= num_months;
    return value;
}

float *minimum(const float *sales) {
    float *value = &sales[0];
    for (int i=1; i<MONTHS; i++) {
        value = min(value, &sales[i]);
    }
    return value;
}

float *maximum(const float *sales) {
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
    for (int i=0; i<6; i++) {
        printf("%-12s - %-12s $%10f\n", months[i], months[i+6], *average(&*(sales+i), 6));
    }

    
    /*printf("\nSales Report (Highest to Lowest):\n");
    printf("%-12s %-10s\n", "Month", "Sales");
    char *month;
    for (int i=0; i<MONTHS; i++) {
        //float *value = max(sales);
        printf("%-12s $%10f\n", month, *value);
        *value = 0;
    }*/
}

void print_highest_to_lowest(const char *months[], const float *sales) {
    char *months_copy[MONTHS];
    for(int i = 0; i < MONTHS; ++i) {
        char *month = (char*)malloc(sizeof(months[i]));
        strcpy(month, months[i]);
        months_copy[i] = month;
    }

    
    float *sales_copy = (float*)malloc(sizeof(float)*MONTHS);
    for(int i = 0; i < MONTHS; ++i) {
        sales_copy[i] = sales[i];
    }

    printf("\nSales Report (Highest to Lowest):\n");
    printf("%-12s %-10s\n", "Month", "Sales");
    char *month;
    float *value;
    for (int i=0; i<MONTHS; i++) {
        value = maximum(sales_copy);
        for (int i=0; i<MONTHS; i++) {
            if (*value == sales_copy[i]) {
                month = months[i];
            }
        }
        printf("%-12s $%10f\n", month, *value);
        *value = 0;
    }

    // for(int i = 0; i < MONTHS; ++i) {
    //     printf("%s %f\n", months_copy[i], sales_copy[i]);
    // }
}

int main() {
    float *sales = read_data_from("Cprogram1/data.txt");
    const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    /*float *ave = average(sales, MONTHS);
    float *min = minimum(sales);
    float *max = maximum(sales);
    
    print_data(months, sales, min, max, ave);*/

    print_highest_to_lowest(months, sales);
    return 0;
}