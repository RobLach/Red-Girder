#ifndef NATIVE_FS
#define NATIVE_FS

#include <string>

namespace Vfs {

bool nativeFileExists(const std::string &filename);
bool isNativeFile(const std::string &filename);
bool isNativeDirectory(const std::string &dir);
int nativeFileLength(const std::string &file);
void nativeStats(const std::string &file, unsigned int &size, unsigned int &lastModified);

}

#endif NATIVE_FS