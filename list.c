#include "list.h"
#include "cell.h"
#include <stdio.h>
#include <stdlib.h>

t_d_list *create_list(int max_level) {
    t_d_list *list = (t_d_list *)malloc(sizeof(t_d_list));
    list->max_level = max_level;
    list->header = (t_d_cell **)malloc(sizeof(t_d_cell *) * (max_level + 1));
    for (int i = 0; i <= max_level; i++) {
        list->header[i] = create_cell(0, list->max_level); // Correct si create_cell attend 2 arguments
    }
    return list;
}

void free_list(t_d_list *list) {
    // Vérifier si la liste est déjà nulle
    if (list == NULL) return;

    t_d_cell *current = list->header[0]; // Commencer par le niveau le plus bas
    while (current != NULL) {
        t_d_cell *temp = current;
        current = current->forward[0]; // Aller à la cellule suivante au niveau le plus bas
        free_cell(temp); // Libérer la cellule actuelle
    }

    // Après avoir libéré toutes les cellules, libérer les têtes
    free(list->header);

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
        current = list->header[i];
        while (current->forward[i] != NULL && current->forward[i]->value < new_cell->value) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    for (int i = 0; i <= new_cell->level; i++) {
        new_cell->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_cell;
    }

    free(update);
}


void display_list(t_d_list *list) {
    if (list == NULL) {
        printf("List is empty.\n");
        return;
    }

    // Déterminer l'espacement nécessaire pour chaque valeur
    int max_value_width = 0;
    for (t_d_cell *cell = list->header[0]->forward[0]; cell != NULL; cell = cell->forward[0]) {
        int value_width = snprintf(NULL, 0, "%d", cell->value);
        if (value_width > max_value_width) {
            max_value_width = value_width;
        }
    }

    // Afficher les niveaux de la liste du niveau 0 à max_level
    for (int i = 0; i <= list->max_level; i++) {
        printf("Level %d: header", i);

        t_d_cell *current = list->header[i]->forward[i]; // Commencer par le premier nœud du niveau i

        // Parcourir la liste à ce niveau
        while (current != NULL) {
            printf(" -> %*d", max_value_width, current->value);
            current = current->forward[i]; // Aller au nœud suivant au niveau i
        }

        printf(" -> NULL\n");
    }
}


void display_level(t_d_list *list, int level) {
    if (list == NULL || level < 0 || level > list->max_level) {
        printf("Invalid level or list is empty.\n");
        return;
    }

    t_d_cell *current = list->header[level];
    printf("Level %d: header", level);

    // Parcourir les cellules du niveau spécifié
    while (current != NULL && current->forward[level] != NULL) {
        printf(" -> %d", current->forward[level]->value);
        current = current->forward[level];
    }

    printf(" -> NULL\n");
}


t_d_cell *find_cell(t_d_list *list, int value) {
    if (list == NULL) {
        return NULL; // La liste n'existe pas.
    }

    t_d_cell *current = list->header[list->max_level]; // Commencer par le niveau le plus élevé.

    // Parcourir les niveaux de haut en bas.
    for (int i = list->max_level; i >= 0; i--) {
        // Parcourir les cellules au niveau actuel.
        while (current->forward[i] != NULL && current->forward[i]->value < value) {
            current = current->forward[i];
        }
    }

    // Après avoir parcouru les niveaux, la position actuelle est juste avant l'emplacement de la valeur recherchée.
    current = current->forward[0]; // Passer au niveau 0 pour vérifier la valeur.

    // Vérifier si la cellule actuelle a la valeur recherchée.
    if (current != NULL && current->value == value) {
        return current; // La cellule a été trouvée.
    }

    return NULL; // La valeur n'a pas été trouvée dans la liste.
}

