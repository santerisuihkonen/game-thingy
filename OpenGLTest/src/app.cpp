#include "core/application.h"

int main(void)
{
    Core::Application* app = new Core::Application;

    app->run();

    delete app;

    return 0;
}
