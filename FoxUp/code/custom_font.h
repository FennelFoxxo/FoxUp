#include <string>
#include <vector>
#include <map>
#include <SDL.h>
#include <stdio.h>

#ifndef CUSTOM_FONT
#define CUSTOM_FONT

class dot_matrix_letter {
public:
    dot_matrix_letter(std::string bin_string, int width, int height, std::string name);
    bool** bin_array;
    int width;
    int height;
    std::string name;
};

class font {
public:
    int width;
    int height;
    int total_width;
    int spacing;
    int size;
    float dot_scale;

    int color_r; int color_g; int color_b;

    std::map<std::string, dot_matrix_letter*> font_array;
    font(std::map<std::string, dot_matrix_letter*> font_array);
    void set_color(int r, int g, int b);
    bool** make_array(std::string text);
    void render_text(std::string text, SDL_Surface*);
    SDL_Surface* set_blank_surface(int max_string_length);
};

std::vector<std::string> split_string(std::string str, char delimiter);
std::string rjust(std::string str, int width, char pad_char);
std::string trim(std::string str, int width);
font* load_font(std::string& fname);

#endif
