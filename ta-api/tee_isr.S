#include "core_cm1.h"
#include "tee_isr.h"

.syntax unified

.extern _open_session
.extern _close_session
.extern _invoke_command


# -------------------------------------------------------------
.section        .text.tee_isr
# -------------------------------------------------------------
.align 2
tee_isr_tbl:
# -------------------------------------------------------------
  .word   _open_session
  .word   _close_session
  .word   _invoke_command




# -------------------------------------------------------------
.section        .text.tee_isr
# -------------------------------------------------------------

# -------------------------------------------------------------
.align 2
.global         _tee_entry
.type           _tee_entry, %function
_tee_entry:
 # -------------------------------------------------------------    
  push    {lr}

  ldr     r0, =TEE_OP_ARGS
  ldr     r1, [r0]              //obtain intended function
  ldr     r0, =(tee_isr_tbl)
  lsls    r1, r1, #2
  ldr     r0, [r0, r1]                                                          // Get the tee handle
  blx     r0
  
  @  # clear interrupt
  ldr     r0, =0xBEEF
  ldr     r1, =TEE_RETURN_ARGS
  str     r0, [r1]                                                             // Get the tee handle
  pop     {pc}
