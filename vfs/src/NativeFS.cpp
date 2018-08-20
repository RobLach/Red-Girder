#include "NativeFS.h"

#include <sys/types.h>
#include <sys/stat.h>

namespace Vfs {

bool nativeFileExists(const std::string &filename){
	struct stat buf;
	int result = stat(filename.c_str(), &buf);
	return result == 0;
}

bool isNativeFile(const std::string &filename){
	struct stat buf;
	int result = stat(filename.c_str(), &buf);
	if(result != 0) return false;
	return (buf.st_mode & S_IFREG) != 0;
}

bool isNativeDirectory(const std::string &dir){
	// Special case hack.
	if(dir == ""){
		return true;
	}

	struct stat buf;
	int result = stat(dir.c_str(), &buf);

	// Does it exist?
	if(result != 0){
		return false;
	}
	
	// Is it a directory?
	if(buf.st_mode & S_IFDIR){
		return true;
	}else{
		return false;
	}
}

int nativeFileLength(const std::string &file){
	struct stat buf;
	int result = stat(file.c_str(), &buf);
	return buf.st_size;
}

void nativeStats(const std::string &file, unsigned int &size, unsigned int &lastModified){
	struct stat buf;
	int result = stat(file.c_str(), &buf);
	size = buf.st_size;	
	lastModified = (unsigned int)buf.st_mtime;
}

}