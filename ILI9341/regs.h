
#ifndef HW_REGS_H_
#define HW_REGS_H_

#define CONCAT2X(X,Y)                   X##Y
#define CONCAT3X(X,Y,Z)                 X##Y##Z
#define CONCAT4X(W,X,Y,Z)               W##X##Y##Z

#define CONCAT2(X,Y)                    CONCAT2X(X,Y)
#define CONCAT3(X,Y,Z)                  CONCAT3X(X,Y,Z)
#define CONCAT4(W,X,Y,Z)                CONCAT4X(W,X,Y,Z)
#define _BV(bit)                        (1 << bit)


#endif /* HW_REGS_H_ */
