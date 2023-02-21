#include <string>
#include <vector>
#include <bitset>
#include <map>
#include <SDL.h>
#include <stdio.h>
#include <cmath>

#include "custom_font.h"
#include "utility.h"

dot_matrix_letter::dot_matrix_letter(std::string bin_string, int width, int height, std::string name) {
    this->width = width;
    this->height = height;
    this->name = name;
    this->bin_array = new bool*[height];
    for (int i = 0; i < height; i++) {
        this->bin_array[i] = new bool[width];
        for (int j = 0; j < width; j++) {
            this->bin_array[i][j] = bin_string[i*width+j] == '1';
        }
    }
}

std::string rjust(std::string str, int width, char pad_char) { //Adds pad_char to left of string so that str.length() == width
    if ((int)str.length() > width) return str;
    return std::string(width - str.length(), pad_char) + str;
}

std::string trim(std::string str, int width) { //Trims str, starting from the left, until str.length() == width
    if ((int)str.length() < width) return str;
    return str.substr(str.length()-width,std::string::npos);
}

font* load_font(std::string& font_string) {
    std::vector<std::string> splitted = split_string(font_string, '\n');
    std::vector<std::string> width_height = split_string(splitted.front(), ';');
    int width = std::stoi(width_height.front());
    int height = std::stoi(width_height.back());
    int total_size = width*height;

    std::string letter;
    std::string bin_string;
    
    std::map<std::string, dot_matrix_letter*> dot_matrix_array;
    
    
    for (auto line = splitted.begin()+1; line != splitted.end(); line++){
        letter = (*line)[0];
        bin_string = "";
        for (auto hexChar = (*line).begin()+1; hexChar != (*line).end(); hexChar++) {
            std::string hexString(1, *hexChar);
            bin_string += std::bitset<4>(std::stoi(hexString,0,16)).to_string();
        }
        bin_string = trim(rjust(bin_string, total_size, '0'), total_size);
        
        dot_matrix_array.insert(std::make_pair(letter, new dot_matrix_letter(bin_string, width, height, letter)));

        
    }
    static font font_out = font(dot_matrix_array);
    
    return &font_out;
    
}

font::font(std::map<std::string, dot_matrix_letter*> font_array) {
    this->font_array = font_array;
    this->width = font_array.begin()->second->width;
    this->height = font_array.begin()->second->height;
    this->spacing = 1;
    this->size = 5;
    this->dot_scale = 5.0/6;
    this->color_r = 255; this->color_g = 255; this->color_b = 255;
}

void font::set_color(int r, int g, int b) {
    this->color_r = r; this->color_g = g; this->color_b = b;
}


bool** font::make_array(std::string text) {
    this->total_width = text.length()*this->width + (text.length()-1)*this->spacing;
    bool** string_arr = new bool*[this->height];
    for (int i = 0; i < this->height; i++) {
        string_arr[i] = new bool[this->total_width];
        for (int j = 0; j < this->total_width; j++) {
            string_arr[i][j] = 0;
        }
    }
    
    int xpos = 0;
    dot_matrix_letter* temp_dml;
    for (int char_num = 0; char_num < (int)text.length(); char_num++) {
        temp_dml = this->font_array[std::string(1, text[char_num])];
        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                string_arr[i][xpos+j] = temp_dml->bin_array[i][j];
                
            }
        }
        xpos += this->width + this->spacing;
        
    }
    
    return string_arr;
    
}

void font::render_text(std::string text, SDL_Surface* surface) {
    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0, 0, 0, 0));
    
    if (text == "") {
        return;
    }
    
    bool** string_arr = make_array(text);

    
    SDL_Rect rect;
    rect.w = rect.h = this->size * this->dot_scale;
    
    for (int i = 0; i < this->total_width; i++) {
        for (int j = 0; j < this->height; j++) {
            if (string_arr[j][i]) {
                rect.x = round(this->size*i);
                rect.y = round(this->size*j);
                SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, this->color_r, this->color_g, this->color_b));
            }
        }
    }
}

SDL_Surface* font::set_blank_surface(int max_string_length) {
    this->total_width = max_string_length*this->width + (max_string_length-1)*this->spacing;
    
    Uint32 rmask = 0x000000ff; Uint32 gmask = 0x0000ff00; Uint32 bmask = 0x00ff0000; Uint32 amask = 0xff000000;
    if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        rmask = 0xff000000; gmask = 0x00ff0000; bmask = 0x0000ff00; amask = 0x000000ff;
    }

    return SDL_CreateRGBSurface(0, this->total_width*this->size, this->height*this->size, 32, rmask, gmask, bmask, amask);
}