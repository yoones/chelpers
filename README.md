libchelpers.so
==========

Shared library containing some functions I usually use in my projects.

* Linked list related functions
* Split strings & join them back
* xfunctions (calls that will call `exit()` uppon error)

How to compile this library:
---

`make`


How to compile and link your program against this library:
---

`gcc <your .{c,o} files -I path/to/chelpers_directory/include -L path/to/chelpers_directory -lchelpers`
