#include "list.h"
#include "cell.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> // Pour la fonction pow

int main() {
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires
    int max_level = 5; // Définir le niveau maximal pour la liste à niveaux

    // Créer une liste à niveaux vide avec un niveau maximal
    t_d_list *list = create_list(max_level);
    if (!list) {
        fprintf(stderr, "Failed to create list.\n");
        return 1;
    }
    display_list(list);

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
    

    // Afficher la liste à un niveau donné
    printf("Affichage du niveau 2:\n");
    display_level(list, 2);

    // Afficher la liste à niveaux
    printf("Affichage de la list apres insertion:\n");
    display_list(list);


    // Nettoyer
    free_list(list);

    printf("test de la partie 2 :\n"); // PARTIE 2 
    int max_level2 = 3; // Définir le niveau maximal pour la liste à niveaux

    // Créer une liste à niveaux vide avec un niveau maximal
    t_d_list *list2 = create_list(max_level2);
    if (!list2) {
        fprintf(stderr, "Failed to create list.\n");
        return 1;
    }
    printf("Liste vide:\n");
    display_list(list2);

    // Insérer des cellules dans la liste avec des valeurs allant de 10 à 50
    int nb_cell = pow(2, max_level2) - 1;
    for (int i = 0; i < nb_cell; i ++) {
        t_d_cell *cell = create_cell(0, max_level2);
        if (!cell) {
            fprintf(stderr, "Failed to create a cell.\n");
            free_list(list2);
            return 1;
        }
        insert_cell(list2, cell);
    }
    printf("Liste remplie:\n");
    display_list(list2);

    // Change les 0 en 1 une cellule sur 2
    printf("Liste remplie avec 1 cellule sur 2:\n");
    t_d_cell *current = list2->head[0]->next[0];
    int count = 0;
    while (current != NULL) {
        if (count % 2 != 0) {
            current->value = 1;
        }
        current = current->next[0];
        count++;
    }
    display_list(list2);

    
    // Change les valeurs des cellules en 2 toutes les 4 cellules
    printf("Liste remplie avec 2 cellules sur 4:\n");
    t_d_cell *current2 = list2->head[0]->next[0];
    int count2 = 1;
    while (current2 != NULL) {
        if (count2 % 4 == 0) {
            current2->value = 2;
        }
        current2 = current2->next[0];
        count2++;
    }
    display_list(list2);

    // test de schearch classique
    printf("test de schearch classique:\n");
    t_d_cell *cell = search_classic(list2, 2); // on cherche la cellule qui contient la valeur 2
    if (cell != NULL) {
        printf("cellule trouvee\n");
    } else {
        printf("cellule non trouvee\n");
    }
    printf("la valeur de la cellule est : %d\n", cell->value);


    printf("test de schearch optimise:\n");
    t_d_cell *cell3 = search_optimized(list2, 2); // on cherche la cellule qui contient la valeur 2
    if (cell3 != NULL) {
        printf("cellule trouvee\n");
        printf("la valeur de la cellule est : %d\n", cell3->value);
    } else {
        printf("cellule non trouvee\n");
    }

    printf("test de mesure de performance:\n");
    measure_search_performance(list2);

    return 0;
}
