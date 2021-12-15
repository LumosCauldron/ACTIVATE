	.file	"tracer.c"
	.text
	.globl	orientation
	.bss
	.type	orientation, @object
	.size	orientation, 1
orientation:
	.zero	1
	.globl	architecture
	.type	architecture, @object
	.size	architecture, 1
architecture:
	.zero	1
	.text
	.globl	MOD
	.type	MOD, @function
MOD:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	cqto
	idivq	-16(%rbp)
	movq	%rdx, %rax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	notq	%rax
	shrq	$63, %rax
	movzbl	%al, %eax
	movl	%edx, %ecx
	imull	%eax, %ecx
	movq	-8(%rbp), %rax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	cltq
	cqto
	idivq	-16(%rbp)
	movq	-16(%rbp), %rax
	subq	%rdx, %rax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	shrq	$63, %rax
	movzbl	%al, %eax
	imull	%edx, %eax
	addl	%ecx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	MOD, .-MOD
	.section	.rodata
.LC0:
	.string	"NULLPTR GIVEN TO PRINT"
	.text
	.globl	PRINT
	.type	PRINT, @function
PRINT:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L4
	leaq	.LC0(%rip), %rdi
	call	THROW
.L4:
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	puts@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	PRINT, .-PRINT
	.globl	EXIT
	.type	EXIT, @function
EXIT:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	cmpb	$0, -4(%rbp)
	je	.L7
	movl	$0, %edi
	call	exit@PLT
.L7:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	EXIT, .-EXIT
	.globl	THROW
	.type	THROW, @function
THROW:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	PRINT
	movl	$9, %edi
	call	exit@PLT
	.cfi_endproc
.LFE8:
	.size	THROW, .-THROW
	.section	.rodata
.LC1:
	.string	"MALLOC ERROR"
	.text
	.globl	MALLOC
	.type	MALLOC, @function
MALLOC:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	$0, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L10
	leaq	.LC1(%rip), %rdi
	call	PRINT
	movl	$1, %edi
	call	EXIT
.L10:
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	MALLOC, .-MALLOC
	.section	.rodata
.LC2:
	.string	"REALLOC ERROR"
	.text
	.globl	REALLOC
	.type	REALLOC, @function
REALLOC:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	realloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L13
	leaq	.LC2(%rip), %rdi
	call	PRINT
	movl	$1, %edi
	call	EXIT
.L13:
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	REALLOC, .-REALLOC
	.section	.rodata
.LC3:
	.string	"CALLOC ERROR"
	.text
	.globl	CALLOC
	.type	CALLOC, @function
CALLOC:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	$0, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	movl	$1, %edi
	call	calloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L16
	leaq	.LC3(%rip), %rdi
	call	PRINT
	movl	$1, %edi
	call	EXIT
.L16:
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	CALLOC, .-CALLOC
	.globl	arch
	.type	arch, @function
arch:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movb	$64, architecture(%rip)
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	arch, .-arch
	.globl	stackorient
	.type	stackorient, @function
stackorient:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movb	$7, -17(%rbp)
	movl	$1, %edi
	call	MALLOC
	movq	%rax, -16(%rbp)
	leaq	-17(%rbp), %rax
	cmpq	%rax, -16(%rbp)
	jnb	.L20
	movb	$1, orientation(%rip)
	jmp	.L23
.L20:
	movb	$2, orientation(%rip)
.L23:
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L22
	call	__stack_chk_fail@PLT
.L22:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	stackorient, .-stackorient
	.globl	FREE
	.type	FREE, @function
FREE:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movb	$7, -9(%rbp)
	movzbl	orientation(%rip), %eax
	cmpb	$1, %al
	jne	.L25
	leaq	-9(%rbp), %rax
	cmpq	%rax, -24(%rbp)
	jb	.L31
.L25:
	movzbl	orientation(%rip), %eax
	cmpb	$2, %al
	jne	.L32
	leaq	-9(%rbp), %rax
	cmpq	%rax, -24(%rbp)
	jnb	.L32
.L31:
	nop
.L26:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L24
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free@PLT
	movq	-24(%rbp), %rax
	movq	$0, (%rax)
	jmp	.L24
.L32:
	nop
.L24:
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L30
	call	__stack_chk_fail@PLT
.L30:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	FREE, .-FREE
	.globl	PLN
	.type	PLN, @function
PLN:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	jmp	.L34
.L35:
	movl	$10, %edi
	call	putchar@PLT
	movzbl	-4(%rbp), %eax
	subl	$1, %eax
	movb	%al, -4(%rbp)
.L34:
	cmpb	$0, -4(%rbp)
	jns	.L35
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	PLN, .-PLN
	.globl	goodptr
	.type	goodptr, @function
goodptr:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, %eax
	movb	%al, -20(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L37
	cmpb	$101, -20(%rbp)
	jne	.L38
	cmpq	$0, -16(%rbp)
	je	.L39
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	PRINT
.L39:
	movl	$0, %eax
	jmp	.L40
.L38:
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	THROW
.L37:
	movl	$1, %eax
.L40:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	goodptr, .-goodptr
	.section	.rodata
	.align 8
.LC4:
	.string	"NULLPTR PTR GIVEN TO PRINTBYTES"
.LC5:
	.string	"\n%lld in length\n"
	.text
	.globl	PRINTBYTES
	.type	PRINTBYTES, @function
PRINTBYTES:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	$101, %edx
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	testb	%al, %al
	je	.L46
	movq	$0, -8(%rbp)
	jmp	.L44
.L45:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %edi
	call	putchar@PLT
	addq	$1, -8(%rbp)
.L44:
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	cmpq	%rax, %rdx
	ja	.L45
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC5(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %edi
	call	PLN
	jmp	.L41
.L46:
	nop
.L41:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	PRINTBYTES, .-PRINTBYTES
	.section	.rodata
	.align 8
.LC6:
	.string	"NULLPTR PTR GIVEN TO PRINTHEXBYTES"
.LC7:
	.string	"%x "
.LC8:
	.string	"%x  "
	.text
	.globl	PRINTHEXBYTES
	.type	PRINTHEXBYTES, @function
PRINTHEXBYTES:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	$101, %edx
	leaq	.LC6(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	testb	%al, %al
	je	.L55
	movq	$0, -8(%rbp)
	jmp	.L50
.L54:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$15, %al
	jbe	.L51
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC7(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L52
.L51:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, %esi
	leaq	.LC8(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L52:
	movq	-8(%rbp), %rcx
	movabsq	$3279421168659475843, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	sarq	$3, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	addq	%rax, %rax
	addq	%rdx, %rax
	movq	%rax, %rdx
	salq	$4, %rdx
	subq	%rax, %rdx
	subq	%rdx, %rcx
	movq	%rcx, %rdx
	testq	%rdx, %rdx
	jne	.L53
	cmpq	$0, -8(%rbp)
	je	.L53
	movl	$1, %edi
	call	PLN
.L53:
	addq	$1, -8(%rbp)
.L50:
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	cmpq	%rax, %rdx
	ja	.L54
	movl	$0, %edi
	call	PLN
	jmp	.L47
.L55:
	nop
.L47:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	PRINTHEXBYTES, .-PRINTHEXBYTES
	.globl	countuntilnul
	.type	countuntilnul, @function
countuntilnul:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
	movq	%rdi, -16(%rbp)
	movl	$0, %ebx
	jmp	.L57
.L58:
	addq	$1, %rbx
.L57:
	movq	-16(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -16(%rbp)
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L58
	movl	%ebx, %eax
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	countuntilnul, .-countuntilnul
	.section	.rodata
	.align 8
.LC9:
	.string	"NULLPTR S1 GIVEN TO BYTESCMP_WNUL"
	.align 8
.LC10:
	.string	"NULLPTR S2 GIVEN TO BYTESCMP_WNUL"
	.text
	.globl	bytescmp_wnul
	.type	bytescmp_wnul, @function
bytescmp_wnul:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	leaq	.LC9(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	-32(%rbp), %rax
	movl	$0, %edx
	leaq	.LC10(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	countuntilnul
	movslq	%eax, %rbx
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	countuntilnul
	cltq
	cmpq	%rax, %rbx
	je	.L63
	movl	$1, %eax
	jmp	.L62
.L65:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %edx
	movq	-32(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	je	.L64
	movl	$1, %eax
	jmp	.L62
.L64:
	addq	$1, -24(%rbp)
	addq	$1, -32(%rbp)
.L63:
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L65
	movl	$0, %eax
.L62:
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	bytescmp_wnul, .-bytescmp_wnul
	.section	.rodata
	.align 8
.LC11:
	.string	"NULLPTR S1 GIVEN TO BYTESCPY_WNUL"
	.align 8
.LC12:
	.string	"NULLPTR S2 GIVEN TO BYTESCPY_WNUL"
	.text
	.globl	bytescpy_wnul
	.type	bytescpy_wnul, @function
bytescpy_wnul:
.LFB21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	leaq	.LC11(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	-32(%rbp), %rax
	movl	$101, %edx
	leaq	.LC12(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	testb	%al, %al
	jne	.L67
	movl	$0, %eax
	jmp	.L68
.L67:
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.L69
.L70:
	movq	-32(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -32(%rbp)
	movzbl	(%rax), %edx
	movq	-24(%rbp), %rax
	movb	%dl, (%rax)
	addq	$1, -24(%rbp)
.L69:
	movq	-32(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L70
	movq	-32(%rbp), %rax
	movzbl	(%rax), %edx
	movq	-24(%rbp), %rax
	movb	%dl, (%rax)
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
.L68:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	bytescpy_wnul, .-bytescpy_wnul
	.section	.rodata
	.align 8
.LC13:
	.string	"NULLPTR DEST GIVEN TO NBYTESTO"
	.text
	.globl	nbytesto
	.type	nbytesto, @function
nbytesto:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	%rdx, -104(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	movq	-88(%rbp), %rax
	movl	$0, %edx
	leaq	.LC13(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	-96(%rbp), %rax
	movl	$101, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	goodptr
	testb	%al, %al
	je	.L72
	movq	-88(%rbp), %rax
	cmpq	-96(%rbp), %rax
	jne	.L73
.L72:
	movq	-88(%rbp), %rax
	jmp	.L74
.L73:
	movq	-88(%rbp), %rax
	cmpq	-96(%rbp), %rax
	jbe	.L75
	movq	-96(%rbp), %rdx
	movq	-104(%rbp), %rax
	addq	%rdx, %rax
	cmpq	%rax, -88(%rbp)
	jnb	.L75
	movq	%rsp, %rax
	movq	%rax, %rbx
	movq	-104(%rbp), %rax
	movq	%rax, %rdx
	subq	$1, %rdx
	movq	%rdx, -72(%rbp)
	movq	%rax, %r14
	movl	$0, %r15d
	movq	%rax, %r12
	movl	$0, %r13d
	movl	$16, %edx
	subq	$1, %rdx
	addq	%rdx, %rax
	movl	$16, %esi
	movl	$0, %edx
	divq	%rsi
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$0, %rax
	movq	%rax, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	-104(%rbp), %rdx
	movq	-96(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	nbytesto
	movq	%rax, -96(%rbp)
	movq	%rbx, %rsp
.L75:
	movq	$-1, %rbx
	jmp	.L76
.L77:
	movq	%rbx, %rdx
	movq	-96(%rbp), %rax
	addq	%rdx, %rax
	movq	%rbx, %rcx
	movq	-88(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
.L76:
	addq	$1, %rbx
	movq	%rbx, %rax
	cmpq	%rax, -104(%rbp)
	ja	.L77
	movq	-88(%rbp), %rax
.L74:
	movq	-56(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L78
	call	__stack_chk_fail@PLT
.L78:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	nbytesto, .-nbytesto
	.globl	containschar
	.type	containschar, @function
containschar:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movq	%rsi, -16(%rbp)
	movl	%edx, -8(%rbp)
	movb	%al, -4(%rbp)
	jmp	.L80
.L82:
	subl	$1, -8(%rbp)
	movl	-8(%rbp), %eax
	movslq	%eax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, -4(%rbp)
	jne	.L80
	movl	$1, %eax
	jmp	.L81
.L80:
	cmpl	$0, -8(%rbp)
	jne	.L82
	movl	$0, %eax
.L81:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE23:
	.size	containschar, .-containschar
	.globl	containschars
	.type	containschars, @function
containschars:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	%rdx, -32(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	countuntilnul
	movl	%eax, %ebx
	jmp	.L84
.L86:
	subq	$1, -32(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movq	-16(%rbp), %rcx
	movl	%ebx, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	containschar
	testb	%al, %al
	je	.L84
	movl	$1, %eax
	jmp	.L85
.L84:
	cmpq	$0, -32(%rbp)
	jne	.L86
	movl	$0, %eax
.L85:
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE24:
	.size	containschars, .-containschars
	.globl	findchar
	.type	findchar, @function
findchar:
.LFB25:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
	movl	%edi, %eax
	movq	%rsi, -24(%rbp)
	movq	%rdx, -32(%rbp)
	movb	%al, -12(%rbp)
	movq	$-1, %rbx
	jmp	.L88
.L90:
	movq	%rbx, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, -12(%rbp)
	jne	.L88
	movq	%rbx, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	jmp	.L89
.L88:
	addq	$1, %rbx
	cmpq	-32(%rbp), %rbx
	jl	.L90
	movl	$0, %eax
.L89:
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE25:
	.size	findchar, .-findchar
	.globl	findchars
	.type	findchars, @function
findchars:
.LFB26:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	countuntilnul
	movl	%eax, %r12d
	movq	$-1, %rbx
	jmp	.L92
.L94:
	movq	%rbx, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movq	-24(%rbp), %rcx
	movl	%r12d, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	containschar
	testb	%al, %al
	je	.L92
	movq	%rbx, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	jmp	.L93
.L92:
	addq	$1, %rbx
	cmpq	-40(%rbp), %rbx
	jl	.L94
	movl	$0, %eax
.L93:
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE26:
	.size	findchars, .-findchars
	.globl	zeroarray
	.type	zeroarray, @function
zeroarray:
.LFB27:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	$-1, %rbx
	jmp	.L96
.L97:
	movq	%rbx, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
.L96:
	addq	$1, %rbx
	cmpq	-24(%rbp), %rbx
	jl	.L97
	nop
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE27:
	.size	zeroarray, .-zeroarray
	.globl	dynamic_bytes
	.type	dynamic_bytes, @function
dynamic_bytes:
.LFB28:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	cmpl	$0, -28(%rbp)
	jns	.L99
	movl	$0, %eax
	jmp	.L100
.L99:
	movl	$16, %edi
	call	MALLOC
	movq	%rax, -8(%rbp)
	movl	-28(%rbp), %eax
	addl	$1, %eax
	cltq
	movq	%rax, %rdi
	call	CALLOC
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	cmpq	$0, -24(%rbp)
	je	.L101
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	-24(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	nbytesto
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
.L101:
	movl	-28(%rbp), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
.L100:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE28:
	.size	dynamic_bytes, .-dynamic_bytes
	.globl	free_bytes
	.type	free_bytes, @function
free_bytes:
.LFB29:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L104
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	FREE
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	$0, 8(%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	$0, (%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	FREE
	movq	$0, -8(%rbp)
.L104:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE29:
	.size	free_bytes, .-free_bytes
	.globl	copy_bytes
	.type	copy_bytes, @function
copy_bytes:
.LFB30:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L106
	movl	$0, %eax
	jmp	.L107
.L106:
	movq	-40(%rbp), %rax
	movq	(%rax), %rbx
	movl	$16, %edi
	call	MALLOC
	movq	%rax, -24(%rbp)
	leaq	1(%rbx), %rax
	movq	%rax, %rdi
	call	CALLOC
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L108
	movq	-40(%rbp), %rax
	movq	8(%rax), %rcx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rbx, %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	nbytesto
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 8(%rax)
.L108:
	movq	-24(%rbp), %rax
	movq	%rbx, (%rax)
	movq	-24(%rbp), %rax
.L107:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE30:
	.size	copy_bytes, .-copy_bytes
	.globl	eqstr
	.type	eqstr, @function
eqstr:
.LFB31:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	bytescmp_wnul
	testb	%al, %al
	sete	%al
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE31:
	.size	eqstr, .-eqstr
	.globl	eqbytes
	.type	eqbytes, @function
eqbytes:
.LFB32:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	-16(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rdx
	je	.L112
	movl	$0, %eax
	jmp	.L113
.L112:
	movl	$0, %ebx
	jmp	.L114
.L116:
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rbx, %rax
	movzbl	(%rax), %edx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rbx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	je	.L115
	movl	$0, %eax
	jmp	.L113
.L115:
	addq	$1, %rbx
.L114:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rbx
	jb	.L116
	movl	$1, %eax
.L113:
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE32:
	.size	eqbytes, .-eqbytes
	.globl	extractstr
	.type	extractstr, @function
extractstr:
.LFB33:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	cmpq	$0, -24(%rbp)
	je	.L118
	cmpq	$0, -32(%rbp)
	jne	.L119
.L118:
	movl	$0, %eax
	jmp	.L120
.L119:
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	cmpq	%rax, %rdx
	jne	.L121
	movl	$0, %eax
	jmp	.L120
.L121:
	movq	-24(%rbp), %rdx
	movq	-32(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	cltq
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	dynamic_bytes
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
.L120:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE33:
	.size	extractstr, .-extractstr
	.globl	fastmatch
	.type	fastmatch, @function
fastmatch:
.LFB34:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	.cfi_offset 3, -24
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	%rdx, -32(%rbp)
	movl	$0, %ebx
.L123:
	subq	$1, -32(%rbp)
	movq	-16(%rbp), %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	movq	-24(%rbp), %rcx
	movq	-32(%rbp), %rax
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	sete	%al
	movl	%eax, %ebx
	testb	%bl, %bl
	je	.L124
	cmpq	$0, -32(%rbp)
	je	.L124
	jmp	.L123
.L124:
	cmpq	$0, -32(%rbp)
	jne	.L125
	testb	%bl, %bl
	je	.L125
	movl	$1, %eax
	jmp	.L126
.L125:
	movl	$0, %eax
.L126:
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE34:
	.size	fastmatch, .-fastmatch
	.globl	substr
	.type	substr, @function
substr:
.LFB35:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L129
	cmpq	$0, -48(%rbp)
	jne	.L130
.L129:
	movl	$0, %eax
	jmp	.L131
.L130:
	movq	-40(%rbp), %rax
	movq	(%rax), %rbx
	movq	-48(%rbp), %rax
	movq	(%rax), %r12
	cmpq	%r12, %rbx
	jbe	.L132
	movl	$0, %eax
	jmp	.L131
.L132:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	jmp	.L133
.L135:
	movq	-40(%rbp), %rax
	movq	8(%rax), %rcx
	movq	-24(%rbp), %rax
	movq	%rbx, %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fastmatch
	testb	%al, %al
	je	.L134
	movl	%ebx, %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	dynamic_bytes
	jmp	.L131
.L134:
	addq	$1, -24(%rbp)
.L133:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%r12, %rdx
	subq	%rbx, %rdx
	addq	%rdx, %rax
	cmpq	%rax, -24(%rbp)
	jbe	.L135
	movl	$0, %eax
.L131:
	addq	$32, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE35:
	.size	substr, .-substr
	.globl	substr_loc
	.type	substr_loc, @function
substr_loc:
.LFB36:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L137
	cmpq	$0, -48(%rbp)
	jne	.L138
.L137:
	movl	$0, %eax
	jmp	.L139
.L138:
	movq	-40(%rbp), %rax
	movq	(%rax), %rbx
	movq	-48(%rbp), %rax
	movq	(%rax), %r12
	cmpq	%r12, %rbx
	jbe	.L140
	movl	$0, %eax
	jmp	.L139
.L140:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	jmp	.L141
.L143:
	movq	-40(%rbp), %rax
	movq	8(%rax), %rcx
	movq	-24(%rbp), %rax
	movq	%rbx, %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	fastmatch
	testb	%al, %al
	je	.L142
	movq	-24(%rbp), %rax
	jmp	.L139
.L142:
	addq	$1, -24(%rbp)
.L141:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%r12, %rdx
	subq	%rbx, %rdx
	addq	%rdx, %rax
	cmpq	%rax, -24(%rbp)
	jbe	.L143
	movl	$0, %eax
.L139:
	addq	$32, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE36:
	.size	substr_loc, .-substr_loc
	.globl	numsubstr
	.type	numsubstr, @function
numsubstr:
.LFB37:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$48, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movl	$0, %ebx
	movq	-64(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	substr_loc
	movq	%rax, -40(%rbp)
	movq	-64(%rbp), %rax
	movq	(%rax), %r12
	jmp	.L145
.L148:
	movq	-40(%rbp), %rax
	movq	%rax, -32(%rbp)
	movl	%r12d, %ecx
	movq	-40(%rbp), %rdx
	movq	-64(%rbp), %rax
	movq	8(%rax), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, %edx
	movq	-40(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	dynamic_bytes
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	substr_loc
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	je	.L151
	movq	-40(%rbp), %rdx
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	movslq	%eax, %rdx
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	addq	%rax, %rdx
	movq	-32(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -40(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	free_bytes
	addl	$1, %ebx
.L145:
	cmpq	$0, -40(%rbp)
	jne	.L148
	jmp	.L147
.L151:
	nop
.L147:
	movl	%ebx, %eax
	movq	-24(%rbp), %rbx
	xorq	%fs:40, %rbx
	je	.L150
	call	__stack_chk_fail@PLT
.L150:
	addq	$48, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE37:
	.size	numsubstr, .-numsubstr
	.section	.rodata
	.align 8
.LC14:
	.string	"NULLPTR ORIGIN GIVEN TO DELSUBSTR"
	.text
	.globl	delsubstr
	.type	delsubstr, @function
delsubstr:
.LFB38:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$48, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	-40(%rbp), %rax
	movl	$0, %edx
	leaq	.LC14(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	-40(%rbp), %rax
	movq	(%rax), %rcx
	movq	-48(%rbp), %rdx
	movq	-56(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	cltq
	cmpq	%rax, %rcx
	jne	.L153
	movq	-40(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	FREE
	movq	-40(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-40(%rbp), %rax
	movq	$0, (%rax)
	movl	$0, %eax
	jmp	.L154
.L153:
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movl	%eax, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	movl	%edx, %ebx
	xorl	%eax, %ebx
	subl	%eax, %ebx
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movl	%eax, %ecx
	movq	-56(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cltd
	xorl	%edx, %eax
	subl	%edx, %eax
	subl	%eax, %ecx
	movl	%ecx, %eax
	movl	%eax, %r12d
	leal	(%rbx,%r12), %eax
	addl	$1, %eax
	cltq
	movq	%rax, %rdi
	call	CALLOC
	movq	%rax, -24(%rbp)
	movslq	%ebx, %rdx
	movq	-40(%rbp), %rax
	movq	8(%rax), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	nbytesto
	movslq	%r12d, %rdx
	movslq	%ebx, %rcx
	movq	-24(%rbp), %rax
	addq	%rax, %rcx
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	nbytesto
	leal	(%rbx,%r12), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-40(%rbp), %rax
	addq	$8, %rax
	movq	%rax, %rdi
	call	FREE
	movq	-40(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 8(%rax)
	leal	(%rbx,%r12), %eax
	movslq	%eax, %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
.L154:
	addq	$48, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE38:
	.size	delsubstr, .-delsubstr
	.globl	rmsubstr
	.type	rmsubstr, @function
rmsubstr:
.LFB39:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	substr_loc
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L156
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movq	-8(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	delsubstr
.L156:
	movq	-32(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE39:
	.size	rmsubstr, .-rmsubstr
	.globl	rmsubstr_loc
	.type	rmsubstr_loc, @function
rmsubstr_loc:
.LFB40:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	substr_loc
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L159
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movq	-8(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	delsubstr
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	jmp	.L160
.L159:
	movl	$0, %eax
.L160:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE40:
	.size	rmsubstr_loc, .-rmsubstr_loc
	.globl	rmsubstr_all
	.type	rmsubstr_all, @function
rmsubstr_all:
.LFB41:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$0, %ebx
.L162:
	movq	-48(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	rmsubstr_loc
	movq	%rax, -24(%rbp)
	addl	$1, %ebx
	cmpq	$0, -24(%rbp)
	jne	.L162
	subl	$1, %ebx
	movl	%ebx, %eax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE41:
	.size	rmsubstr_all, .-rmsubstr_all
	.globl	concatbytes
	.type	concatbytes, @function
concatbytes:
.LFB42:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%ecx, %eax
	movb	%dl, -52(%rbp)
	movb	%al, -56(%rbp)
	movl	$0, %ebx
	movq	-48(%rbp), %rax
	testq	%rax, %rax
	jne	.L165
	movl	$0, %eax
	jmp	.L166
.L165:
	movq	-40(%rbp), %rax
	testq	%rax, %rax
	je	.L167
	movq	-40(%rbp), %rax
	movq	(%rax), %rbx
.L167:
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	movl	%eax, %edx
	movl	%ebx, %eax
	addl	%eax, %edx
	cmpb	$0, -52(%rbp)
	setne	%al
	movzbl	%al, %eax
	addl	%edx, %eax
	movl	%eax, -28(%rbp)
	movl	-28(%rbp), %eax
	movl	%eax, %esi
	movl	$0, %edi
	call	dynamic_bytes
	movq	%rax, -24(%rbp)
	movq	-40(%rbp), %rax
	testq	%rax, %rax
	je	.L168
	testq	%rbx, %rbx
	je	.L168
	movq	-40(%rbp), %rax
	movq	8(%rax), %rcx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rbx, %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	nbytesto
.L168:
	cmpb	$0, -52(%rbp)
	je	.L169
	cmpb	$-1, -52(%rbp)
	setne	%al
	movzbl	%al, %eax
	movl	%eax, %esi
	movzbl	-52(%rbp), %ecx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	leaq	(%rax,%rbx), %rdx
	movl	%esi, %eax
	imull	%ecx, %eax
	movb	%al, (%rdx)
.L169:
	movq	-48(%rbp), %rax
	movq	(%rax), %rdx
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	-24(%rbp), %rcx
	movq	8(%rcx), %rcx
	cmpb	$0, -52(%rbp)
	setne	%sil
	movzbl	%sil, %esi
	addq	%rbx, %rsi
	addq	%rsi, %rcx
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	nbytesto
	movsbl	-56(%rbp), %eax
	cmpl	$2, %eax
	je	.L171
	cmpl	$3, %eax
	je	.L172
	cmpl	$1, %eax
	jne	.L174
	leaq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	free_bytes
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	free_bytes
	movq	-24(%rbp), %rax
	jmp	.L166
.L172:
	leaq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	free_bytes
	movq	-24(%rbp), %rax
	jmp	.L166
.L171:
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	free_bytes
	movq	-24(%rbp), %rax
	jmp	.L166
.L174:
	movq	-24(%rbp), %rax
.L166:
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE42:
	.size	concatbytes, .-concatbytes
	.globl	appendstr
	.type	appendstr, @function
appendstr:
.LFB43:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	addq	%rdx, %rax
	addq	$1, %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	REALLOC
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rcx
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	addq	%rax, %rcx
	movq	-16(%rbp), %rax
	movq	%rax, %rsi
	movq	%rcx, %rdi
	call	nbytesto
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	addq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE43:
	.size	appendstr, .-appendstr
	.section	.rodata
.LC15:
	.string	"NULLPTR STR GIVEN TO COPYSTR"
	.text
	.globl	copystr
	.type	copystr, @function
copystr:
.LFB44:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	leaq	.LC15(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	$1, %rax
	movq	%rax, %rdi
	call	MALLOC
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	leaq	1(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	nbytesto
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE44:
	.size	copystr, .-copystr
	.globl	appendctostr
	.type	appendctostr, @function
appendctostr:
.LFB45:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, %eax
	movq	%rsi, -32(%rbp)
	movb	%al, -20(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L179
	movq	$0, -8(%rbp)
	movl	$1, %edi
	call	MALLOC
	movq	%rax, -8(%rbp)
	movzbl	-20(%rbp), %edx
	movq	-8(%rbp), %rax
	movb	%dl, (%rax)
	movq	-8(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	dynamic_bytes
	jmp	.L180
.L179:
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	addq	$2, %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	REALLOC
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-32(%rbp), %rax
	movq	8(%rax), %rsi
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	leaq	1(%rax), %rcx
	movq	-32(%rbp), %rdx
	movq	%rcx, (%rdx)
	leaq	(%rsi,%rax), %rdx
	movzbl	-20(%rbp), %eax
	movb	%al, (%rdx)
	movq	-32(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-32(%rbp), %rax
.L180:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE45:
	.size	appendctostr, .-appendctostr
	.globl	prependctostr
	.type	prependctostr, @function
prependctostr:
.LFB46:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, %eax
	movq	%rsi, -32(%rbp)
	movb	%al, -20(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L182
	movq	$0, -8(%rbp)
	movl	$1, %edi
	call	MALLOC
	movq	%rax, -8(%rbp)
	movzbl	-20(%rbp), %edx
	movq	-8(%rbp), %rax
	movb	%dl, (%rax)
	movq	-8(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	dynamic_bytes
	jmp	.L183
.L182:
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	addq	$2, %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	REALLOC
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	leaq	1(%rax), %rcx
	movq	-32(%rbp), %rdx
	movq	%rcx, (%rdx)
	movq	-32(%rbp), %rdx
	movq	8(%rdx), %rcx
	movq	-32(%rbp), %rdx
	movq	8(%rdx), %rdx
	leaq	1(%rdx), %rdi
	movq	%rax, %rdx
	movq	%rcx, %rsi
	call	nbytesto
	movq	-32(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movzbl	-20(%rbp), %edx
	movb	%dl, (%rax)
	movq	-32(%rbp), %rax
.L183:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE46:
	.size	prependctostr, .-prependctostr
	.section	.rodata
	.align 8
.LC16:
	.string	"NULLPTR FILE STRING GIVEN TO UNPENDLEFT"
	.text
	.globl	unpendleft
	.type	unpendleft, @function
unpendleft:
.LFB47:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-24(%rbp), %rax
	movl	$0, %edx
	leaq	.LC16(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	subl	$1, %eax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	addq	$1, %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	dynamic_bytes
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	REALLOC
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	leaq	-1(%rax), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, (%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	8(%rax), %rcx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	nbytesto
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	free_bytes
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L186
	call	__stack_chk_fail@PLT
.L186:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE47:
	.size	unpendleft, .-unpendleft
	.section	.rodata
	.align 8
.LC17:
	.string	"NULLPTR FILE STRING GIVEN TO UNPENDRIGHT"
	.text
	.globl	unpendright
	.type	unpendright, @function
unpendright:
.LFB48:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$0, %edx
	leaq	.LC17(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	REALLOC
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	leaq	-1(%rax), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, (%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE48:
	.size	unpendright, .-unpendright
	.globl	getword
	.type	getword, @function
getword:
.LFB49:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$0, %r12d
	movl	$0, %ebx
	movq	$0, -24(%rbp)
	cmpq	$0, -48(%rbp)
	jne	.L192
	movl	$0, %eax
	jmp	.L191
.L205:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rbx, %rax
	movzbl	(%rax), %eax
	cmpb	$8, %al
	jbe	.L193
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rbx, %rax
	movzbl	(%rax), %eax
	cmpb	$13, %al
	jbe	.L194
.L193:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rbx, %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	jne	.L195
.L194:
	addq	$1, %rbx
	jmp	.L192
.L195:
	addl	$1, %r12d
	cmpl	-36(%rbp), %r12d
	jne	.L201
	jmp	.L197
.L200:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rdx
	movq	%rbx, %rax
	leaq	1(%rax), %rbx
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movq	-24(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	appendctostr
	movq	%rax, -24(%rbp)
.L197:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rbx, %rax
	movzbl	(%rax), %eax
	cmpb	$8, %al
	jbe	.L198
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rbx, %rax
	movzbl	(%rax), %eax
	cmpb	$13, %al
	jbe	.L199
.L198:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rbx, %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	je	.L199
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rbx
	jb	.L200
.L199:
	movq	-24(%rbp), %rax
	jmp	.L191
.L203:
	addq	$1, %rbx
.L201:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rbx, %rax
	movzbl	(%rax), %eax
	cmpb	$8, %al
	jbe	.L202
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rbx, %rax
	movzbl	(%rax), %eax
	cmpb	$13, %al
	jbe	.L192
.L202:
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	addq	%rbx, %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	je	.L192
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rbx
	jb	.L203
.L192:
	cmpl	-36(%rbp), %r12d
	jge	.L204
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rbx
	jb	.L205
.L204:
	movq	-24(%rbp), %rax
.L191:
	addq	$32, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE49:
	.size	getword, .-getword
	.globl	map_decnum_tostr
	.type	map_decnum_tostr, @function
map_decnum_tostr:
.LFB50:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 13, -24
	.cfi_offset 12, -32
	.cfi_offset 3, -40
	movq	%rdi, -56(%rbp)
	movl	%esi, -60(%rbp)
	movq	$0, -40(%rbp)
	movl	$1, %ebx
	movl	$0, %r12d
	jmp	.L207
.L208:
	movq	%rbx, %rax
	salq	$2, %rax
	addq	%rbx, %rax
	addq	%rax, %rax
	movq	%rax, %rbx
	addl	$1, %r12d
.L207:
	movq	-56(%rbp), %rax
	cqto
	idivq	%rbx
	testq	%rax, %rax
	jne	.L208
	movabsq	$7378697629483820647, %rdx
	movq	%rbx, %rax
	imulq	%rdx
	sarq	$2, %rdx
	movq	%rbx, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, %rbx
	cmpl	$0, -60(%rbp)
	setg	%al
	movzbl	%al, %eax
	imull	-60(%rbp), %eax
	subl	%r12d, %eax
	movl	%eax, %r13d
	leal	1(%r12), %eax
	addl	%r13d, %eax
	cltq
	movq	%rax, %rdi
	call	MALLOC
	movq	%rax, -40(%rbp)
	leal	(%r12,%r13), %eax
	movslq	%eax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movl	$0, %r12d
	jmp	.L209
.L210:
	movslq	%r12d, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movb	$48, (%rax)
	addl	$1, %r12d
.L209:
	cmpl	%r13d, %r12d
	jl	.L210
	jmp	.L211
.L212:
	movq	-56(%rbp), %rax
	cqto
	idivq	%rbx
	movl	%eax, %ecx
	movl	%r12d, %eax
	leal	1(%rax), %r12d
	movslq	%eax, %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	leal	48(%rcx), %edx
	movb	%dl, (%rax)
	movq	-56(%rbp), %rax
	cqto
	idivq	%rbx
	movq	%rdx, -56(%rbp)
	movabsq	$7378697629483820647, %rdx
	movq	%rbx, %rax
	imulq	%rdx
	sarq	$2, %rdx
	movq	%rbx, %rax
	sarq	$63, %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, %rbx
.L211:
	testq	%rbx, %rbx
	jne	.L212
	movq	-40(%rbp), %rax
	addq	$40, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE50:
	.size	map_decnum_tostr, .-map_decnum_tostr
	.section	.rodata
	.align 8
.LC18:
	.string	"NULLPTR STR GIVEN TO MAP_DECSTR_TOLONGLONGINT"
	.text
	.globl	map_decstr_tolonglongint
	.type	map_decstr_tolonglongint, @function
map_decstr_tolonglongint:
.LFB51:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, -56(%rbp)
	movq	-56(%rbp), %rax
	movl	$0, %edx
	leaq	.LC18(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movl	$0, %r13d
	movl	$256, %r15d
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	subq	$1, %rax
	movq	%rax, %rbx
	jmp	.L215
.L218:
	movq	-56(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rbx, %rdx
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %r12d
	movq	-56(%rbp), %rax
	movq	(%rax), %rax
	subq	$1, %rax
	movq	%rax, %r14
	jmp	.L216
.L217:
	imulq	%r15, %r12
	subq	$1, %r14
.L216:
	cmpq	%rbx, %r14
	jg	.L217
	orq	%r12, %r13
	subq	$1, %rbx
.L215:
	testq	%rbx, %rbx
	jns	.L218
	movq	%r13, %rax
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE51:
	.size	map_decstr_tolonglongint, .-map_decstr_tolonglongint
	.globl	reflectstr
	.type	reflectstr, @function
reflectstr:
.LFB52:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L221
	movq	-24(%rbp), %rax
	jmp	.L222
.L221:
	movl	$1, -4(%rbp)
	jmp	.L223
.L224:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rcx
	movl	-4(%rbp), %eax
	cltq
	subq	%rax, %rcx
	movq	%rcx, %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %ecx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rsi
	movq	-24(%rbp), %rax
	movq	(%rax), %rdi
	movl	-4(%rbp), %eax
	cltq
	subq	%rax, %rdi
	movq	%rdi, %rax
	addq	%rsi, %rax
	movzbl	(%rdx), %edx
	movb	%dl, (%rax)
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movl	%ecx, %esi
	subl	%eax, %esi
	movq	-24(%rbp), %rax
	movq	8(%rax), %rcx
	movl	-4(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -4(%rbp)
	movslq	%eax, %rdx
	addq	%rcx, %rdx
	movzbl	(%rdx), %ecx
	movq	-24(%rbp), %rdx
	movq	8(%rdx), %rdx
	cltq
	addq	%rdx, %rax
	leal	(%rcx,%rsi), %edx
	movb	%dl, (%rax)
.L223:
	movl	-4(%rbp), %eax
	movslq	%eax, %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rdx
	jb	.L224
	movq	-24(%rbp), %rax
.L222:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE52:
	.size	reflectstr, .-reflectstr
	.globl	ccipherstr
	.type	ccipherstr, @function
ccipherstr:
.LFB53:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L226
	movq	-40(%rbp), %rax
	jmp	.L227
.L226:
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %r12
	movl	$0, %ebx
	jmp	.L228
.L231:
	movslq	%ebx, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %edx
	movl	-44(%rbp), %eax
	addl	%edx, %eax
	cltq
	movl	$255, %esi
	movq	%rax, %rdi
	call	MOD
	movl	%eax, %ecx
	movslq	%ebx, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
	movslq	%ebx, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L229
	cmpl	$0, -44(%rbp)
	jle	.L229
	movslq	%ebx, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %edx
	addl	$1, %edx
	movb	%dl, (%rax)
.L229:
	movslq	%ebx, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L230
	cmpl	$0, -44(%rbp)
	jns	.L230
	movslq	%ebx, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movb	$-1, (%rax)
.L230:
	addl	$1, %ebx
.L228:
	movslq	%ebx, %rax
	cmpq	%rax, %r12
	ja	.L231
	movq	-40(%rbp), %rax
.L227:
	addq	$32, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE53:
	.size	ccipherstr, .-ccipherstr
	.globl	rotatestr
	.type	rotatestr, @function
rotatestr:
.LFB54:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 14, -24
	.cfi_offset 13, -32
	.cfi_offset 12, -40
	.cfi_offset 3, -48
	movq	%rdi, -56(%rbp)
	movl	%esi, %eax
	movl	%edx, -64(%rbp)
	movb	%al, -60(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -40(%rbp)
	xorl	%eax, %eax
	cmpq	$0, -56(%rbp)
	jne	.L233
	movl	$0, %eax
	jmp	.L238
.L233:
	movq	-56(%rbp), %rax
	movq	(%rax), %rbx
	movq	%rbx, %rdx
	movl	-64(%rbp), %eax
	cltq
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	MOD
	testl	%eax, %eax
	jne	.L235
	movq	-56(%rbp), %rax
	jmp	.L238
.L235:
	movq	%rbx, %rcx
	movsbl	-60(%rbp), %edx
	cmpb	$0, -60(%rbp)
	sete	%al
	movzbl	%al, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	imull	-64(%rbp), %eax
	cltq
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	MOD
	movl	%eax, %edx
	movl	%edx, %eax
	sarl	$31, %eax
	xorl	%eax, %edx
	movl	%edx, -64(%rbp)
	subl	%eax, -64(%rbp)
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	MALLOC
	movq	%rax, -48(%rbp)
	movl	$0, %r12d
	jmp	.L236
.L237:
	movq	-56(%rbp), %rax
	movq	8(%rax), %rdx
	movslq	%r12d, %rax
	leaq	(%rdx,%rax), %r13
	movq	-48(%rbp), %r14
	movq	%rbx, %rdx
	movl	-64(%rbp), %eax
	addl	%r12d, %eax
	cltq
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	MOD
	cltq
	leaq	(%r14,%rax), %rdx
	movzbl	0(%r13), %eax
	movb	%al, (%rdx)
	addl	$1, %r12d
.L236:
	movslq	%r12d, %rax
	cmpq	%rax, %rbx
	ja	.L237
	movq	-48(%rbp), %rcx
	movq	-56(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rbx, %rdx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	nbytesto
	movq	%rax, %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, 8(%rax)
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	FREE
	movq	-56(%rbp), %rax
.L238:
	movq	-40(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L239
	call	__stack_chk_fail@PLT
.L239:
	addq	$32, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE54:
	.size	rotatestr, .-rotatestr
	.globl	encrypt7
	.type	encrypt7, @function
encrypt7:
.LFB55:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L241
	movl	$0, %eax
	jmp	.L242
.L241:
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	shrq	%rax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	rotatestr
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	reflectstr
	movq	-8(%rbp), %rax
	movl	$77, %esi
	movq	%rax, %rdi
	call	ccipherstr
	movq	-8(%rbp), %rax
.L242:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE55:
	.size	encrypt7, .-encrypt7
	.globl	decrypt7
	.type	decrypt7, @function
decrypt7:
.LFB56:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L244
	movl	$0, %eax
	jmp	.L245
.L244:
	movq	-8(%rbp), %rax
	movl	$-77, %esi
	movq	%rax, %rdi
	call	ccipherstr
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	reflectstr
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	shrq	%rax
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	rotatestr
	movq	-8(%rbp), %rax
.L245:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE56:
	.size	decrypt7, .-decrypt7
	.section	.rodata
.LC19:
	.string	"%c\n"
	.text
	.globl	PRINTC
	.type	PRINTC, @function
PRINTC:
.LFB57:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, %eax
	movb	%al, -4(%rbp)
	movsbl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC19(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE57:
	.size	PRINTC, .-PRINTC
	.section	.rodata
.LC20:
	.string	"%d\n"
	.text
	.globl	PRINTN
	.type	PRINTN, @function
PRINTN:
.LFB58:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC20(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE58:
	.size	PRINTN, .-PRINTN
	.section	.rodata
.LC21:
	.string	"%u\n"
	.text
	.globl	PRINTUN
	.type	PRINTUN, @function
PRINTUN:
.LFB59:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC21(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE59:
	.size	PRINTUN, .-PRINTUN
	.section	.rodata
.LC22:
	.string	"%lld\n"
	.text
	.globl	PRINTLLN
	.type	PRINTLLN, @function
PRINTLLN:
.LFB60:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC22(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE60:
	.size	PRINTLLN, .-PRINTLLN
	.section	.rodata
.LC23:
	.string	"%llu\n"
	.text
	.globl	PRINTULLN
	.type	PRINTULLN, @function
PRINTULLN:
.LFB61:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC23(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE61:
	.size	PRINTULLN, .-PRINTULLN
	.section	.rodata
.LC24:
	.string	"%x\n"
	.text
	.globl	PRINTX
	.type	PRINTX, @function
PRINTX:
.LFB62:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC24(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE62:
	.size	PRINTX, .-PRINTX
	.section	.rodata
.LC25:
	.string	"%llx\n"
	.text
	.globl	PRINTLLX
	.type	PRINTLLX, @function
PRINTLLX:
.LFB63:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC25(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE63:
	.size	PRINTLLX, .-PRINTLLX
	.section	.rodata
.LC26:
	.string	"%lf\n"
	.text
	.globl	PRINTD
	.type	PRINTD, @function
PRINTD:
.LFB64:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movsd	%xmm0, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	leaq	.LC26(%rip), %rdi
	movl	$1, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE64:
	.size	PRINTD, .-PRINTD
	.section	.rodata
	.align 8
.LC27:
	.string	"NULLPTR GIVEN TO PRINTNUMARRAY"
.LC28:
	.string	"%lld "
	.text
	.globl	PRINTNUMARRAY
	.type	PRINTNUMARRAY, @function
PRINTNUMARRAY:
.LFB65:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	leaq	.LC27(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movl	$0, %ebx
	jmp	.L255
.L256:
	movslq	%ebx, %rax
	leaq	0(,%rax,8), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC28(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, %ebx
.L255:
	cmpl	-28(%rbp), %ebx
	jl	.L256
	movl	$10, %edi
	call	putchar@PLT
	nop
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE65:
	.size	PRINTNUMARRAY, .-PRINTNUMARRAY
	.globl	dynamic_string
	.type	dynamic_string, @function
dynamic_string:
.LFB66:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movl	$101, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	goodptr
	testb	%al, %al
	jne	.L258
	movl	$0, %eax
	jmp	.L259
.L258:
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	countuntilnul
	movl	%eax, %ebx
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	countuntilnul
	addl	$1, %eax
	cltq
	movq	%rax, %rdi
	call	MALLOC
	movq	%rax, -24(%rbp)
	movslq	%ebx, %rdx
	movq	-40(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	nbytesto
	movq	%rax, -24(%rbp)
	movslq	%ebx, %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movb	$0, (%rax)
	movq	-24(%rbp), %rax
.L259:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE66:
	.size	dynamic_string, .-dynamic_string
	.globl	dynamic_obj
	.type	dynamic_obj, @function
dynamic_obj:
.LFB67:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -88(%rbp)
	movl	%esi, -92(%rbp)
	movl	%edx, -96(%rbp)
	movq	-88(%rbp), %rax
	movl	$101, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	goodptr
	testb	%al, %al
	je	.L261
	cmpl	$0, -92(%rbp)
	je	.L261
	cmpl	$0, -96(%rbp)
	jne	.L262
.L261:
	movl	$0, %eax
	jmp	.L263
.L262:
	movl	-92(%rbp), %eax
	cmpl	$2, %eax
	je	.L265
	cmpl	$2, %eax
	ja	.L266
	cmpl	$1, %eax
	je	.L267
	jmp	.L264
.L266:
	cmpl	$4, %eax
	je	.L268
	cmpl	$8, %eax
	je	.L269
	jmp	.L264
.L267:
	movl	-92(%rbp), %eax
	imull	-96(%rbp), %eax
	movl	%eax, %eax
	movq	%rax, %rdi
	call	MALLOC
	movq	%rax, -32(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -24(%rbp)
	movl	$0, %ebx
	jmp	.L270
.L271:
	movl	%ebx, %edx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	%ebx, %ecx
	movq	-32(%rbp), %rdx
	addq	%rcx, %rdx
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	addl	$1, %ebx
.L270:
	cmpl	-96(%rbp), %ebx
	jb	.L271
	movq	-32(%rbp), %rax
	jmp	.L263
.L265:
	movl	-92(%rbp), %eax
	imull	-96(%rbp), %eax
	movl	%eax, %eax
	movq	%rax, %rdi
	call	MALLOC
	movq	%rax, -48(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -40(%rbp)
	movl	$0, %ebx
	jmp	.L272
.L273:
	movl	%ebx, %eax
	leaq	(%rax,%rax), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	%ebx, %edx
	leaq	(%rdx,%rdx), %rcx
	movq	-48(%rbp), %rdx
	addq	%rcx, %rdx
	movzwl	(%rax), %eax
	movw	%ax, (%rdx)
	addl	$1, %ebx
.L272:
	cmpl	-96(%rbp), %ebx
	jb	.L273
	movq	-48(%rbp), %rax
	jmp	.L263
.L268:
	movl	-92(%rbp), %eax
	imull	-96(%rbp), %eax
	movl	%eax, %eax
	movq	%rax, %rdi
	call	MALLOC
	movq	%rax, -64(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -56(%rbp)
	movl	$0, %ebx
	jmp	.L274
.L275:
	movl	%ebx, %eax
	leaq	0(,%rax,4), %rdx
	movq	-56(%rbp), %rax
	addq	%rdx, %rax
	movl	%ebx, %edx
	leaq	0(,%rdx,4), %rcx
	movq	-64(%rbp), %rdx
	addq	%rcx, %rdx
	movl	(%rax), %eax
	movl	%eax, (%rdx)
	addl	$1, %ebx
.L274:
	cmpl	-96(%rbp), %ebx
	jb	.L275
	movq	-64(%rbp), %rax
	jmp	.L263
.L269:
	movl	-92(%rbp), %eax
	imull	-96(%rbp), %eax
	movl	%eax, %eax
	movq	%rax, %rdi
	call	MALLOC
	movq	%rax, -80(%rbp)
	movq	-88(%rbp), %rax
	movq	%rax, -72(%rbp)
	movl	$0, %ebx
	jmp	.L276
.L277:
	movl	%ebx, %eax
	leaq	0(,%rax,8), %rdx
	movq	-72(%rbp), %rax
	addq	%rdx, %rax
	movl	%ebx, %edx
	leaq	0(,%rdx,8), %rcx
	movq	-80(%rbp), %rdx
	addq	%rcx, %rdx
	movq	(%rax), %rax
	movq	%rax, (%rdx)
	addl	$1, %ebx
.L276:
	cmpl	-96(%rbp), %ebx
	jb	.L277
	movq	-80(%rbp), %rax
	jmp	.L263
.L264:
	movl	$0, %eax
.L263:
	addq	$88, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE67:
	.size	dynamic_obj, .-dynamic_obj
	.globl	elemcnt
	.type	elemcnt, @function
elemcnt:
.LFB68:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movw	$0, -2(%rbp)
	jmp	.L279
.L280:
	movzwl	-2(%rbp), %eax
	addl	$1, %eax
	movw	%ax, -2(%rbp)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -24(%rbp)
.L279:
	cmpq	$0, -24(%rbp)
	jne	.L280
	movswl	-2(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE68:
	.size	elemcnt, .-elemcnt
	.section	.rodata
	.align 8
.LC29:
	.string	"NULLPTR 'node' GIVEN TO PUSH Node"
	.text
	.globl	push_elem
	.type	push_elem, @function
push_elem:
.LFB69:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	$0, %edx
	leaq	.LC29(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L283
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 40(%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, 32(%rax)
	jmp	.L284
.L283:
	movq	-16(%rbp), %rax
	movq	$0, 32(%rax)
.L284:
	movq	-16(%rbp), %rax
	movq	$0, 40(%rax)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE69:
	.size	push_elem, .-push_elem
	.globl	make_elem
	.type	make_elem, @function
make_elem:
.LFB70:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	movl	%ecx, %edx
	movl	%r8d, %esi
	movl	%r9d, %ecx
	movl	32(%rbp), %eax
	movw	%dx, -40(%rbp)
	movl	%esi, %edx
	movb	%dl, -44(%rbp)
	movl	%ecx, %edx
	movb	%dl, -48(%rbp)
	movb	%al, -52(%rbp)
	movl	$48, %edi
	call	MALLOC
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movl	-36(%rbp), %edx
	movl	%edx, 8(%rax)
	movq	-8(%rbp), %rax
	movzwl	-40(%rbp), %edx
	movw	%dx, 12(%rax)
	movq	-8(%rbp), %rax
	movzbl	-44(%rbp), %edx
	movb	%dl, 14(%rax)
	movq	-8(%rbp), %rax
	movzbl	-48(%rbp), %edx
	movb	%dl, 15(%rax)
	movq	-8(%rbp), %rax
	movq	16(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movq	-8(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rdx, 24(%rax)
	cmpb	$0, -52(%rbp)
	je	.L287
	movq	-8(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	push_elem
	jmp	.L288
.L287:
	movq	-8(%rbp), %rax
.L288:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE70:
	.size	make_elem, .-make_elem
	.globl	free_elem
	.type	free_elem, @function
free_elem:
.LFB71:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	$0, (%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movl	$0, 8(%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movw	$0, 12(%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movb	$0, 14(%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movb	$0, 15(%rax)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	addq	$16, %rax
	movq	%rax, %rdi
	call	free_bytes
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	$0, 24(%rax)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	FREE
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE71:
	.size	free_elem, .-free_elem
	.globl	rm_elem
	.type	rm_elem, @function
rm_elem:
.LFB72:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	40(%rax), %rax
	testq	%rax, %rax
	jne	.L291
	movq	-16(%rbp), %rax
	movq	32(%rax), %rax
	testq	%rax, %rax
	je	.L292
	movq	-16(%rbp), %rax
	movq	32(%rax), %rax
	movq	$0, 40(%rax)
.L292:
	movq	-16(%rbp), %rax
	movq	32(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	jmp	.L293
.L291:
	movq	-16(%rbp), %rax
	movq	32(%rax), %rax
	testq	%rax, %rax
	jne	.L294
	movq	-16(%rbp), %rax
	movq	40(%rax), %rax
	movq	$0, 32(%rax)
	jmp	.L293
.L294:
	movq	-16(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	40(%rax), %rax
	movq	32(%rdx), %rdx
	movq	%rdx, 32(%rax)
	movq	-16(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	32(%rax), %rax
	movq	40(%rdx), %rdx
	movq	%rdx, 40(%rax)
.L293:
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	free_elem
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE72:
	.size	rm_elem, .-rm_elem
	.section	.rodata
	.align 8
.LC30:
	.string	"NULLPTR ADDRESS OF 'hd' GIVEN TO POP_ELEM"
	.text
	.globl	pop_elem
	.type	pop_elem, @function
pop_elem:
.LFB73:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$0, %edx
	leaq	.LC30(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L297
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	rm_elem
.L297:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE73:
	.size	pop_elem, .-pop_elem
	.globl	free_all
	.type	free_all, @function
free_all:
.LFB74:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	jmp	.L299
.L300:
	movq	-16(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-16(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -16(%rbp)
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free_elem
.L299:
	cmpq	$0, -16(%rbp)
	jne	.L300
	movq	-40(%rbp), %rax
	movq	$0, (%rax)
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L301
	call	__stack_chk_fail@PLT
.L301:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE74:
	.size	free_all, .-free_all
	.globl	make_into_list
	.type	make_into_list, @function
make_into_list:
.LFB75:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	$0, -32(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	jmp	.L303
.L304:
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-16(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	push_elem
.L303:
	cmpq	$0, -24(%rbp)
	jne	.L304
	movq	-32(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, (%rax)
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L305
	call	__stack_chk_fail@PLT
.L305:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE75:
	.size	make_into_list, .-make_into_list
	.globl	change_elem
	.type	change_elem, @function
change_elem:
.LFB76:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, %eax
	movw	%ax, -20(%rbp)
	movswl	-20(%rbp), %eax
	subl	$71, %eax
	cmpl	$9, %eax
	ja	.L319
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L309(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L309(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L309:
	.long	.L308-.L309
	.long	.L310-.L309
	.long	.L311-.L309
	.long	.L312-.L309
	.long	.L313-.L309
	.long	.L314-.L309
	.long	.L315-.L309
	.long	.L316-.L309
	.long	.L317-.L309
	.long	.L318-.L309
	.text
.L308:
	movq	-16(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, (%rax)
	jmp	.L307
.L310:
	movq	-16(%rbp), %rax
	movl	(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, 8(%rax)
	jmp	.L307
.L311:
	movq	-16(%rbp), %rax
	movzwl	(%rax), %edx
	movq	-8(%rbp), %rax
	movw	%dx, 12(%rax)
	jmp	.L307
.L312:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	movb	%dl, 14(%rax)
	jmp	.L307
.L313:
	movq	-16(%rbp), %rax
	movzbl	(%rax), %edx
	movq	-8(%rbp), %rax
	movb	%dl, 15(%rax)
	jmp	.L307
.L314:
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 16(%rax)
	jmp	.L307
.L318:
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 8(%rax)
	jmp	.L307
.L315:
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 24(%rax)
	jmp	.L307
.L316:
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 32(%rax)
	jmp	.L307
.L317:
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 32(%rax)
	nop
.L307:
.L319:
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE76:
	.size	change_elem, .-change_elem
	.section	.rodata
	.align 8
.LC31:
	.string	"NULLPTR ADDRESS OF 'start' GIVEN TO FOREACH_ELEM"
	.align 8
.LC32:
	.string	"NULLPTR 'start' GIVEN TO FOREACH_ELEM"
	.text
	.globl	foreach_elem
	.type	foreach_elem, @function
foreach_elem:
.LFB77:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, %eax
	movb	%al, -36(%rbp)
	movq	-24(%rbp), %rax
	movl	$101, %edx
	leaq	.LC31(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	testb	%al, %al
	je	.L327
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	$101, %edx
	leaq	.LC32(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	testb	%al, %al
	je	.L328
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -12(%rbp)
	jmp	.L324
.L326:
	movq	-8(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rdi
	call	*%rax
	movl	%eax, -12(%rbp)
	cmpl	$101, -12(%rbp)
	je	.L329
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdx
	cmpb	$0, -36(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, %rcx
	cmpb	$1, -36(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rcx, %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
.L324:
	cmpq	$0, -8(%rbp)
	jne	.L326
	jmp	.L320
.L327:
	nop
	jmp	.L320
.L328:
	nop
	jmp	.L320
.L329:
	nop
.L320:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE77:
	.size	foreach_elem, .-foreach_elem
	.section	.rodata
.LC33:
	.string	"NULLPTR Q GIVEN TO FIND_ELEM"
	.text
	.globl	find_elem
	.type	find_elem, @function
find_elem:
.LFB78:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%ecx, %eax
	movw	%dx, -20(%rbp)
	movb	%al, -24(%rbp)
	movq	-8(%rbp), %rax
	movl	$101, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	goodptr
	testb	%al, %al
	jne	.L331
	movl	$0, %eax
	jmp	.L332
.L331:
	movq	-16(%rbp), %rax
	movl	$101, %edx
	leaq	.LC33(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	testb	%al, %al
	jne	.L333
	movl	$0, %eax
	jmp	.L332
.L333:
	movswl	-20(%rbp), %eax
	subl	$71, %eax
	cmpl	$9, %eax
	ja	.L334
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L336(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L336(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L336:
	.long	.L346-.L336
	.long	.L349-.L336
	.long	.L352-.L336
	.long	.L355-.L336
	.long	.L358-.L336
	.long	.L361-.L336
	.long	.L370-.L336
	.long	.L373-.L336
	.long	.L376-.L336
	.long	.L366-.L336
	.text
.L348:
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	cmpq	%rax, %rdx
	jne	.L347
	movq	-8(%rbp), %rax
	jmp	.L332
.L347:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdx
	cmpb	$0, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, %rcx
	cmpb	$1, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rcx, %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
.L346:
	cmpq	$0, -8(%rbp)
	jne	.L348
	jmp	.L334
.L351:
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	movq	-16(%rbp), %rdx
	cmpl	%edx, %eax
	jne	.L350
	movq	-8(%rbp), %rax
	jmp	.L332
.L350:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdx
	cmpb	$0, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, %rcx
	cmpb	$1, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rcx, %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
.L349:
	cmpq	$0, -8(%rbp)
	jne	.L351
	jmp	.L334
.L354:
	movq	-8(%rbp), %rax
	movzwl	12(%rax), %eax
	movq	-16(%rbp), %rdx
	cmpw	%dx, %ax
	jne	.L353
	movq	-8(%rbp), %rax
	jmp	.L332
.L353:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdx
	cmpb	$0, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, %rcx
	cmpb	$1, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rcx, %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
.L352:
	cmpq	$0, -8(%rbp)
	jne	.L354
	jmp	.L334
.L357:
	movq	-8(%rbp), %rax
	movzbl	14(%rax), %eax
	movq	-16(%rbp), %rdx
	cmpb	%dl, %al
	jne	.L356
	movq	-8(%rbp), %rax
	jmp	.L332
.L356:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdx
	cmpb	$0, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, %rcx
	cmpb	$1, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rcx, %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
.L355:
	cmpq	$0, -8(%rbp)
	jne	.L357
	jmp	.L334
.L360:
	movq	-8(%rbp), %rax
	movzbl	15(%rax), %eax
	movq	-16(%rbp), %rdx
	cmpb	%dl, %al
	jne	.L359
	movq	-8(%rbp), %rax
	jmp	.L332
.L359:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdx
	cmpb	$0, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, %rcx
	cmpb	$1, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rcx, %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
.L358:
	cmpq	$0, -8(%rbp)
	jne	.L360
	jmp	.L334
.L365:
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	testq	%rax, %rax
	je	.L379
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	eqbytes
	testb	%al, %al
	je	.L364
	movq	-8(%rbp), %rax
	jmp	.L332
.L364:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdx
	cmpb	$0, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, %rcx
	cmpb	$1, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rcx, %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
.L361:
	cmpq	$0, -8(%rbp)
	jne	.L365
	jmp	.L334
.L369:
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	testq	%rax, %rax
	je	.L380
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L381
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	8(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	eqstr
	testb	%al, %al
	je	.L382
	movq	-8(%rbp), %rax
	jmp	.L332
.L379:
	nop
	jmp	.L363
.L380:
	nop
	jmp	.L363
.L381:
	nop
	jmp	.L363
.L382:
	nop
.L363:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdx
	cmpb	$0, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, %rcx
	cmpb	$1, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rcx, %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
.L366:
	cmpq	$0, -8(%rbp)
	jne	.L369
	jmp	.L334
.L372:
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	cmpq	%rax, -16(%rbp)
	jne	.L371
	movq	-8(%rbp), %rax
	jmp	.L332
.L371:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdx
	cmpb	$0, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, %rcx
	cmpb	$1, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rcx, %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
.L370:
	cmpq	$0, -8(%rbp)
	jne	.L372
	jmp	.L334
.L375:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	cmpq	%rax, -16(%rbp)
	jne	.L374
	movq	-8(%rbp), %rax
	jmp	.L332
.L374:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdx
	cmpb	$0, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, %rcx
	cmpb	$1, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rcx, %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
.L373:
	cmpq	$0, -8(%rbp)
	jne	.L375
	jmp	.L334
.L378:
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	cmpq	%rax, -16(%rbp)
	jne	.L377
	movq	-8(%rbp), %rax
	jmp	.L332
.L377:
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, %rdx
	cmpb	$0, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	movq	%rax, %rcx
	cmpb	$1, -24(%rbp)
	sete	%al
	movzbl	%al, %eax
	imulq	%rcx, %rax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
.L376:
	cmpq	$0, -8(%rbp)
	jne	.L378
	nop
.L334:
	movl	$0, %eax
.L332:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE78:
	.size	find_elem, .-find_elem
	.section	.rodata
	.align 8
.LC34:
	.string	"################### Element %d ################## \n"
.LC35:
	.string	"lnum : "
.LC36:
	.string	"mnum : "
.LC37:
	.string	"snum : "
.LC38:
	.string	"type : "
.LC39:
	.string	"hold : "
.LC40:
	.string	"line points to null"
.LC41:
	.string	"line : "
.LC42:
	.string	"path : "
.LC43:
	.string	"branch : "
	.text
	.globl	print_elems
	.type	print_elems, @function
print_elems:
.LFB79:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movw	$1, -2(%rbp)
	jmp	.L384
.L386:
	movswl	-2(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC34(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	.LC35(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	PRINTLLN
	leaq	.LC36(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rax
	movl	8(%rax), %eax
	movl	%eax, %edi
	call	PRINTN
	leaq	.LC37(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rax
	movzwl	12(%rax), %eax
	cwtl
	movl	%eax, %edi
	call	PRINTN
	leaq	.LC38(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rax
	movzbl	14(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	PRINTN
	leaq	.LC39(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rax
	movzbl	15(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	PRINTC
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	testq	%rax, %rax
	jne	.L385
	leaq	.LC40(%rip), %rdi
	call	PRINT
.L385:
	leaq	.LC41(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	PRINT
	leaq	.LC42(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movq	8(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movq	(%rax), %rax
	addq	$1, %rax
	addq	%rdx, %rax
	movq	%rax, %rdi
	call	PRINT
	leaq	.LC43(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rax
	movq	24(%rax), %rax
	movl	%eax, %edi
	call	PRINTX
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -24(%rbp)
	movzwl	-2(%rbp), %eax
	addl	$1, %eax
	movw	%ax, -2(%rbp)
.L384:
	cmpq	$0, -24(%rbp)
	jne	.L386
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE79:
	.size	print_elems, .-print_elems
	.globl	filehdr
	.bss
	.align 8
	.type	filehdr, @object
	.size	filehdr, 8
filehdr:
	.zero	8
	.globl	FILESOPEN
	.align 4
	.type	FILESOPEN, @object
	.size	FILESOPEN, 4
FILESOPEN:
	.zero	4
	.section	.rodata
.LC44:
	.string	"NULLPTR FILE GIVEN TO FOPEN"
.LC45:
	.string	"NULLPTR OPT GIVEN TO FOPEN"
.LC46:
	.string	"FOPEN ERROR"
	.text
	.globl	FOPEN
	.type	FOPEN, @function
FOPEN:
.LFB80:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	leaq	.LC44(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	-32(%rbp), %rax
	movl	$0, %edx
	leaq	.LC45(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	$0, -8(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L388
	leaq	.LC46(%rip), %rdi
	call	THROW
	jmp	.L389
.L388:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	countuntilnul
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	dynamic_bytes
	movq	%rax, %rcx
	movl	FILESOPEN(%rip), %eax
	addl	$1, %eax
	movl	%eax, FILESOPEN(%rip)
	movl	FILESOPEN(%rip), %eax
	movswl	%ax, %edx
	movq	-8(%rbp), %rax
	subq	$8, %rsp
	pushq	$1
	pushq	-32(%rbp)
	pushq	%rcx
	movl	$0, %r9d
	movl	$0, %r8d
	movl	%edx, %ecx
	movl	$0, %edx
	movq	%rax, %rsi
	leaq	filehdr(%rip), %rdi
	call	make_elem
	addq	$32, %rsp
.L389:
	movq	-8(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE80:
	.size	FOPEN, .-FOPEN
	.section	.rodata
	.align 8
.LC47:
	.string	"NULLPTR STREAM GIVEN TO FCLOSE"
	.text
	.globl	FCLOSE
	.type	FCLOSE, @function
FCLOSE:
.LFB81:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	$101, %edx
	leaq	.LC47(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	testb	%al, %al
	je	.L395
	movq	filehdr(%rip), %rax
	movq	-24(%rbp), %rsi
	movl	$0, %ecx
	movl	$71, %edx
	movq	%rax, %rdi
	call	find_elem
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L394
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	filehdr(%rip), %rdi
	call	rm_elem
.L394:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
	movl	FILESOPEN(%rip), %eax
	subl	$1, %eax
	movl	%eax, FILESOPEN(%rip)
	jmp	.L391
.L395:
	nop
.L391:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE81:
	.size	FCLOSE, .-FCLOSE
	.section	.rodata
	.align 8
.LC48:
	.string	"FILE NOT FOUND IN ELEMENT LIST -- FGETC"
	.text
	.globl	FGETC
	.type	FGETC, @function
FGETC:
.LFB82:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, %ebx
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	testl	%eax, %eax
	je	.L397
	movq	filehdr(%rip), %rax
	movq	-40(%rbp), %rsi
	movl	$0, %ecx
	movl	$71, %edx
	movq	%rax, %rdi
	call	find_elem
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L398
	leaq	.LC48(%rip), %rdi
	call	THROW
.L398:
	movq	-24(%rbp), %rax
	movzbl	15(%rax), %eax
	addl	$1, %eax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movb	%dl, 15(%rax)
.L397:
	movl	%ebx, %eax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE82:
	.size	FGETC, .-FGETC
	.section	.rodata
	.align 8
.LC49:
	.string	"NULLPTR STREAM GIVEN TO SKIPWHITE"
	.align 8
.LC50:
	.string	"FILE NOT FOUND IN ELEMENT LIST -- SKIPWHITE"
	.text
	.globl	skipwhite
	.type	skipwhite, @function
skipwhite:
.LFB83:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	$0, %edx
	leaq	.LC49(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	filehdr(%rip), %rax
	movq	-24(%rbp), %rsi
	movl	$0, %ecx
	movl	$71, %edx
	movq	%rax, %rdi
	call	find_elem
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L401
	leaq	.LC50(%rip), %rdi
	call	THROW
.L401:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	movb	%al, -9(%rbp)
	jmp	.L402
.L406:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	movb	%al, -9(%rbp)
.L402:
	cmpb	$8, -9(%rbp)
	jle	.L403
	cmpb	$13, -9(%rbp)
	jle	.L404
.L403:
	cmpb	$32, -9(%rbp)
	jne	.L405
.L404:
	movq	-8(%rbp), %rax
	movzbl	15(%rax), %eax
	testb	%al, %al
	je	.L406
.L405:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	testl	%eax, %eax
	jne	.L407
	movsbl	-9(%rbp), %eax
	movq	-24(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	ungetc@PLT
.L407:
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	feof@PLT
	testl	%eax, %eax
	sete	%al
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE83:
	.size	skipwhite, .-skipwhite
	.globl	ispure
	.type	ispure, @function
ispure:
.LFB84:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L410
	movl	$0, %eax
	jmp	.L411
.L410:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	jne	.L412
	movl	$0, %eax
	jmp	.L411
.L412:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	%eax, %r12d
	movl	$0, %ebx
	jmp	.L413
.L416:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movl	%ebx, %eax
	leal	1(%rax), %ebx
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$8, %al
	jbe	.L414
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movl	%ebx, %eax
	leal	1(%rax), %ebx
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$13, %al
	jbe	.L413
.L414:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movl	%ebx, %eax
	leal	1(%rax), %ebx
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$32, %al
	je	.L413
	movl	$0, %eax
	jmp	.L411
.L413:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movslq	%ebx, %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L415
	cmpl	%r12d, %ebx
	jl	.L416
.L415:
	movl	%r12d, %eax
.L411:
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE84:
	.size	ispure, .-ispure
	.globl	pushback
	.type	pushback, @function
pushback:
.LFB85:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	cmpq	$0, -24(%rbp)
	je	.L422
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movl	%eax, %ebx
	jmp	.L420
.L421:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rdx
	movslq	%ebx, %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movq	-32(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	ungetc@PLT
.L420:
	movl	%ebx, %eax
	leal	-1(%rax), %ebx
	testl	%eax, %eax
	je	.L417
	testl	%ebx, %ebx
	jg	.L421
	jmp	.L417
.L422:
	nop
.L417:
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE85:
	.size	pushback, .-pushback
	.section	.rodata
	.align 8
.LC51:
	.string	"NULLPTR STREAM GIVEN TO READUNTIL"
	.align 8
.LC52:
	.string	"FILE NOT FOUND IN ELEMENT LIST -- READUNTIL"
	.text
	.globl	readuntil
	.type	readuntil, @function
readuntil:
.LFB86:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$64, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movl	%edx, %eax
	movq	%rcx, -72(%rbp)
	movl	%edi, %edx
	movb	%dl, -52(%rbp)
	movl	%esi, %edx
	movb	%dl, -56(%rbp)
	movb	%al, -60(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-72(%rbp), %rax
	movl	$0, %edx
	leaq	.LC51(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	filehdr(%rip), %rax
	movq	-72(%rbp), %rsi
	movl	$0, %ecx
	movl	$71, %edx
	movq	%rax, %rdi
	call	find_elem
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L424
	leaq	.LC52(%rip), %rdi
	call	THROW
.L424:
	movl	$0, %ebx
	movq	$0, -48(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	movl	%eax, %r12d
	jmp	.L425
.L427:
	movl	%ebx, %eax
	addl	$1, %eax
	movl	%eax, %ebx
	movswq	%bx, %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	REALLOC
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movswq	%bx, %rdx
	subq	$1, %rdx
	addq	%rdx, %rax
	movb	%r12b, (%rax)
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	movl	%eax, %r12d
.L425:
	cmpb	-52(%rbp), %r12b
	je	.L426
	movq	-40(%rbp), %rax
	movzbl	15(%rax), %eax
	testb	%al, %al
	je	.L427
.L426:
	cmpb	-52(%rbp), %r12b
	jne	.L428
	cmpb	$0, -56(%rbp)
	je	.L428
	movl	%ebx, %eax
	addl	$1, %eax
	movl	%eax, %ebx
	movswq	%bx, %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	REALLOC
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movswq	%bx, %rdx
	subq	$1, %rdx
	addq	%rdx, %rax
	movb	%r12b, (%rax)
.L428:
	movswl	%bx, %edx
	movq	-48(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	dynamic_bytes
	movq	%rax, -32(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	FREE
	cmpb	$0, -60(%rbp)
	je	.L429
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	skipwhite
.L429:
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L431
	call	__stack_chk_fail@PLT
.L431:
	addq	$64, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE86:
	.size	readuntil, .-readuntil
	.section	.rodata
	.align 8
.LC53:
	.string	"NULLPTR STREAM GIVEN TO CHECKAHEAD_FOR"
	.align 8
.LC54:
	.string	"FILE NOT FOUND IN ELEMENT LIST -- CHECKAHEAD_FOR"
	.text
	.globl	checkahead_for
	.type	checkahead_for, @function
checkahead_for:
.LFB87:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movl	%edi, %eax
	movq	%rsi, -80(%rbp)
	movb	%al, -68(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-80(%rbp), %rax
	movl	$0, %edx
	leaq	.LC53(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	filehdr(%rip), %rax
	movq	-80(%rbp), %rsi
	movl	$0, %ecx
	movl	$71, %edx
	movq	%rax, %rdi
	call	find_elem
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L433
	leaq	.LC54(%rip), %rdi
	call	THROW
.L433:
	movl	$0, %ebx
	movq	$0, -48(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	movb	%al, -49(%rbp)
	jmp	.L434
.L436:
	addl	$1, %ebx
	movslq	%ebx, %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	REALLOC
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movslq	%ebx, %rdx
	subq	$1, %rdx
	addq	%rax, %rdx
	movzbl	-49(%rbp), %eax
	movb	%al, (%rdx)
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	movb	%al, -49(%rbp)
.L434:
	movzbl	-49(%rbp), %eax
	cmpb	-68(%rbp), %al
	je	.L435
	movq	-32(%rbp), %rax
	movzbl	15(%rax), %eax
	testb	%al, %al
	je	.L436
.L435:
	movq	-48(%rbp), %rax
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	dynamic_bytes
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	-80(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	pushback
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	FREE
	leaq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	free_bytes
	movl	%ebx, %eax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L438
	call	__stack_chk_fail@PLT
.L438:
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE87:
	.size	checkahead_for, .-checkahead_for
	.section	.rodata
	.align 8
.LC55:
	.string	"NULLPTR STREAM GIVEN TO READWORD"
	.align 8
.LC56:
	.string	"FILE NOT FOUND IN ELEMENT LIST -- READWORD"
	.text
	.globl	readword
	.type	readword, @function
readword:
.LFB88:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$48, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -56(%rbp)
	movl	%esi, %eax
	movb	%al, -60(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-56(%rbp), %rax
	movl	$0, %edx
	leaq	.LC55(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	filehdr(%rip), %rax
	movq	-56(%rbp), %rsi
	movl	$0, %ecx
	movl	$71, %edx
	movq	%rax, %rdi
	call	find_elem
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L440
	leaq	.LC56(%rip), %rdi
	call	THROW
.L440:
	movl	$0, %r12d
	movq	$0, -48(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	skipwhite
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	movl	%eax, %ebx
	jmp	.L441
.L444:
	movl	%r12d, %eax
	addl	$1, %eax
	movl	%eax, %r12d
	movswq	%r12w, %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	REALLOC
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movswq	%r12w, %rdx
	subq	$1, %rdx
	addq	%rdx, %rax
	movb	%bl, (%rax)
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	movl	%eax, %ebx
.L441:
	cmpb	$8, %bl
	jle	.L442
	cmpb	$13, %bl
	jle	.L443
.L442:
	cmpb	$32, %bl
	je	.L443
	movq	-40(%rbp), %rax
	movzbl	15(%rax), %eax
	testb	%al, %al
	je	.L444
.L443:
	movswl	%r12w, %edx
	movq	-48(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	dynamic_bytes
	movq	%rax, -32(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	FREE
	cmpb	$0, -60(%rbp)
	je	.L445
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	skipwhite
.L445:
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L447
	call	__stack_chk_fail@PLT
.L447:
	addq	$48, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE88:
	.size	readword, .-readword
	.section	.rodata
	.align 8
.LC57:
	.string	"NULLPTR STREAM GIVEN TO READNUM"
	.text
	.globl	readnum
	.type	readnum, @function
readnum:
.LFB89:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movl	%esi, %eax
	movb	%al, -44(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-40(%rbp), %rax
	movl	$0, %edx
	leaq	.LC57(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movsbl	-44(%rbp), %edx
	movq	-40(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	readword
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	atol@PLT
	movq	%rax, %rbx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	free_bytes
	movq	%rbx, %rax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L450
	call	__stack_chk_fail@PLT
.L450:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE89:
	.size	readnum, .-readnum
	.section	.rodata
.LC58:
	.string	"NULLPTR GIVEN TO READFLT"
	.text
	.globl	readflt
	.type	readflt, @function
readflt:
.LFB90:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movl	%esi, %eax
	movb	%al, -44(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-40(%rbp), %rax
	movl	$0, %edx
	leaq	.LC58(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movsbl	-44(%rbp), %edx
	movq	-40(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	readword
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	atof@PLT
	movq	%xmm0, %rbx
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	free_bytes
	movq	%rbx, -56(%rbp)
	movsd	-56(%rbp), %xmm0
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L453
	call	__stack_chk_fail@PLT
.L453:
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE90:
	.size	readflt, .-readflt
	.section	.rodata
	.align 8
.LC59:
	.string	"NULLPTR FILE GIVEN TO READFILE"
.LC60:
	.string	"r"
	.align 8
.LC61:
	.string	"FILE NOT FOUND IN ELEMENT LIST -- READFILE"
	.text
	.globl	readfile
	.type	readfile, @function
readfile:
.LFB91:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$64, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -72(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-72(%rbp), %rax
	movl	$0, %edx
	leaq	.LC59(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	-72(%rbp), %rax
	leaq	.LC60(%rip), %rsi
	movq	%rax, %rdi
	call	FOPEN
	movq	%rax, -48(%rbp)
	movq	filehdr(%rip), %rax
	movq	-48(%rbp), %rsi
	movl	$0, %ecx
	movl	$71, %edx
	movq	%rax, %rdi
	call	find_elem
	movq	%rax, -40(%rbp)
	movl	$0, %ebx
	cmpq	$0, -40(%rbp)
	jne	.L455
	leaq	.LC61(%rip), %rdi
	call	THROW
.L455:
	movq	$0, -56(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	movl	%eax, %r12d
	jmp	.L456
.L457:
	addl	$1, %ebx
	movslq	%ebx, %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	REALLOC
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movslq	%ebx, %rdx
	subq	$1, %rdx
	addq	%rdx, %rax
	movb	%r12b, (%rax)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	movl	%eax, %r12d
.L456:
	movq	-40(%rbp), %rax
	movzbl	15(%rax), %eax
	testb	%al, %al
	je	.L457
	movq	-56(%rbp), %rax
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	dynamic_bytes
	movq	%rax, -32(%rbp)
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	FREE
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	FCLOSE
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L459
	call	__stack_chk_fail@PLT
.L459:
	addq	$64, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE91:
	.size	readfile, .-readfile
	.section	.rodata
	.align 8
.LC62:
	.string	"NULLPTR FILE GIVEN TO FILECOUNT"
	.align 8
.LC63:
	.string	"FILE NOT FOUND IN ELEMENT LIST -- FILECOUNT"
	.text
	.globl	filecount
	.type	filecount, @function
filecount:
.LFB92:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movl	$0, %edx
	leaq	.LC62(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	-40(%rbp), %rax
	leaq	.LC60(%rip), %rsi
	movq	%rax, %rdi
	call	FOPEN
	movq	%rax, -32(%rbp)
	movq	filehdr(%rip), %rax
	movq	-32(%rbp), %rsi
	movl	$0, %ecx
	movl	$71, %edx
	movq	%rax, %rdi
	call	find_elem
	movq	%rax, -24(%rbp)
	cmpq	$0, -24(%rbp)
	jne	.L461
	leaq	.LC63(%rip), %rdi
	call	THROW
.L461:
	movl	$0, %ebx
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	jmp	.L462
.L463:
	addq	$1, %rbx
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
.L462:
	movq	-24(%rbp), %rax
	movzbl	15(%rax), %eax
	testb	%al, %al
	je	.L463
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	FCLOSE
	movq	%rbx, %rax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE92:
	.size	filecount, .-filecount
	.section	.rodata
	.align 8
.LC64:
	.string	"NULLPTR FILE GIVEN TO READFILE_WITHOUTC"
	.align 8
.LC65:
	.string	"FILE NOT FOUND IN ELEMENT LIST -- READFILE_WITHOUTC"
	.text
	.globl	readfile_withoutc
	.type	readfile_withoutc, @function
readfile_withoutc:
.LFB93:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$64, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -72(%rbp)
	movl	%esi, %eax
	movb	%al, -76(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-72(%rbp), %rax
	movl	$0, %edx
	leaq	.LC64(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	-72(%rbp), %rax
	leaq	.LC60(%rip), %rsi
	movq	%rax, %rdi
	call	FOPEN
	movq	%rax, -48(%rbp)
	movq	filehdr(%rip), %rax
	movq	-48(%rbp), %rsi
	movl	$0, %ecx
	movl	$71, %edx
	movq	%rax, %rdi
	call	find_elem
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L466
	leaq	.LC65(%rip), %rdi
	call	THROW
.L466:
	movl	$0, %ebx
	movq	$0, -56(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	movl	%eax, %r12d
	jmp	.L467
.L469:
	cmpb	-76(%rbp), %r12b
	je	.L468
	addl	$1, %ebx
	movslq	%ebx, %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	REALLOC
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movslq	%ebx, %rdx
	subq	$1, %rdx
	addq	%rdx, %rax
	movb	%r12b, (%rax)
.L468:
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	movl	%eax, %r12d
.L467:
	movq	-40(%rbp), %rax
	movzbl	15(%rax), %eax
	testb	%al, %al
	je	.L469
	movq	-56(%rbp), %rax
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	dynamic_bytes
	movq	%rax, -32(%rbp)
	leaq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	FREE
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	FCLOSE
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L471
	call	__stack_chk_fail@PLT
.L471:
	addq	$64, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE93:
	.size	readfile_withoutc, .-readfile_withoutc
	.globl	readline
	.type	readline, @function
readline:
.LFB94:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rcx
	movl	$0, %edx
	movl	$1, %esi
	movl	$10, %edi
	call	readuntil
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE94:
	.size	readline, .-readline
	.section	.rodata
	.align 8
.LC66:
	.string	"NULLPTR STREAM GIVEN TO READNXT"
	.align 8
.LC67:
	.string	"FILE NOT FOUND IN ELEMENT LIST -- READNXT"
	.text
	.globl	readnxt
	.type	readnxt, @function
readnxt:
.LFB95:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$48, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-64(%rbp), %rax
	movl	$0, %edx
	leaq	.LC66(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	filehdr(%rip), %rax
	movq	-64(%rbp), %rsi
	movl	$0, %ecx
	movl	$71, %edx
	movq	%rax, %rdi
	call	find_elem
	movq	%rax, -40(%rbp)
	cmpq	$0, -40(%rbp)
	jne	.L475
	leaq	.LC67(%rip), %rdi
	call	THROW
.L475:
	movl	$0, %ebx
	movq	$0, -48(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	movl	%eax, %r12d
	jmp	.L476
.L478:
	addq	$1, %rbx
	movq	-48(%rbp), %rax
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	REALLOC
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movq	%rbx, %rdx
	subq	$1, %rdx
	addq	%rdx, %rax
	movb	%r12b, (%rax)
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	movl	%eax, %r12d
.L476:
	movq	-56(%rbp), %rax
	leaq	-1(%rax), %rdx
	movq	%rdx, -56(%rbp)
	testq	%rax, %rax
	je	.L477
	movq	-40(%rbp), %rax
	movzbl	15(%rax), %eax
	testb	%al, %al
	je	.L478
.L477:
	movsbl	%r12b, %eax
	movq	-64(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	ungetc@PLT
	movl	%ebx, %edx
	movq	-48(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	dynamic_bytes
	movq	%rax, -32(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	FREE
	movq	-40(%rbp), %rax
	movzbl	15(%rax), %eax
	testb	%al, %al
	je	.L479
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	FCLOSE
.L479:
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L481
	call	__stack_chk_fail@PLT
.L481:
	addq	$48, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE95:
	.size	readnxt, .-readnxt
	.section	.rodata
	.align 8
.LC68:
	.string	"NULLPTR STREAM GIVEN TO SKIPREADWORD"
	.text
	.globl	skipreadword
	.type	skipreadword, @function
skipreadword:
.LFB96:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movl	$0, %edx
	leaq	.LC68(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movl	$0, %ebx
	jmp	.L483
.L484:
	movq	-32(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	readword
	addl	$1, %ebx
.L483:
	cmpl	-20(%rbp), %ebx
	jl	.L484
	movq	-32(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	readword
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE96:
	.size	skipreadword, .-skipreadword
	.globl	skipreadline
	.type	skipreadline, @function
skipreadline:
.LFB97:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset 3, -24
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, %ebx
	jmp	.L487
.L488:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	readline
	addl	$1, %ebx
.L487:
	cmpl	-20(%rbp), %ebx
	jl	.L488
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	readline
	addq	$24, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE97:
	.size	skipreadline, .-skipreadline
	.globl	set_to_nextline
	.type	set_to_nextline, @function
set_to_nextline:
.LFB98:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rcx
	movl	$0, %edx
	movl	$1, %esi
	movl	$10, %edi
	call	readuntil
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE98:
	.size	set_to_nextline, .-set_to_nextline
	.section	.rodata
	.align 8
.LC69:
	.string	"NULLPTR STREAM GIVEN TO READWORDS"
	.text
	.globl	readwords
	.type	readwords, @function
readwords:
.LFB99:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movl	%edi, -36(%rbp)
	movl	%esi, %eax
	movq	%rdx, -48(%rbp)
	movb	%al, -40(%rbp)
	movq	-48(%rbp), %rax
	movl	$0, %edx
	leaq	.LC69(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	$0, -24(%rbp)
	cmpl	$0, -36(%rbp)
	je	.L492
	movq	-48(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	readword
	movq	%rax, -24(%rbp)
.L492:
	movl	$1, %ebx
	jmp	.L493
.L494:
	movq	-48(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	readword
	movq	%rax, %rsi
	movq	-24(%rbp), %rax
	movl	$1, %ecx
	movl	$32, %edx
	movq	%rax, %rdi
	call	concatbytes
	movq	%rax, -24(%rbp)
	addl	$1, %ebx
.L493:
	cmpl	-36(%rbp), %ebx
	jl	.L494
	cmpb	$0, -40(%rbp)
	je	.L495
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	set_to_nextline
.L495:
	movq	-24(%rbp), %rax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE99:
	.size	readwords, .-readwords
	.section	.rodata
	.align 8
.LC70:
	.string	"FILE NOT FOUND IN ELEMENT LIST -- LINELIST"
	.text
	.globl	linelist
	.type	linelist, @function
linelist:
.LFB100:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$48, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	-56(%rbp), %rax
	leaq	.LC60(%rip), %rsi
	movq	%rax, %rdi
	call	FOPEN
	movq	%rax, -40(%rbp)
	movq	filehdr(%rip), %rax
	movq	-40(%rbp), %rsi
	movl	$0, %ecx
	movl	$71, %edx
	movq	%rax, %rdi
	call	find_elem
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L498
	leaq	.LC70(%rip), %rdi
	call	THROW
.L498:
	movl	$0, %ebx
	movq	$0, -48(%rbp)
	jmp	.L499
.L500:
	movq	-48(%rbp), %rax
	movq	%rax, -24(%rbp)
	leal	1(%rbx), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdx
	movq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	REALLOC
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -48(%rbp)
	movl	%ebx, %eax
	leal	1(%rax), %ebx
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-48(%rbp), %rax
	leaq	(%rdx,%rax), %r12
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	readline
	movq	%rax, (%r12)
.L499:
	movq	-32(%rbp), %rax
	movzbl	15(%rax), %eax
	testb	%al, %al
	je	.L500
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	FCLOSE
	movq	-64(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, (%rax)
	movl	%ebx, %eax
	addq	$48, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE100:
	.size	linelist, .-linelist
	.section	.rodata
	.align 8
.LC71:
	.string	"BAD ARG: WOULD HAVE DIVIDED BY ZERO"
	.align 8
.LC72:
	.string	"NULLPTR FILE GIVEN TO READCOLUMN"
.LC73:
	.string	"FILE : %s --> EMPTY\n"
	.text
	.globl	readcolumn
	.type	readcolumn, @function
readcolumn:
.LFB101:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$48, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movl	%edi, %ecx
	movl	%esi, %eax
	movq	%rdx, -64(%rbp)
	movl	%ecx, %edx
	movw	%dx, -52(%rbp)
	movb	%al, -56(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	cmpw	$0, -52(%rbp)
	jne	.L503
	leaq	.LC71(%rip), %rdi
	call	THROW
.L503:
	movq	-64(%rbp), %rax
	movl	$0, %edx
	leaq	.LC72(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movl	$0, %ebx
	movq	$0, -48(%rbp)
	movq	$0, -40(%rbp)
	leaq	-48(%rbp), %rdx
	movq	-64(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	linelist
	movl	%eax, %r12d
	movq	-48(%rbp), %rax
	testq	%rax, %rax
	jne	.L506
	movq	-64(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC73(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L505
.L511:
	movq	-48(%rbp), %rdx
	movl	%ebx, %eax
	leal	1(%rax), %ebx
	cltq
	salq	$3, %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movswl	-52(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	getword
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	je	.L506
	cmpb	$1, -56(%rbp)
	jne	.L507
	movl	$32, %edx
	jmp	.L508
.L507:
	movl	$0, %edx
.L508:
	cmpb	$0, -56(%rbp)
	jne	.L509
	movl	$10, %eax
	jmp	.L510
.L509:
	movl	$0, %eax
.L510:
	addl	%edx, %eax
	movsbl	%al, %edx
	movq	-32(%rbp), %rsi
	movq	-40(%rbp), %rax
	movl	$2, %ecx
	movq	%rax, %rdi
	call	concatbytes
	movq	%rax, -40(%rbp)
.L506:
	cmpl	%r12d, %ebx
	jl	.L511
.L505:
	movq	-40(%rbp), %rax
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L513
	call	__stack_chk_fail@PLT
.L513:
	addq	$48, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE101:
	.size	readcolumn, .-readcolumn
	.section	.rodata
	.align 8
.LC74:
	.string	"NULL STR TO FIND IN STREAM -- SUBSTR_LOC_STREAM"
	.align 8
.LC75:
	.string	"NULLPTR STREAM GIVEN TO -- SUBSTR_LOC_STREAM"
	.align 8
.LC76:
	.string	"FILE NOT FOUND IN ELEMENT LIST -- SUBSTR_LOC_STREAM"
	.text
	.globl	substr_loc_STREAM
	.type	substr_loc_STREAM, @function
substr_loc_STREAM:
.LFB102:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movq	-56(%rbp), %rax
	movl	$101, %edx
	leaq	.LC74(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	testb	%al, %al
	jne	.L515
	movl	$0, %eax
	jmp	.L516
.L515:
	movq	-64(%rbp), %rax
	movl	$0, %edx
	leaq	.LC75(%rip), %rsi
	movq	%rax, %rdi
	call	goodptr
	movq	filehdr(%rip), %rax
	movq	-64(%rbp), %rsi
	movl	$0, %ecx
	movl	$71, %edx
	movq	%rax, %rdi
	call	find_elem
	movq	%rax, -32(%rbp)
	cmpq	$0, -32(%rbp)
	jne	.L517
	leaq	.LC76(%rip), %rdi
	call	THROW
.L517:
	movq	-56(%rbp), %rax
	movq	(%rax), %rbx
.L519:
	movq	%rbx, %rdx
	movq	-64(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	readnxt
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	eqbytes
	testb	%al, %al
	jne	.L518
	movq	-40(%rbp), %rax
	movq	-64(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	pushback
	leaq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	FREE
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	FGETC
	movq	-32(%rbp), %rax
	movzbl	15(%rax), %eax
	testb	%al, %al
	je	.L519
	jmp	.L522
.L518:
	movq	-40(%rbp), %rax
	movq	-64(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	pushback
	movl	$1, %eax
	jmp	.L516
.L522:
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	FCLOSE
	movl	$0, %eax
.L516:
	movq	-24(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L521
	call	__stack_chk_fail@PLT
.L521:
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE102:
	.size	substr_loc_STREAM, .-substr_loc_STREAM
	.globl	print_tofile
	.type	print_tofile, @function
print_tofile:
.LFB103:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$48, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, %eax
	movb	%al, -52(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %r12
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	movl	$0, %ebx
	jmp	.L524
.L525:
	movq	-24(%rbp), %rax
	addq	%rbx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	movq	-48(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fputc@PLT
	addq	$1, %rbx
.L524:
	cmpq	%r12, %rbx
	jb	.L525
	cmpb	$0, -52(%rbp)
	je	.L527
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	FCLOSE
.L527:
	nop
	addq	$48, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE103:
	.size	print_tofile, .-print_tofile
	.globl	main
	.type	main, @function
main:
.LFB104:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	cmpl	$1, -36(%rbp)
	jg	.L529
	movl	$1, %eax
	jmp	.L530
.L529:
	movq	-48(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi@PLT
	movl	%eax, -20(%rbp)
	cmpl	$0, -20(%rbp)
	jne	.L531
	movl	$1, %eax
	jmp	.L530
.L531:
	movl	$10, %edi
	call	MALLOC
	movq	%rax, -16(%rbp)
	movl	$0, -24(%rbp)
	jmp	.L532
.L533:
	movl	-24(%rbp), %eax
	cltq
	negq	%rax
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movb	$2, (%rax)
	movl	-24(%rbp), %eax
	cltq
	leaq	10(%rax), %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movb	$3, (%rax)
	movl	-24(%rbp), %eax
	movl	%eax, %edi
	call	PRINTN
	addl	$1, -24(%rbp)
.L532:
	cmpl	$63, -24(%rbp)
	jle	.L533
	movq	$10, -16(%rbp)
	movl	$10, %edi
	call	free@PLT
	movl	$1, %edi
	call	EXIT
	movl	-20(%rbp), %eax
	movl	$0, %ecx
	movl	$0, %edx
	movl	%eax, %esi
	movl	$16, %edi
	movl	$0, %eax
	call	ptrace@PLT
	movq	%rax, -8(%rbp)
	movl	$0, %edi
	call	wait@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	PRINTLLN
	movl	$0, %eax
.L530:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE104:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
