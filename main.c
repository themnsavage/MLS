#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MLS.h"
#include "vector.h"
int main()
{
    int number_of_lines = get_number_of_lines("data.txt");
    Vector *all_data = read_data("data.txt", number_of_lines);
    read_query("test.txt", all_data, number_of_lines);


    free_all_data(all_data, number_of_lines);
    return 0;
}