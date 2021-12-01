#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "MLS.h"
#include "vector.h"


int get_number_of_lines(char *filename)
{
    FILE *fp = fopen(filename, "r");

    if(fp == NULL) exit(1); // does file exist?
    
    const int line_size = 150;
    char line[line_size];
    int count = 0;
    while(!feof(fp))
    {
        fgets(line, line_size, fp);
        count++;
    }
    fclose(fp);
    return count;
}

Vector *read_data(char *filename, int number_of_lines)
{
    FILE *fp = fopen(filename, "r");

    if(fp == NULL) exit(1); // does file exist?

    Vector *all_data = malloc(sizeof(Vector)*number_of_lines);
    for(int i = 0; i < number_of_lines; i++)
    {
        initiate_vector(&all_data[i]);
    }

    const int line_size = 150;
    char line[150];
    int line_counter = 0;
    while(!feof(fp))
    {
        fgets(line, line_size, fp);
        char *l = line;
        char c[150];
        int offset;
        int counter = 0;
        char field_name;
        int value;
        while (sscanf(l, "%s%n", &c, &offset) == 1)
        {
            if(counter % 2 == 0)
            {
                if(counter != 0) 
                {
                    push_back(&all_data[line_counter], field_name, value);            
                }
                field_name = c[0];
            }
            else
            {
                value = atoi(c);
            }
            counter++;
            l += offset;
        }

        push_back(&all_data[line_counter], field_name, value);
        line_counter++;
    }
    fclose(fp);
    return all_data;
}
