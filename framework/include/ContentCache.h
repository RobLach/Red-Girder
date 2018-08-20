#ifndef CONTENTCACHE_H
#define CONTENTCACHE_H

#include "NixVfs.h"

template < class T > class ContentCache {
public:
	virtual T get(const std::string &name) {
		if(!cache.containsKey(name)){
			cache.set(name, load(name));
		}

		return cache.get(name);
	}

	virtual void clear() {
		cache.clear();
	}

	void setVFS(NixVfs * const v){
		vfs = v;
	}

protected:
	virtual T load(const std::string &name) const = 0;

	Table<std::string, T> cache;
	NixVfs *vfs;
};


class TextureCache : public ContentCache<NixTextureRef> {
public:
	NixTextureRef load(const std::string &name) const;
};

//class SoundDataCache : public ContentCache<SoundDataRef> {
//public:
//	SoundDataRef load(const std::string &name) const;
//};

class FontCache : public ContentCache<NixFontRef> {
public:
	NixFontRef load(const std::string &name) const;
};


#endif