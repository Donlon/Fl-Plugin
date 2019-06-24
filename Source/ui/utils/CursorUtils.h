#pragma once

#include <JuceHeader.h>

namespace CursorUtils {
    Point<int> getCurrentCursorPos();

    void hideCursor();

    void hideCursorAndSavePos();

    void restoreCursor();

    void showCursor();

    void showCursor(int x, int y);

    void showCursor(Point<int> &pos);
}

