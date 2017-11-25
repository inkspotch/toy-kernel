bits 32

MAGIC equ 0x1BADB002
MBALIGN equ 1<<0
MEMINFO equ 1<<1
FLAGS equ MBALIGN | MEMINFO

section .multiboot
align 4
  dd MAGIC
  dd FLAGS
  dd -(MAGIC + FLAGS) ;checksum. m+f+c should be zero

section .bss
align 16
stack_bottom:
resb 16384
stack_top:

section .text

global start:function (start.end - start)
start:
  cli
  mov esp, stack_top

  extern kmain
  call kmain
  hlt
.end:
