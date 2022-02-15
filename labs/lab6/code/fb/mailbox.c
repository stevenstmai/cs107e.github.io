/*
 * Interface to Raspberry Pi mailbox system, used by libpi to interact
 * with GPU. Note that this interface has been deprecated and so future
 * code should use the property interface instead.
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 * Author: Philip Levis <pal@cs.stanford.edu>
 * Date: 6/20/17
 */

#include "mailbox.h"

#define MAILBOX_BASE     0x2000B880

// This bit is set in status register if no space to write to mailbox
#define MAILBOX_FULL   (1<<31)

// This bit is set in status register if nothing to read in mailbox
#define MAILBOX_EMPTY  (1<<30)

// This prevents the GPU and CPU from caching mailbox messages
#define GPU_NOCACHE 0x40000000

typedef struct {
    unsigned int read;
    unsigned int padding[3]; // note padding to skip 3 words
    unsigned int peek;
    unsigned int sender;
    unsigned int status;
    unsigned int configuration;
    unsigned int write;
} mailbox_t;


// If the mailbox memory is not qualified as volatile, the compiler may
// take liberties in optimizing the code that can be problematic.
// Below we use the preprocessor to compile two versions of mailbox:
// one where mailbox is properly qualified as volatile and a second
// (buggy) one that does not. Use `make` to generate both versions
// and compare the assembly instructions in the two .list files. Can
// you spot the problems introduced by the compiler's optimizations
// of the non-volatile version?
#ifdef NVOLATILE
static mailbox_t *mailbox = (mailbox_t *)MAILBOX_BASE;
#else
static volatile mailbox_t *mailbox = (mailbox_t *)MAILBOX_BASE;
#endif

bool mailbox_request(unsigned int channel, unsigned int addr) {
    if (!mailbox_write(channel, addr))
        return false;
    return (mailbox_read(channel) == 0); // returned data is 0 on success
}

bool mailbox_write(unsigned int channel, unsigned int addr) {
    // mailbox has a maximum of 16 channels
    if (channel >= MAILBOX_MAXCHANNEL) {
        return false;
    }

    // addr must be a multiple of 16
    if (addr & 0xF) {
        return false;
    }

    // wait until mailbox is not full ...
    while (mailbox->status & MAILBOX_FULL) ;

    // set GPU_NOCACHE bit so that the GPU does not cache the memory
    addr |= GPU_NOCACHE;

    // addr is a multiple of 16, so the low 4 bits are zeros
    // 4-bit channel number is stuffed into those low bits
    mailbox->write = addr | channel;
    return true;
}

// Return the top 28 bits of the read register (shifted right 4) 
// when a message is read for `channel`. If a message is received for
// a different channel, discard it and read again. Return 1 if the channel is 
// invalid or the read fails in some way.
unsigned int mailbox_read(unsigned int channel) {
	// You fill in this function. It should:
	//   1. Check that the channel is valid (see `mailbox_write` for how to do this.
    //   2. Spin-wait until the `MAILBOX_EMPTY` flag in the mailbox `status` register
    //      is cleared (meaning there is data in the `read` register).
    //   3. Check that the bottom 4 bits of the `read` register are the same as
    //      the channel: if so, return the top 28 bits of `read` shifted right 4 bits.
    //      Otherwise, wait for another message in the mailbox (step 2).
    return 1;
}
