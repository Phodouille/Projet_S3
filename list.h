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

#endif // LIST_H
