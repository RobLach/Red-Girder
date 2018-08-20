#include "ZipPackage.h"
#include "NativeFS.h"

#include <iostream>

namespace Vfs {

ZipPackage::ZipPackage(){
};

ZipPackage::~ZipPackage(){
	if(isValidPackage()) unloadPackage();
};

int ZipPackage::loadPackage(const std::string &name){
	if(isValidPackage()) unloadPackage();

	if(!isNativeFile(name)) return 1;

	zipSource = unzOpen(name.c_str());

	// Looks like it's not a valid zip file... doh!
	if(zipSource == NULL) return 1;

	/*
    uLong i;
    unz_global_info gi;
    int err;

    err = unzGetGlobalInfo (zipSource,&gi);
    if (err!=UNZ_OK) printf("error %d with zipfile in unzGetGlobalInfo \n",err);

	unzGoToFirstFile(zipSource);
    for (i=0;i<gi.number_entry;i++){
		char filename_inzip[256];
        unz_file_info file_info;
        err = unzGetCurrentFileInfo(zipSource,	&file_info,
										filename_inzip, sizeof(filename_inzip),
										NULL,0,NULL,0);
		std::cout << filename_inzip << std::endl;

		err = unzGoToNextFile(zipSource);
	}
	*/

	packageName = name;
	return 0;
};

int ZipPackage::unloadPackage(){
	packageName.clear();

	unzCloseCurrentFile(zipSource);
	int status = unzClose(zipSource);
	return status != UNZ_OK;
};

bool ZipPackage::containsFile(const std::string &filename){
	if(!isValidPackage()) return false;
	return unzLocateFile(zipSource, filename.c_str(), 0) == UNZ_OK;
}

bool ZipPackage::containsDirectory(const std::string &filename){
	if(!isValidPackage()) return false;
	// The following is NOT guarrentied to work for all zip files.  Arg.

    uLong i;
    unz_global_info gi;
    int err;
	char filename_inzip[256];
	unz_file_info file_info;

    err = unzGetGlobalInfo (zipSource,&gi);
    if (err!=UNZ_OK) return false;

	unzGoToFirstFile(zipSource);
    for (i=0;i<gi.number_entry;i++){
        err = unzGetCurrentFileInfo(zipSource,	&file_info,
										filename_inzip, sizeof(filename_inzip),
										NULL,0,NULL,0);

		int compare = filename.compare(0, filename.length(), filename_inzip, filename.length());

		if(compare == 0){
			// Make sure it's a directory, or it's a file in the directory.
			// Make sure it's not a normal file named the same thing as the directory we're looking for.
			if( strlen(filename_inzip) > filename.length() && 
				(filename_inzip[filename.length()] == '/' || 
				  filename_inzip[filename.length()] == '\\')  ){
				return true;
			}else{
				return false;
			}
		}

		// Are the file names in strict order? Can we exit earily if we get a "less"?

		err = unzGoToNextFile(zipSource);
	}

	return false;
}


VfsData * ZipPackage::loadFile(const std::string &filename){
	if(!isValidPackage()) return 0;
	if(!containsFile(filename)) return 0;

	int status;
	unz_file_info info;

	status = unzLocateFile(zipSource, filename.c_str(), 0);
	if(status != UNZ_OK) {
		std::cout << "Could not find file?" << std::endl;
		return 0;
	}

	status = unzGetCurrentFileInfo(zipSource, &info, 0, 0, 0, 0, 0, 0);
	if(status != UNZ_OK) {
		std::cout << "Could not get file info." << std::endl;
		return 0;
	}

	int size = info.uncompressed_size;

	status = unzOpenCurrentFile(zipSource);
	if(status != UNZ_OK) {
		std::cout << "Could not open file." << std::endl;
		return 0;
	}

	char * data    = new char[size];
	status = unzReadCurrentFile(zipSource, data, size);
	if(status < 0) {
		std::cout << "Error reading file. (" << status << ")" << std::endl;
		delete data;
		return 0;
	}

	status = unzCloseCurrentFile(zipSource);
	if(status != UNZ_OK) {
		std::cout << "Error closing file." << std::endl;
		delete data;
		return 0;
	}

	VfsData *vdata = new VfsData(filename, data, size);
	vdata->lastModified = info.dosDate;

	return vdata;
}

bool ZipPackage::isCurrent(const std::string &fn, const unsigned int size, const unsigned int lastModified){
	if(!isValidPackage()) return false;
	if(!containsFile(fn)) return false;

	int status;
	unz_file_info info;

	status = unzLocateFile(zipSource, fn.c_str(), 0);
	if(status != UNZ_OK) {
		std::cout << "Could not find file?" << std::endl;
		return false;
	}

	status = unzGetCurrentFileInfo(zipSource, &info, 0, 0, 0, 0, 0, 0);
	if(status != UNZ_OK) {
		std::cout << "Could not get file info." << std::endl;
		return false;
	}

	unsigned int currentSize = info.uncompressed_size;
	unsigned int currentLastModified = info.dosDate;

	return size == currentSize && lastModified == currentLastModified;
}

}