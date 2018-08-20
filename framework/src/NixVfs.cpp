#include "stdafx.h"
#include "NixVfs.h"

//#include "StreamedSoundData.h"

NixVfs::NixVfs(){
}

NixVfs::~NixVfs(){
}

int NixVfs::loadPackage(const std::string &name){
	return vfs.loadPackage(name);
}

bool NixVfs::containsFile(const std::string &name){
	return vfs.containsFile(name);
}

void NixVfs::configureTexture(NixTextureRef &texture){
	VfsData *data = vfs.loadFile(texture->fileInfo.name);

	GImage image = GImage((unsigned char *)(data->data), data->size); // Decode the image.

	// Make the texture.
	texture->texture = 0;

	const TextureFormat * desiredFormat;

	// Should the texture be compressed?
	if(false){
		if(image.channels == 3){
			desiredFormat = TextureFormat::RGB_DXT1;
		}else if(image.channels == 4){
			desiredFormat = TextureFormat::RGBA_DXT5;
		}else{
			desiredFormat = TextureFormat::L8;
		}
	}else{
		desiredFormat = TextureFormat::AUTO;
	}

	texture->texture = Texture::fromGImage(texture->fileInfo.name, image, 
						desiredFormat, Texture::WrapMode::CLAMP);  // Duplicated filenames?

	texture->fileInfo.size = data->size;
	texture->fileInfo.lastModified = data->lastModified;

	delete data;
}


NixTextureRef NixVfs::loadTexture(const std::string &filename){
	NixTextureRef nt;

	if(containsFile(filename)){
		nt.reset(new NixTexture());
		nt->fileInfo.name = filename;
		configureTexture(nt);
	} else {
		std::cout << "Cannot find texture: " << filename << std::endl;
	}

	return nt;
}

void NixVfs::reloadTexture(NixTextureRef &texture){
	if(vfs.isCurrent(	texture->fileInfo.name, 
						texture->fileInfo.size, 
						texture->fileInfo.lastModified)) return;

	std::cout << "Reloading " << texture->fileInfo.name 
			<< " (" << texture->fileInfo.size << ", " << texture->fileInfo.lastModified << ")" << std::endl;

	configureTexture(texture);
}

NixFontRef NixVfs::loadFont(const std::string &filename){
	if(!containsFile(filename)) {
		std::cout << "Cannot find font: " << filename << std::endl;
		throw("Tried to load non-existant file.");
	}

	VfsData *data = vfs.loadFile(filename);
	// HACK: lastRenderDevice created.
	NixFontRef f(new NixFont());
	f->fileInfo.name = filename;
	f->font = GFontExt::fromMemory(RenderDevice::lastRenderDeviceCreated, filename, (unsigned char *)(data->data), data->size);
	delete data;
	return f;
}


/*
SoundDataRef NixVfs::loadSound(const std::string &filename){
	if(!containsFile(filename)) throw("Tried to load non-existant file.");


	if(filename.length() < 5) throw("Filename too short to have extention.  Cannot determine sound type.");
	std::string ext = toLower(filename.substr(filename.length()-3));

	if(ext.compare("wav") == 0){
		return loadWAV(filename);
	}else if(ext.compare("ogg") == 0){
		return loadOGG(filename);
	}else{
		throw("Unknown sound format.");
	}
}

SoundDataRef NixVfs::loadWAV(const std::string &filename){
	if(!containsFile(filename)) throw("Tried to load non-existant file.");

	VfsData *data = vfs.loadFile(filename);
	SoundDataRef s(SoundData::fromMemory((char *)(data->data), data->size));
	delete data;
	return s;
}


SoundDataRef NixVfs::loadOGG(const std::string &filename){
	if(!containsFile(filename)) throw("Tried to load non-existant file.");

	VfsData *data = vfs.loadFile(filename);
	SoundDataRef s(SoundData::loadOGG((char *)(data->data), data->size));
	delete data;
	return s;
}

SoundDataRef NixVfs::loadStream(const std::string &filename){
	if(!containsFile(filename)) throw("Tried to load non-existant file.");

	VfsData *data = vfs.loadFile(filename);
	SoundDataRef s(new StreamedSoundData((char *)(data->data), data->size));
	data->data = 0; /// @todo Do somthing more graceful that steal the data pointer.
	delete data;
	return s;
}
*/