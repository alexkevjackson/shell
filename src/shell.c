#include "shell.h"


int 
sh_loop(FILE* in, FILE* out, sh_opts opts)
{
  /* Invoke the parsing loop. As of now this simply hooks to readline with configuration in opts flags. */
  static char* line = NULL;
  const char* prompt = "";

  if ( opts.interactive ) 
    prompt = "shell% ";
  else {
    report_error("Non-interactive not yet supported.\n");
    exit(EXIT_FAILURE);
  }
  /* We should probably not use readline if this is not interactive, but whatever. */
  if ( opts.history )
    using_history();

  rl_instream = in;
  rl_outstream = out;

  do {
    if (line){ // Return memory if allocated.
      free(line);
      line = NULL;
    }

    line = readline(prompt); // Where da magic happens baybee

    if ( opts.history == true && line && *line)
      add_history(line);
  } while ( line != NULL && strcmp(line, "exit") );

  return 0; 
}

#pragma GCC diagnostic ignored "-Wunused-parameter" // We ignore for now unused arguments to main, as we have no options yet implemented.
int
main (int argc, char* argv[]){
  sh_opts opts;
  opts.interactive = true;
  opts.history = true;
  sh_loop(stdin, stdout, opts);
	return 0;
}
#pragma GCC diagnostic pop // Re-enable -Wunused-parameter (test below)
//{{{ Vim configuration
// vim: expandtab: foldmethod=marker: autoindent: smartindent: shiftwidth=2: noai: ts=2:
// Note: You must have the following set in vim: set modeline
//}}}
