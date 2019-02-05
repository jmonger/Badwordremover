# Badwordremover

Badwordremover is a C program used to remove strings in the form of regular expressions from an input text file.
The user passes an input file containing content and a configuration file containing removal words. 
The program then outputs a text file containing the original content from the input file, but with the identified words removed.

## Installation
Download Makefile and program.c to a local linux machine. You can use the manual download feature in git or the clone command.

Once files are downloaded run the make command to compile the program

~~~bash
make
~~~

## Usage
As the 2nd argument pass an input file containing the content you would like to filter. 
As the third argument pass the configuration file containing the words you would like to remove

~~~bash
./Badwordremover input.txt config.txt
~~~

## Output
The filtered.txt file contains the filtered input content.
~~~bash
filtered.txt
~~~
