#include "vfs.h"

namespace Vfs {

VirtualFileSystem::VirtualFileSystem(){
}

VirtualFileSystem::~VirtualFileSystem(){
}

int VirtualFileSystem::loadPackage(const std::string &path){
	return vfsPkgMan.loadPackage(path);
}

int VirtualFileSystem::unloadPackage(const std::string &path){
	return vfsPkgMan.unloadPackage(path);
}

bool VirtualFileSystem::containsFile(const std::string &fn){
	return vfsPkgMan.fileExists(fn);
}

bool VirtualFileSystem::isCurrent(const std::string &fn, const unsigned int size, const unsigned int lastModified){
	return vfsPkgMan.isCurrent(fn, size, lastModified);
}


VfsData * VirtualFileSystem::loadFile(const std::string &fn){
	return vfsPkgMan.loadFile(fn);
}

}