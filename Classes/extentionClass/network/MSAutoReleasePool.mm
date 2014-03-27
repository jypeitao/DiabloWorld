#import <UIKit/UIKit.h>

#include "MSAutoReleasePool.h"



MSAutoReleasePool::MSAutoReleasePool(){
	pool = [[NSAutoreleasePool alloc] init];

}

MSAutoReleasePool::~MSAutoReleasePool(){
//	[pool drain];
	[(NSAutoreleasePool*)pool release];
}
