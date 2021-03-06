#ifndef __BASE_SIGNLETON_H
#define __BASE_SIGNLETON_H

#include <stdlib.h>
#include "base_os.h"

template<class T>
class CSingleton
{
public:
	static T* instance()
	{
#ifndef WIN32
		pthread_once(&ponce_, &CSingleton::init);
#else
		if(obj_ == NULL)		/*WINDOWS下不支持多线程单例*/
			obj_ = new T();
#endif

		return obj_;
	};

	static void destroy()
	{
		if(obj_ != NULL)
		{
			delete obj_;
			obj_ = NULL;
		}
	};

protected:
	CSingleton()
	{
	};

	virtual ~CSingleton()
	{
	};

protected:
#ifndef WIN32
	static pthread_once_t ponce_;
#endif

	static T*	obj_;

private:
	CSingleton(const CSingleton&)
	{
	};

	CSingleton& operator=(const CSingleton&)
	{
	};

	static void init()
	{
		obj_ = new T();
	};
};

#ifndef WIN32
template <class T> pthread_once_t CSingleton<T>::ponce_ = PTHREAD_ONCE_INIT;
#endif

template <class T> T* CSingleton<T>::obj_ = NULL;

#endif

