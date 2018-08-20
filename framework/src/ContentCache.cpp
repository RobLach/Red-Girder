#include "stdafx.h"
#include "ContentCache.h"
#include "NixVfs.h"

NixTextureRef TextureCache::load(const std::string &name) const {
	return vfs->loadTexture(name);
}

NixFontRef FontCache::load(const std::string &name) const {
	return vfs->loadFont(name);
}

//SoundDataRef SoundDataCache::load(const std::string &name) const {
//	return vfs->loadSound(name);
//}
