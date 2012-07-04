#ifndef KEVENTHANDER_H
#define KEVENTHANDER_H

#include "kObject.h"

template<typename T>
class kEventHandler
{
	typedef void (*handlerType)(KObject*, T);

	public:
		kEventHandler(handlerType handler = 0) :
			_handler(handler)
		{}

		void operator=(handlerType h)
		{
			_handler = h;
		}

		void operator()(KObject* sender, T arg)
		{
			if (_handler)
				_handler(sender, arg);
		}

	protected:
		handlerType _handler;
};

#endif
