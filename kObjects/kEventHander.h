#ifndef KEVENTHANDER_H
#define KEVENTHANDER_H

template<typename T>
class kEventHandler
{
	typedef void (*handlerType)(T);

	public:
		kEventHandler(handlerType handler = 0) :
			_handler(handler)
		{}

		void operator=(handlerType h)
		{
			_handler = h;
		}

		void operator()(T arg)
		{
			if (_handler)
				_handler(arg);
		}

	protected:
		handlerType _handler;
};

#endif
