#!/bin/bash


################################################################################
# The variable 'shell_input' HAS TO BE DEFINED
#
# The content of this variable will be piped to the student's shell and to sh
# as follows: "echo $shell_input | ./hsh"
#
# It can be empty and multiline
shell_input="env"

################################################################################
# The variable 'shell_params' IS OPTIONNAL
#
# The content of this variable will be passed to as the paramaters array to the
# shell as follows: "./hsh $shell_params"
#
# It can be empty
# shell_params=""


function check_setup()
{
	current_env=$(/usr/bin/env)
	for i in `/usr/bin/env | /usr/bin/cut -d'=' -f1`
	do
		unset $i
	done

	export HBTN="Holberton"

	return 0
}

################################################################################
# The function 'sh_setup' will be called AFTER the execution of the students
# shell, and BEFORE the execution of the real shell (sh)
# It allows you to set custom VARIABLES, prepare files, etc
# If you want to set variables for the shell to use, be sure to export them,
# since the shell will be launched in a subprocess
#
# Return value: Discarded
function sh_setup()
{
	return 0
}

################################################################################
# The function `check_callback` will be called AFTER the execution of the shell
# It allows you to clear VARIABLES, cleanup files, ...
#
#
# Parameters:
#     $1 -> Status of the comparison with sh
#             0 -> The output is the same as sh
#             1 -> The output differs from sh
#
# Return value:
#     0  -> Check succeed
#     1  -> Check fails
function check_callback()
{
	let status=0

	# Remove environment variables and set by valgrind from student output
	content=`$CAT "$OUTPUTFILE"`
	content=`$ECHO "$content" | $GREP -v -e "^GLIBCPP_FORCE_NEW="`
	content=`$ECHO "$content" | $GREP -v -e "^GLIBCXX_FORCE_NEW="`
	content=`$ECHO "$content" | $GREP -v -e "^LD_PRELOAD="`
	content=`$ECHO "$content" | $GREP -v -e "^LD_LIBRARY_PATH="`
	content=`$ECHO "$content" | $GREP -v -e "^_="`
	content=`$ECHO "$content" | $GREP -v -e "^PWD="`
	$ECHO "$content" > $OUTPUTFILE

	# Remove "_" environment variable from expected output
	content=`$CAT "$EXPECTED_OUTPUTFILE"`
	content=`$ECHO "$content" | $GREP -v -e "^_="`
	content=`$ECHO "$content" | $GREP -v -e "^PWD="`
	$ECHO "$content" > $EXPECTED_OUTPUTFILE

	$ECHO -n "" > $EXPECTED_ERROR_OUTPUTFILE
	$ECHO -n "0" > $EXPECTED_STATUS

	check_diff

	return $status
}
