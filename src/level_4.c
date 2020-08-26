#include "header.h"

int correct_4[11] = {SDLK_UP, SDLK_LEFT, SDLK_UP, SDLK_RIGHT, SDLK_UP, SDLK_RIGHT,
                     SDLK_UP, SDLK_DOWN, SDLK_RIGHT, SDLK_DOWN, SDLK_UP};
int finish_4 = 0;
SDL_Texture* texture_worker_3;
SDL_Texture* texture_box;
SDL_Texture* texture_bar;
SDL_Texture* texture_kran;
SDL_Texture* texture_machine_ready_1;
SDL_Texture* texture_success03;
SDL_Texture* texture_text03;
SDL_Texture* texture_product;

void setup_4() {
    SDL_Surface* worker_3 = IMG_Load("resource/img/worker.png");
    texture_worker_3 = SDL_CreateTextureFromSurface(renderer, worker_3);
    SDL_FreeSurface(worker_3);

    SDL_Surface* surface_box = IMG_Load("resource/img/box.jpeg");
    texture_box = SDL_CreateTextureFromSurface(renderer, surface_box);
    SDL_FreeSurface(surface_box);

    SDL_Surface* surface_bar = IMG_Load("resource/img/bar.png");
    texture_bar = SDL_CreateTextureFromSurface(renderer, surface_bar);
    SDL_FreeSurface(surface_bar);

    SDL_Surface* surface_kran = IMG_Load("resource/img/kran.png");
    texture_kran = SDL_CreateTextureFromSurface(renderer, surface_kran);
    SDL_FreeSurface(surface_kran);

    SDL_Surface* machine_ready = IMG_Load("resource/img/machine_4.png");
    texture_machine_ready_1 = SDL_CreateTextureFromSurface(renderer, machine_ready);
    SDL_FreeSurface(machine_ready);

    SDL_Surface* success03 = IMG_Load("resource/img/next_4.png");
    texture_success03 = SDL_CreateTextureFromSurface(renderer, success03);
    SDL_FreeSurface(success03);

    SDL_Surface* text03 = IMG_Load("resource/img/text_4.png");
    texture_text03 = SDL_CreateTextureFromSurface(renderer, text03);
    SDL_FreeSurface(text03);

    SDL_Surface* surface_product = IMG_Load("resource/img/acum.png");
    texture_product = SDL_CreateTextureFromSurface(renderer, surface_product);
    SDL_FreeSurface(surface_product);

    sprintf(buffer, "%d", (int)score);
    texture_score = renderText(buffer, renderer);
    stop_score = 0;
}

void update_4() {
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    static int step = 0;

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        SDL_Delay(time_to_wait);

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();


    if (finish_4 && score <= 150000 && stop_score == 0) {
        score += 24000 * delta_time;
        sprintf(buffer, "%d", (int)score);
        texture_score = renderText(buffer, renderer);

        if (score > 149000 && stop_score == 0) {
            score = 150000;
            sprintf(buffer, "%d", (int)score);
            texture_score = renderText(buffer, renderer);
            stop_score = 1;
        }
    }

    if (box.x < 700) {
        if (text.x > 670) {
            text.x -= 350 * delta_time;
        }
    }

    if (restart == 1 && start == 0) {
        count = 0, start = 0, step = 0;
        for (int j = 0; j < 100; ++j) real[j] = 0;
        box.x = 470, box.y = 510, box.width = 50, box.height = 50;
        restart = 0;
    }

    if (start) {
        if (step == 0) {
            if (worker.x < 220) {
                worker.x += 110 * delta_time;
                worker.y -= 50 * delta_time;
            }
            if (worker.x > 210) step = 1;
        }
        if (step == 1) {
            if (box.x < 525) {
                if (correct_4[0] == real[0]) {
                    box.x += 110 * delta_time;
                    box.y -= 65 * delta_time;
                }
            }
            if (box.x > 520) step = 2;
        }
        if (step == 2) {
            if (box.x > 210) {
                if (correct_4[1] == real[1]) {
                    if (correct_4[2] == real[2]) {
                        box.x -= 110 * delta_time;
                        box.y -= 65 * delta_time;
                    }
                }
            }
            if (box.x < 215) step = 3;
        }
        if (step == 3) {
            if (box.x < 370) {
                if (correct_4[3] == real[3]) {
                    if (correct_4[4] == real[4]) {
                        box.x += 110 * delta_time;
                        box.y -= 60 * delta_time;
                    }
                }
            }
            if (box.x > 365) step = 4;
        }
        if (step == 4) {
            if (box.x < 675) {
                if (correct_4[5] == real[5]) {
                    if (correct_4[6] == real[6]) {
                        box.x += 110 * delta_time;
                        box.y += 62 * delta_time;
                    }
                }
            }
            if (box.x > 670) step = 5;
        }
        if (step == 5) {
            if (box.x < 890) {
                if (correct_4[7] == real[7]) {
                    if (correct_4[8] == real[8]) {
                        box.x += 55 * delta_time;
                        box.y -= 33 * delta_time;
                        kran.x += 55 * delta_time;
                        kran.y -= 33 * delta_time;
                    }
                }
            }
            if (box.x > 885) step = 6;
        }

        for (int i = 0; i < 11; ++i) {
            if (correct_4[i] != real[i]) {
                if (restart == 1) {
                    count = 0, start = 0, step = 0;
                    for (int j = 0; j < 100; ++j) real[j] = 0;
                    box.x = 287, box.y = 595, box.width = 50, box.height = 50;
                    kran.x = 640, kran.y = 300, kran.width = 100, kran.height = 100;
                    restart = 0;
                }
            }
        }

        if (step == 6) {
            if (box.x < 965) {
                if (correct_4[9] == real[9]) {
                    if (correct_4[10] == real[10]) {
                        box.x += 110 * delta_time;
                        box.y += 62 * delta_time;
                        finish_4 = 1;
                    }
                }
            }
            if (box.x > 960) step = 7;
        }
    }
}

void render_4() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_Rect worker_rect = {(int)worker.x, (int)worker.y, (int)worker.width, (int)worker.height};
    SDL_RenderCopy(renderer, texture_worker_3, NULL, &worker_rect);

    SDL_Rect box_rect = {(int)box.x, (int)box.y, (int)box.width, (int)box.height};
    if (box.y > 500)    
        SDL_RenderCopy(renderer, texture_box, NULL, &box_rect);
    if (box.y < 500)    
        SDL_RenderCopy(renderer, texture_product, NULL, &box_rect);

    SDL_Rect bar_rect = {545, 118, 200, 380};
    SDL_RenderCopy(renderer, texture_bar, NULL, &bar_rect);

    SDL_Rect kran_rect = {(int)kran.x, (int)kran.y, (int)kran.width, (int)kran.height};
    SDL_RenderCopy(renderer, texture_kran, NULL, &kran_rect);

    SDL_Rect machine_rect = {335, 395, 290, 290};
    SDL_RenderCopy(renderer, texture_machine_ready_1, NULL, &machine_rect);

    SDL_Rect text_rect = {(int)text.x, (int)text.y, (int)text.width, (int)text.height};
    if(!finish_4)
        SDL_RenderCopy(renderer, texture_text03, NULL, &text_rect);

    SDL_Rect next_rect = {(int) next.x, (int) next.y, (int) next.width, (int) next.height};
    if (finish_4)
        SDL_RenderCopy(renderer, texture_success03, NULL, &next_rect);

    SDL_Rect icons[11] = {{182, 11, 42, 42}, {230, 11, 42, 42}, {278, 11, 42, 42},
                          {326, 11, 42, 42}, {374, 11, 42, 42}, {422, 11, 42, 42},
                          {470, 11, 42, 42}, {518, 11, 42, 42}, {566, 11, 42, 42},
                          {612, 11, 42, 42}, {660, 11, 42, 42}};
    render_copy_icons(11, icons);

    SDL_Rect score_rect = {1050, 35, 120, 50};
    SDL_RenderCopy(renderer, texture_score, NULL, &score_rect);

    SDL_RenderPresent(renderer);
}

void cleanup_4() {
    SDL_DestroyTexture(texture_worker_3);
    SDL_DestroyTexture(texture_box);
    SDL_DestroyTexture(texture_bar);
    SDL_DestroyTexture(texture_kran);
    SDL_DestroyTexture(texture_machine_ready_1);
    SDL_DestroyTexture(texture_success03);
    SDL_DestroyTexture(texture_text03);
    SDL_DestroyTexture(texture_score);
    SDL_DestroyTexture(texture_product);
}
