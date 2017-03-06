#include <stdio.h>
#include "gtest/gtest.h"

const char *TESTNAME = TESTNAME_STR;
const char *SW_TESTNAME = SW_TESTNAME_STR;

int main(int argc, char **argv) {
  int status;
  ::testing::GTEST_FLAG(filter) = SW_TESTNAME;
 
  status = RUN_ALL_TESTS();

  return 0;
}

