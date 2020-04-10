#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdlib.h>
#include <uthash.h>

extern char** environ;

typedef enum {
  T_INT,
  T_FLOAT,
  T_STR, /* String (char *) */
  T_BUILTIN, /* Builtin function with func pointer in table (callable c-funcs) */
  T_EXEC, /* Executable file within PATH */
  T_FUNC/* Like a function in shells, a string or opcode-compiled function */
} _type;

typedef struct {
  unsigned int id;
  char* name; // Actual key
  _type type;
  void* data;
  UT_hash_handle hh; // Makes this hashable.
} ut_entry;

typedef struct {
  unsigned int interactive : 1;
  unsigned int history : 1; 
} sh_opts;

int
process(ut_entry* entry);

void 
add_entry(ut_entry* entry);

ut_entry* 
make_entry(_type type, char* name, void* data);

/* List all elements in hash table */
void
list();

/* Returns name of a type */
char*
typestr(_type type);

/* Formats data for a type */
char*
fdata(_type type, void* data);



/* Prints file, line, and error message. This is a macro as otherwise it will not have the correct file and line as it is dependent on preprocessor expansion. */
#define report_error(msg){\
fprintf(stderr, "%s:%d %s", __FILE__, __LINE__, msg);\
}

//{{{ Vim configuration
// vim: expandtab: foldmethod=marker: autoindent: smartindent: shiftwidth=2: noai: ts=2:
// Note: You must have the following set in vim: set modeline
//}}}
#endif /* SHELL_H */
