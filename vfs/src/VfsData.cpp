#include <stdio.h>

#include "VfsData.h"

namespace Vfs {

VfsData::VfsData(const std::string &n, char *d, int s){
	// Note that VfsData only keeps the relative file name.
	name = n;

	// Beware, the destructor destroys *d!
	data = d;

	size = s;
}

/** Destructor deletes the data. Be careful.*/
VfsData::~VfsData(){
	if(data){
		delete [] data;
	}
}

}