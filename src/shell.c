#include "shell.h"

ut_entry* table;

void
clear(){
  puts("\e[1;1H\e[2J");
}

void
env(){
  printf(environ[0]);
  for (int i = 0; environ[i] != NULL; i++)
  {
    printf("\n%s", environ[i]);
  }
}

void 
init_entries(){
  /* Just creates list, which is T_BUILTIN pointing to (*list) */
  ut_entry* entry = make_entry( T_BUILTIN, "list", &list );
  add_entry(entry);
  entry = make_entry( T_BUILTIN, "env", &env );
  add_entry(entry);
  entry = make_entry( T_BUILTIN, "clear", &clear );
  add_entry(entry);
  entry = make_entry ( T_BUILTIN, "exit", &exit );
  add_entry(entry);
}

int
process (ut_entry* entry){
  void (*fun)() = (entry->data);
  switch (entry->type)
  {
    case T_BUILTIN:
      {
        fun();
        return 0;
      }
    default:
      fprintf(stderr, "Not yet implemented.\n");
  }
  return 0;
}

char*
fdata(_type type, void* data) 
{
  /* Just uses a static on this things stack. Terrible, but quick, implementation. */
  static char retstring[64];
  switch (type)
  {
    case T_INT:
      snprintf(retstring, 64, "%d", *((int *)data));
      break;
    case T_FLOAT:
      snprintf(retstring, 64, "%f", *((float *)data));
      break;
    case T_STR:
      /* FIXME: This truncates! Make it dynamic or something! 
      Currently, it must also copy because the strings from fdata must be freed after invocation.
      Make it more like printf! */
      strncpy(retstring, (char*) data, 64);
      break;
    case T_BUILTIN:
      strncpy(retstring, "builtin - NYI", 64);
      break;
    case T_EXEC:
      strncpy(retstring, "exec -NYI", 64);
      break;
    case T_FUNC:
      strncpy(retstring, (char*) data, 64);
      break;
  }
  return retstring;
}

char* 
typestr(_type type){
  switch (type)
  {
    case T_INT: return "integer";
    case T_FLOAT: return "float";
    case T_STR: return "string";
    case T_BUILTIN: return "builtin (cfunc)";
    case T_EXEC: return "Path-residing executable";
    case T_FUNC: return "function (sequence of interpretable types)";
    default: return "No such type - sorry bud, this is not a production shell.";
  }
}

void list(){
  /* Lists all objects within the table */
  ut_entry* entry = table;
  char* entryrep = fdata(entry->type, entry->data);
  for (unsigned int index = 0; entry != NULL; index++)
  {
    printf("entry[%d] {\n\
            name = %s;\n\
            type = %d - %s;\n\
            data = %s;\n\
            }\n", 
            index, 
            entry->name,
            entry->type,
            typestr(entry->type), 
            entryrep);
     entry=entry->hh.next;
  }
}

void 
add_entry(ut_entry* entry){
  ut_entry* cmpentry;
  HASH_FIND_STR( table, entry->name, cmpentry);
  if (cmpentry){
    fprintf(stderr, "Error, %s already in table.\n", entry->name);
  }
  else{
    HASH_ADD_KEYPTR( hh, table, entry->name, strlen(entry->name), entry);
  }
}

ut_entry* 
make_entry(_type type, char* name, void* data){
  ut_entry* entry = malloc(sizeof(ut_entry));
  entry->type = type;
  entry->name = malloc(strlen(name));
  strcpy(entry->name, name);
  entry->data = data;
#ifdef DEBUG
  printf("Made entry: %s\n", entry->name);
#endif 
  return entry;
}

int 
sh_loop(FILE* in, FILE* out, sh_opts opts)
{
  /* Invoke the parsing loop. As of now this simply hooks to readline with configuration in opts flags. */
   
  table = NULL;
  ut_entry* curentry = NULL;
  init_entries();

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

    if ( line && *line){
      if ( opts.history ) 
        add_history(line);
      HASH_FIND_STR( table, line, curentry );
      if ( curentry ) // Match in the table
        process( curentry );
      else
        fprintf(stderr, "Not found: %s\n", line);
    }

  } while ( true );

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
