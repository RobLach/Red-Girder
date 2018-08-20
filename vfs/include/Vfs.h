#ifndef VFS_H
#define VFS_H

#include "VfsData.h"
#include "VfsPackageManager.h"

using namespace Vfs;

/** A virtual filesystem that can load data from directories and zipfiles.*/
namespace Vfs {

/** A base class for that can load raw data from the package manager.
\todo Generate URLs for files, to assist external editors.
*/
class VirtualFileSystem {
public:
	VirtualFileSystem();
	~VirtualFileSystem();

	/** \todo Give more control over search order. */
	int loadPackage(const std::string &path);

	int unloadPackage(const std::string &path);

	bool containsFile(const std::string &fn);
	
	/** Returns a the data corrisponding to a given file name.  Do not forget to delete it, after it is used.*/
	VfsData * loadFile(const std::string &fn);

	bool isCurrent(const std::string &fn, const unsigned int size, const unsigned int lastModified);

protected:
	VfsPackageManager vfsPkgMan;
};

}

#endif //VFS_H
