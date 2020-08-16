#ifndef OpenGLApp_h
#define OpenGLApp_h

#include "GLIncludes.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <string>

namespace glRenderer // user-defined namespace (non-capitalized identifier)
{
	struct LightInfo
	{
		glm::vec3 ambientTerm;
		glm::vec3 diffuseTerm;
		glm::vec3 specularTerm;
	};

	class GLApp
	{
	public:
		static GLApp* currentApp;

	public:
		GLApp(glm::uvec2 _windowSize, std::string _title, std::string _exepath, bool resizeable = true);
		virtual ~GLApp();
		bool run();
		static std::string getPathToExecutable();

	protected:
		void stop();

		// virtual methods for initialization, rendering and termination
		virtual bool init() = 0;
		virtual bool update(double dt) = 0;
		virtual bool render() = 0;
		virtual bool end() = 0;

		// utility methods
		glm::uvec2 getFramebufferSize() const;
		glm::uvec2 getWindowSize() const;
		bool checkGlError(const char* _message);
		void setTitle(std::string _title);

		// create a handle for a combined window/context object
		GLFWwindow* window_;
		const std::string title;
		static std::string pathToExecutable;
		double previousTime = 0;
		double previousFPSTime = glfwGetTime();
		int frameTick = 0;
	};
}

#endif

