#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct seq_dt {
    int *seq; // on stocke seulement les nombre pairs, divisés par 2
    int taille;
};

typedef struct seq_dt seq_dt;

void init_seq_dt(seq_dt *s, int taille) {
    s->seq = (int *)malloc(taille * sizeof(int));
    if (s->seq == NULL) {
        fprintf(stderr, "Pas pu allouer de la mémoire\n");
        exit(EXIT_FAILURE);
    }
    s->taille = taille;
}

void free_seq_dt(seq_dt *s) {
    if (s->seq != NULL) {
        free(s->seq);
        s->seq = NULL;
    }
    s->taille = 0;
}

void print_seq_dt(const seq_dt *s) {
    if (s->seq == NULL || s->taille <= 0) {
        printf("La séquence est vide.\n");
        return;
    }
    for (int i = 0; i < s->taille; i++) {
        printf("(%d; %d), ", 2*i+1, 2*s->seq[i]);
    }
    printf("\n");
}


int abs(int x) {
    return (x < 0) ? -x : x;
}

// ordre : ordre des permutations, puis ordre des sous parties pour les signes
void next_seq_dt(seq_dt *s) {
    if (s->seq == NULL || s->taille <= 0) {
        fprintf(stderr, "La séquence n'est pas initialisée ou a une taille invalide.\n");
        return;
    }
    bool est_entierement_negatif = true;
    for (int i = 0; i < s->taille; i++) {
        if (s->seq[i] >= 0) {
            est_entierement_negatif = false;
            break;
        }
    }

    if (!est_entierement_negatif) { // on prend les positions des moins suivantes en binaire
        int n = 0; // correspond aux positions des moins
        for (int i = 0; i < s->taille; i++) {
            n *= 2;
            if (s->seq[i] < 0) {
                n++;
            }
            // printf("n = %d\n", n);
        }

        n++;
        for (int i = s->taille - 1; i >= 0; i--) {
            s->seq[i] = (n % 2 == 0) ? abs(s->seq[i]) : -abs(s->seq[i]);
            n /= 2;
        }
    } else { // on prend la permutation suivante pour l'ordre lexicographique
        for (int i = 0; i < s->taille; i++) {
            s->seq[i] = -s->seq[i]; // on remet les signes à +
        }

        int pivot_index = s->taille - 2;
        while (pivot_index >= 0 && s->seq[pivot_index + 1] <= s->seq[pivot_index]) {
            pivot_index--;
        }
    
        if (pivot_index < 0) {
            printf("Fin de la séquence.\n");
            free_seq_dt(s);
            exit(EXIT_SUCCESS);
            return;
        }
    
        int swap_index = s->taille - 1;
        while (s->seq[swap_index] <= s->seq[pivot_index]) {
            swap_index--;
        }
    
        int temp = s->seq[pivot_index];
        s->seq[pivot_index] = s->seq[swap_index];
        s->seq[swap_index] = temp;
    
        for (int i = pivot_index + 1, j = s->taille - 1; i < j; i++, j--) {
            int temp = s->seq[i];
            s->seq[i] = s->seq[j];
            s->seq[j] = temp;
        }
    }
}

void test_en_taille_4() {
    int taille = 4;

    seq_dt s;
    init_seq_dt(&s, taille);

    for (int i = 1; i <= taille; i++) {
        s.seq[i-1] = i;
    }

    while (true) {
        print_seq_dt(&s);
        next_seq_dt(&s);
    }

    return 0;
}