#pragma once
#include "window.h"

#include "renderer/renderer.h"


namespace Core {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProperties& props);
		virtual ~WindowsWindow();

		void update() override;

		inline unsigned int getWidth() const override { return this->_data.Width; }
		inline unsigned int getHeight() const override { return this->_data.Height; }

		void setVSync(bool enabled) override;
		bool vSyncEnabled() const override;

		virtual void* getGlfwWindow() const { return this->_window; }
	private:
		virtual void init(const WindowProperties& props);
		virtual void shutdown();
	private:
		GLFWwindow* _window;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
		};

		WindowData _data;
	};
}