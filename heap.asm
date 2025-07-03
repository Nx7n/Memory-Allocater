bits 64
global memspace
%define Heapsize ((1024*1024*1024)/8)

section .data alloc noexec write progbits
	memspace:
		dq _memspace

section .heap alloc noexec write nobits
    _memspace: 
        heapsize equ Heapsize
        resq heapsize

section .note.GNU-stack noalloc
