#include "windows-window.h"

namespace Core {
	static bool isGLFWInitialized = false;

	Window* Window::create(const WindowProperties& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props)
	{
		this->init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		shutdown();
	}

	void WindowsWindow::update()
	{
		glfwPollEvents();
		glfwSwapBuffers(this->_window);
	}

	void WindowsWindow::setVSync(bool enabled)
	{
		enabled ? glfwSwapInterval(1) : glfwSwapInterval(0);

		this->_data.VSync = enabled;
	}

	bool WindowsWindow::vSyncEnabled() const
	{
		return this->_data.VSync;
	}

	void WindowsWindow::init(const WindowProperties& props)
	{
		this->_data.Title = props.Title;
		this->_data.Width = props.Width;
		this->_data.Height = props.Height;

		if (!isGLFWInitialized) {
			int success = glfwInit();

			isGLFWInitialized = true;
		}

		this->_window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(this->_window);
		glfwSetWindowUserPointer(this->_window, &this->_data);

		glfwSetFramebufferSizeCallback(this->_window, [](GLFWwindow* window, int width, int height)
			{
				Renderer::updateViewport(width, height);
			}
		);

		this->setVSync(true);

		glfwSetInputMode(this->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(this->_window);
		glfwTerminate();
	}
}
