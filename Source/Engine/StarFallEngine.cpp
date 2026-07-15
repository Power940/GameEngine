#include "StarFallEngine.h"

namespace STR_FALL
{
    STR_Engine g_engine;

    bool STR_Engine::Initialize(const char* windowName, const int WINDOW_WIDTH, const int WINDOW_HEIGHT)
    {
        m_renderer = Renderer();
        if (!m_renderer.Initialize(windowName, WINDOW_WIDTH, WINDOW_HEIGHT)) { return false; }
        m_input = Input();
        m_input.Initialize();
        m_time = Time();

        return true;
    }
    void STR_Engine::Shutdown()
    {
        m_renderer.ShutDown();
    }
    void STR_Engine::Update()
    {
        m_input.Update();
        m_time.Tick();
    }
};