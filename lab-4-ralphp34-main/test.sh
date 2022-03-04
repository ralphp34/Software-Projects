#!/bin/bash
export CFLAGS="-Wall -Wextra -Wno-unused"

red=''
green=''
nc=''

base=$(dirname $0)


function tobase(){
    cd $(dirname $0)
}

function utest( ){
    ret=0
    if [ "$1" == "$2" ]
    then
	echo -ne "$green pass $nc"
    else
	echo -ne "$red FAIL $nc"
        ret=1
    fi
    echo -ne "\t\t "
    echo "$3"
    return $ret
}

function utest_ne( ){
    ret=0
    if [ "$1" != "$2" ]
    then
	echo -ne "$green pass $nc"
    else
	echo -ne "$red FAIL $nc"
        ret=1
    fi

    echo -ne "\t\t "
    echo "$3"
    return $ret
}

function utest_nz( ){
    ret=0
    if [ ! -z "$1" ]
    then
	echo -ne "$green pass $nc" 
    else
	echo -ne "$red FAIL $nc"
        ret=1
    fi
    echo -ne "\t\t "
    echo "$2"
    return $ret
}

function utest_z( ){
    ret=0
    if [ -z "$1" ]
    then
	echo -ne "$green pass $nc" 
    else
	echo -ne "$red FAIL $nc"
        ret=1
    fi
    echo -ne "\t\t "
    echo "$2"
    return $ret

}



function dodiff(){
    if [ "$1" == "1" ]
    then
        echo
        echo -e "\t\t\t --------- DIFF ---------"
        echo -e "your output \t\t\t\t\t\t\t expected output"
        echo -e "----------- \t\t\t\t\t\t\t ---------------"
        echo "$2" > res
        echo "$3" > expect
        diff -y res expect
        rm -f res expect
        echo
    fi
}

function test_valgrind(){
    echo "--- TEST valgrind ---"

    cd valgrind
    rm -f memleak memviolation
    gcc -g memleak.c -o memleak
    gcc -g memviolation.c -o memviolation

    cmd="valgrind --leak-check=full ./memleak  2>&1 | grep \"definitely lost\""
    res=$(eval $cmd)
    utest_z "$res" "$cmd"

    if [ ! -z "$res" ]
    then
	echo
	echo "--- ERRORS --- "
	echo "$res"
	echo
    fi

    
    cmd="./memleak  2>&1 | grep \"definitely lost\""
    res=$(eval $cmd)
    expect="1 2 3 4 5  ----------- 1 2 3 4 5 1 2 3 4 5  "
    utest "$res" "$exepct" "(consitent output) $cmd"


    cmd="valgrind --leak-check=full ./memleak  2>&1 | grep \"0 errors\""
    res=$(eval $cmd)
    utest_nz "$res" "$cmd"
    if [ -z "$res" ]
    then
	echo
	echo "$(valgrind --leak-check=full ./memleak)"
	echo
    fi

    
    echo
    echo

    cmd="valgrind --leak-check=full ./memviolation 2>&1 | grep  \"0 errors\""
    res=$(eval $cmd)
    utest_nz "$res" "$cmd"

    if [ -z "$res" ]
    then
	echo
	echo "--- ERRORS --- "
	echo "$res"
	echo
    fi

    
    cd ..
    echo
}

function ctime(){
    date +"%a %b %e %H:%M:%S %Y"
}


function test_simplefs(){
    echo "--- TEST simplefs ---"
 
    cd simplefs

    make clean 2>&1 >/dev/null
    cmd="make 2>&1 | tr '\n' ' '"
    res=$(eval $cmd)
    expect="gcc -Wall -g -c -o filesystem.o filesystem.c gcc -Wall -g -c -o shell.o shell.c gcc -o shell shell.o filesystem.o -lreadline -lncurses  "
    utest "$res" "$expect" "Compiles without warnings or errors ($cmd)"

    
    if [ ! -z "$res" ]
    then
	echo
	echo "--- ERRORS --- "
	echo "$res"
	echo
    fi

    echo
    echo "  -touch-"
    echo

    curtime=$(ctime)
    cmd='echo -e "touch a\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch a simplefs > ls   a $curtime simplefs >  "
    utest "$res" "$expect" "Touch one file ($cmd)"
    dodiff "$?" "$res" "$expect"
    
    curtime=$(ctime)
    cmd='echo -e "touch go buff and blue\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch go buff and blue simplefs > ls   go $curtime   buff $curtime   and $curtime   blue $curtime simplefs >  "
    utest "$res" "$expect" "Touch multiple filesone file ($cmd)"
    dodiff "$?" "$res" "$expect"
    
    echo
    echo "  -memory touch-"
    echo

    cmd='echo -e "touch a\nexit" | valgrind --leak-check=full ./shell 2>&1 | grep "definitely lost: 0 bytes in 0 blocks"'
    res=$(eval $cmd)
    utest_nz "$res" "Touch one file memory leaks ($cmd)" 
    dodiff "$?" "$res" "$expect"
    
    cmd='echo -e "touch a\nexit" | valgrind --leak-check=full ./shell 2>&1 | grep "ERROR SUMMARY: 0 errors from 0 contexts"'
    res=$(eval $cmd)
    utest_nz "$res" "Touch one file memory violations ($cmd)" 
    dodiff "$?" "$res" "$expect"
    
    cmd='echo -e "touch a\nexit" | valgrind --leak-check=full ./shell 2>&1 | grep "definitely lost: 0 bytes in 0 blocks"'
    res=$(eval $cmd)
    utest_nz "$res" "Touch multiple files memory leaks ($cmd)" 
    dodiff "$?" "$res" "$expect"
    
    cmd='echo -e "touch go buff and blue\nexit" | valgrind --leak-check=full ./shell 2>&1 | grep "ERROR SUMMARY: 0 errors from 0 contexts"'
    res=$(eval $cmd)
    utest_nz "$res" "Touch multiple files  memory violations ($cmd)" 
    dodiff "$?" "$res" "$expect"
    
    echo
    echo "  -remove-"
    echo

    curtime=$(ctime)
    cmd='echo -e "touch a\nls\nrm a\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch a simplefs > ls   a $curtime simplefs > rm a simplefs > ls simplefs >  "
    utest "$res" "$expect" "Touch and remove one file ($cmd)"
    dodiff "$?" "$res" "$expect"
    
    curtime=$(ctime)
    cmd='echo -e "touch go buff and blue\nls\nrm blue\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch go buff and blue simplefs > ls   go $curtime   buff $curtime   and $curtime   blue $curtime simplefs > rm blue simplefs > ls   go $curtime   buff $curtime   and $curtime simplefs >  "
    utest "$res" "$expect" "Touch many files and remove last file ($cmd)"
    dodiff "$?" "$res" "$expect"
    
    curtime=$(ctime)
    cmd='echo -e "touch go buff and blue\nls\nrm go\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch go buff and blue simplefs > ls   go $curtime   buff $curtime   and $curtime   blue $curtime simplefs > rm go simplefs > ls   buff $curtime   and $curtime   blue $curtime simplefs >  "
    utest "$res" "$expect" "Touch many files and remove first file ($cmd)"
    dodiff "$?" "$res" "$expect"
    
    curtime=$(ctime)
    cmd='echo -e "touch go buff and blue\nls\nrm go\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch go buff and blue simplefs > ls   go $curtime   buff $curtime   and $curtime   blue $curtime simplefs > rm go simplefs > ls   buff $curtime   and $curtime   blue $curtime simplefs >  "
    utest "$res" "$expect" "Touch many files and remove middle file ($cmd)"
    dodiff "$?" "$res" "$expect"
    
    curtime=$(ctime)
    cmd='echo -e "touch go buff and blue\nls\nrm and\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch go buff and blue simplefs > ls   go $curtime   buff $curtime   and $curtime   blue $curtime simplefs > rm and simplefs > ls   go $curtime   buff $curtime   blue $curtime simplefs >  "
    utest "$res" "$expect" "Touch many files and remove middle file ($cmd)"
    dodiff "$?" "$res" "$expect"
    
    curtime=$(ctime)
    cmd='echo -e "touch go buff and blue\nrm and\ntouch goat\nls" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    expect="simplefs > touch go buff and blue simplefs > rm and simplefs > touch goat simplefs > ls   go $curtime   buff $curtime   blue $curtime   goat $curtime simplefs >  "
    utest "$res" "$expect" "Touch many files and remove middle file and add one more file($cmd)"
    dodiff "$?" "$res" "$expect"
    
    echo
    echo   "-memory remove-"
    echo

    cmd='echo -e "touch a\nls\nrm a\nls" | valgrind --leak-check=full ./shell 2>&1 | grep "definitely lost: 0 bytes in 0 blocks"'
    res=$(eval $cmd)
    utest_nz "$res" "Memory leaks for touch and remove one file ($cmd)"
    dodiff "$?" "$res" "$expect"
    
    cmd='echo -e "touch a\nls\nrm a\nls" | valgrind --leak-check=full ./shell 2>&1 | grep "ERROR SUMMARY: 0 errors from 0 context"'
    res=$(eval $cmd)
    utest_nz "$res" "Memory violations  for touch and remove one file ($cmd)"
    dodiff "$?" "$res" "$expect"
    
    cmd='echo -e "touch go buff and blue\nls\nrm go\nls" | valgrind --leak-check=full ./shell 2>&1 | grep "definitely lost: 0 bytes in 0 blocks"'
    res=$(eval $cmd)
    utest_nz "$res"  "Memory leaks for touch many remove first ($cmd)"
    dodiff "$?" "$res" "$expect"
    
    cmd='echo -e "touch go buff and blue\nls\nrm go\nls" | valgrind --leak-check=full ./shell 2>&1 | grep "ERROR SUMMARY: 0 errors from 0 context"'
    res=$(eval $cmd)
    utest_nz "$res" "Memory violations  for touch and remove first ($cmd)"
    dodiff "$?" "$res" "$expect"
    
    cmd='echo -e "touch go buff and blue\nls\nrm blue\nls" | valgrind --leak-check=full ./shell 2>&1 | grep "definitely lost: 0 bytes in 0 blocks"'
    res=$(eval $cmd)
    utest_nz "$res"  "Memory leaks for touch many remove last ($cmd)"
    dodiff "$?" "$res" "$expect"
    
    cmd='echo -e "touch go buff and blue\nls\nrm blue\nls" | valgrind --leak-check=full ./shell 2>&1 | grep "ERROR SUMMARY: 0 errors from 0 context"'
    res=$(eval $cmd)
    utest_nz "$res"  "Memory violations  for touch and remove last ($cmd)"
    dodiff "$?" "$res" "$expect"
    
    echo
    echo   "-touch update time-"
    echo

delay_touch=$(cat <<EOF
echo "touch go buff and blue"
echo "ls"
sleep 1
echo "touch buff"
echo "ls"
EOF
)
    curtime=$(ctime)
    cmd='eval "$delay_touch" | ./shell | tr "\n" " " | tr "\t" " "'
    res=$(eval $cmd)
    nexttime=$(ctime)
    expect="simplefs > touch go buff and blue simplefs > ls   go $curtime   buff $curtime   and $curtime   blue $curtime simplefs > touch buff simplefs > ls   go $curtime   buff $nexttime   and $curtime   blue $curtime simplefs >  "
    utest "$res" "$expect" "Touch updates time ($cmd)"
    dodiff "$?" "$res" "$expect"
    
    cmd='eval "$delay_touch" | valgrind --leak-check=full ./shell 2>&1 | grep "definitely lost: 0 bytes in 0 blocks"'
    res=$(eval $cmd)
    utest_nz "$res" "Memory leak for touch update time ($cmd)"
    dodiff "$?" "$res" "$expect"
    
    cmd='eval "$delay_touch" | valgrind --leak-check=full ./shell 2>&1 | grep "ERROR SUMMARY: 0 errors from 0 context"'
    res=$(eval $cmd)
    utest_nz "$res" "Memory violation for touch update time ($cmd)"
    dodiff "$?" "$res" "$expect"
    

#    echo "($res)"
#    echo "($expect)"
    
    
    cd ..
    echo
}




if [ ! -z $1 ]
then
    cd $1
else
    cd $(dirname $0)
fi

echo

test_valgrind
test_simplefs
