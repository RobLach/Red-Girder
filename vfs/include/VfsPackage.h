#ifndef VFS_PACKAGE_H
#define VFS_PACKAGE_H

#include <string>

#include "VfsData.h"

namespace Vfs {

/** An interface for VFS "packages."  A package can load files, and can also aquire 
information about spesific files.  Implementation details are hidden in the subclasses.*/
class VfsPackage {
public:
	virtual ~VfsPackage() {};

	/** Initalizes the package. */
	virtual int loadPackage(const std::string &packageName) = 0;

	/** Uninitalizes the package. */
	virtual int unloadPackage() = 0;

	/** Returns true, if the package contains the spesified file. */
	virtual bool containsFile(const std::string &filename) = 0;

	/** Returns true, if the package contains the spesified directory. */
	virtual bool containsDirectory(const std::string &filename) = 0;

	/** Loads the specified file. */
	virtual VfsData * loadFile(const std::string &filename) = 0;

	/** Checks if the file information differs from the given information. Used to determine if the file has changed. */
	virtual bool isCurrent(const std::string &fn, const unsigned int size, const unsigned int lastModified) = 0;

	virtual const std::string & getPackageName() { 
		return packageName;
	};

	virtual bool isValidPackage() { 
		return packageName.length() > 0;
	};

protected:
	std::string packageName;
};

}
#endif // VFS_PACKAGE_H