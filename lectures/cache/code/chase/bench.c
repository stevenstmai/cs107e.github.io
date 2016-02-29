/*
** Pointer chasing
** 
** Based on code by Paul Drongowski 
** http://sandsoftwaresound.net/raspberry-pi/raspberry-pi-gen-1/memory-hierarchy/
*/
#include <stdio.h>
#include "rand.h"
#include "uart.h"
#include "timer.h"
#include "armtimer.h"
#include "mmu.h"
#include "system.h"
#include "measure.h"

extern void *malloc(size_t n);

//
// Default values for the pointer array and the cache line size
//
#define N                  1
#define LINES              (N*256)
#define POINTER_SIZE       (sizeof(void*))
#define LINE_SIZE          32
#define POINTERS_PER_LINE  (LINE_SIZE / POINTER_SIZE)
 
typedef struct _CacheLine {
    struct _CacheLine* ptrCacheLine[POINTERS_PER_LINE] ;
} CacheLine ;
 
//
// The program allocates an array of CacheLine structures. The number
// of elements (cache lines) is determined by the variable N.
// The array is initialized such that it forms a linked list of elements.
// Elements in the upper half of the array point to elements in the
// lower half, and vice versa. Thus, access will ping-pong between
// the upper and lower halves when the linked list is walked (pointers
// are chased.)
//
CacheLine* array = NULL ;
 
//
// Allocate and initialize the test array
//
void initialize_array(void)
{
  int steps ;   // Number of initialization setps
  int top ;     // Index of top cache line
  int bottom ;  // Index of bottom cache line
  int i ;       // Array index counter
  int j ;       // Pointer index counter
 
  if ((array = (CacheLine*) malloc(LINES * LINE_SIZE)) == NULL) {
    printf("Couldn't allocate test array\n") ;
    return;
  }
 
  for (i = 0 ; i < LINES ; i++) {
    for (j = 0 ; j < POINTERS_PER_LINE; j++) {
      array[i].ptrCacheLine[j] = NULL ;
    }
  }
 
  //
  // The test array is divided into two halves: top and bottom.
  //
  // Set the pointers so that memory accesses ping-pong 
  // between the two halves of the array.
  //
  steps = LINES / 2 ;
  bottom = 0 ;
  top = steps ;
  for (i = 0 ; i < steps ; i++) {
    array[bottom].ptrCacheLine[0] = &array[top] ;
    array[top].ptrCacheLine[0] = &array[bottom+1] ;
    top++ ;
    bottom++ ;
  }
 
  array[LINES-1].ptrCacheLine[0] = NULL ;
}
 
void chase(CacheLine* array)
{
  for(CacheLine *p = array ; p != NULL ; p = p->ptrCacheLine[0]) ;
}
 
 
void chasen(unsigned n)
{
  for (unsigned i = n ; i > 0 ; i--)
    chase(array) ;
}

void measure( void (*f)(unsigned int), unsigned int n)
{
    measure_instructions(f, n);
    measure_branch(f, n);
    measure_icache(f, n);
    measure_dcache(f, n);
}

void main ( void )
{
    timer_init();
    armtimer_init();
    uart_init();

    delay(1);

    initialize_array();

    mmu_init();
    //system_enable_cache();

    unsigned int n = 0x0800000/LINES;

    printf("size=%d, lines=%d, iterations=%d\n", LINES*LINE_SIZE, LINES, n);
    measure(&chasen, n);
}
