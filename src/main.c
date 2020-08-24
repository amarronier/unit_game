#include "header.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* image = NULL;
SDL_Texture* texture = NULL;

int game_is_running = FALSE;
int last_frame_time = 0;
int count = 0;
int start = 0;
int restart = 0;

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

void setup(t_rectangle box_init, t_rectangle worker_init, const char *background_filename) {
    box.x = box_init.x;
    box.y = box_init.y;
    box.width = box_init.width;
    box.height = box_init.height;

    worker.x = worker_init.x;
    worker.y = worker_init.y;
    worker.width = worker_init.width;
    worker.height = worker_init.height;

    text.x = 1500;
    text.y = 335;
    text.width = 684;
    text.height = 405;

    success.x = 600;
    success.y = 335;
    success.width = 684;
    success.height = 405;

    image = IMG_Load(background_filename);
    texture = SDL_CreateTextureFromSurface(renderer, image);

    icon_up = IMG_Load("resource/img/icon_up.png");
    texture_up = SDL_CreateTextureFromSurface(renderer, icon_up);

    icon_down = IMG_Load("resource/img/icon_down.png");
    texture_down = SDL_CreateTextureFromSurface(renderer, icon_down);

    icon_right = IMG_Load("resource/img/icon_right.png");
    texture_right = SDL_CreateTextureFromSurface(renderer, icon_right);

    icon_left = IMG_Load("resource/img/icon_left.png");
    texture_left = SDL_CreateTextureFromSurface(renderer, icon_left);
}

void process_input() {
    SDL_Event event;
    SDL_PollEvent(&event);
    //SDL_WaitEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            game_is_running = FALSE;
            break;

        case SDL_KEYUP:
            switch(event.key.keysym.sym) {
                case SDLK_RETURN:
                    start = 1; // fallthrough
                case SDLK_UP:
                case SDLK_DOWN:
                case SDLK_RIGHT:
                case SDLK_LEFT:
                    real[count] = event.key.keysym.sym;
                    ++count;
                    break;
                case SDLK_r:
                    restart = 1;
                    break;
                case SDLK_ESCAPE:
                    game_is_running = FALSE;
                    break;
            }
            break;
    }
}

void render_copy_icons(int n, const SDL_Rect *icons) {
    for (int i = 0; i < n; ++i) {
        if (real[i] == SDLK_UP)
            SDL_RenderCopy(renderer, texture_up, NULL, &(icons[i]));
        else if (real[i] == SDLK_DOWN)
            SDL_RenderCopy(renderer, texture_down, NULL, &(icons[i]));
        else if (real[i] == SDLK_RIGHT)
            SDL_RenderCopy(renderer, texture_right, NULL, &(icons[i]));
        else if (real[i] == SDLK_LEFT)
            SDL_RenderCopy(renderer, texture_left, NULL, &(icons[i]));
    }
}

void destroy_window() {
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void cleanup_between_levels() {
    game_is_running = TRUE;
    count = 0;
    start = 0;
    for (int i = 0; i < 100; ++i) real[i] = 0;
}

void run_level(int level) {
    if (level == 1) {
        const char *background = "resource/img/level01.jpg";
        t_rectangle box_init = {210, 500, 50, 50};
        t_rectangle worker_init = {980, 344, 120, 110};
        setup(box_init, worker_init, background);
    }
    else if (level == 2) {
        const char *background = "resource/img/level_2.jpg";
        t_rectangle box_init = {470, 510, 50, 50};
        t_rectangle worker_init = {610, 310, 120, 110};
        setup(box_init, worker_init, background);
    }

    while (game_is_running) {
        process_input();
        if (level == 1) {
            update_1();
            render_1();
        }
        else if (level == 2) {
            update_2();
            render_2();
        }
    }
}

int main() {
    game_is_running = initialize_window();

    for (int level = 1; level <= 2; ++level) {
        run_level(level);
        cleanup_between_levels();
    }

    destroy_window();
    return 0;
}



