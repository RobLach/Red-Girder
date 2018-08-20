#ifndef VFS_PACKAGE_MANAGER_H
#define VFS_PACKAGE_MANAGER_H

#include <vector>
#include "VfsData.h"
#include "VfsPackage.h"

namespace Vfs {

class VfsPackageManager {
public:
	VfsPackageManager();
	~VfsPackageManager();

	int loadPackage(const std::string &filename);
	int unloadPackage(const std::string &filename);

	bool fileExists(const std::string &filename);
	bool directoryExists(const std::string &filename);

	VfsData * loadFile(const std::string &filename);

	bool isCurrent(const std::string &fn, const unsigned int size, const unsigned int lastModified);


	int numPackages();

private:
	bool packageIsLoaded(const std::string &name);

	std::vector <VfsPackage *> packages;
};

}

#endif // VFS_PACKAGE_MANAGER_H

