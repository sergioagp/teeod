#include "arch/cortex-m1/core_cm1.h"
#include "tee_isr.h"

.syntax unified

.section .isr_vector, "ax"
.align 2
.globl    _isr_vector
_isr_vector:
    .long    __StackTop           /* Top of Stack */
    .long    _entry                 /* Reset Handler */
    .long    nmi_handler           /* NMI Handler */
    .long    hardfault_handler     /* Hard Fault Handler */
    .long    memmanage_handler     /* MPU Fault Handler */
    .long    busfault_handler      /* Bus Fault Handler */
    .long    usagefault_handler    /* Usage Fault Handler */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    svc_handler           /* SVCall Handler */
    .long    debugmon_handler      /* Debug Monitor Handler */
    .long    0                     /* Reserved */
    .long    pendsv_handler        /* PendSV Handler */
    .long    systick_handler       /* SysTick Handler */

    /* TEE interrupts */
    .long    _tee_entry    

  .size    _isr_vector, . - _isr_vector

# -------------------------------------------------------------
.section .text.entry
# -------------------------------------------------------------

.align 2
.global     _entry
.type       _entry, %function
_entry:     # Reset Handler
# -------------------------------------------------------------

  ldr     r0, =__StackTop
  mov     sp, r0          /* set stack pointer */

/*  Single section scheme.
 *
 *  The ranges of copy from/to are specified by following symbols
 *    __etext: LMA of start of the section to copy from. Usually end of text
 *    __data_start__: VMA of start of the section to copy to
 *    __data_end__: VMA of end of the section to copy to
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
	ldr	r1, =__etext
	ldr	r2, =__data_start__
	ldr	r3, =__data_end__

	subs	r3, r2
	ble	.L_loop1_done

.L_loop1:
	subs	r3, #4
	ldr	r0, [r1,r3]
	str	r0, [r2,r3]
	bgt	.L_loop1

.L_loop1_done:
/*  Single BSS section scheme.
 *
 *  The BSS section is specified by following symbols
 *    __bss_start__: start of the BSS section.
 *    __bss_end__: end of the BSS section.
 *
 *  Both addresses must be aligned to 4 bytes boundary.
 */
	ldr	r1, =__bss_start__
	ldr	r2, =__bss_end__

	movs	r0, 0

	subs	r2, r1
	ble	.L_loop3_done

.L_loop3:
	subs	r2, #4
	str	r0, [r1, r2]
	bgt	.L_loop3
.L_loop3_done:

  # Init TEE IRQ
  ldr     r0, =NVIC_ISER_BASE
  ldr     r1, =TEE_INT_Msk
  str     r1, [r0]

loop:
  #wfi
  b loop    // Should not run here


/*  Macro to define default handlers. */
.macro    def_irq_handler    handler_name
.align    1
.thumb_func
.weak    \handler_name
\handler_name:
  b        \handler_name
.endm

/* Core exceptions */
def_irq_handler       nmi_handler       
def_irq_handler       hardfault_handler 
def_irq_handler       memmanage_handler 
def_irq_handler       busfault_handler  
def_irq_handler       usagefault_handler
def_irq_handler       svc_handler           
def_irq_handler       debugmon_handler      
def_irq_handler       pendsv_handler        
def_irq_handler       systick_handler       
/* TEE interrupts */
def_irq_handler       _tee_entry

.end