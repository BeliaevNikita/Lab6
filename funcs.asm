section .data
    x dd 8.0
    c1 dd 3.0
    c2 dd -2.0
    
section .rodata
    lc db '%f'
    
section .text
extern printf
global f1
global f2
global f3
global main

;main:
 ;   push ebp
  ;  mov ebp, esp
   ; and esp, 0xfffffff0
    ;sub esp, 32
    ;finit
    ;push dword [x]
    ;call f3
    ;mov dword [esp], lc
    ;fstp qword [esp+4]
    ;call printf
    ;xor eax, eax
    ;leave
    ;ret

;f1:
    
f2:
    fld1
    fld dword [esp+4]
    fdivp
    ret

f3:
    fld dword [esp+4]
    fld dword [c1]
    faddp
    fld dword [c2]  
    fmulp
    fld dword [c1]
    fdivp
    ret