#pragma once

#include <memory>
#include "window.h"

namespace Core {
	class Application {
	public:
		Application();
		virtual ~Application();

		static Application& get() { return *_instance; }
		static Window& getWindow() { return Application::get().getWindowInternal(); }

		void run();
		void close();
	private:
		Window& getWindowInternal() { return *_window; }

		static Application* _instance;
		bool _running = true;
		std::unique_ptr<Window> _window;
	};
}
