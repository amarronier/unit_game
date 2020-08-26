#include "header.h"

int flag = 0;

SDL_Texture* intro_image;
SDL_Texture* speech_image_1;
SDL_Texture* speech_image_2;

void setup_intro() {
    SDL_Surface* image = IMG_Load("resource/img/intro.jpeg");
    intro_image = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    SDL_Surface* speech_1 = IMG_Load("resource/img/speech_1.jpeg");
    speech_image_1 = SDL_CreateTextureFromSurface(renderer, speech_1);
    SDL_FreeSurface(speech_1);

    SDL_Surface* speech_2 = IMG_Load("resource/img/speech_2.jpg");
    speech_image_2 = SDL_CreateTextureFromSurface(renderer, speech_2);
    SDL_FreeSurface(speech_2);
}

void process_intro() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            game_is_running = FALSE;

            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                if (event.button.x > 0 && event.button.x < 4000
                    && event.button.y > 0 && event.button.y < 1700) {
                    flag++;
                    if (flag == 3) game_is_running = FALSE;
                }
            }
            break;
    }
}

void render_intro() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, intro_image, NULL, NULL);
    SDL_RenderPresent(renderer);
    //sleep(5);
    SDL_RenderClear(renderer);
}

void render_speech_1() {
    if (flag == 1) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, speech_image_1, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}

void render_speech_2() {
    if (flag == 2) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, speech_image_2, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
}

void cleanup_intro() {
    SDL_DestroyTexture(intro_image);
    SDL_DestroyTexture(speech_image_1);
    SDL_DestroyTexture(speech_image_2);
}

