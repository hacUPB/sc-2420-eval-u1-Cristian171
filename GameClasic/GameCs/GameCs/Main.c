#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FRAME_TARGET_TIME (1000 / 60)  // 60 FPS
#define MAX_STRUCTURES 5  // Número de obstáculos
#define MAX_SHOTS 10      // Número máximo de disparos
#define MAX_COLLECTIBLES 5  // Número de recolectables
#define MAX_BOSS_HEALTH 10  // Vida del jefe

struct game_object {
    float x;
    float y;
    float width;
    float height;
    float vel_x;  // Velocidad en la dirección horizontal
    float vel_y;  // Velocidad en la dirección vertical
} paddle, structures[MAX_STRUCTURES], shots[MAX_SHOTS], collectibles[MAX_COLLECTIBLES], boss;

int boss_health = MAX_BOSS_HEALTH;  // Vida inicial del jefe
bool boss_active = true;  // Si el jefe está activo
bool game_is_running = false;
int last_frame_time = 0;
float gravity = 1000.0f;  // Gravedad más fuerte
float jump_force = -600.0f;  // Mayor fuerza de salto para más velocidad
bool is_jumping = false;  // Si el paddle está saltando
bool show_start_menu = true;  // Si el menú de inicio está visible
int score = 0;  // Puntuación inicial
int shot_count = 0;  // Número de disparos activos

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;

void render_start_menu(void) {
    // Aquí puedes implementar el renderizado del menú de inicio
    // Por ejemplo, renderiza un texto que diga "Presiona Enter para empezar"
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    char menu_text[] = "Press Enter to Start";
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, menu_text, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    SDL_Rect text_rect = { WINDOW_WIDTH / 2 - textSurface->w / 2, WINDOW_HEIGHT / 2 - textSurface->h / 2, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &text_rect);
    SDL_DestroyTexture(textTexture);

    SDL_RenderPresent(renderer);
}

// Dentro de process_input()
void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
    case SDL_QUIT:
        game_is_running = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
            game_is_running = false;
        if (event.key.keysym.sym == SDLK_SPACE && !is_jumping) {
            paddle.vel_y = jump_force;  // Aplica la fuerza de salto
            is_jumping = true;

            // Disparar un nuevo proyectil horizontalmente
            if (shot_count < MAX_SHOTS) {
                shots[shot_count].x = paddle.x + paddle.width / 2;
                shots[shot_count].y = paddle.y + paddle.height / 2 - 5;
                shots[shot_count].width = 10;
                shots[shot_count].height = 10;
                shots[shot_count].vel_x = 500.0f;
                shot_count++;
            }
        }
        break;
    }
}

void process_menu_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        game_is_running = false;
    }
    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
        show_start_menu = false;  // Comienza el juego al presionar Enter
    }
}

void setup(void) {
    paddle.width = 50;
    paddle.height = 20;
    paddle.x = 50;
    paddle.y = WINDOW_HEIGHT - 40 - paddle.height;
    paddle.vel_y = 0;

    // Configuración del jefe
    boss.width = 100;
    boss.height = 50;
    boss.x = WINDOW_WIDTH - boss.width;  // Jefe al lado derecho de la pantalla
    boss.y = 100;
    boss.vel_x = -100.0f;

    // Crear obstáculos
    for (int i = 0; i < MAX_STRUCTURES; i++) {
        structures[i].width = 20;
        structures[i].height = 50;
        structures[i].x = WINDOW_WIDTH + i * 400;
        structures[i].y = WINDOW_HEIGHT - 40 - structures[i].height;
        structures[i].vel_x = -200.0f;
    }

    // Crear recolectables
    for (int i = 0; i < MAX_COLLECTIBLES; i++) {
        collectibles[i].width = 20;
        collectibles[i].height = 20;
        collectibles[i].x = (float)(rand() % (WINDOW_WIDTH - 20));
        collectibles[i].y = (float)(rand() % (WINDOW_HEIGHT / 2));
        collectibles[i].vel_y = 100.0f;
    }
}

bool check_collision(struct game_object* a, struct game_object* b) {
    if (a->x < b->x + b->width && a->x + a->width > b->x &&
        a->y < b->y + b->height && a->y + a->height > b->y) {
        return true;
    }
    return false;
}

void update(void) {
    int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
    if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
        SDL_Delay(time_to_wait);

    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0;
    last_frame_time = SDL_GetTicks();

    paddle.y += paddle.vel_y * delta_time;
    paddle.vel_y += gravity * delta_time;

    if (paddle.y + paddle.height >= WINDOW_HEIGHT - 40) {
        paddle.y = WINDOW_HEIGHT - 40 - paddle.height;
        paddle.vel_y = 0;
        is_jumping = false;
    }

    for (int i = 0; i < MAX_STRUCTURES; i++) {
        structures[i].x += structures[i].vel_x * delta_time;

        if (structures[i].x + structures[i].width < 0) {
            structures[i].x = WINDOW_WIDTH;
        }

        if (check_collision(&paddle, &structures[i])) {
            game_is_running = false;
            printf("¡Colisión detectada! Fin del juego.\n");
        }
    }

    if (boss_active) {
        boss.x += boss.vel_x * delta_time;

        if (boss.x <= 0 || boss.x + boss.width >= WINDOW_WIDTH) {
            boss.vel_x = -boss.vel_x;
        }

        for (int i = 0; i < shot_count; i++) {
            if (check_collision(&shots[i], &boss)) {
                boss_health--;
                if (boss_health <= 0) {
                    boss_active = false;
                    score += 100;  // Incrementa la puntuación al derrotar al jefe
                    printf("¡Jefe derrotado!\n");
                }

                // Mover los disparos restantes
                for (int j = i; j < shot_count - 1; j++) {
                    shots[j] = shots[j + 1];
                }
                shot_count--;
                i--;
            }
        }
    }

    for (int i = 0; i < MAX_COLLECTIBLES; i++) {
        collectibles[i].y += collectibles[i].vel_y * delta_time;

        if (collectibles[i].y > WINDOW_HEIGHT) {
            collectibles[i].x = (float)(rand() % (WINDOW_WIDTH - (int)collectibles[i].width));
            collectibles[i].y = -collectibles[i].height;
        }

        for (int j = 0; j < shot_count; j++) {
            if (check_collision(&shots[j], &collectibles[i])) {
                collectibles[i].x = (float)(rand() % (WINDOW_WIDTH - (int)collectibles[i].width));
                collectibles[i].y = -collectibles[i].height;

                // Incrementa la puntuación por cada recolectable destruido
                score += 10;

                // Mover los disparos restantes
                for (int k = j; k < shot_count - 1; k++) {
                    shots[k] = shots[k + 1];
                }
                shot_count--;
                j--;
            }
        }
    }

    for (int i = 0; i < shot_count; i++) {
        shots[i].x += shots[i].vel_x * delta_time;

        if (shots[i].x > WINDOW_WIDTH) {
            // Mover los disparos restantes
            for (int j = i; j < shot_count - 1; j++) {
                shots[j] = shots[j + 1];
            }
            shot_count--;
            i--;
        }
    }
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (show_start_menu) {
        render_start_menu();
    }
    else {
        SDL_Rect paddle_rect = {
            (int)paddle.x, (int)paddle.y,
            (int)paddle.width, (int)paddle.height
        };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &paddle_rect);

        for (int i = 0; i < MAX_STRUCTURES; i++) {
            SDL_Rect structure_rect = {
                (int)structures[i].x, (int)structures[i].y,
                (int)structures[i].width, (int)structures[i].height
            };
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &structure_rect);
        }

        for (int i = 0; i < shot_count; i++) {
            SDL_Rect shot_rect = {
                (int)shots[i].x, (int)shots[i].y,
                (int)shots[i].width, (int)shots[i].height
            };
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &shot_rect);
        }

        for (int i = 0; i < MAX_COLLECTIBLES; i++) {
            SDL_Rect collectible_rect = {
                (int)collectibles[i].x, (int)collectibles[i].y,
                (int)collectibles[i].width, (int)collectibles[i].height
            };
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &collectible_rect);
        }

        if (boss_active) {
            SDL_Rect boss_rect = {
                (int)boss.x, (int)boss.y,
                (int)boss.width, (int)boss.height
            };
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &boss_rect);
        }

        // Mostrar la puntuación
        char score_text[100];
        snprintf(score_text, sizeof(score_text), "Score: %d", score);
        SDL_Color textColor = { 255, 255, 255 };
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text, textColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);

        SDL_Rect text_rect = { 10, 10, textSurface->w, textSurface->h };
        SDL_RenderCopy(renderer, textTexture, NULL, &text_rect);
        SDL_DestroyTexture(textTexture);
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    window = SDL_CreateWindow("Mi Juego", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    font = TTF_OpenFont("C:/Users/USUARIO/OneDrive/Escritorio/sc-2420-eval-u1-Cristian171/GameClasic/GameCs/font.ttf", 24);

    if (!font) {
        printf("Error loading font: %s\n", TTF_GetError());
        return 1;
    }

    setup();

    game_is_running = true;
    while (game_is_running) {
        if (show_start_menu) {
            process_menu_input();
        }
        else {
            process_input();
            update();
        }
        render();
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();

    return 0;
}
