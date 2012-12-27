	bits 64
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

_add:
 ; rdi(引数1)をrax(戻り値)に格納
	mov    rax, rdi
 ; rsi(引数2)をraxに加算
	add    rax, rsi
    RET
	
_sub:
	mov    rax, rdi
	sub    rax, rsi
    RET

_mul:
	mov    rax, rdi
	imul    rax, rsi
    RET

_div:
	mov    rax, rdi
	mov    rbx, rsi
 ; 符号拡張した値をedxに格納
	cdq
	idiv    rbx
    RET

	
_fadd:
 ;xmm1をxmm0に加算し、xmm0に格納
	addss xmm0, xmm1
	ret

_fsub:
	subss xmm0, xmm1
	ret

_fmul:
	mulss xmm0, xmm1
	ret

_fdiv:
	divss xmm0, xmm1
	ret