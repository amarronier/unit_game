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
SDL_Texture* texture_product;
Mix_Chunk* coinDrop;
Mix_Chunk* conveyorBelt;

void setup_1() {
    SDL_Surface* panel01 = IMG_Load("resource/img/panel_1.png");
    texture_panel_1 = SDL_CreateTextureFromSurface(renderer, panel01);
    SDL_FreeSurface(panel01);

    SDL_Surface* text01 = IMG_Load("resource/img/text_1.png");
    texture_text01 = SDL_CreateTextureFromSurface(renderer, text01);
    SDL_FreeSurface(text01);

    SDL_Surface* next01 = IMG_Load("resource/img/next_1.png");
    texture_next01 = SDL_CreateTextureFromSurface(renderer, next01);
    SDL_FreeSurface(next01);

    SDL_Surface* person01 = IMG_Load("resource/img/person_1.png");
    texture_person_1 = SDL_CreateTextureFromSurface(renderer, person01);
    SDL_FreeSurface(person01);

    SDL_Surface* token00 = IMG_Load("resource/img/0.png");
    texture_token00 = SDL_CreateTextureFromSurface(renderer, token00);
    SDL_FreeSurface(token00);

    SDL_Surface* worker_1 = IMG_Load("resource/img/worker.jpeg");
    texture_worker_1 = SDL_CreateTextureFromSurface(renderer, worker_1);
    SDL_FreeSurface(worker_1);

    SDL_Surface* surface_box = IMG_Load("resource/img/box.jpeg");
    texture_box = SDL_CreateTextureFromSurface(renderer, surface_box);
    SDL_FreeSurface(surface_box);

    SDL_Surface* surface_product = IMG_Load("resource/img/product.png");
    texture_product = SDL_CreateTextureFromSurface(renderer, surface_product);
    SDL_FreeSurface(surface_product);

    SDL_Surface* machine_ready = IMG_Load("resource/img/machine_my.png");
    texture_machine_ready_1 = SDL_CreateTextureFromSurface(renderer, machine_ready);
    SDL_FreeSurface(machine_ready);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    coinDrop = Mix_LoadWAV("resource/audio/coins-drop-pirate-gold-doubloon-ring_G16XQD4d.mp3");
    conveyorBelt = Mix_LoadWAV("resource/audio/conveyor-belt-starting_MktIka4u.mp3");
    coinDrop -> volume = 50;
    conveyorBelt -> volume = 15;
}

void update_1() {
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        SDL_Delay(time_to_wait);

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();


    if (box.x > 700 && score <= 10000 && stop_score == 0) {
        score += 4000 * delta_time;
        sprintf(buffer, "%d", (int)score);
        texture_score = renderText(buffer, renderer);

        if (score > 9600 && stop_score == 0) {
            score = 10000;
            sprintf(buffer, "%d", (int)score);
            texture_score = renderText(buffer, renderer);
            stop_score = 1;
        }
        
    }
    
    if (box.x > 800 && score <= 10000 && stop_score == 0) {
        score += 4000 * delta_time;
        sprintf(buffer, "%d", (int)score);
        texture_score = renderText(buffer, renderer);
        

        if (score > 9600 && stop_score == 0) {
            score = 10000;
            sprintf(buffer, "%d", (int)score);
            texture_score = renderText(buffer, renderer);
            stop_score = 1;
        }
        
    }
    
    if (panel.x < -46)
        panel.x += 180 * delta_time;

    if (person.x > 1050)
        person.x -= 180 * delta_time;

    if (restart == 1 && start == 0) {
        count = 0, start = 0;
        for (int i = 0; i < 100; ++i) real[i] = 0;
        restart = 0;
    }

    if (start) {
        if (box.x < 770) {
            if (correct_1[0] == real[0]) {
                box.x += 90 * delta_time;
                box.y -= 52 * delta_time;
                Mix_PlayChannel( -1, conveyorBelt, 0);
            } else if (restart == 1) {
                count = 0, start = 0;
                for (int i = 0; i < 100; ++i) real[i] = 0;
                restart = 0;
            }
        }
    }


    if (box.x > 760 && worker.y > 210 && restart == 0) {
        Mix_PlayChannel( -1, coinDrop, 0);
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
    if (box.x < 700)
        SDL_RenderCopy(renderer, texture_token00, NULL, &token0_rect);


    SDL_Rect worker_rect = {(int)worker.x, (int)worker.y, (int)worker.width, (int)worker.height};
    SDL_RenderCopy(renderer, texture_worker_1, NULL, &worker_rect);

    SDL_Rect box_rect = {(int)box.x, (int)box.y, (int)box.width, (int)box.height};
    if (box.x < 600)
        SDL_RenderCopy(renderer, texture_box, NULL, &box_rect);
    if (box.x > 600)
        SDL_RenderCopy(renderer, texture_product, NULL, &box_rect);

    SDL_Rect machine_rect = {520, 200, 190, 212};
    SDL_RenderCopy(renderer, texture_machine_ready_1, NULL, &machine_rect);

    SDL_Rect icons[1] = {{180, 13, 42, 42}};
    render_copy_icons(1, icons);

    SDL_Rect score_rect = {1050, 35, 120, 50};

    if(score > 1000)
        SDL_RenderCopy(renderer, texture_score, NULL, &score_rect);

    SDL_RenderPresent(renderer);
}

void cleanup_1() {
    SDL_DestroyTexture(texture_panel_1);
    SDL_DestroyTexture(texture_text01);
    SDL_DestroyTexture(texture_next01);
    SDL_DestroyTexture(texture_person_1);
    SDL_DestroyTexture(texture_token00);
    //SDL_DestroyTexture(texture_token01);
    SDL_DestroyTexture(texture_worker_1);
    SDL_DestroyTexture(texture_box);
    SDL_DestroyTexture(texture_machine_ready_1);
    SDL_DestroyTexture(texture_score);
    SDL_DestroyTexture(texture_product);
    Mix_FreeChunk(conveyorBelt);
    Mix_FreeChunk(coinDrop);
    coinDrop = NULL;
    conveyorBelt = NULL;
}
