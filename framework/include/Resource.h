#ifndef NIX_RESOURCE_H
#define NIX_RESOURCE_H

/** \todo Refactor into seperate files. */


#include "GLG3D/GFont.h"
#include "GLG3D/Texture.h"
using namespace G3D;

#include "SmartPtr.h"

/** File information.  Used to tell if resources have changed on disk, and need to be reloaded. */
class FileInfo {
public:
	FileInfo(){};

	FileInfo(const std::string n, const unsigned int s, const unsigned int l){
		name = n;
		size = s;
		lastModified = l;
	};

	/** The file name.*/
	std::string name;

	/** The size of the file, in bytes.*/
	unsigned int size;

	/** The file's modification timestamp.*/
	unsigned int lastModified;
};

class Resource : public SmartPointerBase {
public:
	FileInfo	fileInfo;
};

typedef SmartPointerRef<class NixTexture> NixTextureRef;
//typedef boost::shared_ptr<class NixTexture> NixTextureRef;


/** An extended version of G3D's texture, with added file information. 
@todo Allow external reloading of textures? */
class NixTexture : public Resource {
public:
	~NixTexture(){
		std::cout << "NixTexture " << fileInfo.name.c_str() << " destroyed." << std::endl;		
	}

	TextureRef	texture;
};


/** An extended version of G3D's font, that can load from memory.*/
class GFontExt : public GFont {
protected:
	GFontExt(RenderDevice* renderDevice, const std::string &filename, BinaryInput &b);

public:
	static GFontRef fromMemory(RenderDevice *renderDevice, const std::string &filename, const uint8 *bytes, const int size);
};

typedef SmartPointerRef<class NixFont> NixFontRef;
//typedef boost::shared_ptr<class NixFont> NixFontRef;


class NixFont : public Resource {
public:
	GFontRef	font;
};

#endif