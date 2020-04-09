#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  unsigned int interactive : 1;
  unsigned int history : 1; 
} sh_opts;

/* Prints file, line, and error message. This is a macro as otherwise it will not have the correct file and line as it is dependent on preprocessor expansion. */
#define report_error(msg){\
fprintf(stderr, "%s:%d %s", __FILE__, __LINE__, msg);\
}

//{{{ Vim configuration
//vim: expandtab: foldmethod=marker: autoindent: smartindent: shiftwidth=2: noai: ts=2:
//Note: You must have the following set in vim: set modeline
//}}}
#endif /* SHELL_H */
