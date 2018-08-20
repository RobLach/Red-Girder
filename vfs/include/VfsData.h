#ifndef VFS_DATA_H
#define VFS_DATA_H

#include <string>

namespace Vfs {

class VfsData {
public:
	VfsData(const std::string &n, char *d, int s);
	~VfsData();

	std::string name;
	char *data;
	unsigned int size;
	unsigned int lastModified;
};

}

#endif // VFS_DATA_H