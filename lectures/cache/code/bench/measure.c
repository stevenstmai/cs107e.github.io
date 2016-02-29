#include <stdio.h>
#include "pmu.h"
#include "armtimer.h"
#include "measure.h"

void measure_instructions(void (*f)(unsigned int), unsigned int n)
{
    unsigned beg = armtimer_get_time();
    (*f)(n);
    unsigned elapsed = (armtimer_get_time() - beg)/250;;
    // armtimer runs at the system core clock frequency = 250 Mhz

    pmu_set_events(ARMV6_EVENT_INSTRUCTION_EXECUTED, ARMV6_EVENT_CPU_CYCLES) ;
    pmu_start_counting(1,1) ;
    
    (*f)(n);

    pmu_stop_counting() ;

    int overflow;

    unsigned instructions = pmu_get_counter(ARMV6_COUNTER0, &overflow);
    unsigned mips = instructions / elapsed;
    printf("instructions=%d, seconds=%d, mips=%d\n",
        instructions, elapsed, mips );

    unsigned cycles       = pmu_get_counter(ARMV6_COUNTER1, &overflow);
    unsigned long long cpi = (1000LLU*cycles) / instructions;
    unsigned icpi = cpi / 1000;
    unsigned fcpi = cpi % 1000;

    printf("cycles=%d, instructions=%d, cpi=%d.%d\n",
        cycles, instructions, icpi, fcpi);
}

void measure_branch(void (*f)(unsigned), unsigned n)
{
    pmu_set_events(ARMV6_EVENT_BRANCH_EXECUTED, ARMV6_EVENT_BRANCH_MISPREDICT) ;
    pmu_start_counting(1,1) ;

    (*f)(n);

    pmu_stop_counting() ;

    int overflow;
    unsigned branch = pmu_get_counter(ARMV6_COUNTER0, &overflow);
    unsigned mispredict = pmu_get_counter(ARMV6_COUNTER1, &overflow);
    printf("branches=%d, mispredict=%d\n", branch, mispredict);
}

void measure_icache(void (*f)(unsigned), unsigned n)
{
    pmu_set_events(ARMV6_EVENT_ICACHE_MISS, ARMV6_EVENT_ISTALL) ;
    pmu_start_counting(1,1) ;

    (*f)(n);

    pmu_stop_counting() ;

    int overflow;
    unsigned miss  = pmu_get_counter(ARMV6_COUNTER0, &overflow);
    unsigned stall = pmu_get_counter(ARMV6_COUNTER1, &overflow);
    printf("icache: miss=%d, stall=%d\n", miss, stall);
}

void measure_dcache(void (*f)(unsigned), unsigned n)
{
    pmu_set_events(ARMV6_EVENT_DCACHE_CACHED_ACCESS, ARMV6_EVENT_DCACHE_MISS) ;
    pmu_start_counting(1,1) ;

    (*f)(n);

    pmu_stop_counting() ;

    int overflow;
    unsigned access = pmu_get_counter(ARMV6_COUNTER0, &overflow);
    unsigned miss   = pmu_get_counter(ARMV6_COUNTER1, &overflow);
    printf("dcache: access=%d, miss=%d\n", access, miss);
}

void measure_tlb(void (*f)(unsigned), unsigned n)
{
    pmu_set_events(ARMV6_EVENT_DMICROTLB_MISS, ARMV6_EVENT_IMICROTLB_MISS) ;
    pmu_start_counting(1,1) ;

    (*f)(n);

    pmu_stop_counting() ;

    int overflow;
    unsigned dmiss = pmu_get_counter(ARMV6_COUNTER0, &overflow);
    unsigned imiss = pmu_get_counter(ARMV6_COUNTER1, &overflow);
    printf("tlb: data miss=%d, instruction miss=%d\n", dmiss, imiss);
}

