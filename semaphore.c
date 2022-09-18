#include <limits.h>
#include "semaphore.h"


/** If the communication is between the tasks only
  * you can replace disabling and enabling the interrupts instructions
  * with ; and if there are interrupts communicate with the tasks by using
  * the semaphore you have to use disabling and enabling interrupts instructions .
  */

#define DISABLE_INTERRUPTS        ;
#define ENABLE_INTERRUPTS         ;


Status_t initSemaphore(Semaphore_t * semaphore , uint32_t initialValue)
{
    Status_t status = FAILED ;

    DISABLE_INTERRUPTS ;
    if(initialValue == 0)
    {
        semaphore->state = UNAVAILABLE ;
        semaphore->counter = initialValue ;
        ENABLE_INTERRUPTS ;

        status = SUCCESS ;
    }
    else if ((initialValue > 0) && (initialValue <= ULONG_MAX))
    {
        semaphore->state = AVAILABLE ;
        semaphore->counter = initialValue ;
        ENABLE_INTERRUPTS ;

        status = SUCCESS ;
    }
    else
    {
        ENABLE_INTERRUPTS ;

        status = FAILED ;
    }

    return status ;

}

Status_t acquireSemaphore(Semaphore_t * semaphore)
{
    Status_t status = FAILED ;

    switch(semaphore->state)
    {
        case UNAVAILABLE :
        {
            status = FAILED ;

            break ;
        }
        case AVAILABLE :
        {
            DISABLE_INTERRUPTS ;
            if (semaphore->counter == 1)
            {
                semaphore->state = UNAVAILABLE ;
                semaphore->counter = 0;
                ENABLE_INTERRUPTS ;

                status = SUCCESS ;
            }
            else if (semaphore->counter > 1)
            {
                -- semaphore->counter ;
                ENABLE_INTERRUPTS ;

                status = SUCCESS ;
            }
            else
            {
                ENABLE_INTERRUPTS ;

                status = FAILED ;
            }
            break ;
        }
        default :
        {
            /*Should not be here !*/
            break ;
        }
    }

    return status ;
}

Status_t releaseSemaphore(Semaphore_t * semaphore)
{
    Status_t status = FAILED ;

    switch(semaphore->state)
    {
        case UNAVAILABLE :
        {
            DISABLE_INTERRUPTS ;
            if (semaphore->counter == 0)
            {
                semaphore->state = AVAILABLE ;
                semaphore->counter = 1;
                ENABLE_INTERRUPTS ;

                status = SUCCESS ;
            }
            else
            {
                ENABLE_INTERRUPTS ;

                status = FAILED ;
            }

            break ;
        }
        case AVAILABLE :
        {
            DISABLE_INTERRUPTS ;
            if ((semaphore->counter > 0) && (semaphore->counter < ULONG_MAX))
            {
                ++ semaphore->counter ;
                ENABLE_INTERRUPTS ;

                status = SUCCESS ;
            }
            else
            {
                ENABLE_INTERRUPTS ;

                status = FAILED ;
            }

            break ;
        }
        default :
        {
            /*Should not be here !*/
            break ;
        }
    }

    return status ;
}


State_t getSemaphoreState(Semaphore_t * semaphore)
{
    State_t  state  = UNAVAILABLE ;

    DISABLE_INTERRUPTS ;
    state = semaphore->state ;
    ENABLE_INTERRUPTS ;

    return state ;
}

uint32_t getSemaphoreCounter(Semaphore_t * semaphore)
{
    uint32_t counter  = 0;

    DISABLE_INTERRUPTS ;
    counter = semaphore->counter ;
    ENABLE_INTERRUPTS ;

    return counter ;
}
