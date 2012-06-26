#ifndef KACTION_H
#define KACTION_H

class KAction
{
	public:
		virtual ~KAction() {}
		static KAction* getAction(KServerListener* listener, KServerPaquet* paquet);
		virtual void exec(void) = 0;
};

#endif
