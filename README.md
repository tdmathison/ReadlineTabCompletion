# ReadlineTabCompletion
Example of tab completion using the Readline C library.  This also shows how to tab complete sub-commands.

```
[ciph34block@ciph34block ~]$ ./ReadlineExample 
shell > help 
Simple shell using readline with multiple levels of tab completion

Core Commands
=============

    Command    Description
    -------    -----------
    help       Shows this menu
    show       Shows options and information
    exit       Exits this shell

shell > show 
info     options  
shell > show options 
OPTION 1: X
OPTION 2: Y

shell > show info 
This is just an example command where you can tab
complete after tab completing an initial command

shell > exit
```