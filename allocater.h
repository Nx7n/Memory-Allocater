#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<assert.h>
#include<errno.h>
#include<inttypes.h>

#define MAX 100

#define public __attribute__((visibility("default")))
#define private static
#define packed __attribute__((__packed__))
#define unused __attribute__((__unused__))
#define Maxwords (((1024*1024*1024)/8)-1)
#define ZERO_WORDS 1073741823

#define ErrNoErr 0
#define ErrNoMem 1
#define ErrUnknown 2
#define ErrFree 8
typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long long int int64;
typedef unsigned _BitInt(128) int128;
typedef void heap;
typedef int64 word;

struct packed s_header{
    word w:62;
    bool alloced:1;
    bool unused reserved:1;
};
typedef struct packed s_header header;

#define $1 (int8 *)
#define $2 (int16 )
#define $4 (int32 )
#define $8 (int64)
#define $16 (int128 )
#define $c (char *)
#define $i (int )
#define $v (void *) 
#define $h (header *)

#define reterr(x)  do{ \
	errno = (x); \
 	return $v 0; \
} while(false) 

#define findBlock(x) findBlock_($h memspace, (x), 0)
#define show() show_($h memspace)
#define allocK(x) alloc((x)*1024)
#define allocM(x) alloc((x)*(1024*1024))
#define allocG(x) allocM((x)*(1024))

public void zero(int8*, int16);
public bool destroy(void*);
private void show_(header*);
private header *findBlock_(header*, word, word);
private void *mkalloc(word, header*);
public void *alloc(int64);
int main(int, char**);

