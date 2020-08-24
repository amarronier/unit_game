#include "header.h"

int correct_1[2] = {SDLK_UP, 13};

void update_1() {
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        SDL_Delay(time_to_wait);

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();

    if (box.x < 770) {
        if (correct_1[0] == real[0]) {
            if (correct_1[1] == real[1]) {
                box.x += 90 * delta_time;
                box.y -= 52 * delta_time;
            }
        }
    }

    if (box.x > 760 && worker.y > 250) {
        worker.x -= 60 * delta_time;
        worker.y -= 35 * delta_time;
    }
}

void render_1() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_Surface* worker_1 = IMG_Load("resource/img/worker.jpeg");
    SDL_Texture* texture_worker_1 = SDL_CreateTextureFromSurface(renderer, worker_1);

    SDL_Rect icons[1] = {{182, 14, 42, 42}};

    render_copy_icons(1, icons);

    SDL_Rect worker_rect = {
            (int)worker.x,
            (int)worker.y,
            (int)worker.width,
            (int)worker.height
    };

    SDL_RenderCopy(renderer, texture_worker_1, NULL, &worker_rect);

    if (box.x < 523 ||  box.x > 717 ) {
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
