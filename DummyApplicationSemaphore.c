#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "semaphore.h"

/*Dummy example .*/

#define MASSAGE_LENGTH        (50)
#define MASSAGES_NUMBER       (3)

Semaphore_t semaphore ;

char massage[MASSAGE_LENGTH] ;

char PrintedMassages[MASSAGES_NUMBER][MASSAGE_LENGTH] = {"Hello World !\n" ,
                                                         "Hi Semaphore !\n" ,
                                                         "Bye Semaphore !\n"} ;

void WaitTask(void)
{

    if(acquireSemaphore(&semaphore) == SUCCESS)
    {
        printf(massage);
    }
    else
    {
        ;
    }
}

void SignalTask(void)
{
    static uint8_t currentIndex = 0;
    static uint8_t currentMassage = 0;


    if(PrintedMassages[currentMassage][currentIndex] == '\0' )
    {
        massage[currentIndex] = '\0' ;

        currentIndex = 0;

        if (currentMassage == MASSAGES_NUMBER - 1 )
        {
            currentMassage = 0 ;
        }
        else
        {
            ++ currentMassage ;
        }



        releaseSemaphore(&semaphore) ;

    }
    else
    {
        massage[currentIndex] = PrintedMassages[currentMassage][currentIndex] ;
        ++ currentIndex ;
    }

}

int main(void)
{
    initSemaphore(&semaphore , 0);

    while(1)
    {
        WaitTask() ;
        SignalTask() ;
    }

    return 0;
}
