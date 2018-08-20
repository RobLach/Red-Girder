#ifndef NIXREFERENCECOUNTEDPOINTER_H
#define NIXREFERENCECOUNTEDPOINTER_H

// NixReferenceCountedPointer ripped from G3D.  Modified to be somewhat comparabile with boost::shared_ptr
template <class T>
class NixReferenceCountedPointer {
private:

    T*           pointer;

public:

	typedef T element_type;

	inline T* get_pointer() const {
		return pointer;
	}

    inline T* getPointer() const {
        return pointer;
    }

private:

    void registerReference() { 
        pointer->ReferenceCountedObject_refCount += 1;
        //debugPrintf("  ++0x%x\n", pointer);
        //debugPrintf("  [0x%x] = %d\n", pointer, pointer->ReferenceCountedObject_refCount);
    }


    int deregisterReference() {
        if (pointer->ReferenceCountedObject_refCount > 0) {
            pointer->ReferenceCountedObject_refCount -= 1;
            //debugPrintf("  --0x%x\n", pointer);
            //debugPrintf("  [0x%x] = %d\n", pointer, pointer->ReferenceCountedObject_refCount);
        }

        return pointer->ReferenceCountedObject_refCount;
    }


    void zeroPointer() {
        if (pointer != NULL) {

            debugAssert(isValidHeapPointer(pointer));

            if (deregisterReference() <= 0) {
                // We held the last reference, so delete the object
                //debugPrintf("  delete 0x%x\n", pointer);
                delete pointer;
            }

            pointer = NULL;
        }
    }


    void setPointer(T* x) {
        if (x != pointer) {
            zeroPointer();

            if (x != NULL) {
                debugAssert(isValidHeapPointer(x));

		        pointer = x;
		        registerReference();
            }
        }
    }

public:      

    inline NixReferenceCountedPointer() : pointer(NULL) {}

    /**
      Allow compile time subtyping rule 
      RCP&lt;<I>T</I>&gt; &lt;: RCP&lt;<I>S</I>&gt; if <I>T</I> &lt;: <I>S</I>
     */
    template <class S>
    inline NixReferenceCountedPointer(const NixReferenceCountedPointer<S>& p) : pointer(NULL) {
        setPointer(p.getPointer());
    }

    // We need an explicit version of the copy constructor as well or 
    // the default copy constructor will be used.
    inline NixReferenceCountedPointer(const NixReferenceCountedPointer<T>& p) : pointer(NULL) {
        setPointer(p.pointer);
    }

    /** Allows construction from a raw pointer.  That object will thereafter be
        reference counted -- do not call delete on it. */
    inline NixReferenceCountedPointer(T* p) : pointer(NULL) { 
        setPointer(p); 
    }
    
    inline ~NixReferenceCountedPointer() {
        zeroPointer();
    }
  
    inline const NixReferenceCountedPointer<T>& reset(const NixReferenceCountedPointer<T>& p) {
        setPointer(p.pointer);
        return *this;
    }   


    inline NixReferenceCountedPointer<T>& reset(T* p) {
        setPointer(p);
        return *this;
    }

    inline const NixReferenceCountedPointer<T>& operator=(const NixReferenceCountedPointer<T>& p) {
        setPointer(p.pointer);
        return *this;
    }   


    inline NixReferenceCountedPointer<T>& operator=(T* p) {
        setPointer(p);
        return *this;
    }


    inline bool operator==(const NixReferenceCountedPointer<T>& y) const { 
        return (pointer == y.pointer); 
    }


    inline bool operator!=(const NixReferenceCountedPointer<T>& y) const { 
        return (pointer != y.pointer); 
    }


    inline T& operator*() const {
        return (*pointer);
    }


    inline T* operator->() const {
        return pointer;
    }


    inline bool isNull() const {
        return (pointer == NULL);
    }

    inline bool notNull() const {
        return (pointer != NULL);
    }

    /**
     Returns true if this is the last reference to an object.
     Useful for flushing memoization caches-- a cache that holds the last
     reference is unnecessarily keeping an object alive.
     */
    inline int isLastReference() const {
        return (pointer->ReferenceCountedObject_refCount == 1);
    }
};

#endif