#ifndef CELL_H
#define CELL_H

typedef struct s_d_cell {
    int value;
    struct s_d_cell **next; // Tableau de pointeurs vers la cellule suivante à chaque niveau
    int level;
} t_d_cell;

// Fonction pour créer une nouvelle cellule
t_d_cell *create_cell(int value, int max_level);
// Fonction pour libérer une cellule
void free_cell(t_d_cell *cell);


#endif // CELL_H
