#ifndef UI_CONTROLS_H
#define UI_CONTROLS_H

namespace Cosmoverse {
    class UIControls {
    public:
        UIControls();
        float getTimeScale() const;
        void togglePause();
        bool isPaused() const;
    private:
        float timeScale;
        bool paused;
    };
}
#endif