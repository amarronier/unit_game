#include "header.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Surface* image = NULL;
SDL_Texture* texture = NULL;
SDL_Texture* texture_score = NULL; 

int game_is_running = FALSE;
int last_frame_time = 0;
int count = 0;
int start = 0;
int restart = 0;
int stop_score = 0;

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
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        exit(1);
    }
    TTF_Init();

    return TRUE;
}

void setup(t_rectangle box_init, t_rectangle worker_init, t_rectangle panel_init, t_rectangle person_init,
           t_rectangle text_init, t_rectangle next_init, t_rectangle token0_init, t_rectangle token_init,
           t_rectangle coin_init, t_rectangle kran_init, const char *background_filename) {

    box = box_init;
    worker = worker_init;
    panel = panel_init;
    person = person_init;
    text = text_init;
    next = next_init;
    token = token_init;
    token0 = token0_init;
    coin = coin_init;
    kran = kran_init;

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

    switch (event.type) {
        case SDL_QUIT:
            game_is_running = FALSE;
            break;

        case SDL_MOUSEBUTTONDOWN:

            if (event.button.button == SDL_BUTTON_LEFT)
                if (event.button.x > 805 && event.button.x < 940
                    && event.button.y > 590 && event.button.y < 640 && box.x > 750)
                    game_is_running = FALSE;
                if(event.button.x > 250 && event.button.x < 400
                    && event.button.y > 590 && event.button.y < 700)
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

SDL_Texture* renderText(const char *buffer, SDL_Renderer *renderer) {
        
        SDL_Color color = {255, 210, 0, 255};
        int fontSize = 60;
        char fontFile[] = "resource/img/arial.ttf";
        TTF_Font *font = TTF_OpenFont(fontFile, fontSize);
    
        SDL_Surface *surf = TTF_RenderText_Blended(font, buffer, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);

        SDL_FreeSurface(surf);
        TTF_CloseFont(font);
        return texture;
}

void destroy_window() {
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void cleanup_between_levels(int level) {
    game_is_running = TRUE;
    count = 0;
    start = 0;
    for (int i = 0; i < 100; ++i) real[i] = 0;
    if (level == 1) {
        cleanup_1();
    }
    else if (level == 2) {
        cleanup_2();
    }
    else if (level == 3) {
        cleanup_3();
    }
    else if (level == 4) {
        cleanup_4();
    }
}

void run_level(int level) {
    if (level == 1) {
        const char *background = "resource/img/level_1.jpg";
        t_rectangle box_init = {210, 500, 50, 50};
        t_rectangle worker_init = {980, 310, 120, 110};
        t_rectangle panel_init = {-342, -68, 292, 376};
        t_rectangle person_init = {1300, 300, 249, 423};
        t_rectangle text_init = {587, 490, 508, 290};
        t_rectangle next_init = {650, 490, 448, 177};
        t_rectangle token0_init = {1150, 43, 20, 35};
        t_rectangle token_init = {1085, 43, 89, 35};
        t_rectangle coin_init = {1180, 22, 70, 70};
        t_rectangle kran_init = {0, 0, 0, 0};
        setup(box_init, worker_init, panel_init, person_init, text_init, next_init,
              token0_init, token_init, coin_init, kran_init, background);
        setup_1();
    }
      else if (level == 2) {
        const char *background = "resource/img/level_2.png";
        t_rectangle box_init = {650, 595, 50, 50};
        t_rectangle worker_init = {420, 140, 150, 150};
        t_rectangle panel_init = {20, 20, 292, 376};
        t_rectangle person_init = {1300, 300, 249, 423};
        t_rectangle text_init = {-300, 330, 500, 400};
        t_rectangle next_init = {10, 330, 500, 400};
        t_rectangle token0_init = {1085, 43, 680, 35};
        t_rectangle token_init = {1085, 43, 89, 35};
        t_rectangle coin_init = {1170, 20, 70, 70};
        t_rectangle kran_init = {640, 300, 100, 100};
        setup(box_init, worker_init, panel_init, person_init, text_init, next_init,
              token0_init, token_init, coin_init, kran_init, background);
        setup_2();
    }
    else if (level == 3) {
        const char *background = "resource/img/level_3_final.jpg";
        t_rectangle box_init = {470, 510, 50, 50};
        t_rectangle worker_init = {610, 310, 120, 110};
        t_rectangle panel_init = {20, 20, 292, 376};
        t_rectangle person_init = {1300, 320, 289, 404};
        t_rectangle text_init = {590, 490, 459, 208};
        t_rectangle next_init = {670, 500, 400, 177};
        t_rectangle token0_init = {1085, 43, 89, 35};
        t_rectangle token_init = {1085, 43, 89, 35};
        t_rectangle coin_init = {1170, 20, 70, 70};
        t_rectangle kran_init = {0, 0, 0, 0};
        setup(box_init, worker_init, panel_init, person_init, text_init, next_init,
              token0_init, token_init, coin_init, kran_init, background);
        setup_3();
    }
    else if (level == 4) {
        const char *background = "resource/img/level_4_final.jpg";
        t_rectangle box_init = {287, 595, 50, 50};
        t_rectangle worker_init = {80, 585, 120, 110};
        t_rectangle panel_init = {20, 20, 292, 376};
        t_rectangle person_init = {1300, 300, 249, 423};
        t_rectangle text_init = {1300, 330, 670, 400};
        t_rectangle next_init = {640, 300, 685, 435};
        t_rectangle token0_init = {1085, 43, 680, 35};
        t_rectangle token_init = {1085, 43, 89, 35};
        t_rectangle coin_init = {1170, 20, 70, 70};
        t_rectangle kran_init = {640, 300, 100, 100};
        setup(box_init, worker_init, panel_init, person_init, text_init, next_init,
              token0_init, token_init, coin_init, kran_init, background);
        setup_4();
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
        else if (level == 3) {
            update_3();
            render_3();
        }
        else if (level == 4) {
            update_4();
            render_4();
        }
    }
}

int main() {
    game_is_running = initialize_window();

    for (int level = 1; level <= 4; ++level) {
        run_level(level);
        cleanup_between_levels(level);
    }

    destroy_window();
    return 0;
}
