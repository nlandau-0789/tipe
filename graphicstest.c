#include <cairo/cairo.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

void draw_rond(int x, int y, int r, cairo_t* cr){
    cairo_save(cr);                 
    cairo_translate(cr, x, y);  
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);     // Noir
    cairo_arc(cr, 0, 0, r, 0, 2 * M_PI); 
    cairo_stroke(cr);
    cairo_restore(cr);                               
}

void draw_cross(int x, int y, int r, int angle, cairo_t* cr){
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

void draw_noeud(int n, int* dtcode) { //Pas eu la foi de finir
    //Prend le nombre de noeuds, le DT code
    int taille = 1000;
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
    //On place les noeuds


    // Enregistrer image
    cairo_surface_write_to_png(surface, "output.png");

    // Nettoyage
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}

int main(){

    return 0;
}