all:

asm64:
	gcc -o x64_test_c.o -c x64_test.c
	nasm -f elf64 -o x64_test_s.o x64_test.s
	gcc -o x64_test x64_test_c.o x64_test_s.o

asm32:
	gcc -o x32_test_c.o -c x32_test.c
	nasm -f elf32 -o x32_test_s.o x32_test.s
	gcc -o x32_test x32_test_c.o x32_test_s.o
