#include <stdio.h>
#include <stdlib.h>

#define MONTHS 12

float *read_data_from(char *filename) {
    float *month_sales = (float*)malloc(sizeof(float)*MONTHS);
    FILE *fp = fopen(filename, "r+");       //reads from the file
    for (int i=0; i<MONTHS; i++) {
        fscanf(fp, "%f\n", &month_sales[i]);
    }
    return month_sales;
}

void print_data(const char *months[], const float *sales) { //prints the data in desired format
    printf("Month           Sales\n");
    for (int i=0; i<MONTHS; i++) {
        printf("%30s %10f\n", months[i], sales[i]);
    }
}

int main() {
    float *sales = read_data_from("data_txt");
    const char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    print_data(months, sales);
    return 0;
}