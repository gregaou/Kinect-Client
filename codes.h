#ifndef CODES_H
#define CODES_H

typedef enum ServerCode {ColorStream = 1,
                         SkeletonStream = 2,
                         /* ... */
                         QueryOK = 255
                        } ServerCode;

#endif // CODES_H
