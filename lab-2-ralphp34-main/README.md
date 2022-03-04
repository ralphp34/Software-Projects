# Lab 2


## Answer the following questions:

(1) Why do you have to pass the length of the array to the functions?

We need to provide the length of our arrays because without it we will not know how big we want our array 

(2) What is a random seed used for?

Random seed is a number generator that gives us test cases but it isn't necessarily random.

## Help Received

Please document any help you received in completing this lab. Note that the what you submit should be your own work. Refer to the syllabus for more details. 

Looked back at insertion sort algorithm from 1112 and implemented it into c.

## Describe your work

For each of the parts, describe your actions and code and generally
provide any additional information needed to grade your assignment:

### Part 1:

In this part of the program I am writing code to read inputs that we ask for in the program. I am also checking for error cases. If the user doesn't input a valid int or if the int isn't within the correct range we will throw an error messages. In this case we used ```  res = scanf("%d", &len); ``` to see how many successful scans we had and if res == 0 then we knew the input was invalid.


### Part 2:

In this part of my program I am writing the code for printing out the array of numbers past in by the user. For this method I passed in an array and an int as parameters. Then I looped through the entire array and I printed the value at each index and I surrounded them with curly braces.

### Part 3:

This part of the program was for reversing the array that was passed in by the user. For this I created an array to store the reversed array. I looped through the array and got the reversed values and put it into the new array. After I looped through the array reversed again and put those values into our original array, then I called my print_array method.

### Part 4:

With this part of the program the array I am randomizing the values in the array. I am doing this by going through a for loop and generating a "random" index and I then switching the random index with our current index. Then I called print_array to print my randomized array. 

### Part 5:

This part is for sorting the values of our array. I did this by implementing an selection sort algorithm where I looped through my array and compared each value to the one to the left of it and switched the values if the number was less than the one before it. 
