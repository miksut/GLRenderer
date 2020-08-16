#ifndef Example_Main_h
#define Example_Main_h

#include "OpenGLApp.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argv[0] != nullptr) 
	{
		// path to executable from command line argument
		std::string exePath(argv[0]);

		std::cout << exePath << std::endl;

		glRenderer::LightInfo light;
		light.ambientTerm.x = 10;

		std::cout << "The value of 'testVar' is: " << light.ambientTerm.x << std::endl;

		// creating the app
		//glRenderer::GLApp app(glm::uvec2(1600, 900), std::string("OpenGL Renderer"), exePath);



	}	
}

#endif 