# 563 Generic Functions

A library of functions for all of your needs! These should work with any robot, provided you modify them in a few key places.

##Editing the Libraries and Your Own Files
###Your Code
Here's what you need to change in your own code to use these libraries:
1. Insert `#include` statements for every library
  1. To do this, underneath the automatic `#include` statement created by the Competition Template (or above PreAuton or similar task), use `#include <file name>`. If the file is in a different spot than your main code, also use the file path like `include path/to/file/<file name>`. [![git1.png](https://s23.postimg.org/e7z521ee3/git1.png)](https://postimg.org/image/3xwq2soif/).

2. Add in `startTask()`
  1. Depending on where you want to use these functions, you can include them in PreAuton (for choosing autons with the LCD), Auton, or User Control sections
