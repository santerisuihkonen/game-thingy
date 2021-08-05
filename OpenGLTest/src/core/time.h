#pragma once

#include <GLFW/glfw3.h>

namespace Core
{
    class TimeManager {
    private:
        float _deltaTime;
        float _lastFrame;

        inline void internalUpdate() {
            float currentFrame = glfwGetTime();
            _deltaTime = currentFrame - _lastFrame;
            _lastFrame = currentFrame;
        }

        TimeManager() : _deltaTime(0.0f), _lastFrame(0.0f) {}
    public:
        TimeManager(const TimeManager&) = delete;

        static TimeManager& getInstance() {
            static TimeManager timeManager;
            return timeManager;
        }

        /// <summary>
        /// Call in the game loop.
        /// Updates delta time
        /// </summary>
        inline static void update() {
            getInstance().internalUpdate();
        }

        inline static float getDeltaTime() { return getInstance()._deltaTime; }

        inline static float getTime() { return glfwGetTime(); }
    };
}
