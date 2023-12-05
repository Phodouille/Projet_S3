#ifndef LIST_H
#define LIST_H

#include "cell.h"

typedef struct s_d_list {
    t_d_cell **header; // Tableau de têtes pour chaque niveau
    int max_level;
} t_d_list;

t_d_list *create_list(int max_level);
void free_list(t_d_list *list);
void insert_cell(t_d_list *list, t_d_cell *new_cell);
void display_list(t_d_list *list);
void display_level(t_d_list *list, int level);
t_d_cell *find_cell(t_d_list *list, int value);
void measure_search_performance(t_d_list *list);

t_d_list *create_skip_list(int n);
void calculate_levels(int *levels, int n);
t_d_cell *search_classic(t_d_list *list, int value);
t_d_cell *search_optimized(t_d_list *list, int value);
#endif // LIST_H
