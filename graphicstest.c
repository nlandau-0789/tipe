#include <cairo/cairo.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

struct seq_dt {
    int *seq; // on stocke seulement les nombre pairs, divisés par 2
    int taille;
};

typedef struct seq_dt seq_dt;

struct croisement {
    int x; 
    int y; //Position sur le Canva
    float angle;
    int pair;
    int impair;
    crois* suivp;
    crois* suivi;
    crois* precp;
    crois* preci;
};

typedef struct croisement crois;

void force_vois(int* acc, crois* c){ //Force attractive des voisins
    int coef = 1E20; //Coefficient a tweak
    crois* vois = c->suivp;
    //Voisins pairs
    int distcarre = (c->x-vois->x)*(c->x-vois->x)+(c->y-vois->y)*(c->y-vois->y);
    int force = coef/distcarre; //distance au carre
    acc[0] = force*(vois->x-c->x)/sqrt(distcarre);
    acc[1] = force*(vois->y-c->y)/sqrt(distcarre);

    vois = c->precp;
    int distcarre = (c->x-vois->x)*(c->x-vois->x)+(c->y-vois->y)*(c->y-vois->y);
    int force = coef/distcarre; //distance au carre
    acc[0] += force*(vois->x-c->x)/sqrt(distcarre);
    acc[1] += force*(vois->y-c->y)/sqrt(distcarre);

    //Voisins impairs
    vois = c->suivi;
    int distcarre = (c->x-vois->x)*(c->x-vois->x)+(c->y-vois->y)*(c->y-vois->y);
    int force = coef/distcarre; //distance au carre
    acc[0] += force*(vois->x-c->x)/sqrt(distcarre);
    acc[1] += force*(vois->y-c->y)/sqrt(distcarre);

    vois = c->preci;
    int distcarre = (c->x-vois->x)*(c->x-vois->x)+(c->y-vois->y)*(c->y-vois->y);
    int force = coef/distcarre; //distance au carre
    acc[0] += force*(vois->x-c->x)/sqrt(distcarre);
    acc[1] += force*(vois->y-c->y)/sqrt(distcarre);
}

//To do: Faire des calculs pour calibrer a peu pres les forces entre elles
//Force repulsive des croisements entre eux
//Force attractive du centre

void draw_rond(int x, int y, int r, cairo_t* cr){
    cairo_save(cr);                 
    cairo_translate(cr, x, y);  
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);     // Noir
    cairo_arc(cr, 0, 0, r, 0, 2 * M_PI); 
    cairo_stroke(cr);
    cairo_restore(cr);                               
}

void draw_cross(int x, int y, int r, float angle, cairo_t* cr){
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);     // Noir
    cairo_save(cr);                 
    cairo_translate(cr, x, y); 
    cairo_move_to(cr, cos(angle)*r, sin(angle)*r);
    cairo_line_to(cr, cos(M_PI+angle)*r, sin(M_PI+angle)*r);
    cairo_move_to(cr, cos(angle+M_PI/2)*r, sin(angle+M_PI/2)*r);
    cairo_line_to(cr, cos(angle-M_PI/2)*r, sin(angle-M_PI/2)*r);
    cairo_stroke(cr);
    cairo_restore(cr);
}

void draw_noeud(seq_dt* dtcode) { //Pas eu la foi de finir
    //Prend le nombre de noeuds, le DT code
    int taille = 1000;
    int n = dtcode->taille;
    //Taille du canva dépend du nombre de noeud
    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, taille*n, taille*n);

    //Stylo
    cairo_t *cr = cairo_create(surface);
    cairo_set_line_width (cr, 10);

    // Fond blanc
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);

    //Origine placee au milieu
    cairo_translate(cr, taille*n/2, taille*n/2);

    // Dessin
    //On place les croisements


    // Enregistrer image
    cairo_surface_write_to_png(surface, "output.png");

    // Nettoyage
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}

int main(){

    return 0;
}