#include "StarFallEngine.h"

namespace STR_FALL
{
    int STR_Engine::Initialize(const char* windowName, const int WINDOW_WIDTH, const int WINDOW_HEIGHT)
    {
        m_renderer = Renderer();
        if (!m_renderer.Initialize(windowName, WINDOW_WIDTH, WINDOW_HEIGHT)) { return 1; }
        m_input = Input();
        if (!m_input.Initialize()) { return 2; }
        m_audio = Audio();
        if (!m_audio.Initialize()) { return 3; }
        m_time = Time();

        return 0;
    }
    void STR_Engine::Shutdown()
    {
        m_renderer.ShutDown();
        m_audio.ShutDown();
    }
    void STR_Engine::Update()
    {
        m_input.Update();
        m_audio.Update();
        m_time.Tick();
    }
};