#include <stdio.h>
#include "gtest/gtest.h"
#include <errno.h>
#include <reent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>


const char *TESTNAME = TESTNAME_STR;
const char *SW_TESTNAME = SW_TESTNAME_STR;


int main(int argc, char **argv) {
  int status;
  char arg0[16] = {0};
  char *argv_p[] = {arg0};
  argc = 1;

  ::testing::InitGoogleTest(&argc, argv);

  ::testing::GTEST_FLAG(filter) = SW_TESTNAME;

  fprintf(stdout, "--> RUN_ALL_TESTS\n"); 
  status = RUN_ALL_TESTS();
  fprintf(stdout, "<-- RUN_ALL_TESTS\n"); 

  exit(0);
  return 0;
}

