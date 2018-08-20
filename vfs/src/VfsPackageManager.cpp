#include "VfsPackageManager.h"

#include "NativeFS.h"
#include "DirPackage.h"
#include "ZipPackage.h"

namespace Vfs {

VfsPackageManager::VfsPackageManager(){
	packages.clear();
}

VfsPackageManager::~VfsPackageManager(){
	std::vector <VfsPackage *>::iterator pkgit;
	for ( pkgit = packages.begin( ) ; pkgit != packages.end( ) ; pkgit++ ){
		(*pkgit)->unloadPackage();
		delete (*pkgit);
	}
	packages.clear();
}

int VfsPackageManager::numPackages(){
	return packages.size();
}

bool VfsPackageManager::packageIsLoaded(const std::string &name){
	std::vector <VfsPackage *>::iterator pkgit;
	for ( pkgit = packages.begin( ) ; pkgit != packages.end( ) ; pkgit++ ){
		if(name == (*pkgit)->getPackageName()){
			return true;
		}
	}
	return false;
}

int VfsPackageManager::loadPackage(const std::string &name){
	VfsPackage *pkg;

	// Don't load the same package twice.
	if(packageIsLoaded(name)) return 0;

	if(isNativeDirectory(name)){
		pkg = new DirPackage();
	}else if (isNativeFile(name)){
		pkg = new ZipPackage();
	}else{
		// No idea how to handle the requested package...
		return 1;
	}

	pkg->loadPackage(name);

	if(!pkg->isValidPackage()){
		//Somthing went wrong, so cleanup.
		delete pkg;
		return 1;
	}

	// Looks good, keep it.
	packages.push_back(pkg);
	return 0;
}

int VfsPackageManager::unloadPackage(const std::string &name){
	std::vector <VfsPackage *>::iterator pkgit;
	for ( pkgit = packages.begin( ) ; pkgit != packages.end( ) ; pkgit++ ){
		if( name == (*pkgit)->getPackageName() ){
			(*pkgit)->unloadPackage();
			delete (*pkgit);
			packages.erase(pkgit);
			return 0;
		}
	}
	return 1;
}

bool VfsPackageManager::fileExists(const std::string &filename){
	std::vector <VfsPackage *>::iterator pkgit;
	for ( pkgit = packages.begin( ) ; pkgit != packages.end( ) ; pkgit++ ){
		if( (*pkgit)->containsFile(filename) ){
			return true;
		}
	}
	return false;
}

bool VfsPackageManager::directoryExists(const std::string &filename){
	std::vector <VfsPackage *>::iterator pkgit;
	for ( pkgit = packages.begin( ) ; pkgit != packages.end( ) ; pkgit++ ){
		if( (*pkgit)->containsDirectory(filename) ){
			return true;
		}
	}
	return false;
}

VfsData * VfsPackageManager::loadFile(const std::string &filename){
	VfsData *vdata = 0;
	std::vector <VfsPackage *>::iterator pkgit;
	for ( pkgit = packages.begin( ) ; pkgit != packages.end( ) ; pkgit++ ){
		vdata = (*pkgit)->loadFile(filename);
		if(vdata != 0){
			return vdata;
		}
	}
	return 0;
}

bool VfsPackageManager::isCurrent(const std::string &fn, const unsigned int size, const unsigned int lastModified){
	std::vector <VfsPackage *>::iterator pkgit;
	for ( pkgit = packages.begin( ) ; pkgit != packages.end( ) ; pkgit++ ){
		if( (*pkgit)->containsFile(fn) ){
			return (*pkgit)->isCurrent(fn, size, lastModified);
		}
	}
	return false;
}

}