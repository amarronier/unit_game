#pragma once

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


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
t_rectangle box, worker, text, success, panel, person, next, token, token0, coin, kran;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* image;
SDL_Texture* texture;

SDL_Surface* icon_up, *icon_down, *icon_right, *icon_left;
SDL_Texture* texture_up, *texture_down, *texture_right, *texture_left;

SDL_Texture* renderText(const char *buffer, SDL_Renderer *renderer);
SDL_Texture* texture_score;

int game_is_running;
int last_frame_time;
int real[100];
int count;
int start;
int restart;
int finish;

int stop_score;
float score;
char buffer[50];


void render_copy_icons(int n, const SDL_Rect *icons);
void run_level(int level);

void setup_1();
void update_1();
void render_1();
void cleanup_1();

void setup_2();
void update_2();
void render_2();
void cleanup_2();

void setup_3();
void update_3();
void render_3();
void cleanup_3();

void setup_4();
void update_4();
void render_4();
void cleanup_4();
