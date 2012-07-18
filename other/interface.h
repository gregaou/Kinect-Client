#ifndef INTERFACE_H
#define INTERFACE_H

#define interface                   class
#define implements                  public

#define beginInterface(name)        interface name				\
									{                           \
										public:                 \
											virtual ~name() {}

#define interfaceMethod(method)				virtual method = 0;

#define endInterface()              };

#endif
