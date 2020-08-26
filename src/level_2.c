#include "header.h"

int correct_2[4] = {SDLK_UP, SDLK_LEFT, SDLK_UP, SDLK_RETURN};
int finish_2 = 0;

SDL_Texture* texture_worker_1;
SDL_Texture* texture_box;
SDL_Texture* texture_machine_ready_1;
SDL_Texture* texture_success04;
SDL_Texture* texture_text04;
SDL_Texture* texture_product;
Mix_Chunk* coinDrop;
Mix_Chunk* conveyorBelt;

void setup_2() {
    SDL_Surface* worker_1 = IMG_Load("resource/img/worker.png");
    texture_worker_1 = SDL_CreateTextureFromSurface(renderer, worker_1);
    SDL_FreeSurface(worker_1);

    SDL_Surface* surface_box = IMG_Load("resource/img/box.jpeg");
    texture_box = SDL_CreateTextureFromSurface(renderer, surface_box);
    SDL_FreeSurface(surface_box);

    SDL_Surface* machine_ready = IMG_Load("resource/img/machine.png");
    texture_machine_ready_1 = SDL_CreateTextureFromSurface(renderer, machine_ready);
    SDL_FreeSurface(machine_ready);

    SDL_Surface* success02 = IMG_Load("resource/img/next_2.png");
    texture_success04 = SDL_CreateTextureFromSurface(renderer, success02);
    SDL_FreeSurface(success02);

    SDL_Surface* text02 = IMG_Load("resource/img/text_2.png");
    texture_text04 = SDL_CreateTextureFromSurface(renderer, text02);
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

void update_2() {
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    static int step = 0;

   

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        SDL_Delay(time_to_wait);

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();

    if (finish_2 && score <= 35000 && stop_score == 0) {
        score += 12000 * delta_time;
        sprintf(buffer, "%d", (int)score);
        texture_score = renderText(buffer, renderer);

        if (score > 34600 && stop_score == 0) {
            score = 35000;
            sprintf(buffer, "%d", (int)score);
            texture_score = renderText(buffer, renderer);
            stop_score = 1;
        }
    }
     if (box.x < 1200) {
        if (text.x < 10) {
            text.x += 350 * delta_time;
        }
    }

    if (restart == 1 && start == 0) {
        count = 0, start = 0, step = 0;
        for (int j = 0; j < 100; ++j) real[j] = 0;
        box.x = 650, box.y = 595, box.width = 50, box.height = 50;
        restart = 0;
    }

    if (start) {
        if (step == 0) {
            Mix_PlayChannel( -1, conveyorBelt, 0);
            if (box.x < 1120) {
                if (correct_2[0] == real[0]) {
                    box.x += 100 * delta_time;
                    box.y -= 58 * delta_time;
                }
            }
            if (box.x > 1110 ) step = 1;
        }

        if (step == 1) {
            if (box.x > 750) {
                if (correct_2[1] == real[1]) {
                    if (correct_2[2] == real[2]) {
                       box.x -= 110 * delta_time;
                        box.y -= 64 * delta_time;
                    }
                }
            }
            if (box.x < 755) step = 2;
        }

        for (int i = 0; i < 3; ++i) {
            if (correct_2[i] != real[i]) {
                if (restart == 1) {
                    count = 0, start = 0, step = 0;
                    for (int j = 0; j < 100; ++j) real[j] = 0;
                    box.x = 650, box.y = 595, box.width = 50, box.height = 50;
                    restart = 0;
                }
            }
        }

        if (worker.x < 610 && step == 2) {
            Mix_PlayChannel( -1, coinDrop, 0);
            worker.x += 110 * delta_time;
            worker.y -= 50 * delta_time;
            finish_2 = 1;
        }
        if (worker.x > 600) step = 3;
    }
}

void render_2() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    SDL_Rect worker_rect = {(int)worker.x, (int)worker.y, (int)worker.width, (int)worker.height};
    SDL_RenderCopy(renderer, texture_worker_1, NULL, &worker_rect);

    SDL_Rect box_rect = {(int)box.x, (int)box.y, (int)box.width, (int)box.height};

    if (box.y > 450)
        SDL_RenderCopy(renderer, texture_box, NULL, &box_rect);
    if (box.y < 450)
        SDL_RenderCopy(renderer, texture_product, NULL, &box_rect);

    SDL_Rect machine_rect = {780,310,300,300};
    SDL_RenderCopy(renderer, texture_machine_ready_1, NULL, &machine_rect);


    SDL_Rect text_rect = {(int)text.x, (int)text.y, (int)text.width, (int)text.height};
    if(!finish_2)
        SDL_RenderCopy(renderer, texture_text04, NULL, &text_rect);

    SDL_Rect next_rect = {(int) next.x, (int) next.y, (int) next.width, (int) next.height};
    if (finish_2)
        SDL_RenderCopy(renderer, texture_success04, NULL, &next_rect);


    SDL_Rect icons[3] = {{183, 13, 42, 42}, {231, 13, 42, 42}, {280, 13, 42, 42}};
    render_copy_icons(3, icons);

    SDL_Rect score_rect = {1050, 35, 120, 50};
    SDL_RenderCopy(renderer, texture_score, NULL, &score_rect);

    SDL_RenderPresent(renderer);
}

void cleanup_2() {
    SDL_DestroyTexture(texture_worker_1);
    SDL_DestroyTexture(texture_box);
    SDL_DestroyTexture(texture_machine_ready_1);
    SDL_DestroyTexture(texture_success04);
    SDL_DestroyTexture(texture_text04);
    SDL_DestroyTexture(texture_score);
    SDL_DestroyTexture(texture_product);
    Mix_FreeChunk(conveyorBelt);
    Mix_FreeChunk(coinDrop);
    coinDrop = NULL;
    conveyorBelt = NULL;
}
