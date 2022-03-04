[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=5634119&assignment_repo_type=AssignmentRepo)
# Lab 1

## Help Received

Please document any help you received in completing this lab. Note that the what you submit should be your own work. Refer to the syllabus for more details. 

[ANSWER HERE]


## Describe your programming work

### Part 1

Provide a short description of how you converted the Java functionality to C

#### Prob 1

First I had to change the scanning so that it corresponds to the c language. Then I created an error case in c, after I had to concatinate using %d instead of using the java way.

#### Prob 2

The main things that I had to worry about was the scanning and the printing, using scanf() instead of nextInt(), and printf() instead of System.out.println()

#### Prob 3

For this problem the format for dealing with files looks pretty similar. I just used the fopen function.

### Part 2

Describe the kinds of errors in this program and how you corrected them

#### mybad.c

This program had a semicolon missing on one of the printf statements, and also instead of having \n it had \m

#### whoops.c

One of the printf statements had a capital P, and a lot of the formating was off. They didn't correspond with their correct type. And also the operations were off due to the lack of parenthesis so I added them correctly.

### thatsgotthurt.c

This program was missing ```#include <stdio.h>```

### Part 3

Provide a short description of your program and development experience of that program

First I started by creating two conditions for when the value is even and when its odd. Then I created two for loops for each horizontal half of the hourglass.  In the for loops there were nested for loops for printing the stars and spaces that corresponding to row.
