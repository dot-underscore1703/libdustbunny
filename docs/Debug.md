# Debug Documentation
## DUSTBUNNY_DEBUG
```c
#define DUSTBUNNY_DEBUG(fmt, ...) printf("dustbunny: DEBUG: " fmt "\n", ##__VA_ARGS__);
```
A macro for debugging functions.
Will check the `is_debug` variable in the debug header file, if it is 1, it will print the text, will not otherwise.
Should be the same as printf usage-wise.
## is_debug
```c
int is_debug;
```
An integer defined in the debug header file. It is used in the DUSTBUNNY_DEBUG macro.
To enable debugging, set it to 1. To disable debugging, set it to a number other than 1 (preferably 0).
It defaults to 0.
