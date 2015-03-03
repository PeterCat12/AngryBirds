#ifndef INPUT_H
#define INPUT_H

#include "AzulCore.h"
#include "GameObject.h"
#include"ScreenLine.h"

#define ORIGINAL_X	100
#define ORIGINAL_Y  215
#define STRING_SPACE 45



void KeyboardTest( GLFWwindow* window, IGameObject *pbird);
void KeyboardTest( GLFWwindow* window);
void MouseTest( GLFWwindow* window,  IGameObject *pbird, ScreenLine* line1, ScreenLine* line2);

#endif