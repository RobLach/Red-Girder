#ifndef ZIP_PACKAGE_H
#define ZIP_PACKAGE_H

#pragma comment(lib, "zdll.lib")

#include "VfsData.h"
#include "VfsPackage.h"

#include "unzip.h"

namespace Vfs {

/** A VFS package that can load data out of zipfiles. 
\todo Find an alternitive to minizip. */
class ZipPackage : public VfsPackage {
public:
	ZipPackage();
	virtual ~ZipPackage();

	virtual int loadPackage(const std::string &name);
	virtual int unloadPackage();

	virtual bool containsFile(const std::string &filename);
	virtual bool containsDirectory(const std::string &filename);
	virtual VfsData * loadFile(const std::string &filename);

	virtual bool isCurrent(const std::string &fn, const unsigned int size, const unsigned int lastModified);

protected:
	unzFile zipSource;
};

}

#endif //ZIP_PACKAGE_H
