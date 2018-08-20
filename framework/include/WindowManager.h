#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "G3DAll.h"

/** A class that deals with resolution issues, etc. */
class WindowManager { //tolua_export
public:
	//tolua_begin
	WindowManager();
	~WindowManager();
	void init(int width, int height, int samples=1, int fs=0, int sync=1);
	void cleanup();
	
	void setCaption(const std::string &caption);

	void enableInputCapture();
	void disableInputCapture();

	void showCursor();
	void hideCursor();

	/** Takes a screenshot and writes it to the file filename. Encodeds the file as a png, without reguard to the filename. */
	void takeScreenshot(const std::string &filename) const;

	//tolua_end
private:
	GWindow *window;
	bool initalized;
	RenderDevice *renderDevice;
}; //tolua_export

#endif