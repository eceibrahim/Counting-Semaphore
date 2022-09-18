#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <stdint.h>


typedef enum
{
    AVAILABLE  ,
    UNAVAILABLE
}State_t ;

typedef enum
{
    SUCCESS ,
    FAILED
}Status_t ;

typedef struct
{
    uint32_t counter ;
    State_t   state ;
}Semaphore_t ;



Status_t initSemaphore(Semaphore_t * semaphore , uint32_t initialValue) ;

Status_t  acquireSemaphore(Semaphore_t * semaphore);

Status_t releaseSemaphore(Semaphore_t * semaphore) ;

State_t getSemaphoreState(Semaphore_t * semaphore) ;

uint32_t getSemaphoreCounter(Semaphore_t * semaphore);

#endif /*__SEMAPHORE_H__*/
