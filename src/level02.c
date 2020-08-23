#include "../inc/header.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;
int start = 0;
int up = 0;
int right = 0;
int down = 0;
int left = 0;
int enter = 0;
int correct_2[7] = {1073741905, 1073741906, 1073741903, 1073741906, 1073741903, 1073741906, 13};
int real_2[100];
static int count = 0;

struct ball {
    float x;
    float y;
    float width;
    float height;
}   ball, worker;


SDL_Surface* image = NULL;
SDL_Texture* texture = NULL;

SDL_Surface* icon_up, *icon_down, *icon_right, *icon_left;
SDL_Texture* texture_up, *texture_down, *texture_right, *texture_left;

SDL_Surface* box = NULL;
SDL_Texture* texture2 = NULL;

SDL_Surface* worker_1 = NULL;
SDL_Texture* texture3 = NULL;

int initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return FALSE;
    }
    window = SDL_CreateWindow(
        NULL, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDHT,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL Window.\n");
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return 0;
    }
    return TRUE;
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            game_is_running = FALSE;
            break;
        
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_UP) {
                real_2[count] = 1073741906;
                ++count;
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
                real_2[count] = 1073741905;
                ++count;
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                real_2[count] = 1073741903;
                ++count;
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
                real_2[count] = 1073741904;
                ++count;
            }

            if (event.key.keysym.sym == SDLK_RETURN) {
                real_2[count] = 13;
                ++count;
                start = 1;
            }

            if (event.key.keysym.sym == SDLK_ESCAPE)
                game_is_running = FALSE;
            break;
    }
}

void setup() {
    ball.x = 470;
    ball.y = 510;
    ball.width = 50;
    ball.height = 50;

    worker.x = 610;
    worker.y = 310;
    worker.width = 120;
    worker.height = 110;

    image = IMG_Load("../resource/img/level_2.jpg");
    texture = SDL_CreateTextureFromSurface(renderer, image);

    icon_up = IMG_Load("../resource/img/icon_up.png");
    texture_up = SDL_CreateTextureFromSurface(renderer, icon_up);

    icon_down = IMG_Load("../resource/img/icon_down.png");
    texture_down = SDL_CreateTextureFromSurface(renderer, icon_down);

    icon_right = IMG_Load("../resource/img/icon_right.png");
    texture_right = SDL_CreateTextureFromSurface(renderer, icon_right);

    icon_left = IMG_Load("../resource/img/icon_left.png");
    texture_left = SDL_CreateTextureFromSurface(renderer, icon_left);
}

void update() {
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    static int i = 0;
    static int j = 0;
    static int k = 0;
    static int m = 0;

    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        SDL_Delay(time_to_wait);

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
    last_frame_time = SDL_GetTicks();

    if (start) {
        if (i == 0) {
            if (ball.y < 571) {
                if (correct_2[0] == real_2[0]) {
                    ball.x += 0 * delta_time;
                    ball.y += 60 * delta_time;
                }
            }
            if (ball.y > 570) j = 1, i = 1;
        }

        if (j == 1) {
            if (ball.y > 390 && ball.x > 190) {
                if (correct_2[1] == real_2[1]) {
                    ball.x -= 110 * delta_time;
                    ball.y -= 64 * delta_time;
                }
            }
            if (ball.y < 410) k = 2, j = 0;
        }

        if (k == 2) {
            if (ball.y > 120 && ball.x < 720) {
                if (correct_2[2] == real_2[2]) {
                    if (correct_2[3] == real_2[3]) {
                        ball.x += 110 * delta_time;
                        ball.y -= 64 * delta_time;
                    }
                }
            }
            if (ball.x > 690) k = 0, m = 3;
        }

        if (m == 3 && ball.y < 170 && ball.x < 900) {
            if (correct_2[4] == real_2[4]) {
                if (correct_2[5] == real_2[5]) {
                    ball.x += 110 * delta_time;
                    ball.y += 64 * delta_time;
                }
            }
        }

        if (ball.x > 650 && worker.x < 780) {
            worker.x += 73 * delta_time;
            worker.y -= 43 * delta_time;
        }
    }
}

void render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    
    worker_1 = IMG_Load("../resource/img/worker.png");
    texture3 = SDL_CreateTextureFromSurface(renderer, worker_1);

    SDL_Rect worker_rect = { 
            (int)worker.x, 
            (int)worker.y, 
            (int)worker.width, 
            (int)worker.height 
        };

    SDL_RenderCopy(renderer, texture3, NULL, &worker_rect);

    SDL_Rect icons[6][4] = {{{182, 14, 42, 42}}, {{230, 14, 42, 42}}, {{278, 14, 42, 42}},
                            {{326, 14, 42, 42}}, {{374, 14, 42, 42}}, {{422, 14, 42, 42}}};

    if (real_2[0] == 1073741906)
        SDL_RenderCopy(renderer, texture_up, NULL, icons[0]);
    else if (real_2[0] == 1073741905)
        SDL_RenderCopy(renderer, texture_down, NULL, icons[0]);
    else if (real_2[0] == 1073741903)
        SDL_RenderCopy(renderer, texture_right, NULL, icons[0]);
    else if (real_2[0] == 1073741904)
        SDL_RenderCopy(renderer, texture_left, NULL, icons[0]);

    if (real_2[1] == 1073741906)
        SDL_RenderCopy(renderer, texture_up, NULL, icons[1]);
    else if (real_2[1] == 1073741905)
        SDL_RenderCopy(renderer, texture_down, NULL, icons[1]);
    else if (real_2[1] == 1073741903)
        SDL_RenderCopy(renderer, texture_right, NULL, icons[1]);
    else if (real_2[1] == 1073741904)
        SDL_RenderCopy(renderer, texture_left, NULL, icons[1]);

    if (real_2[2] == 1073741906)
        SDL_RenderCopy(renderer, texture_up, NULL, icons[2]);
    else if (real_2[2] == 1073741905)
        SDL_RenderCopy(renderer, texture_down, NULL, icons[2]);
    else if (real_2[2] == 1073741903)
        SDL_RenderCopy(renderer, texture_right, NULL, icons[2]);
    else if (real_2[2] == 1073741904)
        SDL_RenderCopy(renderer, texture_left, NULL, icons[2]);

    if (real_2[3] == 1073741906)
        SDL_RenderCopy(renderer, texture_up, NULL, icons[3]);
    else if (real_2[3] == 1073741905)
        SDL_RenderCopy(renderer, texture_down, NULL, icons[3]);
    else if (real_2[3] == 1073741903)
        SDL_RenderCopy(renderer, texture_right, NULL, icons[3]);
    else if (real_2[3] == 1073741904)
        SDL_RenderCopy(renderer, texture_left, NULL, icons[3]);

    if (real_2[4] == 1073741906)
        SDL_RenderCopy(renderer, texture_up, NULL, icons[4]);
    else if (real_2[4] == 1073741905)
        SDL_RenderCopy(renderer, texture_down, NULL, icons[4]);
    else if (real_2[4] == 1073741903)
        SDL_RenderCopy(renderer, texture_right, NULL, icons[4]);
    else if (real_2[4] == 1073741904)
        SDL_RenderCopy(renderer, texture_left, NULL, icons[4]);

    if (real_2[5] == 1073741906)
        SDL_RenderCopy(renderer, texture_up, NULL, icons[5]);
    else if (real_2[5] == 1073741905)
        SDL_RenderCopy(renderer, texture_down, NULL, icons[5]);
    else if (real_2[5] == 1073741903)
        SDL_RenderCopy(renderer, texture_right, NULL, icons[5]);
    else if (real_2[5] == 1073741904)
        SDL_RenderCopy(renderer, texture_left, NULL, icons[5]);


    if (ball.y < 200 || ball.y > 300) {
        box = IMG_Load("../resource/img/box.jpeg");
        texture2 = SDL_CreateTextureFromSurface(renderer, box);

        SDL_Rect ball_rect = {
            (int)ball.x,
            (int)ball.y,
            (int)ball.width,
            (int)ball.height
        };

        SDL_RenderCopy(renderer, texture2, NULL, &ball_rect);
        SDL_RenderPresent(renderer);
    }

}

void destroy_window() {
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
/*
int main(void) {
    game_is_running = initialize_window();

    setup();

    while (game_is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();
    return 0;
}
*/
