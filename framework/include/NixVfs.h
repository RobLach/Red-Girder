#ifndef NIX_VFS_H
#define NIX_VFS_H

#pragma comment(lib, "vfs.lib")

#include "Vfs.h"

//#include "SoundData.h"
//using namespace ALG3D;

#include "Resource.h"

class NixVfs { //tolua_export
public:
	//tolua_begin
	NixVfs();
	~NixVfs();
	int loadPackage(const std::string &name);
	bool containsFile(const std::string &fn);

	NixTextureRef	loadTexture(const std::string &filename);	
	void reloadTexture(NixTextureRef &texture);

	NixFontRef loadFont(const std::string &filename);

	//SoundDataRef loadSound(const std::string &filename);
	//SoundDataRef loadStream(const std::string &filename);

	//tolua_end
private:
	//SoundDataRef loadWAV(const std::string &filename);
	//SoundDataRef loadOGG(const std::string &filename);

	void configureTexture(NixTextureRef &texture);

	VirtualFileSystem vfs;
}; //tolua_export

#endif