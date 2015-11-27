#ifndef UTIL_H_
#define UTIL_H_

#include <sys/time.h>
#include "Lock.h"

class CRefObject
{
public:
	CRefObject();
	virtual ~CRefObject();

	void SetLock(CLock* lock) { m_lock = lock; }
	void AddRef();
    
	void ReleaseRef();
private:
	int				m_refCount;
	CLock*	m_lock;
};

uint64_t get_tick(int a=0);

#endif
