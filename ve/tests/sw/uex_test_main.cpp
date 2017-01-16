#include "gtest/gtest.h"
#include <stdio.h>
#include <string.h>

extern "C" int uex_test_main(const char *test, int *status);


int uex_test_main(
		const char *test,
		int 		*status) {
	int argc = 2;
	char arg0[16];
	char arg1[256];
	char *argv[2];

	strcpy(arg0, "swtest");
	sprintf(arg1, "--gtest_filter=%s", test);

	argv[0] = arg0;
	argv[1] = arg1;

	testing::InitGoogleTest(&argc, argv);

	*status = RUN_ALL_TESTS();

	return 0;
}
