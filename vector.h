#ifndef _VECTOR_H_
#define _VECTOR_H_
typedef struct _data
{
    char field_name;
    int value;
} Data;

typedef struct _vector
{
    Data **data; // array of data 
    int used; // index that indicate how full the vector is
    int capacity; // current max size of vector
    int indicator; // helper variable that helps filter documents based on find, security level, and sort
} Vector;

Data *create_data(char field_name, int value);

void initiate_vector(Vector *v);
void free_vector(Vector vector);
void free_all_data(Vector all_data[], int number_of_vectors);
void push_back(Vector *vector, char field_name, int value);

int get_vector_size(Vector vector);
char get_field_name_at(Vector vector, int index);
int get_value_at(Vector vector,int index);

void print_vector(Vector vector);
void print_all_data(Vector *all_data, int number_vectors);

void set_indicator_off(Vector *vector);
void set_indicator_on(Vector *vector);
void reset_indicator(Vector *all_data, int number_vectors);
void security_filter(Vector all_data[], int number_vectors, int security_level);
int find_value_with_field_name(Vector vector, char element);
void find(Vector all_data[], int number_of_vectors, char field_name, char operator, int value);
void project(Vector all_data[], int number_vectors, char project_elements[], int number_of_project_elements);
Vector *find_smallest_vector(Vector all_data[], int number_vectors, char search_for_field_name);
Vector *find_largest_vector(Vector all_data[], int number_vectors, char search_for_field_name);
void sort(Vector all_data[], int number_vectors, int security_level,char field_name_sorting_by,int sorting_type);
#endif