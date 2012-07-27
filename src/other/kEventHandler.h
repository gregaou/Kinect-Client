#ifndef KEVENTHANDER_H
#define KEVENTHANDER_H

/**
 * \file kEventHandler.h
 * \brief kinect event handler
 * \author Gaëtan Champarnaud
 *
 * Used to handle all the events emitted by the Kinect.
 */

#include "../kObjects/kObject.h"

template<typename T>
class KEventHandler
{
	typedef void (*handlerType)(KObject*, T);
	/**< Type of the callback function */

	public:
		/** \param handler The callback function */
		KEventHandler(handlerType handler = 0) :
			_handler(handler)
		{}

		/** \brief Assignment operator.
		 *  \param handler the New callback function */
		void operator=(handlerType h)
		{
			_handler = h;
		}

		/**
		 * \brief Call operator.
		 * \param sender The sender of the event
		 * \param arg The sent arguments
		 */
		void operator()(KObject* sender, T arg)
		{
			if (_handler)
				_handler(sender, arg);
		}

		/** \brief Logical negation operator.
		 *  \return whether the handler is null */
		bool operator!(void)
		{
			return !_handler;
		}

	protected:
		handlerType _handler;
};

#endif
