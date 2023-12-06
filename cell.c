#include "cell.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

t_d_cell *create_cell(int value, int max_level) {
    int level = max_level;
    
    t_d_cell *cell = malloc(sizeof(t_d_cell));
    if (!cell) {
        perror("Unable to allocate memory for the cell");
        return NULL;
    }

    // Allocation de mémoire pour les pointeurs 'next'
    cell->next = malloc(sizeof(t_d_cell *) * (max_level + 1));
    if (!cell->next) {
        perror("Unable to allocate memory for the next pointers");
        free(cell); // Ne pas oublier de libérer la cellule si l'allocation suivante échoue
        return NULL;
    }

    for (int i = 0; i <= max_level; i++) {
        cell->next[i] = NULL;
    }

    cell->value = value;
    cell->level = level;

    return cell;
}


void free_cell(t_d_cell *cell) {
    if (cell) {
        free(cell->next);
        free(cell);
    }
}


int random_level(int max_level) {
    int level = 0;
    while (rand() < RAND_MAX / 2 && level < max_level) { // P(1/2) de monter d'un niveau
        level++;
    }
    return level;
}