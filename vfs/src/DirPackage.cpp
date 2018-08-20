#include "DirPackage.h"
#include "NativeFS.h"

#include <iostream>
#include <fstream>

namespace Vfs {

DirPackage::DirPackage(){
};

DirPackage::~DirPackage(){
	unloadPackage();
};

int DirPackage::loadPackage(const std::string &name){
	unloadPackage();
	if(!isNativeDirectory(name)) return 1;
	packageName = name;
	return 0;
};

int DirPackage::unloadPackage(){
	packageName.clear();
	return 0;
};

bool DirPackage::containsFile(const std::string &filename){
	if(!isValidPackage()) return false;
	std::string fullFilename = fullPathName(filename);
	return isNativeFile(fullFilename);
}

bool DirPackage::containsDirectory(const std::string &filename){
	if(!isValidPackage()) return false;
	std::string fullFilename = fullPathName(filename);
	return isNativeDirectory(fullFilename);
}

std::string DirPackage::fullPathName(const std::string &filename){
	if(packageName.length() == 0){
		return filename;
	}else{
		return packageName + "/" + filename;
	}
};

char * DirPackage::getFile(const std::string &filename, int size){
	char * data = new char[size+1];  // HACK (string termination.)

	/*
	std::string sdata;

	std::ifstream f(filename.c_str());
	f.read(data, size);

	/// @todo Eliminate copy.
	//memcpy(data, sdata.c_str(), size);

	f.close();
	*/

	
	FILE *f = fopen(filename.c_str(), "rb");
	size_t amt = fread(data, sizeof(char), size, f);
	fclose(f);
	

	data[size] = 0; // Tack on the null terminator.

	return data;
};

VfsData * DirPackage::loadFile(const std::string &filename){
	if(!isValidPackage()) return 0;

	std::string fullFilename = fullPathName(filename);
	if(!isNativeFile(fullFilename)) return 0;

	unsigned int size, lastModified;
	nativeStats(fullFilename, size, lastModified);

	// Looks good, let's grab it.
	char * data    = getFile(fullFilename, size);
	VfsData *vdata = new VfsData(filename, data, size);
	vdata->lastModified = lastModified;

	return vdata;
};

bool DirPackage::isCurrent(const std::string &fn, const unsigned int size, const unsigned int lastModified){
	std::string fullFilename = fullPathName(fn);
	if(!isNativeFile(fullFilename)) return false;

	unsigned int currentSize, currentLastModified;
	nativeStats(fullFilename, currentSize, currentLastModified);
	return size == currentSize && lastModified == currentLastModified;
}

}