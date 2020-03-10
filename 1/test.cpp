#include <iostream>
#include "allocator.h"
#include <stdlib.h>
#include <stdio.h>
#include "cstring"


int main() {
    Allocator allocator(200);
    char *a = allocator.alloc(200);//Allocated 200 bytes, total alloc usage is 200 bytes
    char *b = allocator.alloc(100);//    Too much memory required, only 0 bytes is available
    char *c = allocator.alloc(0);//    0 bytes allocated
    allocator.reset(); //    Reset completed, 200 bytes is available
    char *d = allocator.alloc(300); //    Too much memory required, only 200 bytes is available
    char *e = allocator.alloc(0); //    0 bytes allocated
    char *f = allocator.alloc(150); //    Allocated 150 bytes, total alloc usage is 150 bytes
    char *h = allocator.alloc(50); //    Allocated 50 bytes, total alloc usage is 200 bytes
    allocator.reset(); //    Reset completed, 200 bytes is available
    char *k = allocator.alloc(-30); //    0 bytes allocated
    char *l = allocator.alloc(30); //    Allocated 30 bytes, total alloc usage is 30 bytes
    char *m = allocator.alloc(40); //    Allocated 40 bytes, total alloc usage is 70 bytes
    char *n = allocator.alloc(130); //    Allocated 130 bytes, total alloc usage is 200 bytes
    allocator.reset(); //    Reset completed, 200 bytes is available

}
