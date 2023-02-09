#include <stdio.h>
#include <stdlib.h>

#define MONTHS 12

float *read_data_from(char *filename) {
    float *month_sales_data = (float*)malloc(sizeof(float)*MONTHS);
    FILE *fp = fopen(filename, "r+");       //reads from the file


    for (int i=0; i<MONTHS; i++) {
        fscanf(fp, "%f\n", &month_sales_data[i]);
    }
    return month_sales_data;
}

float *average(const float *sales) {
    float *value = 0;
    for (int i=0; i<MONTHS; i++) {
        *value += sales[i];
    }
    *value /= MONTHS;
    return value;
}

float *minimum(const float *sales) {
    float *value = 0;
    for (int i=0; i<MONTHS; i++) {
        *value = min(*value, sales[i]);
    }
    return value;
}

float *maximum(const float *sales) {
    float *value = 0;
    for (int i=0; i<MONTHS; i++) {
        *value = max(*value, sales[i]);
    }
    return value;
}

void print_data(const char *months[], const float *sales, const float *min, const float *max, const float *ave) { //prints the data in desired format
    printf("Month           Sales\n");
    for (int i=0; i<MONTHS; i++) {
        printf("%-15s $%10f\n", months[i], sales[i]);
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
    printf("Average sales:  $%10f\n", *min);
}

int main() {
    float *sales = read_data_from("Cprogram1/data.txt");
    float *ave = average(sales);
    float *min = minimum(sales);
    float *max = maximum(sales);
    const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    print_data(months, sales, min, max, ave);
    return 0;
}