#include "GraphicsManager.h"
#include "../Graphics/GraphicsConstants.h"
#include "../Graphics/Font.h"
#include <iostream>

int GraphicsManager::mWindowWidth = 0;
int GraphicsManager::mWindowHeight = 0;
int GraphicsManager::mScreenWidth = 0;
int GraphicsManager::mScreenHeight = 0;

uint32_t* GraphicsManager::mColorBuffer = nullptr;
SDL_Texture* GraphicsManager::mColorBufferTexture = nullptr;
SDL_Window* GraphicsManager::mWindow = nullptr;
SDL_Renderer* GraphicsManager::mRenderer = nullptr;
SDL_Rect GraphicsManager::mCamera;

Vec2 GraphicsManager::mScreenOffset = { 0.0f, 0.0f };
float GraphicsManager::mScreenZoom = 1.0f;

bool GraphicsManager::mHighlighted = false;
int GraphicsManager::mHighlightedOffset = 0;

bool GraphicsManager::OpenWindow()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing SDL" << std::endl;
        return false;
    }
    if (TTF_Init() != 0)
    {
        return false;
    }

    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);
    mWindowWidth = display_mode.w;
    mWindowHeight = display_mode.h;
    mWindowWidth = 16 * TILE_SIZE * TILE_SPRITE_SCALE;
    mWindowHeight = 9 * TILE_SIZE * TILE_SPRITE_SCALE;

    mWindow = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowWidth, mWindowHeight, SDL_WINDOW_BORDERLESS);
    if (!mWindow)
    {
        std::cerr << "Error creating SDL window" << std::endl;
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
    {
        std::cerr << "Error creating SDL renderer" << std::endl;
        return false;
    }

    //mColorBuffer = new uint32_t[mScreenWidth * mScreenHeight];
    //mColorBufferTexture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, mScreenWidth, mScreenHeight);

    // Initialize the camera view with the entire screen area
    mCamera.x = 0.0f;
    mCamera.y = 0.0f;
    mCamera.w = mWindowWidth;
    mCamera.h = mWindowHeight;

    return true;
}

void GraphicsManager::CloseWindow(void)
{
    delete[] mColorBuffer;
    SDL_DestroyTexture(mColorBufferTexture);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void GraphicsManager::PresentRender()
{
    SDL_RenderPresent(mRenderer);
}

void GraphicsManager::AdjustScreenOffset(const Vec2& offset)
{
    mScreenOffset.x += offset.x;
    mScreenOffset.y += offset.y;
}

void GraphicsManager::ResetScreenOffset()
{
    mScreenOffset = { 0.0f, 0.0f };
}

void GraphicsManager::ScrollZoom(const int scroll)
{
    mScreenZoom += static_cast<float>(scroll) * 0.25f;
}

bool GraphicsManager::CircleOffScreen(const int x, const int y, const float radius)
{
    return
        x + radius + mScreenOffset.x < 0 ||
        x - radius + mScreenOffset.x > mScreenWidth ||
        y + radius + mScreenOffset.y < 0 ||
        y - radius + mScreenOffset.y > mScreenHeight;

}

void GraphicsManager::ClearScreen(const uint32_t color)
{
    for (int i = 0; i < mScreenWidth * mScreenHeight; i++)
    {
        mColorBuffer[i] = color;
    }

    SDL_RenderClear(mRenderer);
}

void GraphicsManager::RenderFrame()
{
    SDL_UpdateTexture(mColorBufferTexture, nullptr, mColorBuffer, sizeof(uint32_t) * mScreenWidth);
    SDL_RenderCopy(mRenderer, mColorBufferTexture, nullptr, nullptr);
    SDL_RenderPresent(mRenderer);
}

void GraphicsManager::DrawPixel(const int x, const int y, const bool highlighted)
{
    if (highlighted) SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    else SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);

    SDL_Rect rect = { x, y, TEXT_SIZE, TEXT_SIZE };
    SDL_RenderFillRect(mRenderer, &rect);

    SDL_RenderDrawRect(mRenderer, &rect);
}

void GraphicsManager::DrawLine(const int x0, const int y0, const int x1, const int y1, const uint32_t color, const bool lockToScreen)
{
    float x = x0;
    float y = y0;
    int deltaX = x1 - x0;
    int deltaY = y1 - y0;

    int steps = abs(deltaX) > abs(deltaY) ? abs(deltaX) : abs(deltaY);

    float xIncrement = deltaX / (float)steps;
    float yIncrement = deltaY / (float)steps;

    for (int i = 0; i < steps; i++)
    {
        if (lockToScreen)
            DrawPixel(static_cast<int>(x), static_cast<int>(y), color);
        else
            DrawPixel(static_cast<int>(x + mScreenOffset.x), static_cast<int>(y + mScreenOffset.y), color);
        x += xIncrement;
        y += yIncrement;
    }
}

void GraphicsManager::DrawGrid(const uint32_t color)
{
    for (int y = 0; y < mScreenHeight; y++)
    {
        for (int x = 0; x < mScreenWidth; x++)
        {
            if (x % PIXELS_PER_METER == 0 || y % PIXELS_PER_METER == 0)
                DrawPixel(x, y, color);
        }
    }
}

void GraphicsManager::DrawRect(const int x, const int y, const int width, const int height, const uint32_t color)
{
    DrawPixel(x + width / 2, y + height / 2, color);

    for (int i = x; i < x + width; i++)
        mColorBuffer[i + y * mScreenWidth] = color;

    for (int i = y; i < y + height; i++)
        mColorBuffer[x + i * mScreenWidth] = color;

    for (int i = y; i < y + height + 1; i++)
        mColorBuffer[(x + width) + i * mScreenWidth] = color;

    for (int i = x; i < x + width + 1; i++)
        mColorBuffer[i + (y + height) * mScreenWidth] = color;
}

void GraphicsManager::DrawFillRect(const int x, const int y, const int width, const int height, const uint32_t color)
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
    SDL_Rect rect = { x, y, width, height };
    SDL_RenderFillRect(mRenderer, &rect);

    SDL_RenderDrawRect(mRenderer, &rect);
}

void GraphicsManager::DrawCircle(const int x, const int y, const int radius, const float angle, const uint32_t color, const bool lockToScreen)
{
    if (CircleOffScreen(x, y, radius)) return;

    int x0 = 0;
    int y0 = radius;
    int p0 = 3 - (2 * radius);

    DisplayBresenhamCircle(x, y, x0, y0, color, lockToScreen);

    while (y0 >= x0)
    {
        x0++;

        if (p0 > 0)
        {
            y0--;
            p0 += 4 * (x0 - y0) + 10;
        }
        else
        {
            p0 += 4 * x0 + 6;
        }

        DisplayBresenhamCircle(x, y, x0, y0, color, lockToScreen);
    }
}

void GraphicsManager::DrawFillCircle(const int x, const int y, const int radius, const uint32_t color)
{
    if (CircleOffScreen(x, y, radius)) return;
    int pRadius = radius;
    int topLeftX = x - pRadius;
    int topLeftY = y - pRadius;

    for (int i = topLeftY; i < topLeftY + pRadius * 2 + 1; i++)
    {
        for (int j = topLeftX; j < topLeftX + pRadius * 2 + 1; j++)
        {
            Vec2 point = { static_cast<float>(x - j), static_cast<float>(y - i) };

            if (point.MagnitudeSquared() < pRadius * pRadius)
                DrawPixel(j + mScreenOffset.x, i + mScreenOffset.y, color);
        }
    }
}

void GraphicsManager::DrawPolygon(const int x, const int y, const std::vector<Vec2>& vertices, const uint32_t color, const bool lockToScreen)
{
    Vec2 current = vertices[0];
    Vec2 previous = vertices[vertices.size() - 1];

    DrawLine(previous.x, previous.y, current.x, current.y, 0xFFFFFFFF, lockToScreen);

    for (int i = 1; i < vertices.size(); i++)
    {
        previous = current;
        current = vertices[i];
        DrawLine(previous.x, previous.y, current.x, current.y, color, lockToScreen);
    }
}

void GraphicsManager::DrawFillPolygon(const int x, const int y, const std::vector<Vec2>& vertices, const uint32_t color, const bool lockToScreen)
{

}

void GraphicsManager::DrawTexture(const int x, const int y, const int width, const int height, const float rotation, SDL_Texture* texture)
{
    SDL_Rect dstRect = { x - (width / 2), y - (height / 2), width, height };
    float rotationDeg = rotation * 57.2958;
    SDL_RenderCopyEx(mRenderer, texture, nullptr, &dstRect, rotationDeg, nullptr, SDL_FLIP_NONE);
}

void GraphicsManager::DrawChar(const int x, const int y, const char character, const bool highlight, const bool lockToScreen)
{
    for (int j = 0; j < Font::fontHeight; j++)
    {
        for (int k = 0; k < Font::fontWidth; k++)
        {
            if (character == ' ') continue;

            if (Font::fontMap[character][k + j * Font::fontWidth])
            {
                int yOffset = 0;
                if (character == '/' && highlight)
                {
                    mHighlighted = !mHighlighted;
                    mHighlightedOffset++;
                    continue;
                }
                if (character == 'g' || character == 'j' || character == 'p' || character == 'q' || character == 'y' || character == ',') yOffset = 2 * TEXT_SIZE;
                
                DrawPixel(x + k * TEXT_SIZE - mHighlightedOffset * TEXT_SIZE, y + yOffset + j * TEXT_SIZE, mHighlighted);
            }
        }
    }
}

void GraphicsManager::DrawString(const int x, const int y, const char* string, const bool highlight, const bool lockToScreen)
{
    int i = 0;
    int xPos = x;
    int yPos = y;
    while (string[i] != '\0')
    {
        DrawChar(xPos, yPos, string[i], highlight);
        i++;
        xPos += Font::fontWidth * TEXT_SIZE + Font::fontSpacing * TEXT_SIZE;
    }

    mHighlighted = false;
    mHighlightedOffset = 0;
}

void GraphicsManager::DrawSpriteRect(SDL_Texture* spriteSheet, SDL_Rect& srcRect, SDL_Rect& destRect)
{
    SDL_RenderCopy(mRenderer, spriteSheet, &srcRect, &destRect);
}

SDL_Rect GraphicsManager::DrawDialogueBox()
{
    SDL_Rect rect =
    {
        mWindowWidth / 2 - DIALOGUE_BOX_WIDTH / 2 - DIALOGUE_BOX_BORDER_SIZE,
        static_cast<int>(mWindowHeight * 0.75f - DIALOGUE_BOX_BORDER_SIZE),
        DIALOGUE_BOX_WIDTH + DIALOGUE_BOX_BORDER_SIZE * 2,
        DIALOGUE_BOX_HEIGHT + DIALOGUE_BOX_BORDER_SIZE * 2
    };
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderFillRect(mRenderer, &rect);

    rect =
    {
        mWindowWidth / 2 - DIALOGUE_BOX_WIDTH / 2,
        static_cast<int>(mWindowHeight * 0.75f),
        DIALOGUE_BOX_WIDTH,
        DIALOGUE_BOX_HEIGHT
    };
    SDL_SetRenderDrawColor(mRenderer, 232, 220, 202, 255);
    SDL_RenderFillRect(mRenderer, &rect);

    SDL_RenderDrawRect(mRenderer, &rect);

    return rect;
}

void GraphicsManager::DrawDialogue(const SDL_Rect& rect, const std::vector<std::string>& dialogue)
{
    int xOffset = 0;
    int yOffset = 0;

    for (int i = 0; i < dialogue.size(); i++)
    {
        DrawString(
            rect.x + TEXT_PADDING,
            rect.y + TEXT_PADDING + i * Font::fontHeight * TEXT_SIZE + i * TEXT_VERTICAL_PADDING * TEXT_SIZE,
            dialogue[i].c_str(),
            true);
    }
}

SDL_Rect GraphicsManager::DrawUIBox(const int x, const int y, const int width, const int height)
{
    SDL_Rect rect =
    {
        x - DIALOGUE_BOX_BORDER_SIZE,
        y - DIALOGUE_BOX_BORDER_SIZE,
        width + UI_BOX_BORDER_SIZE * 2,
        height + UI_BOX_BORDER_SIZE * 2
    };
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderFillRect(mRenderer, &rect);

    rect = { x, y, width, height };
    SDL_SetRenderDrawColor(mRenderer, 232, 220, 202, 255);
    SDL_RenderFillRect(mRenderer, &rect);

    SDL_RenderDrawRect(mRenderer, &rect);

    return rect;
}

void GraphicsManager::DrawUISelector(const int x, const int y, const int width, const int height)
{
    SDL_Rect rect = { x, y, width, height };
    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(mRenderer, &rect);
}

void GraphicsManager::DrawBattleBackground(SDL_Texture* texture)
{
    SDL_RenderCopy(mRenderer, texture, NULL, NULL);
}

void GraphicsManager::DisplayBresenhamCircle(const int xc, const int yc, const int x0, const int y0, const uint32_t color, const bool lockToScreen)
{
    if (lockToScreen)
    {
        DrawPixel(xc + x0, yc + y0, color);
        DrawPixel(xc - x0, yc + y0, color);
        DrawPixel(xc + x0, yc - y0, color);
        DrawPixel(xc - x0, yc - y0, color);
        DrawPixel(xc + y0, yc + x0, color);
        DrawPixel(xc - y0, yc + x0, color);
        DrawPixel(xc + y0, yc - x0, color);
        DrawPixel(xc - y0, yc - x0, color);
    }
    else
    {
        DrawPixel(xc + x0 + mScreenOffset.x, yc + y0 + mScreenOffset.y, color);
        DrawPixel(xc - x0 + mScreenOffset.x, yc + y0 + mScreenOffset.y, color);
        DrawPixel(xc + x0 + mScreenOffset.x, yc - y0 + mScreenOffset.y, color);
        DrawPixel(xc - x0 + mScreenOffset.x, yc - y0 + mScreenOffset.y, color);
        DrawPixel(xc + y0 + mScreenOffset.x, yc + x0 + mScreenOffset.y, color);
        DrawPixel(xc - y0 + mScreenOffset.x, yc + x0 + mScreenOffset.y, color);
        DrawPixel(xc + y0 + mScreenOffset.x, yc - x0 + mScreenOffset.y, color);
        DrawPixel(xc - y0 + mScreenOffset.x, yc - x0 + mScreenOffset.y, color);
    }
}