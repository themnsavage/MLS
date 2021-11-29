#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MLS.h"
#include "vector.h"
int main()
{
    char projections[2] = {'C','H'};
    int number_of_lines = get_number_of_lines("data.txt");
    Vector *all_data = read_data("data.txt", number_of_lines);
    security_filter(all_data, number_of_lines, 2);
    project(all_data, number_of_lines, projections, 2);
    reset_indicator(all_data, number_of_lines);
    free_all_data(all_data, number_of_lines);
    return 0;
}