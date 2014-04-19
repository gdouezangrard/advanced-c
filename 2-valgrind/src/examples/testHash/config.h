/****************************************************************************
 *
 *       config.h
 *
 *         This file contains all of the configuration dependent information.
 *
 ****************************************************************************/

#ifndef CONFIG_H
#define CONFIG_H

/* for Function Prototypes */
#if defined(__STDC__) || defined(c_plus_plus)
#define P(args) args
#else 
#define P(args) ()
/* endif defined(__STDC__) */
#endif 

#ifndef NULL
#define NULL 0
#endif 

#ifndef TRUE
#define TRUE 1
#endif 

#ifndef FALSE
#define FALSE 0
#endif 

typedef int boolean;

/* endif  CONFIG_H */
#endif 
