#include "list.h"
#include "cell.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


t_d_list *create_list(int max_level) {
    t_d_list *list = (t_d_list *)malloc(sizeof(t_d_list));
    list->max_level = max_level;
    list->head = (t_d_cell **)malloc(sizeof(t_d_cell *) * (max_level + 1));
    for (int i = 0; i <= max_level; i++) {
        list->head[i] = create_cell(0, list->max_level); // Correct si create_cell attend 2 arguments
    }
    return list;
}

void free_list(t_d_list *list) {
    // Vérifier si la liste est déjà nulle
    if (list == NULL) return;

    t_d_cell *current = list->head[0]; // Commencer par le niveau le plus bas
    while (current != NULL) {
        t_d_cell *temp = current;
        current = current->next[0]; // Aller à la cellule suivante au niveau le plus bas
        free_cell(temp); // Libérer la cellule actuelle
    }

    // Après avoir libéré toutes les cellules, libérer les têtes
    free(list->head);

    // Finalement, libérer la structure de liste elle-même
    free(list);
}


void insert_cell(t_d_list *list, t_d_cell *new_cell) {
    if (list == NULL || new_cell == NULL) {
        fprintf(stderr, "List or cell is NULL.\n");
        return;
    }

    t_d_cell **update = (t_d_cell **)malloc(sizeof(t_d_cell *) * (list->max_level + 1));
    if (update == NULL) {
        fprintf(stderr, "Memory allocation for update pointers failed.\n");
        free(new_cell); // Nettoyer la nouvelle cellule allouée
        return;
    }

    t_d_cell *current = NULL;

    // Initialiser les pointeurs de mise à jour
    for (int i = list->max_level; i >= 0; i--) {
        current = list->head[i];
        while (current->next[i] != NULL && current->next[i]->value < new_cell->value) {
            current = current->next[i];
        }
        update[i] = current;
    }

    for (int i = 0; i <= new_cell->level; i++) {
        new_cell->next[i] = update[i]->next[i];
        update[i]->next[i] = new_cell;
    }

    free(update);
}


void display_list(t_d_list *list) {
    if (list == NULL) {
        printf("List is empty.\n");
        return;
    }

    // Déterminer l'espacement nécessaire pour chaque valeur PAS NECESSAIRE
    int max_value_width = 0;
    for (t_d_cell *cell = list->head[0]->next[0]; cell != NULL; cell = cell->next[0]) {
        int value_width = snprintf(NULL, 0, "%d", cell->value);
        if (value_width > max_value_width) {
            max_value_width = value_width;
        }
    }

    // Afficher les niveaux de la liste du niveau 0 à max_level
    for (int i = 0; i <= list->max_level; i++) {
        printf("Level %d: head", i);

        t_d_cell *current = list->head[i]->next[i]; // Commencer par le premier nœud du niveau i

        // Parcourir la liste à ce niveau
        while (current != NULL) {
            printf(" -> %*d", max_value_width, current->value);
            current = current->next[i]; // Aller au nœud suivant au niveau i
        }

        printf(" -> NULL\n");
    }
}


void display_level(t_d_list *list, int level) {
    if (list == NULL || level < 0 || level > list->max_level) {
        printf("Invalid level or list is empty.\n");
        return;
    }

    t_d_cell *current = list->head[level];
    printf("Level %d: head", level);

    // Parcourir les cellules du niveau spécifié
    while (current != NULL && current->next[level] != NULL) {
        printf(" -> %d", current->next[level]->value);
        current = current->next[level];
    }

    printf(" -> NULL\n");
}






void measure_search_performance(t_d_list *list) {
    const int num_searches = 10000;
    int successes = 0;

    // Mesure de la recherche classique
    startTimer();
    for (int i = 0; i < num_searches; ++i) {
        int random_value = rand() % ((1 << (list->max_level + 1)) - 1) + 1;
        if (search_classic(list, random_value)) {
            successes++;
        }
    }
    stopTimer();
    printf("Classic search: %s seconds\n", getTimeAsString());

    // Mesure de la recherche optimisée
    successes = 0;
    startTimer();
    for (int i = 0; i < num_searches; ++i) {
        
        int random_value = rand() % ((1 << (list->max_level + 1)) - 1) + 1;
        if (search_optimized(list, random_value)) {
            successes++;
        }
    }
    stopTimer();
    printf("Optimized search: %s seconds\n", getTimeAsString());
}

t_d_cell *search_classic(t_d_list *list, int value) {
    t_d_cell *current = list->head[0];
    while (current && current->value != value) {
        current = current->next[0];
    }
    return current; // Retourne la cellule trouvée ou NULL
}



 t_d_cell *search_optimized(t_d_list* list, int value) {
    if (list == NULL || list->head == NULL || list->max_level <= 0) {
        return NULL;  // Liste invalide
    }

    t_d_cell* cell = list->head[list->max_level - 1];
    int cur_level = list->max_level - 1;

    while (cur_level >= 0 && cell != NULL) {
        if (cell->value == value) {
            return cell;  // Élément trouvé
        } else if (cell->value > value) {
            cur_level--;  // Déplacer vers le niveau inférieur
        } else if (cell->next[cur_level] == NULL || cell->next[cur_level]->value > value) {
            cur_level--;  // Descendre d'un niveau
        } else {
            cell = cell->next[cur_level];  // Passer au prochain élément sur le même niveau
        }
    }

    return NULL;  // Élément non trouvé
}






