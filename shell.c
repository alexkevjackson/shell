#include <unistd.h>

#pragma GCC diagnostic ignored "-Wunused-parameter"
int
main (int argc, char* argv[]){
	return 0;
}
#pragma GCC diagnostic pop // Re-enable -Wunused-parameter (test below)
int
warnMe(int neverUser) { return 0; }
