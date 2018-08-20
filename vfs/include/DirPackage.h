#ifndef DIR_PACKAGE_H
#define DIR_PACKAGE_H

#include "VfsData.h"
#include "VfsPackage.h"

namespace Vfs {

/** A VFS package that can load data from a traditional file system. */
class DirPackage : public VfsPackage {
public:
	DirPackage();
	virtual ~DirPackage();

	virtual int loadPackage(const std::string &name);
	virtual int unloadPackage();

	virtual bool containsFile(const std::string &filename);
	virtual bool containsDirectory(const std::string &filename);
	virtual VfsData * loadFile(const std::string &filename);

	virtual bool isCurrent(const std::string &fn, const unsigned int size, const unsigned int lastModified);

private:
	std::string fullPathName(const std::string &file);
	char * getFile(const std::string &filename, int size);
};

}

#endif //DIR_PACKAGE_H
