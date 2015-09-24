/*
 * Labo 01 par
 *  Bastien Clément
 *  Alain Hardy
 */

#include "GraphFromImage.h"

GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
    const int width = image.width();
    const int height = image.height();


    adjacents.resize(width * height);

    // On parcourt chaque pixel dans le sens de la lecture
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // On récupère la couleur du pixel courant
            unsigned char r, g, b;
            image.get_pixel(x, y, r, g, b);

            // Cette fonction compare la couleur d'un pixel spécifique avec la couleur du pixel courant
            // Si la couleur est identique, le sommet correspondant est ajouté à la liste d'adjacence
            // Elle vérifie également que le pixel existe (bords de l'image)
            const auto check_pixel = [&](int px, int py) {
                // Le pixel existe
                if (px >= 0 && px < width && py >= 0 && py < height) {
                    // Couleur du pixel avoisinant
                    unsigned char pr, pg, pb;
                    image.get_pixel(px, py, pr, pg, pb);

                    // Même couleur !
                    if (r == pr && g == pg && b == pb) {
                        adjacents[idx(x, y)].push_back(idx(px, py));
                    }
                }
            };

            // On check systématiquement les 4 pixels avoisinant
            // La fonction se chargera d'ignorer ceux qui n'existent pas (bords)
            check_pixel(x, y-1);
            check_pixel(x, y+1);
            check_pixel(x+1, y);
            check_pixel(x-1, y);
        }
    }
}

GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
    // Puisqu'on a déjà construit les listes d'adjacence pour chaque sommet,
    // il suffit de retourner celle pour le sommet désiré.
    return adjacents[v];
}

int GraphFromImage::idx(int x, int y) const {
     return y * image.width() + x;
}

int GraphFromImage::x(int idx) const {
   return idx % image.width();
}

int GraphFromImage::y(int idx) const {
    return idx / image.width();
}

int GraphFromImage::V() const {
    return image.width() * image.height();
}
