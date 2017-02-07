
# should find a way to accept the value from a higher-level script
if test "x$SIMSCRIPTS_PROJECT_ENV" = "xtrue"; then
 export UEX=`dirname $SIMSCRIPTS_DIR`
 export UEX=`dirname $UEX`
fi

uname_o=`uname -o`

if test "$uname_o" = "Cygwin"; then
	UEX=`cygpath -w $UEX | sed -e 's%\\\\%/%g'`
fi

export GOOGLETEST_UVM=$UEX/ve/googletest_uvm


