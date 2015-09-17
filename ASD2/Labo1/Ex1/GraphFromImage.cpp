#include "GraphFromImage.h"

GraphFromImage::GraphFromImage(const bitmap_image& i) : image(i) {
    const int width = image.width();
    const int height = image.height();

    adjacents.resize(width * height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char r, g, b;
            image.get_pixel(x, y, r, g, b);

            const auto check_pixel = [&](int px, int py) {
                if (px >= 0 && px < width && py >= 0 && py < height) {
                    unsigned char pr, pg, pb;
                    image.get_pixel(px, py, pr, pg, pb);

                    if (r == pr && g == pg && b == pb) {
                        adjacents[idx(x, y)].push_back(idx(px, py));
                    }
                }
            };

            check_pixel(x, y-1);
            check_pixel(x, y+1);
            check_pixel(x+1, y);
            check_pixel(x-1, y);
        }
    }
}

GraphFromImage::Iterable GraphFromImage::adjacent(int v) const {
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
