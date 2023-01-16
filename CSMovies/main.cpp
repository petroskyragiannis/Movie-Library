#pragma once
#include "config.h"
#include "graphics.h"
#include "browser.h"

void update(float ms) {
    Browser* app = (Browser*)graphics::getUserData();
    app->update();
}

void draw() {
    Browser* app = (Browser*)graphics::getUserData();
    app->draw();
}

int main() {
    Browser app;

    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CSMovies");
    //graphics::setFullScreen(true);
    graphics::setUserData(&app);
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);
    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
    
    app.init();

    graphics::startMessageLoop();
    //graphics::destroyWindow();

    return 0;
}