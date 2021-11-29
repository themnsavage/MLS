#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"


Data *create_data(char field_name, int value)
{
    Data *d = malloc(sizeof(Data));
    d->field_name = field_name;
    d->value = value;
    return d;
}

void initiate_vector(Vector *vector)
{
    vector->capacity = 3;
    vector->data = malloc(vector->capacity * sizeof(Data));
    vector->used = 0;
    vector->indicator = 1;
}

void free_vector(Vector vector)
{
   free(vector.data);
}

void free_all_data(Vector all_data[], int number_of_vectors)
{
    for(int i = 0; i < number_of_vectors; i++)
    {
        free_vector(all_data[i]);
    }
}

//add to the back of the vector
void push_back(Vector *vector, char field_name, int value)
{
    Data *d = create_data(field_name,value);

    if(vector->used == vector->capacity) // is vector full? 
    {
        vector->capacity += vector->capacity;
        vector->data = realloc(vector->data, vector->capacity * sizeof(Data)); 
    }

    vector->data[vector->used++] = d; // add new data to vector
}
int get_vector_size(Vector vector)
{
    return vector.used;
}
char get_field_name_at(Vector vector, int index)
{
    if(index < 0 || index >= vector.used)
    {
        printf("%d is out of bounds of vector in get_field_name_at()",index);
        exit(1);
    }
    return vector.data[index]->field_name;
}

int get_value_at(Vector vector, int index)
{
    if(index < 0 || index >= vector.used)
    {
        printf("%d is out of bounds of vector in get_value_at()",index);
        exit(1);
    }
    return vector.data[index]->value;
}

void print_vector(Vector vector)
{
    for(int i = 0; i < vector.used; i++)
    {
        printf("%c: %d ", vector.data[i]->field_name, vector.data[i]->value);
    }
    printf("\n");
}

void print_all_data(Vector *all_data, int number_of_vectors)
{
    for(int i = 0; i < number_of_vectors; i++)
    {
        printf("----%d----\n", i+1);
        print_vector(all_data[i]);
        printf("\n");
    }
}

void set_indicator_off(Vector *vector)
{
    vector->indicator = 0;
}

void set_indicator_on(Vector *vector)
{
    vector->indicator = 1;
}

void reset_indicator(Vector *all_data, int number_vectors)
{
    for(int i = 0; i < number_vectors; i++)
    {
        set_indicator_on(&all_data[i]);
    }
}



void security_filter(Vector all_data[], int number_vectors, int security_level)
{
    for (int i = 0; i < number_vectors; i++)
    {
        for(int j = 0; j < all_data[i].used; j++)
        {
            if(all_data[i].data[j]->field_name == 'Y' && all_data[i].data[j]->value > security_level)
            {
                set_indicator_off(&all_data[i]);
            }
        }
    }   
}

void find(Vector all_data[], int number_of_vectors, char field_name, char operator, int value)
{
    
}

void project(Vector all_data[], int number_vectors, char project_elements[], int number_of_project_elements)
{
    if(number_of_project_elements == 1 && project_elements[0] == 'X')
    {
        for(int i = 0; i < number_vectors; i++)
        {
            if(all_data[i].indicator)
            {
                print_vector(all_data[i]);
            }
        }
    }
    else
    {
        for(int i = 0; i < number_vectors; i++)
        {
            if(all_data[i].indicator)
            {
                for(int j = 0; j < all_data[i].used; j++)
                {
                    for(int z = 0; z < number_of_project_elements; z++)
                    {
                        if(all_data[i].data[j]->field_name == project_elements[z])
                        {
                            printf("%c: %d ",all_data[i].data[j]->field_name, all_data[i].data[j]->value);
                        }
                    }
                }
                printf("\n");
            }
        }
    }
}