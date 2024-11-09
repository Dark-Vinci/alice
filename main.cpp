#include "ui.h";

int main() {
    auto app = new Terminal();
    app->start();
    delete app;
    return 0;
}
