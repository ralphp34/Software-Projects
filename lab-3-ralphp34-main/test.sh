#!/bin/bash

export CFLAGS="-Wall -Wextra -Wno-unused"

#red='\e[0;31m'
#green='\e[0;32m'
#nc='\e[0m'     

base=$(dirname $0)


function tobase(){
    cd $(dirname $0)
}


function utest( ){

    if [ "$1" == "$2" ]
    then
	echo -ne "$green pass $nc"
    else
	echo -ne "$red FAIL $nc" 
    fi
    echo -ne "\t\t "
    echo "$3"
}

function utest_ne( ){

    if [ "$1" != "$2" ]
    then
	echo -ne "$green pass $nc"
    else
	echo -ne "$red FAIL $nc" 
    fi

    echo -ne "\t\t "
    echo "$3"
}

function utest_nz( ){
    if [ ! -z "$1" ]
    then
	echo -ne "$green pass $nc" 
    else
	echo -ne "$red FAIL $nc" 
    fi
    echo -ne "\t\t "
    echo "$2"

}

function utest_z( ){
    if [ -z "$1" ]
    then
	echo -ne "$green pass $nc" 
    else
	echo -ne "$red FAIL $nc" 
    fi
    echo -ne "\t\t "
    echo "$2"

}


function test_part1(){
    echo "--- TEST part1 ---"

    cd part1

    rm -f palindrome
    cmd="gcc -Wall palindrome.c -o palindrome 2>&1"
    res=$(eval $cmd)
    utest_z "$res" "Compiles without warnings or errors ($cmd)"

    if [ ! -z "$res" ]
    then
	echo
	echo "--- ERRORS --- "
	echo "$res"
	echo
    fi

    
    
    
    cmd='echo "madamimadam" | ./palindrome  | tr "\n" " "'
    res=$(eval $cmd)
    expect="Enter a string: Palindrome according to check 1 Palindrome according to check 2 "
    utest "$res" "$expect" "Test madamimadam ($cmd)"

    
    cmd='echo "amanaplanacanalpanama" | ./palindrome  | tr "\n" " "'
    res=$(eval $cmd)
    expect="Enter a string: Palindrome according to check 1 Palindrome according to check 2 "
    utest "$res" "$expect" "Test amanaplanacanalpanama ($cmd)"

    cmd='echo "natapalindrome" | ./palindrome  | tr "\n" " "'
    res=$(eval $cmd)
    expect="Enter a string: NOT a palindrome according to check 1 NOT a palindrome according to check 2 "
    utest "$res" "$expect" "Test notapalidrome ($cmd)"
    
    cd ..
    echo
}


function test_part2(){
    echo "--- TEST part2  ---"
    
    cd part2
    
    rm -f freq
    cmd="gcc -Wall freq.c -o freq 2>&1"
    res=$(eval $cmd)
    utest_z "$res" "Compiles without warnings or errors ($cmd)"

    if [ ! -z "$res" ]
    then
	echo
	echo "--- ERRORS --- "
	echo "$res"
	echo
    fi


    cmd='./freq swift.txt'
    res=$(eval $cmd)
    expect=$(cat <<EOF 
A: 2232 (7.15%)
B: 580 (1.86%)
C: 1009 (3.23%)
D: 1147 (3.67%)
E: 3793 (12.14%)
F: 801 (2.56%)
G: 732 (2.34%)
H: 1385 (4.43%)
I: 2157 (6.91%)
J: 113 (0.36%)
K: 239 (0.77%)
L: 1137 (3.64%)
M: 761 (2.44%)
N: 2226 (7.13%)
O: 2658 (8.51%)
P: 768 (2.46%)
Q: 31 (0.10%)
R: 2224 (7.12%)
S: 1669 (5.34%)
T: 2979 (9.54%)
U: 978 (3.13%)
V: 291 (0.93%)
W: 590 (1.89%)
X: 61 (0.20%)
Y: 666 (2.13%)
Z: 4 (0.01%)
EOF
          )

    utest "$res" "$expect" "frequency on hemmingway($cmd)"

    
    cmd='echo $hemmingway>h.txt;./freq h.txt;rm -f h.txt'
    res=$(eval $cmd)
    expect=$(cat <<EOF 
A: 205 (8.01%)
B: 60 (2.35%)
C: 38 (1.49%)
D: 115 (4.50%)
E: 334 (13.06%)
F: 39 (1.52%)
G: 55 (2.15%)
H: 189 (7.39%)
I: 143 (5.59%)
J: 6 (0.23%)
K: 24 (0.94%)
L: 107 (4.18%)
M: 63 (2.46%)
N: 175 (6.84%)
O: 215 (8.41%)
P: 29 (1.13%)
Q: 4 (0.16%)
R: 145 (5.67%)
S: 99 (3.87%)
T: 286 (11.18%)
U: 69 (2.70%)
V: 16 (0.63%)
W: 65 (2.54%)
X: 3 (0.12%)
Y: 62 (2.42%)
Z: 12 (0.47%)
EOF
          )


    cmd="gcc -Wall sub.c -o sub 2>&1"
    res=$(eval $cmd)
    utest_z "$res" "Compiles without warnings or errors ($cmd)"

    if [ ! -z "$res" ]
    then
	echo
	echo "--- ERRORS --- "
	echo "$res"
	echo
    fi


    cmd='./sub key.txt cipher.txt  | shasum'
    res=$(eval $cmd)
    expect="487b8d8e60edc2c9a505564c7247e029b0c09adc  -"
    utest "$res" "$expect" "sub on secret ($cmd)"

    
    cmd='echo "$test_key_r" > r.txt; echo "$test_cipher" > c.txt; ./sub r.txt c.txt  | tr -d "\n" | shasum'
    res=$(eval $cmd)
    expect="7c9a804a5b4d80295d67ee14d12009b17cecd1f3  -"
    utest "$res" "$expect" "sub on test ($cmd)"


}


if [ ! -z $1 ]
then
    cd $1
else
    cd $(dirname $0)
fi

echo


hemmingway=$(cat<<EOF
A Very Short Story by Ernest Hemingway 


One hot evening in Padua they carried him up onto the roof and he could look out over the top 
of the town. There were chimney swifts in the sky. After a while it got dark and the searchlights 
came out. The others went down and took the bottles with them. He and Luz could hear them 
below on the balcony. Luz sat on the bed. She was cool and fresh in the hot night. 

Luz stayed on night duty for three months. They were glad to let her. When they operated on 
him she prepared him for the operating table; and they had a joke about friend or enema. He 
went under the anaesthetic holding tight on to himself so he would not blab about anything 
during the silly, talky time. After he got on crutches he used to take the temperatures so Luz 
would not have to get up from the bed. There were only a few patients, and they all knew about 
it. They all liked Luz. As he walked back along the halls he thought of Luz in his bed. 

Before he went back to the front they went into the Duomo and prayed. It was dim and quiet, 
and there were other people praying. They wanted to get married, but there was not enough 
time for the banns, and neither of them had birth certificates. They felt as though they were 
married, but they wanted everyone to know about it, and to make it so they could not lose it. 

Luz wrote him many letters that he never got until after the armistice. Lifteen came in a bunch 
to the front and he sorted them by the dates and read them all straight through. They were all 
about the hospital, and how much she loved him and how it was impossible to get along 
without him and how terrible it was missing him at night. 

After the armistice they agreed he should go home to get a job so they might be married. Luz 
would not come home until he had a good job and could come to New York to meet her. It was 
understood he would not drink, and he did not want to see his friends or anyone in the States. 
Only to get a job and be married. On the train from Padua to Milan they quarreled about her not 
being willing to come home at once. When they had to say good-bye, in the station at Milan, 
they kissed good-bye, but were not finished with the quarrel. He felt sick about saying good- 
bye like that. 

He went to America on a boat from Genoa. Luz went back to Pordonone to open a hospital. It 
was lonely and rainy there, and there was a battalion of arditi quartered in the town. Living in 
the muddy, rainy town in the winter, the major of the battalion made love to Luz, and she had 
never known Italians before, and finally wrote to the States that theirs had only been a boy and 
girl affair. She was sorry, and she knew he would probably not be able to understand, but might 
some day forgive her, and be grateful to her, and she expected, absolutely unexpectedly, to be 
married in the spring. She loved him as always, but she realized now it was only a boy and girl 
love. She hoped he would have a great career, and believed in him absolutely. She knew it was 
for the best. 

The major did not marry her in the spring, or any other time. Luz never got an answer to the 
letter to Chicago about it. A short time after he contracted gonorrhea from a sales girl in a loop 
department store while riding in a taxicab through Lincoln Park. 
EOF
          )

test_cipher=$(cat<<EOF
... FO CMR TKHMO PKMWOFWMU YMUJH – GQJ WMB SKMP FO MKQJBX GQJ VQK SMKAOC MR GQJ LQJBX MWKQRR OCH WQUX AQQBR QV NMTUMB LHOM; GQJ WMB UFH QB FO QB OCH LKFUUFMBO AMKLUH-RMBXHX LHMWCHR QV RMBOKMTFBJR Y, FBCMUFBT OCH CHMXG RHM YMPQJKR; GQJ WMB RUHHP JBXHK FO LHBHMOC OCH ROMKR SCFWC RCFBH RQ KHXUG QB OCH XHRHKO SQKUX QV EMEKMVQQB; JRH FO OQ RMFU M AFBF KMVO XQSB OCH RUQS CHMYG KFYHK AQOC; SHO FO VQK JRH FB CMBX-OQ-CMBX-WQALMO; SKMP FO KQJBX GQJK CHMX OQ SMKX QVV BQZFQJR VJAHR QK OQ MYQFX OCH TMDH QV OCH KMYHBQJR LJTLUMOOHK LHMRO QV OKMMU (M AFBXLQTTFBTUG ROJPFX MBFAMU, FO MRRJAHR OCMO FV GQJ WMB’O RHH FO, FO WMB’O RHH GQJ – XMVO MR M LJRC, LJO YHKG, YHKG KMYHBQJR); GQJ WMB SMYH GQJK OQSHU FB HAHKTHBWFHR MR M XFROKHRR RFTBMU, MBX QV WQJKRH XKG GQJKRHUV QVV SFOC FO FV FO ROFUU RHHAR OQ LH WUHMB HBQJTC. 
EOF
            )

test_key_r=$(cat<<EOF
M:A
L:B
W:C
X:D
H:E
V:F
T:G
C:H
F:I
N:J
E:K
U:L
A:M
B:N
Q:O
P:P
I:Q
K:R
R:S
O:T
J:U
Y:V
S:W
Z:X
G:Y
D:Z
EOF
            )
test_part1
test_part2
