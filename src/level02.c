#include "header.h"

int correct_2[7] = {SDLK_DOWN, SDLK_UP, SDLK_RIGHT, SDLK_UP, SDLK_RIGHT, SDLK_UP, SDLK_RETURN};

void update_2() {
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    static int step = 0;

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        SDL_Delay(time_to_wait);

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();

    if (start) {
        if (step == 0) {
            if (box.y < 571) {
                if (correct_2[0] == real[0]) {
                    box.x += 0 * delta_time;
                    box.y += 60 * delta_time;
                }
            }
            if (box.y > 570) step = 1;
        }

        if (step == 1) {
            if (box.y > 390 && box.x > 190) {
                if (correct_2[1] == real[1]) {
                    box.x -= 110 * delta_time;
                    box.y -= 64 * delta_time;
                }
            }
            if (box.y < 410) step = 2;
        }

        if (step == 2) {
            if (box.y > 120 && box.x < 720) {
                if (correct_2[2] == real[2]) {
                    if (correct_2[3] == real[3]) {
                        box.x += 110 * delta_time;
                        box.y -= 64 * delta_time;
                    }
                }
            }
            if (box.x > 690) step = 3;
        }

        if (step == 3) {
            if (box.y < 170 && box.x < 900) {
                if (correct_2[4] == real[4]) {
                    if (correct_2[5] == real[5]) {
                        box.x += 110 * delta_time;
                        box.y += 64 * delta_time;
                    }
                }
            }
        }

        if (box.x > 650 && worker.x < 780) {
            worker.x += 73 * delta_time;
            worker.y -= 43 * delta_time;
        }
    }
}

void render_2() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_Surface* worker_1 = IMG_Load("resource/img/worker.png");
    SDL_Texture* texture_worker_1 = SDL_CreateTextureFromSurface(renderer, worker_1);

    SDL_Rect worker_rect = { 
            (int)worker.x, 
            (int)worker.y, 
            (int)worker.width, 
            (int)worker.height 
        };

    SDL_RenderCopy(renderer, texture_worker_1, NULL, &worker_rect);

    SDL_Rect icons[6] = {{182, 14, 42, 42}, {230, 14, 42, 42}, {278, 14, 42, 42},
                         {326, 14, 42, 42}, {374, 14, 42, 42}, {422, 14, 42, 42}};

    render_copy_icons(6, icons);

    if (box.y < 200 || box.y > 300) {
        SDL_Surface* surface_box = IMG_Load("resource/img/box.jpeg");
        SDL_Texture* texture_box = SDL_CreateTextureFromSurface(renderer, surface_box);

        SDL_Rect box_rect = {
            (int)box.x,
            (int)box.y,
            (int)box.width,
            (int)box.height
        };

        SDL_RenderCopy(renderer, texture_box, NULL, &box_rect);
        SDL_RenderPresent(renderer);
    }

}
