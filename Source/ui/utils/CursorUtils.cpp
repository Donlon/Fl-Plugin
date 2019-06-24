#include <Windows.h>

#include "CursorUtils.h"

namespace CursorUtils {
    Point<int> *lastMousePos = nullptr;
}

Point<int> CursorUtils::getCurrentCursorPos() {
    POINT pt;
    GetCursorPos(&pt);
    return Point<int>(pt.x, pt.y);
}

void CursorUtils::hideCursor() {
    ShowCursor(false);
}

void CursorUtils::hideCursorAndSavePos() {
    if (!lastMousePos) {
        lastMousePos = new Point<int>;
    }
    *lastMousePos = getCurrentCursorPos();
    hideCursor();
}

void CursorUtils::restoreCursor() {
    if (lastMousePos) {
        showCursor(*lastMousePos);
    } else {
        showCursor();
    }
}

void CursorUtils::showCursor() {
    ShowCursor(true);
}

void CursorUtils::showCursor(int x, int y) {
    showCursor();
    SetCursorPos(x, y);
}

void CursorUtils::showCursor(Point<int> &pos) {
    showCursor(pos.x, pos.y);
}
