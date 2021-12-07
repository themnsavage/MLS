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

int find_value_with_field_name(Vector vector, char element)
{
    for(int i = 0; i < vector.used; i++)
    {
        if(vector.data[i]->field_name == element) return vector.data[i]->value;
    }
    return -99; // not found 
}

void find(Vector all_data[], int number_of_vectors, char field_name, char operator, int value)
{
    if(field_name == 'Z') return;

    for(int i = 0; i < number_of_vectors; i++)
    {
       int found_value = find_value_with_field_name(all_data[i], field_name); // note also finds out if field_name exists in the vector by returning -99 if not

       if(found_value == -99)
       {
           set_indicator_off(&all_data[i]);
       }
       else
       {
           if(operator == '=' && found_value != value)
           {
               set_indicator_off(&all_data[i]);
           }
           else if(operator == '>' && found_value <= value)
           {
               set_indicator_off(&all_data[i]);
           }
           else if(operator == '<' && found_value >= value)
           {
               set_indicator_off(&all_data[i]);
           }
       }
    }
}

void project(Vector all_data[], int number_vectors, char project_elements[], int number_of_projections)
{
    
    if(number_of_projections == 1 && project_elements[0] == 'X')
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
        int flag = 0;
        for(int i = 0; i < number_vectors; i++)
        {
            if(all_data[i].indicator)
            {
                for(int j = 0; j < all_data[i].used; j++)
                {
                    for(int z = 0; z < number_of_projections; z++)
                    {
                        if(all_data[i].data[j]->field_name == project_elements[z])
                        {
                            printf("%c: %d ",all_data[i].data[j]->field_name, all_data[i].data[j]->value);
                            flag = 1;
                        }
                    }
                }
                if(flag)printf("\n");
            }
            flag = 0;
        }
    }

}

Vector *find_smallest_vector(Vector all_data[], int number_vectors,char search_for_field_name)
{
    Vector *min = NULL;
    int min_index;
    for(int i = 0; i < number_vectors; i++)
    {
       if(all_data[i].indicator != 0) // does not reach requirements or already was return from prev search
       {
           for(int j = 0; j < all_data[i].used; j++)
           {
               char curr_field_name = all_data[i].data[j]->field_name;
               int curr_value = all_data[i].data[j]->value;
               if(min == NULL && curr_field_name == search_for_field_name)
               {
                   min = &all_data[i];
                   min_index = j;
               }
               else if(curr_field_name == search_for_field_name && curr_value < min->data[min_index]->value)
               {
                   min = &all_data[i];
                   min_index = j; 
               }
           }
       }
    }

    return min;
}

Vector *find_largest_vector(Vector all_data[], int number_vectors,char search_for_field_name) 
{
    Vector *max = NULL;
    int max_index;
    for(int i = 0; i < number_vectors; i++)
    {
       if(all_data[i].indicator != 0) // does not reach requirements or already was return from prev search
       {
           for(int j = 0; j < all_data[i].used; j++)
           {
               char curr_field_name = all_data[i].data[j]->field_name;
               int curr_value = all_data[i].data[j]->value;
               if(max == NULL && curr_field_name == search_for_field_name)
               {
                   max = &all_data[i];
                   max_index = j;
               }
               else if(curr_field_name == search_for_field_name && curr_value > max->data[max_index]->value)
               {
                   max = &all_data[i];
                   max_index = j;
               }
           }
       }
    }
    return max;
}


void sort(Vector all_data[], int number_vectors, char field_name_sorting_by, int sorting_type)
{
   find(all_data, number_vectors, field_name_sorting_by, ' ', -1); // filter out documents that does not have field_name that we sorting by
   if(sorting_type != 1 && sorting_type != -1) 
   {
       printf("sorting type is not 1 or -1 (in sort function)\n");
       exit(1);
   }

   // get first smallest/biggest vector 
   Vector *curr_vector = NULL;
   if(sorting_type == 1) curr_vector = find_smallest_vector(all_data, number_vectors,field_name_sorting_by);
   else curr_vector = find_largest_vector(all_data, number_vectors,field_name_sorting_by);

   // keep getting all smallest/biggest vector one by one until none are left or dont reach requirements 
   while (curr_vector != NULL)
   {
       for(int i = 0; i < curr_vector->used; i++) printf("%c: %d ", curr_vector->data[i]->field_name, curr_vector->data[i]->value); 
       printf("\n");

       set_indicator_off(curr_vector); // set indicator off for curr_vector to prevent searching for it again
       
       // finds curr_vector based on acsending(1) or descending order(-1)
       if(sorting_type == 1) curr_vector = find_smallest_vector(all_data, number_vectors,field_name_sorting_by);
       else curr_vector = find_largest_vector(all_data, number_vectors,field_name_sorting_by);
   }
   
}