#ifndef NIX_SHAREDPTR_H
#define NIX_SHAREDPTR_H

//#define USE_BOOST_SMARTPTR

#ifdef USE_BOOST_SMARTPTR
	#include <boost/shared_ptr.hpp>
	//There must be no space at the end of the following line.
	#define SmartPointerRef boost::shared_ptr
	class SmartPointerBase {
	};
#else
	#include "NixReferenceCountedPointer.h"
	//There must be no space at the end of the following line.
	#define SmartPointerRef NixReferenceCountedPointer
	typedef ReferenceCountedObject SmartPointerBase;
#endif

#endif