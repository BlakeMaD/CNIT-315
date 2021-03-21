# CNIT-315
Group Project for CNIT-315. Members: Blake Dukes, Bryan Supinski, Cray Cordero, Duy Hoang, Jason Croddy

# Project Abstract
  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;The goal of our project is to create a C program that accepts user input in the form of a Haiku poem or couplet and ensures
that they are within a valid format. In the case of an invalid poem,
the program will check for synonyms or rhyming words, and attempt to offer the user alternative words in creating their poem.
The project will include a functional GUI, implemented with GTK, which allows the user to interact with the program and its
options through a menu and other navigational elements such as buttons and lists. The program will be functional on the
Linux Operating System.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;A Haiku is a type of poem in which there are three lines in a 5-7-5 format. The first line should contain five syllables,
seven for the second, and five for the third. The program will accept three lines, and by utilizing the ‘Words’ API, determine
whether or not the user actually followed the proper Haiku format as stated. If the user does not follow the proper format, the
program will identify which line(s) are incorrect, and offer suggestions to fix the line(s). Couplets are two-line poems that
end with a rhyming word, which the program will also identify possible rhymes for, suggesting options to create a valid poem.
