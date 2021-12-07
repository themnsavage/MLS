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
        push_back(&all_data[line_counter], 'A', line_counter+1); // making unique key A
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

void read_query(char *filename, Vector all_data[], int number_of_vectors)
{
    FILE *fp = fopen(filename, "r");
    char line[150];
    int security_level;
    for(int i = 1; !feof(fp); i++)
    {
        printf("//Query %d\n", i);
        security_level = -1;
        fgets(line, 150, fp);
        if(strstr(line, "FIND"))
        {
            sscanf(line,"%*s%d", &security_level);
            if(security_level != -1) security_filter(all_data, number_of_vectors, security_level);

            char field_name, operator;
            int value = 0;
            
            fgets(line, 150, fp);
            while(!strchr(line, ';'))
            {
                sscanf(line,"%c%*c%c%*c%d", &field_name, &operator, &value);
                find(all_data, number_of_vectors, field_name, operator, value);
                fgets(line, 150, fp);
            }

            char *l = line;
            char c[50];
            int offset;
            int count = 0;
            char projections[50];
            while(sscanf(l, "%s%n", c, &offset) == 1)
            {
                if(c[0] != ';' && c[0] != ' ')projections[count++] = c[0];
                l += offset;
            }
            //for(int i = 0; i < count; i++)printf("%c", projections[i]);
            project(all_data, number_of_vectors, projections, count);
        }
        else if(strstr(line, "SORT"))
        {
            sscanf(line,"%*s%d", &security_level);
            if(security_level != -1) security_filter(all_data, number_of_vectors, security_level);
            fgets(line, 150, fp);

            char field_name;
            int sort_type=0;
            sscanf(line, "%c%*c%*c%*c%d", &field_name, &sort_type);
            sort(all_data, number_of_vectors, field_name, sort_type);
        }
        else
        {
            printf("ERROR - No such operation\n");
            while(!strchr(line, ';'))
            {
                fgets(line, 150, fp);
            }
        }
        reset_indicator(all_data, number_of_vectors);
    }
    

    fclose(fp);
}