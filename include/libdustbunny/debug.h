#ifndef LDB_DEBUG_H
#define LDB_DEBUG_H


#define DUSTBUNNY_DEBUG(fmt, ...) printf("dustbunny: DEBUG: " fmt "\n", ##__VA_ARGS__);

int is_debug;

#endif
