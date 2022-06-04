#include <irrlicht.h>
#include "driverChoice.h"
#include "exampleHelper.h"
#include <GLFW/glfw3.h>

using namespace irr;

void log(int errCode, const char* errMsg)
{
    printf("glfwErr>> #%d: %s\n", errCode, errMsg);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // glViewport(0, 0, width, height); // Seems no effect ? Tested in GL03
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        printf(">> GLFW_KEY: space\n");
    else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        printf(">> GLFW_KEY: F\n");
}

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwSetErrorCallback(log);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(600, 400, "glfwWindow", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // end of glfw-window-init

    video::E_DRIVER_TYPE driverType = video::EDT_OPENGL;

	IrrlichtDevice *device = createDevice(driverType, core::dimension2d<u32>(512, 384));

	device->setWindowCaption(L"Irrlicht Engine - 2D Graphics Demo");

	video::IVideoDriver* driver = device->getVideoDriver();

	const io::path mediaPath = getExampleMediaPath();

	video::ITexture* images = driver->getTexture(mediaPath + "2ddemo.png");
	driver->makeColorKeyTexture(images, core::position2d<s32>(0,0));

	core::rect<s32> imp1(349,15,385,78);
	core::rect<s32> imp2(387,15,423,78);

	while(device->run() && driver)
	{
        processInput(window); // glfw

		if (device->isWindowActive())
		{
			u32 time = device->getTimer()->getTime();

			driver->beginScene(video::ECBF_COLOR | video::ECBF_DEPTH, video::SColor(255,120,102,136));

			// draw fire & dragons background world
			driver->draw2DImage(images, core::position2d<s32>(50,50),
				core::rect<s32>(0,0,342,224), 0,
				video::SColor(255,255,255,255), true);

			// draw flying imp
			driver->draw2DImage(images, core::position2d<s32>(164,125),
				(time/500 % 2) ? imp1 : imp2, 0,
				video::SColor(255,255,255,255), true);

			driver->endScene();
		}

        glfwSwapBuffers(window);
        glfwPollEvents();
	}

	device->drop();

	return 0;
}
