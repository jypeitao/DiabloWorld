#ifndef _MS_AUTO_RELEASE_POOL_H_
#define _MS_AUTO_RELEASE_POOL_H_


//class NSAutoreleasePool;

class MSAutoReleasePool{
private:
	void * pool;
public:
	MSAutoReleasePool();
	~MSAutoReleasePool();
};
#endif
