#include "OpenGLApp.h"
#include <glm/vec2.hpp>
#include <iostream>
#include <fstream>
#include "InputManager.h"

namespace glRenderer
{
	std::string GLApp::pathToExecutable;
	GLApp* GLApp::currentApp = nullptr;
	
	GLApp::GLApp(glm::uvec2 _windowSize, std::string _title, std::string _exepath, bool resizeable) : title(_title)
	{
		pathToExecutable = _exepath;
		// GLFW initialization
		if (!glfwInit())
		{
			std::cout << "Initialization of GLFW failed\n" << std::endl;
		}
	
		// OpenGL context initialization/configuration
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, resizeable ? GLFW_TRUE : GLFW_FALSE);
		
		// creating a window and an OpenGL context
		window_ = glfwCreateWindow(int(_windowSize.x), int(_windowSize.y), title.c_str(), NULL, NULL);
		assert(window_);

		glfwSetWindowPos(window_, 100, 100);
		glfwSetWindowUserPointer(window_, this);
		glfwSetInputMode(window_, GLFW_STICKY_KEYS, 1);
		glfwSetKeyCallback(window_, InputManager::keyCallback);

		// Make OpenGL context of the specified window current for the calling thread
		glfwMakeContextCurrent(window_);
		glfwSwapInterval(0);

		// Initialize GLEW (provides run-time mechanisms to determine the supported extensions for target platform)
		if (glewInit() != GLEW_OK) 
		{
			std::cout << "Failed to initialize GLEW\n" << std::endl;
		}

		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	}

	GLApp::~GLApp() 
	{
		if (window_)
		{
			glfwDestroyWindow(window_);
			window_ = 0;
		}
		glfwTerminate();
	}

	bool GLApp::run()
	{
		if (!init())
		{
			return false;
		}

		double t;
		double dt;
		const double FPSInterval = 0.5;

		// Render loop: procssing input and calling custom rendering
		while (!glfwWindowShouldClose(window_))
		{
			t = glfwGetTime();
			dt = t - previousTime;
			if (dt > 0.008)
			{
				glfwPollEvents();
				previousTime = t;
				if (t - previousFPSTime < FPSInterval)
				{
					frameTick++;
				}
				else {
					setTitle(std::to_string((double)frameTick / FPSInterval));
					frameTick = 0;
					previousFPSTime = t;
				}
				if(!this->update(dt))
				{
					return false;
				}
				if(!this->render())
				{
					return false;
				}
				glfwSwapBuffers(window_);
			}
		}
		// calling custom application cleaning
		return end();
	}

	void GLApp::stop()
	{
		glfwSetWindowShouldClose(window_, GL_TRUE);
	}

	glm::uvec2 GLApp::getFramebufferSize() const
	{
		glm::ivec2 sizes(0);
		glfwGetFramebufferSize(window_, &sizes.x, &sizes.y);
		return glm::uvec2(sizes);
	}

	glm::uvec2 GLApp::getWindowSize() const
	{
		glm::ivec2 sizes(0);
		glfwGetWindowSize(window_, &sizes.x, &sizes.y);
		return glm::uvec2(sizes);
	}

	bool GLApp::checkGlError(const char* _message)
	{
		// querying the value of the error flag
		int error = glGetError();

		if (error != GL_NO_ERROR)
		{
			std::string errStr;
			switch (error)
			{
			case GL_INVALID_ENUM:
				errStr = "GL_INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:
				errStr = "GL_INVALID_VALUE";
				break;
			case GL_INVALID_OPERATION:
				errStr = "GL_INVALID_OPERATION";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				errStr = "GL_INVALID_FRAMEBUFFER_OPERATION";
				break;
			case GL_OUT_OF_MEMORY:
				errStr = "GL_OUT_OF_MEMORY";
				break;
			default:
				errStr = "UNKNOWN";
				break;
			}
			std::cerr << "[" << _message << "] OpenGL Error(" << "): " << errStr << std::endl;
		}
		return error == GL_NO_ERROR;
	}

	std::string GLApp::getPathToExecutable()
	{
		return pathToExecutable;
	}

	void GLApp::setTitle(std::string _title)
	{
		glfwSetWindowTitle(window_, _title.c_str());
	}
}