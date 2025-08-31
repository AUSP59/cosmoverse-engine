#include "UIControls.h"

using namespace Cosmoverse;

UIControls::UIControls() : timeScale(1.0f), paused(false) {}

float UIControls::getTimeScale() const {
    return paused ? 0.0f : timeScale;
}

void UIControls::togglePause() {
    paused = !paused;
}

bool UIControls::isPaused() const {
    return paused;
}