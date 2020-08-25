#include "header.h"

int correct_1[2] = {SDLK_UP, 13};

SDL_Texture* texture_panel_1;
SDL_Texture* texture_text01;
SDL_Texture* texture_next01;
SDL_Texture* texture_person_1;
SDL_Texture* texture_token00;
SDL_Texture* texture_token01;
SDL_Texture* texture_worker_1;
SDL_Texture* texture_box;
SDL_Texture* texture_machine_ready_1;

void setup_1() {
    SDL_Surface* panel01 = IMG_Load("resource/img/panel01.png");
    texture_panel_1 = SDL_CreateTextureFromSurface(renderer, panel01);
    SDL_FreeSurface(panel01);

    SDL_Surface* text01 = IMG_Load("resource/img/text01.png");
    texture_text01 = SDL_CreateTextureFromSurface(renderer, text01);
    SDL_FreeSurface(text01);

    SDL_Surface* next01 = IMG_Load("resource/img/nextlevel01.png");
    texture_next01 = SDL_CreateTextureFromSurface(renderer, next01);
    SDL_FreeSurface(next01);

    SDL_Surface* person01 = IMG_Load("resource/img/person1.png");
    texture_person_1 = SDL_CreateTextureFromSurface(renderer, person01);
    SDL_FreeSurface(person01);

    SDL_Surface* token00 = IMG_Load("resource/img/0.png");
    texture_token00 = SDL_CreateTextureFromSurface(renderer, token00);
    SDL_FreeSurface(token00);

    SDL_Surface* token01 = IMG_Load("resource/img/1000.png");
    texture_token01 = SDL_CreateTextureFromSurface(renderer, token01);
    SDL_FreeSurface(token01);

    SDL_Surface* worker_1 = IMG_Load("resource/img/worker.jpeg");
    texture_worker_1 = SDL_CreateTextureFromSurface(renderer, worker_1);
    SDL_FreeSurface(worker_1);

    SDL_Surface* surface_box = IMG_Load("resource/img/box.jpeg");
    texture_box = SDL_CreateTextureFromSurface(renderer, surface_box);
    SDL_FreeSurface(surface_box);

    SDL_Surface* machine_ready = IMG_Load("resource/img/machine_my.png");
    texture_machine_ready_1 = SDL_CreateTextureFromSurface(renderer, machine_ready);
    SDL_FreeSurface(machine_ready);
}

void update_1() {
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        SDL_Delay(time_to_wait);

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();

    if (panel.x < -46)
        panel.x += 180 * delta_time;

    if (person.x > 1050)
        person.x -= 180 * delta_time;

    if (box.x < 770) {
        if (correct_1[0] == real[0]) {
            if (correct_1[1] == real[1]) {
                box.x += 90 * delta_time;
                box.y -= 52 * delta_time;
            }
        } else if (restart == 1) {
            count = 0, start = 0;
            for (int i = 0; i < 100; ++i) real[i] = 0;
            restart = 0;
        }
    }

    if (box.x > 760 && worker.y > 210 && restart == 0) {
        worker.x -= 60 * delta_time;
        worker.y -= 35 * delta_time;
    }
}

void render_1() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_Rect panel_rect = {(int)panel.x, (int)panel.y, (int)panel.width, (int)panel.height};
    SDL_RenderCopy(renderer, texture_panel_1, NULL, &panel_rect);

    SDL_Rect text_rect = {(int)text.x, (int)text.y, (int)text.width, (int)text.height};
    if (person.x < 1050 && box.x < 770)
        SDL_RenderCopy(renderer, texture_text01, NULL, &text_rect);

    SDL_Rect next_rect = {(int)next.x, (int)next.y, (int)next.width, (int)next.height};
    if (box.x > 770)
        SDL_RenderCopy(renderer, texture_next01, NULL, &next_rect);

    SDL_Rect person_rect = {(int)person.x, (int)person.y, (int)person.width, (int)person.height};
    SDL_RenderCopy(renderer, texture_person_1, NULL, &person_rect);

    SDL_Rect token0_rect = {(int)token0.x, (int)token0.y, (int)token0.width, (int)token0.height};
    if (box.x < 770)
        SDL_RenderCopy(renderer, texture_token00, NULL, &token0_rect);

    SDL_Rect token_rect = {(int)token.x, (int)token.y, (int)token.width, (int)token.height};
    if (box.x > 770)
        SDL_RenderCopy(renderer, texture_token01, NULL, &token_rect);

    SDL_Rect worker_rect = {(int)worker.x, (int)worker.y, (int)worker.width, (int)worker.height};
    SDL_RenderCopy(renderer, texture_worker_1, NULL, &worker_rect);

    SDL_Rect box_rect = {(int)box.x, (int)box.y, (int)box.width, (int)box.height};
    SDL_RenderCopy(renderer, texture_box, NULL, &box_rect);

    SDL_Rect machine_rect = {520, 200, 190, 212};
    SDL_RenderCopy(renderer, texture_machine_ready_1, NULL, &machine_rect);

    SDL_Rect icons[1] = {{182, 14, 42, 42}};
    render_copy_icons(1, icons);

    SDL_RenderPresent(renderer);
}

void cleanup_1() {
    SDL_DestroyTexture(texture_panel_1);
    SDL_DestroyTexture(texture_text01);
    SDL_DestroyTexture(texture_next01);
    SDL_DestroyTexture(texture_person_1);
    SDL_DestroyTexture(texture_token00);
    SDL_DestroyTexture(texture_token01);
    SDL_DestroyTexture(texture_worker_1);
    SDL_DestroyTexture(texture_box);
    SDL_DestroyTexture(texture_machine_ready_1);
}
