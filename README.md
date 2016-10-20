libchelpers.so
==========

Shared library containing some functions I usually use in my projects.

* Linked list related functions
* Split strings & join them back
* xfunctions (calls that will call `exit()` uppon error)

How to compile this library:
---

`make`

How to link your program against this library:
---

`gcc <your .{c,o} files -L path/to/chelpers/directory -lchelpers`
