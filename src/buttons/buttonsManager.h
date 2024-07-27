#ifndef BUTTONSMANAGER_H
#define BUTTONSMANAGER_H

#include <functional>
#include <Bounce2.h>
#include <Arduino.h>

class ButtonsManager {
public:
    using ClickListener = std::function<void()>;

    ButtonsManager();

    void onLeftClick(const ClickListener& listener);
    void onMiddleClick(const ClickListener& listener);
    void onRightClick(const ClickListener& listener);

    void checkButtons();

private:
    static const int LEFT_PIN;
    static const int MIDDLE_PIN;
    static const int RIGHT_PIN;

    Bounce leftButton;
    Bounce middleButton;
    Bounce rightButton;

    ClickListener leftClickListener;
    ClickListener middleClickListener;
    ClickListener rightClickListener;

    void setupButton(Bounce& button, int pin);
};

#endif // BUTTONSMANAGER_H
