#ifndef AZULCORE_H
#define AZULCORE_H

#include "AzulHeader.h"

struct GLFWwindow;
#define WindowViewWidth 800
#define WindowViewHeight 600
class AzulCore : public Engine
{

public:

	AzulCore();

	void Initialize();
	void LoadContent();
	void Update();
	void Draw();
	void UnLoadContent();

	static Engine *getEngine();
	
private:
	void SetupRC();
	void ShutdownRC(GLFWwindow* window);

	static AzulCore *privInstance();

	GLFWwindow * window;
	bool joystickActive;
};


GLFWwindow* createGraphicsWindow( const char* windowName, const int Width,const int Height );


#endif 