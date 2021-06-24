All files are linked to a single header.h file:
main.c - contain main function and is responsible for printing menu 
and calling functions
input_func.c - contain all functions responsible for input, like reading 
in files, creating structures and some help functions like search() which is 
a simple linear search.
output_func.c - functions resposible for outputing prossesed informations, 
creating timetable, or printing modules.

No external libraries were used, to compile program only thing you have to do 
is using compiler e.g. gcc