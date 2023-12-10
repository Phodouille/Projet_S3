#include "cell.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

t_d_cell *create_cell(int value, int max_level) {
    int level = max_level;
    
    t_d_cell *cell = malloc(sizeof(t_d_cell));
    if (!cell) {
        perror("ERREUR : Impossible d'allouer de la mémoire pour la cellule");
        return NULL;
    }

    // Allocation de mémoire pour les pointeurs 'next'
    cell->next = malloc(sizeof(t_d_cell *) * (max_level + 1));
    if (!cell->next) {
        perror("ERREUR : Impossible d'allouer de la mémoire pour les pointeurs 'next'");
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

