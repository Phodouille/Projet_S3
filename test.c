#include "cell.h"
#include "list.h"
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> // Pour la fonction pow


int main() {
    int max_level = 3; // Définir le niveau maximal pour la liste à niveaux

    // Créer une liste à niveaux vide avec un niveau maximal
    t_d_list *list = create_list(max_level);
    if (!list) {
        fprintf(stderr, "Failed to create list.\n");
        return 1;
    }
    printf("Liste vide:\n");
    display_list(list);

    // Insérer des cellules dans la liste avec des valeurs allant de 10 à 50
    int nb_cell = pow(2, max_level) - 1;
    for (int i = 0; i < nb_cell; i ++) {
        t_d_cell *cell = create_cell(0, 2);
        if (!cell) {
            fprintf(stderr, "Failed to create a cell.\n");
            free_list(list);
            return 1;
        }
        insert_cell(list, cell);
    }
    printf("Liste remplie:\n");
    display_list(list);

}

