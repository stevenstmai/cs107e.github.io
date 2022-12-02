#ifndef STACKPROF_H
#define STACKPROF_H

/*
 * Stack-sampling profiler. Not releasing the code but it's mostly a
 * straightforward mashup of gprof and backtrace.
 *
 * Author: Omar Rizwan <osnr@stanford.edu>
 *
 * Date: June 1, 2017
 */

#include "backtrace.h"

void stackprof_init(unsigned interval_us, int max_samp);

struct sample {
    unsigned time; // in us.

    frame_t frames[10];
    unsigned num_frames;
};

void stackprof_on();
void stackprof_off();

void stackprof_dump();

/* Returns 1 if handled interrupt. */
int stackprof_vector(unsigned pc, unsigned fp);

#endif
