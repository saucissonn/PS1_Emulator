#include "ps1/ps1.hpp"

#include <stdio.h>


#include "utils/error.hpp"

int main()
{
	printf("Hello World!\n");

	Ps1 ps1 = Ps1();

	int ret = ps1.run();

	if (ret != ERR_OK) {
		printf("%s\n", error_string(ret));
		return ret;
	}

	return ERR_OK;
}
