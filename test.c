#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
	if (argc > 1){
	  int prior = atoi(argv[1])%32;
		update_prior(prior);
		for(int i=0; i<1000; i++){
			asm("nop");
			for (int j = 0; j < 2000; j++) {
				asm("nop");
			}
		}
//		printf(1,"\n Bye from %s %d!\n", argv[0],atoi(argv[1]));
	}

	exit(1);
}

//test 30&; test 20&;test 10&; test 7&;test 6&; test 7&;
