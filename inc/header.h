#pragma once

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include <stdio.h>
#include <stddef.h>

#define FALSE 0
#define TRUE 1

#define WINDOW_WIDHT 1280
#define WINDOW_HEIGHT 720

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

typedef struct {
    float x;
    float y;
    float width;
    float height;
} t_rectangle;
t_rectangle box, worker;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* image;
SDL_Texture* texture;

SDL_Surface* icon_up, *icon_down, *icon_right, *icon_left;
SDL_Texture* texture_up, *texture_down, *texture_right, *texture_left;

int game_is_running;
int last_frame_time;
int real[100];
int count;
int start;

void render_copy_icons(int n, const SDL_Rect *icons);
void update_1();
void render_1();
void update_2();
void render_2();
