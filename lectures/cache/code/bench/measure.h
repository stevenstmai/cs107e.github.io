#ifndef MEASURE_H
#define MEASURE_H

extern void measure_instructions(void (*f)(unsigned), unsigned);
extern void measure_icache(void (*f)(unsigned),unsigned);
extern void measure_dcache(void (*f)(unsigned),unsigned);
extern void measure_tlb(void (*f)(unsigned),unsigned);
extern void measure_branch(void (*f)(unsigned),unsigned);

#endif
