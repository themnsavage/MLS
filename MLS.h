#ifndef _MLS_H_
#define _MLS_H_
#include "vector.h"
int get_number_of_lines(char *filename);
Vector *read_data(char *filename, int number_of_lines);
void read_query(char *filename, Vector all_data[], int number_of_vectors);
#endif