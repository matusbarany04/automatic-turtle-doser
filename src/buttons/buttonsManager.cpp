#include "buttonsManager.h"

// Define pin constants
const int ButtonsManager::LEFT_PIN = 9;
const int ButtonsManager::MIDDLE_PIN = 8; // might be reset pin
const int ButtonsManager::RIGHT_PIN = 7;



ButtonsManager::ButtonsManager() {
    // Initialize Bounce objects with pin and debounce interval
    setupButton(leftButton, LEFT_PIN);
    setupButton(middleButton, MIDDLE_PIN);
    setupButton(rightButton, RIGHT_PIN);
}

void ButtonsManager::setupButton(Bounce& button, int pin) {
    button.attach(pin);
    pinMode(pin, INPUT_PULLUP);
    button.interval(25); // Debounce interval in milliseconds
}

void ButtonsManager::onLeftClick(const ClickListener& listener) {
    leftClickListener = listener;
}

void ButtonsManager::onMiddleClick(const ClickListener& listener) {
    middleClickListener = listener;
}

void ButtonsManager::onRightClick(const ClickListener& listener) {
    rightClickListener = listener;
}

void ButtonsManager::checkButtons() {
    leftButton.update();
    middleButton.update();
    rightButton.update();

    if (leftButton.fell()) {
        if (leftClickListener) {
            leftClickListener();
        }
    }

    if (middleButton.fell()) {
        if (middleClickListener) {
            middleClickListener();
        }
    }

    if (rightButton.fell()) {
        if (rightClickListener) {
            rightClickListener();
        }
    }
}
