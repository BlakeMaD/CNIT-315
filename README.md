# CNIT-315
Project for Purdue's CNIT 315.

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

# UI implementation
Note: the UI and implementation of the gtk package has not been completed, to run the project in its current state, compile using gcc in your preferred linux provider.

## Linux Installation
Note: Linux operations were completed using Ubuntu 20.04 (https://ubuntu.com/download/desktop) on Oracle VMware VirtualBox (https://www.virtualbox.org/wiki/Downloads)

To install gtk and all dependencies necessary for the gui, run ```sudo apt-get install libgtk-3-dev```

To compile the completed c program with gcc, run ``    gcc `pkg-config --cflags gtk+-3.0` -o example-0 example-0.c `pkg-config --libs gtk+-3.0` ``
where ``example-0`` and ``example-0.c`` can be replaced with the compiled program and completed c file respectively.

## Windows Installation
1. visit https://www.msys2.org/ to download the linux like environment for Windows
2. Install GTK3 and its dependencies. Open a MSYS2 shell, and run: ``pacman -S mingw-w64-x86_64-gtk3``
3. Installing development tools like gcc may be necessary, to install gcc and other development tools, run: ``pacman -S mingw-w64-x86_64-toolchain base-devel`` 
