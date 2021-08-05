#pragma once

#include <string>

namespace Core {

	struct WindowProperties {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(
			const std::string& title = "Game",
			unsigned int width = 1280,
			unsigned int height = 720
		) : Title(title), Width(width), Height(height) {}
	};

	class Window {
	public:
		virtual ~Window() {}
		virtual void update() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void setVSync(bool enabled) = 0;
		virtual bool vSyncEnabled() const = 0;

		virtual void* getGlfwWindow() const = 0;

		static Window* create(const WindowProperties& props = WindowProperties());
	};
}