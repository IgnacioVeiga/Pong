#include "Ball.h"
#include "GameConstants.h"
#include <cstdlib>
#include <ctime>

Ball::Ball(SDL_Renderer *renderer) : renderer(renderer), velX(BALL_SPEED), velY(BALL_SPEED)
{
    // Cargar imagen BMP directamente
    const char *imagePath = "assets/sprites/ball.bmp";
    SDL_Surface *tempSurface = SDL_LoadBMP(imagePath);
    if (!tempSurface)
    {
        SDL_Log("Unable to load BMP file: %s, SDL Error: %s", imagePath, SDL_GetError());
    }
    else
    {
        // Crear una textura a partir de la superficie
        texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface); // Liberar la superficie después de crear la textura
        if (!texture)
        {
            SDL_Log("Unable to create texture from %s, SDL Error: %s", imagePath, SDL_GetError());
        }
    }

    // Definir el rectángulo para el rendering de la textura
    rect = {
        SCREEN_WIDTH / 2 - BALL_SIZE / 2,  // X
        SCREEN_HEIGHT / 2 - BALL_SIZE / 2, // Y
        BALL_SIZE,                         // W
        BALL_SIZE                          // H
    };
}

Ball::~Ball()
{
    SDL_DestroyTexture(texture);
}

void Ball::move()
{
    rect.x += velX;
    rect.y += velY;
}

void Ball::reset(int x, int y)
{
    rect.x = x;
    rect.y = y;
    setInitialDirection();
}

void Ball::setInitialDirection()
{
    // Hacia izquierda o derecha (aleatorio)
    velX = (rand() % 2 == 0 ? -BALL_SPEED : BALL_SPEED);

    // La velocidad en el eje Y no es siempre la misma
    int factor = rand() % BALL_SPEED + 1;

    // Hacia arriba o abajo (aleatorio)
    velY = (rand() % 2 == 0 ? -factor : factor);
}

void Ball::render(SDL_Renderer *renderer)
{
    if (texture)
    {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
    else
    {
        // Dibujo de fallback si no se carga la textura
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanco
        SDL_RenderFillRect(renderer, &rect);
    }
}

const SDL_Rect &Ball::getRect() const
{
    return rect;
}