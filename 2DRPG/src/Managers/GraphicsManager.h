#pragma once

#include "../Utils/Vec2.h"

#include <SDL.h>
#include <stdint.h>
#include <vector>
#include <string>

class GraphicsManager
{
public:
    static bool OpenWindow();
    static void CloseWindow();

    inline static int WindowWidth() { return mWindowWidth; }
    inline static int WindowHeight() { return mWindowHeight; }
    inline static int ScreenWidth() { return mScreenWidth; }
    inline static int ScreenHeight() { return mScreenHeight; }

    static void AdjustScreenOffset(const Vec2& offset);
    static void ResetScreenOffset();

    static void ScrollZoom(const int& scroll);

    static bool CircleOffScreen(const int& x, const int& y, const float& radius);

    static void ClearScreen(const uint32_t& color);
    static void RenderFrame();

    static void DrawPixel(const int& x, const int& y, const uint32_t& color);
    static void DrawLine(const int& x0, const int& y0, const int& x1, const int& y1, const uint32_t& color, const bool& lockToScreen);
    static void DrawGrid(const uint32_t& color);
    static void DrawRect(const int& x, const int& y, const int& width, const int& height, const uint32_t& color);
    static void DrawFillRect(const int& x, const int& y, const int& width, const int& height, const uint32_t& color);
    static void DrawCircle(const int& x, const int& y, const int& radius, const float& angle, const uint32_t& color, const bool& lockToScreen);
    static void DrawFillCircle(const int& x, const int& y, const int& radius, const uint32_t& color);
    static void DrawPolygon(const int& x, const int& y, const std::vector<Vec2>& vertices, const uint32_t& color, const bool& lockToScreen);
    static void DrawFillPolygon(const int& x, const int& y, const std::vector<Vec2>& vertices, const uint32_t& color, const bool& lockToScreen);
    static void DrawTexture(const int& x, const int& y, const int& width, const int& height, const float& rotation, SDL_Texture* texture);

    static void DrawChar(const int& x, const int& y, const char& character, const uint32_t& color, const bool& lockToScreen);
    static void DrawString(const int& x, const int& y, const char* string, const uint32_t& color, const bool& lockToScreen);

    static void DisplayBresenhamCircle(const int& xc, const int& yc, const int& x0, const int& y0, const uint32_t& color, const bool& lockToScreen);

private:
    static int mWindowWidth;
    static int mWindowHeight;
    static int mScreenWidth;
    static int mScreenHeight;

    static uint32_t* mColorBuffer;
    static SDL_Texture* mColorBufferTexture;
    static SDL_Window* mWindow;
    static SDL_Renderer* mRenderer;

    static Vec2 mScreenOffset;
    static float mScreenZoom;
};