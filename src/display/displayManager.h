#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

void blink();

void testdrawchar();

void renderDisplay();

void endRenderDisplay();

void initDisplay();

void invertButtonArea(int buttonIndex);

void drawSelectedIndicator(int y);

void setDescription(String text);

void resetDescription();

#endif