#ifndef COMMANDS_H
#define COMMANDS_H

/*
 * This typedef gives a nickname to the type of function pointer used as the
 * a shell command.  A command_fn_t function has two parameters, the array
 * of tokens and its count. The return value is of type int.
 */
typedef int (*command_fn_t)(int argc, const char *argv[]);

/*
 * This typedef defines the type for each entry in the command table.
 * A command_t stores the info for one command, including the one-word name,
 * usage, help description, and function pointer to execute the command.
 */
typedef struct _command_struct {
    const char *name;
    const char *usage;
    const char *description;
    command_fn_t fn;
} command_t;

/*
 * `cmd_echo`
 *
 * Usage: echo [args]
 * Description: print arguments
 *
 * Example:
 *   Pi> echo Leland Stanford Junior University
 *   Leland Stanford Junior University
 *
 * Print arguments. Returns 0 (success).
*/
int cmd_echo(int argc, const char *argv[]);

/*
 * `cmd_help`
 *
 * Usage: help [cmd]
 * Description: print command usage and description
 *
 * If no argument, print a list of all available commands with
 * usage and description. If an argument is given, print
 * usage and description for named command. If no such
 * named command, prints an error message.
 *
 * Examples:
 *   Pi> help
 *   help [cmd]         print command usage and description
 *   echo [args]        print arguments
 *   reboot             reboot the Raspberry Pi
 *   peek [addr]        print contents of memory at address
 *   poke [addr] [val]  store value into memory at address
 *   Pi> help reboot
 *   reboot             reboot the Raspberry Pi
 *   Pi> help please
 *   error: no such command 'please'
 *
 * Ignores any arguments after the first. Returns 0 on success,
 * nonzero 1on error (command not found).
 */
int cmd_help(int argc, const char *argv[]);

/*
 * `cmd_reboot`
 *
 * Usage: reboot
 * Description: reboot the Raspberry Pi
 *
 * Example:
 *   Pi> reboot
 *   Rebooting Pi, see ya at the bootloader!
 *
 * Ignores all arguments. Prints informative message and reboots Pi.
 * This function does not return; the program exits on reboot.
 */
int cmd_reboot(int argc, const char *argv[]);

/*
 * `cmd_peek`
 *
 * Usage: peek [addr]
 * Description: print contents of memory at address
 *
 * Retrieve 4-byte value at memory address and print it.
 * If address is prefixed with 0x, it is interpreted as hex,
 * otherwise interpreted as decimal. Address must be 4-byte aligned.
 * If address is missing or invalid, prints an error message.
 *
 * Examples:
 *   Pi> peek 0
 *   0x00000000:  e59ff030
 *   Pi> peek
 *   error: peek expects 1 argument [addr]
 *   Pi> peek fred
 *   error: peek cannot convert 'fred'
 *   Pi> peek 13
 *   error: peek address must be 4-byte aligned
 *
 * Ignores any arguments after the first. Returns 0 on success, nonzero on error.
 */
int cmd_peek(int argc, const char *argv[]);

/*
 * `cmd_poke`
 *
 * Usage: poke [addr] [val]
 * Description: store value into memory at address
 *
 * Writes 4-byte value to memory at address.
 * If address or value is prefixed with 0x, it is interpreted as hex,
 * otherwise interpreted as decimal. Address must be 4-byte aligned.
 * If address or value is missing or invalid, prints an error message.
 *
 * Examples:
 *   Pi> poke 0x8000 3
 *   Pi> peek 0x8000
 *   0x00008000:  00000003
 *   Pi> poke 0x8000
 *   error: poke expects 2 arguments [addr] and [val]
 *   Pi> poke bob 3
 *   error: poke cannot convert 'bob'
 *   Pi> poke 11 0
 *   error: poke address must be 4-byte aligned
 *
 * Ignores any arguments after the second. Returns 0 on success, nonzero on error.
 */
int cmd_poke(int argc, const char *argv[]);


#endif
