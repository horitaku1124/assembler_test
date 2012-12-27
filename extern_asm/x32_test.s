	bits 32
	global _add
	global _sub
	global _mul
	global _div
	global _fadd
	global _fsub
	global _fmul
	global _fdiv

    ;; start program area
    section .text

    ;; global functions

_add: ; 二つの引数を足す
    MOV		EDX,[ESP+4]
    ADD		EDX, [ESP+8]
    MOV		EAX, EDX
    RET

_sub: ; 二つの引数をかける
    MOV		EDX,[ESP+4]
    sub		EDX, [ESP+8]
    MOV		EAX, EDX
    RET

_mul: ; 二つの引数をかける
    MOV		eax,[ESP+4]
    mov		ebx,[ESP+8]
    mul		ebx
    RET

_div: ; 二つの引数をかける
    MOV		eax,[ESP+4]
    mov		ebx,[ESP+8]
    div		ebx
    RET

_fadd: ; 2つの実数を足す
	push	ebp
	mov		ebp, esp
	fld		DWORD [ebp+8]
	fadd	DWORD [ebp+12]
	pop		ebp
    RET

_fsub: ; 2つの実数を引く
	push	ebp
	mov		ebp, esp
	fld		DWORD [ebp+8]
	fsub	DWORD [ebp+12]
	pop		ebp
    RET

_fmul: ; 2つの実数を掛ける
	push	ebp
	mov		ebp, esp
	fld		DWORD [ebp+8]
	fmul	DWORD [ebp+12]
	pop		ebp
    RET

_fdiv: ; 2つの実数を割る
	push	ebp
	mov		ebp, esp
	fld		DWORD [ebp+8]
	fdiv	DWORD [ebp+12]
	pop		ebp
    RET
