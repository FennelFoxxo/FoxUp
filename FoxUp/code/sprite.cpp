#include "sprite.h"

Sprite::

Sprite::Sprite(SDL_Surface* texture) {
    this->texture = texture;
    this->hb_tlx = 0;
    this->hb_tly = 0;
    this->hb_width = 0;
    this->hb_height = 0;
}

Sprite::Sprite(SDL_Surface* texture, double x, double y, double width, double height) {
    this->texture = texture;
    this->hb_tlx = x;
    this->hb_tly = y;
    this->hb_width = width;
    this->hb_height = height;
}