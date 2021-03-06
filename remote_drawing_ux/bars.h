#ifndef BARS_H
#define BARS_H

#define FONT_HEIGHT 16
#define FONT_WIDTH 8
#define STATUS_BAR_SIZE FONT_HEIGHT

#define NUMBER_OF_BUTTONS (NUMBER_OF_COLORS + 1)
#define TOOLBAR_HEIGHT (DISPLAY_HEIGHT - STATUS_BAR_SIZE)
#define BUTTON_SIZE (TOOLBAR_HEIGHT / (NUMBER_OF_BUTTONS / 2))
#define TOOLBAR_WIDTH (BUTTON_SIZE * 2)
#define BUTTON_MARGIN 4

#define DRAWABLE_WIDTH (DISPLAY_WIDTH - TOOLBAR_WIDTH - LINE_WIDTH)
#define DRAWABLE_HEIGHT (DISPLAY_HEIGHT - STATUS_BAR_SIZE - LINE_WIDTH)

extern byte selectedColor;

// Print a message in the status bar
void printStatus(const char* msg);

// Like printStatus() but takes printf()-like arguments
void printStatusFormat(const char *format, ...);

void initToolbar();

void renderToolbar();

bool handleToolbarClick(int x, int y);

#endif
