#ifndef KEVENTHANDER_H
#define KEVENTHANDER_H

#include "../kObjects/kObject.h"

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

		bool operator!(void)
		{
			return !_handler;
		}

	protected:
		handlerType _handler;
};

#endif