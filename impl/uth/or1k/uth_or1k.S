
.extern uth_thread_trampoline

.global uth_swap
.type uth_swap,@function

/** uth_swap
 * - uth_thread_t *curr (R3)
 * - uth_thread_t *next (R4)
 *
 *
 * - status     (0x0)
 * - stack_base (0x4)
 * - stack_sz   (0x8)
 * - sp         (0xC)
 * -> Save our state to the current thread
 * -> Check whether the next thread is initialized
 *   -> (False): Set context for the next thread, call trampoline
 *   -> (True): Restore context for the next thread, jump 
 * -> Restore context of the current thread
 */
uth_swap:
	// Book keeping
	l.sw 		-8(r1), r2       // Save current frame
	l.addi		r2, r1, 0
	l.sw		-4(r1), r9       // Save return 
	// First, push all registers. We'll have to eventually anyway
	l.sw		-12(r1), r3
	l.sw		-16(r1), r4
	l.sw		-20(r1), r5
	l.sw		-24(r1), r6
	l.sw		-28(r1), r7
	l.sw		-32(r1), r8
	l.sw		-36(r1), r10
	l.sw		-40(r1), r11
	l.sw		-44(r1), r12
	l.sw		-48(r1), r13
	l.sw		-52(r1), r14
	l.sw		-56(r1), r15
	l.sw		-60(r1), r16
	l.sw		-64(r1), r17
	l.sw		-68(r1), r18
	l.sw		-72(r1), r19
	l.sw		-76(r1), r20
	l.sw		-80(r1), r21
	l.sw		-84(r1), r22
	l.sw		-88(r1), r23
	l.sw		-92(r1), r24
	l.sw		-96(r1), r25
	l.sw		-100(r1), r26
	l.sw		-104(r1), r27
	l.sw		-108(r1), r28
	l.sw		-112(r1), r29
	l.sw		-116(r1), r30
	l.sw		-120(r1), r31
//	l.mfspr		r3, r0, 17 // SR
//	l.sw		-124(r1), r3

	// All registers saved. Now store the stack pointer to the thread
	l.sw		12(r3), r1 // Save SP to current

	// Load status and determine what we need to do
	l.lwz		r5, 0(r4) // load next->status
	l.andi		r6, r5, 2 // init flag
	l.sfeqi		r6, 2 // We're already initialized
	l.bf		.Linit
		// Not initialized yet
		l.lwz		r1, 4(r4) // load next->stack_base
		l.lwz		r6, 8(r4) // load next->stack_sz
		l.add		r1, r1, r6
		l.addi		r1, r1, -12	// Adjust stack down
		l.ori		r2, r1, 0	// fp=sp
		l.sw		4(r1), r3	// Save "curr"
		l.sw		8(r1), r4	// Save "next"
		l.ori		r5, r5, 2  	// now initialized
		l.sw		0(r4), r5	// store-back status
		l.ori		r3, r4, 0	// arg1==next
		l.jal		uth_thread_trampoline
		l.nop
		// Assume r1 comes back
		l.lwz		r3, 4(r1)
		l.lwz		r4, 8(r1)

	l.j			.Lrestore
.Linit:	
	// Already initialized
	// Save SP to curr->SP
//	l.sw		1

	// Assume r3,r4 have been restored 
.Lrestore:
	// Restore the stack pointer from curr
	l.lwz		r1, 12(r3)

	// Restore core registers	
//	l.lwz		r3, -124(r1)
//	l.mtspr		r0, r3, 17 // SR
	l.lwz		r3, -12(r1)
	l.lwz		r4, -16(r1)
	l.lwz		r5, -20(r1)
	l.lwz		r6, -24(r1)
	l.lwz		r7, -28(r1)
	l.lwz		r8, -32(r1)
	l.lwz		r10, -36(r1)
	l.lwz		r11, -40(r1)
	l.lwz		r12, -44(r1)
	l.lwz		r13, -48(r1)
	l.lwz		r14, -52(r1)
	l.lwz		r15, -56(r1)
	l.lwz		r16, -60(r1)
	l.lwz		r17, -64(r1)
	l.lwz		r18, -68(r1)
	l.lwz		r19, -72(r1)
	l.lwz		r20, -76(r1)
	l.lwz		r21, -80(r1)
	l.lwz		r22, -84(r1)
	l.lwz		r23, -88(r1)
	l.lwz		r24, -92(r1)
	l.lwz		r25, -96(r1)
	l.lwz		r26, -100(r1)
	l.lwz		r27, -104(r1)
	l.lwz		r28, -108(r1)
	l.lwz		r29, -112(r1)
	l.lwz		r30, -116(r1)
	l.lwz		r31, -120(r1)

	l.lwz		r2, -8(r1)
	l.lwz		r9, -4(r1)


	l.jr	r9
	l.nop

	.size uth_swap,.-uth_swap

