#include "stdafx.h"
#include "WindowManager.h"

WindowManager::WindowManager(){
	initalized = false;
	window = 0;
	renderDevice = 0;
}

WindowManager::~WindowManager(){
	cleanup();
}



void WindowManager::init(int width, int height, int samples, int fs, int sync){

	if(initalized) return;

	GWindowSettings settings;
	settings.width = width;
	settings.height = height;
	settings.fullScreen = fs == 0 ? false : true;
	settings.fsaaSamples = samples;

	// If 60 Hz update?
	settings.refreshRate = 60;

	/// @todo Determine when should the screen have an alpha channel.
	settings.rgbBits = 8;
	settings.alphaBits = 0;	// 0 or 8?
	settings.depthBits = 0;  // Autodetect.

	//settings.framed = false;

	settings.asychronous  = sync == 0 ? true : false;

	// Note the explicit creation of an SDL window.
	// Win32Window kinda sucks.

	window = new SDLWindow(settings);
	//window = Win32Window::create(settings);

	renderDevice = new RenderDevice();
	renderDevice->init(window);

	initalized = true;

	setCaption("GELF");
	disableInputCapture();
	showCursor();
}

void WindowManager::cleanup(){
	if(initalized){
		renderDevice->cleanup();
		delete renderDevice;
		renderDevice = 0;

		delete window;
		window = 0;
	}
	initalized = false;
}

void WindowManager::setCaption(const std::string &caption) {
	alwaysAssertM(initalized, "Attempted to use uninitalized window manager.");
	window->setCaption(caption);
}

void WindowManager::enableInputCapture() {
	alwaysAssertM(initalized, "Attempted to use uninitalized window manager.");
	window->setInputCapture(true);
}

void WindowManager::disableInputCapture() {
	alwaysAssertM(initalized, "Attempted to use uninitalized window manager.");
	window->setInputCapture(false);
}

void WindowManager::showCursor() {
	alwaysAssertM(initalized, "Attempted to use uninitalized window manager.");
	window->setMouseVisible(true);
}

void WindowManager::hideCursor() {
	alwaysAssertM(initalized, "Attempted to use uninitalized window manager.");
	window->setMouseVisible(false);
}


void WindowManager::takeScreenshot(const std::string &filename) const {
	GImage screenshot;
	renderDevice->screenshotPic(screenshot);
	BinaryOutput bo = BinaryOutput(filename, G3D_LITTLE_ENDIAN);
	screenshot.encode(GImage::Format::PNG, bo);
	bo.commit();
}