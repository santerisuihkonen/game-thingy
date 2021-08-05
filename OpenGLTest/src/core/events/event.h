#pragma once
#include <string>

namespace Core {

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		ApplicationEvent = 1 << 0,
		InputEvent = 1 << 1,
		KeyboardEvent = 1 << 2,
		MouseEvent = 1 << 3,
		MouseButtonEvent = 1 << 4
	};

	class Event {
		friend class EventDispatcher;

	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return this->getName(); }

		inline bool isInCategory(EventCategory category) {
			return getCategoryFlags() & category;
		}
	protected:
		bool _handled = false;
	};
}