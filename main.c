#include "list.h"
#include "cell.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires
    int max_level = 5; // Définir le niveau maximal pour la liste à niveaux

    // Créer une liste à niveaux vide avec un niveau maximal
    t_d_list *list = create_list(max_level);
    if (!list) {
        fprintf(stderr, "Failed to create list.\n");
        return 1;
    }

    // Insérer des cellules dans la liste avec des valeurs allant de 10 à 50
    for (int value = 10; value <= 50; value += 10) {
        t_d_cell *cell = create_cell(value, max_level);
        if (!cell) {
            fprintf(stderr, "Failed to create a cell.\n");
            free_list(list);
            return 1;
        }
        insert_cell(list, cell);
    }

    // Afficher la liste à niveaux
    display_list(list);

    // Nettoyer
    free_list(list);

    return 0;
}
