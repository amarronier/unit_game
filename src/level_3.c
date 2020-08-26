#include "header.h"

int correct_3[7] = {SDLK_DOWN, SDLK_UP, SDLK_RIGHT, SDLK_UP, SDLK_RIGHT, SDLK_UP, SDLK_RETURN};

SDL_Texture* texture_worker_1;
SDL_Texture* texture_box;
SDL_Texture* texture_machine_ready_1;
SDL_Texture* texture_success02;
SDL_Texture* texture_text02;
SDL_Texture* texture_person_1;
SDL_Texture* texture_product;
Mix_Chunk* coinDrop;
Mix_Chunk* conveyorBelt;


void setup_3() {
    SDL_Surface* worker_1 = IMG_Load("resource/img/worker.png");
    texture_worker_1 = SDL_CreateTextureFromSurface(renderer, worker_1);
    SDL_FreeSurface(worker_1);

    SDL_Surface* surface_box = IMG_Load("resource/img/box.jpeg");
    texture_box = SDL_CreateTextureFromSurface(renderer, surface_box);
    SDL_FreeSurface(surface_box);

    SDL_Surface* machine_ready = IMG_Load("resource/img/machine.png");
    texture_machine_ready_1 = SDL_CreateTextureFromSurface(renderer, machine_ready);
    SDL_FreeSurface(machine_ready);

    SDL_Surface* success02 = IMG_Load("resource/img/next_3.png");
    texture_success02 = SDL_CreateTextureFromSurface(renderer, success02);
    SDL_FreeSurface(success02);

    SDL_Surface* person01 = IMG_Load("resource/img/person_3.png");
    texture_person_1 = SDL_CreateTextureFromSurface(renderer, person01);
    SDL_FreeSurface(person01);

    SDL_Surface* text02 = IMG_Load("resource/img/text_3.png");
    texture_text02 = SDL_CreateTextureFromSurface(renderer, text02);
    SDL_FreeSurface(text02);

    SDL_Surface* surface_product = IMG_Load("resource/img/acum.png");
    texture_product = SDL_CreateTextureFromSurface(renderer, surface_product);
    SDL_FreeSurface(surface_product);

    sprintf(buffer, "%d", (int)score);
    texture_score = renderText(buffer, renderer);
    stop_score = 0;

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    coinDrop = Mix_LoadWAV("resource/audio/coins-drop-pirate-gold-doubloon-ring_G16XQD4d.mp3");
    conveyorBelt = Mix_LoadWAV("resource/audio/conveyor-belt-starting_MktIka4u.mp3");
    coinDrop -> volume = 50;
    conveyorBelt -> volume = 15;
}

void update_3() {
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    static int step = 0;

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        SDL_Delay(time_to_wait);

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();

    if (finish && score <= 85000 && stop_score == 0) {
        score += 12000 * delta_time;
        sprintf(buffer, "%d", (int)score);
        texture_score = renderText(buffer, renderer);

        if (score > 84200 && stop_score == 0) {
            score = 85000;
            sprintf(buffer, "%d", (int)score);
            texture_score = renderText(buffer, renderer);
            stop_score = 1;
        }
    }

    if (person.x > 980)
        person.x -= 180 * delta_time;

    if (restart == 1 && start == 0) {
        count = 0, start = 0, step = 0;
        for (int j = 0; j < 100; ++j) real[j] = 0;
        box.x = 470, box.y = 510, box.width = 50, box.height = 50;
        restart = 0;
    }

    if (start) {
        if (step == 0) {
            if (box.y < 571) {
                if (correct_3[0] == real[0]) {
                    Mix_PlayChannel( -1, conveyorBelt, 0);
                    box.x += 0 * delta_time;
                    box.y += 90 * delta_time;
                }
            }
            if (box.y > 570) step = 1;
        }

        if (step == 1) {
            if (box.y > 390 && box.x > 190) {
                if (correct_3[1] == real[1]) {
                    Mix_PlayChannel( -1, conveyorBelt, 0);
                    box.x -= 110 * delta_time;
                    box.y -= 64 * delta_time;
                }
            }
            if (box.y < 410) step = 2;
        }

        if (step == 2) {
            if (box.y > 120 && box.x < 720) {
                if (correct_3[2] == real[2]) {
                    if (correct_3[3] == real[3]) {
                        Mix_PlayChannel( -1, conveyorBelt, 0);
                        box.x += 110 * delta_time;
                        box.y -= 64 * delta_time;
                    }
                }
            }
            if (box.x > 680) step = 3;
        }

        if (step == 3) {
            if (box.y < 180 && box.x < 900) {
                if (correct_3[4] == real[4]) {
                    if (correct_3[5] == real[5]) {
                        //Mix_PlayChannel( -1, conveyorBelt, 0);
                        box.x += 110 * delta_time;
                        box.y += 64 * delta_time;
                    }
                }
            }
            if (box.x > 770) step = 4;
        }

        for (int i = 0; i < 6; ++i) {
            if (correct_3[i] != real[i]) {
                if (restart == 1) {
                    count = 0, start = 0, step = 0;
                    for (int j = 0; j < 100; ++j) real[j] = 0;
                    box.x = 470, box.y = 510, box.width = 50, box.height = 50;
                    restart = 0;
                }
            }
        }

        if (worker.x < 760 && step == 4) {
            Mix_PlayChannel( -1, coinDrop, 0);
            finish = 1;
            worker.x += 73 * delta_time;
            worker.y -= 43 * delta_time;
        }
    }
}

void render_3() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_Rect worker_rect = {(int)worker.x, (int)worker.y, (int)worker.width, (int)worker.height};
    SDL_RenderCopy(renderer, texture_worker_1, NULL, &worker_rect);
    
    SDL_Rect box_rect = {(int)box.x, (int)box.y, (int)box.width, (int)box.height};

    if (box.x < 530)
        SDL_RenderCopy(renderer, texture_box, NULL, &box_rect);
    if (box.x > 530)
        SDL_RenderCopy(renderer, texture_product, NULL, &box_rect);

    SDL_Rect machine_rect = {351,150,250,250};
    SDL_RenderCopy(renderer, texture_machine_ready_1, NULL, &machine_rect);



    SDL_Rect text_rect = {(int)text.x, (int)text.y, (int)text.width, (int)text.height};
    if(person.x < 990 && !finish)
        SDL_RenderCopy(renderer, texture_text02, NULL, &text_rect);

    SDL_Rect text2_rect = {(int)next.x, (int)next.y, (int)next.width, (int)next.height};

    if (finish)
        SDL_RenderCopy(renderer, texture_success02, NULL, &text2_rect);

    SDL_Rect person_rect = {(int)person.x, (int)person.y, (int)person.width, (int)person.height};
    SDL_RenderCopy(renderer, texture_person_1, NULL, &person_rect);

    SDL_Rect icons[6] = {{182, 14, 42, 42}, {230, 14, 42, 42}, {278, 14, 42, 42},
                         {326, 14, 42, 42}, {374, 14, 42, 42}, {422, 14, 42, 42}};
    render_copy_icons(6, icons);

    SDL_Rect score_rect = {1050, 35, 120, 50};
    SDL_RenderCopy(renderer, texture_score, NULL, &score_rect);

    SDL_RenderPresent(renderer);
}

void cleanup_3() {
    SDL_DestroyTexture(texture_worker_1);
    SDL_DestroyTexture(texture_box);
    SDL_DestroyTexture(texture_person_1);
    SDL_DestroyTexture(texture_machine_ready_1);
    SDL_DestroyTexture(texture_success02);
    SDL_DestroyTexture(texture_text02);
    SDL_DestroyTexture(texture_score);
    SDL_DestroyTexture(texture_product);
    Mix_FreeChunk(conveyorBelt);
    Mix_FreeChunk(coinDrop);
    coinDrop = NULL;
    conveyorBelt = NULL;
}
