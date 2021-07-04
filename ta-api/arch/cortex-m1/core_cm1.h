#ifndef __CORE_CM1_H
#define __CORE_CM1_H

#define REGSIZE             (4)
#define IRQ0_NMR            (16)

/* Memory mapping of Core Hardware */
#define SCS_BASE            (0xE000E000)                                                /*!< System Control Space Base Address */
#define SysTick_BASE        (SCS_BASE +  0x0010)                                        /*!< SysTick Base Address */
#define NVIC_BASE           (SCS_BASE +  0x0100)                                        /*!< NVIC Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00)                                        /*!< System Control Block Base Address */

/* APSR Register Definitions */
#define APSR_N_Pos                         31                                            /*!< APSR: N Position */
#define APSR_N_Msk                         (1 << APSR_N_Pos)                            /*!< APSR: N Mask */

#define APSR_Z_Pos                         30                                            /*!< APSR: Z Position */
#define APSR_Z_Msk                         (1 << APSR_Z_Pos)                            /*!< APSR: Z Mask */

#define APSR_C_Pos                         29                                            /*!< APSR: C Position */
#define APSR_C_Msk                         (1 << APSR_C_Pos)                            /*!< APSR: C Mask */

#define APSR_V_Pos                         28                                            /*!< APSR: V Position */
#define APSR_V_Msk                         (1 << APSR_V_Pos)                            /*!< APSR: V Mask */

/* IPSR Register Definitions */
#define IPSR_ISR_Pos                        0                                            /*!< IPSR: ISR Position */
#define IPSR_ISR_Msk                       (0x1FF /*<< IPSR_ISR_Pos*/)                  /*!< IPSR: ISR Mask */

/* xPSR Register Definitions */
#define xPSR_N_Pos                         31                                            /*!< xPSR: N Position */
#define xPSR_N_Msk                         (1 << xPSR_N_Pos)                            /*!< xPSR: N Mask */

#define xPSR_Z_Pos                         30                                            /*!< xPSR: Z Position */
#define xPSR_Z_Msk                         (1 << xPSR_Z_Pos)                            /*!< xPSR: Z Mask */

#define xPSR_C_Pos                         29                                            /*!< xPSR: C Position */
#define xPSR_C_Msk                         (1 << xPSR_C_Pos)                            /*!< xPSR: C Mask */

#define xPSR_V_Pos                         28                                            /*!< xPSR: V Position */
#define xPSR_V_Msk                         (1 << xPSR_V_Pos)                            /*!< xPSR: V Mask */

#define xPSR_T_Pos                         24                                            /*!< xPSR: T Position */
#define xPSR_T_Msk                         (1 << xPSR_T_Pos)                            /*!< xPSR: T Mask */

#define xPSR_ISR_Pos                        0                                            /*!< xPSR: ISR Position */
#define xPSR_ISR_Msk                       (0x1FF /*<< xPSR_ISR_Pos*/)                  /*!< xPSR: ISR Mask */

/* Memory mapping of NVIC Registers */
#define NVIC_ISER_BASE                      (NVIC_BASE + 0x0000)                        /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
#define NVIC_ICER_BASE                      (NVIC_BASE + 0x0080)                        /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
#define NVIC_ISPR_BASE                      (NVIC_BASE + 0x0100)                        /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
#define NVIC_ICPR_BASE                      (NVIC_BASE + 0x0180)                        /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
#define NVIC_IP_BASE                        (NVIC_BASE + 0x0300)                        /*!< Offset: 0x300 (R/W)  Interrupt Priority Register */

/* Memory mapping of SCB Registers */
#define SCB_CPUID_BASE                      (SCB_BASE + 0x0000)                         /*!< Offset: 0x000 (R/ )  CPUID Base Register */
#define SCB_ICSR_BASE                       (SCB_BASE + 0x0004)                         /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
#define SCB_AIRCR_BASE                      (SCB_BASE + 0x000C)                         /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
#define SCB_SCR_BASE                        (SCB_BASE + 0x0010)                         /*!< Offset: 0x010 (R/W)  System Control Register */
#define SCB_CCR_BASE                        (SCB_BASE + 0x0014)                         /*!< Offset: 0x014 (R/W)  Configuration Control Register */
#define SCB_SHP_BASE                        (SCB_BASE + 0x001C)                         /*!< Offset: 0x01C (R/W)  System Handlers Priority Registers. [0] is RESERVED */
#define SCB_SHCSR_BASE                      (SCB_BASE + 0x0024)                         /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */

/* CONTROL Register Definitions */
#define CONTROL_SPSEL_Pos                   1                                            /*!< CONTROL: SPSEL Position */
#define CONTROL_SPSEL_Msk                  (1 << CONTROL_SPSEL_Pos)                     /*!< CONTROL: SPSEL Mask */

/* SCB CPUID Register Definitions */
#define SCB_CPUID_IMPLEMENTER_Pos          24                                            /*!< SCB CPUID: IMPLEMENTER Position */
#define SCB_CPUID_IMPLEMENTER_Msk          (0xFF << SCB_CPUID_IMPLEMENTER_Pos)          /*!< SCB CPUID: IMPLEMENTER Mask */

#define SCB_CPUID_VARIANT_Pos              20                                            /*!< SCB CPUID: VARIANT Position */
#define SCB_CPUID_VARIANT_Msk              (0xF << SCB_CPUID_VARIANT_Pos)               /*!< SCB CPUID: VARIANT Mask */

#define SCB_CPUID_ARCHITECTURE_Pos         16                                            /*!< SCB CPUID: ARCHITECTURE Position */
#define SCB_CPUID_ARCHITECTURE_Msk         (0xF << SCB_CPUID_ARCHITECTURE_Pos)          /*!< SCB CPUID: ARCHITECTURE Mask */

#define SCB_CPUID_PARTNO_Pos                4                                            /*!< SCB CPUID: PARTNO Position */
#define SCB_CPUID_PARTNO_Msk               (0xFFF << SCB_CPUID_PARTNO_Pos)              /*!< SCB CPUID: PARTNO Mask */

#define SCB_CPUID_REVISION_Pos              0                                            /*!< SCB CPUID: REVISION Position */
#define SCB_CPUID_REVISION_Msk             (0xF /*<< SCB_CPUID_REVISION_Pos*/)          /*!< SCB CPUID: REVISION Mask */

/* SCB Interrupt Control State Register Definitions */
#define SCB_ICSR_NMIPENDSET_Pos            31                                            /*!< SCB ICSR: NMIPENDSET Position */
#define SCB_ICSR_NMIPENDSET_Msk            (1 << SCB_ICSR_NMIPENDSET_Pos)               /*!< SCB ICSR: NMIPENDSET Mask */

#define SCB_ICSR_PENDSVSET_Pos             28                                            /*!< SCB ICSR: PENDSVSET Position */
#define SCB_ICSR_PENDSVSET_Msk             (1 << SCB_ICSR_PENDSVSET_Pos)                /*!< SCB ICSR: PENDSVSET Mask */

#define SCB_ICSR_PENDSVCLR_Pos             27                                            /*!< SCB ICSR: PENDSVCLR Position */
#define SCB_ICSR_PENDSVCLR_Msk             (1 << SCB_ICSR_PENDSVCLR_Pos)                /*!< SCB ICSR: PENDSVCLR Mask */

#define SCB_ICSR_PENDSTSET_Pos             26                                            /*!< SCB ICSR: PENDSTSET Position */
#define SCB_ICSR_PENDSTSET_Msk             (1 << SCB_ICSR_PENDSTSET_Pos)                /*!< SCB ICSR: PENDSTSET Mask */

#define SCB_ICSR_PENDSTCLR_Pos             25                                            /*!< SCB ICSR: PENDSTCLR Position */
#define SCB_ICSR_PENDSTCLR_Msk             (1 << SCB_ICSR_PENDSTCLR_Pos)                /*!< SCB ICSR: PENDSTCLR Mask */

#define SCB_ICSR_ISRPREEMPT_Pos            23                                            /*!< SCB ICSR: ISRPREEMPT Position */
#define SCB_ICSR_ISRPREEMPT_Msk            (1 << SCB_ICSR_ISRPREEMPT_Pos)               /*!< SCB ICSR: ISRPREEMPT Mask */

#define SCB_ICSR_ISRPENDING_Pos            22                                            /*!< SCB ICSR: ISRPENDING Position */
#define SCB_ICSR_ISRPENDING_Msk            (1 << SCB_ICSR_ISRPENDING_Pos)               /*!< SCB ICSR: ISRPENDING Mask */

#define SCB_ICSR_VECTPENDING_Pos           12                                            /*!< SCB ICSR: VECTPENDING Position */
#define SCB_ICSR_VECTPENDING_Msk           (0x1FF << SCB_ICSR_VECTPENDING_Pos)          /*!< SCB ICSR: VECTPENDING Mask */

#define SCB_ICSR_VECTACTIVE_Pos             0                                            /*!< SCB ICSR: VECTACTIVE Position */
#define SCB_ICSR_VECTACTIVE_Msk            (0x1FF /*<< SCB_ICSR_VECTACTIVE_Pos*/)       /*!< SCB ICSR: VECTACTIVE Mask */

/* SCB Application Interrupt and Reset Control Register Definitions */
#define SCB_AIRCR_VECTKEY_Pos              16                                            /*!< SCB AIRCR: VECTKEY Position */
#define SCB_AIRCR_VECTKEY_Msk              (0xFFFF << SCB_AIRCR_VECTKEY_Pos)            /*!< SCB AIRCR: VECTKEY Mask */

#define SCB_AIRCR_VECTKEYSTAT_Pos          16                                            /*!< SCB AIRCR: VECTKEYSTAT Position */
#define SCB_AIRCR_VECTKEYSTAT_Msk          (0xFFFF << SCB_AIRCR_VECTKEYSTAT_Pos)        /*!< SCB AIRCR: VECTKEYSTAT Mask */

#define SCB_AIRCR_ENDIANESS_Pos            15                                            /*!< SCB AIRCR: ENDIANESS Position */
#define SCB_AIRCR_ENDIANESS_Msk            (1 << SCB_AIRCR_ENDIANESS_Pos)               /*!< SCB AIRCR: ENDIANESS Mask */

#define SCB_AIRCR_SYSRESETREQ_Pos           2                                            /*!< SCB AIRCR: SYSRESETREQ Position */
#define SCB_AIRCR_SYSRESETREQ_Msk          (1 << SCB_AIRCR_SYSRESETREQ_Pos)             /*!< SCB AIRCR: SYSRESETREQ Mask */

#define SCB_AIRCR_VECTCLRACTIVE_Pos         1                                            /*!< SCB AIRCR: VECTCLRACTIVE Position */
#define SCB_AIRCR_VECTCLRACTIVE_Msk        (1 << SCB_AIRCR_VECTCLRACTIVE_Pos)           /*!< SCB AIRCR: VECTCLRACTIVE Mask */

/* SCB System Control Register Definitions */
#define SCB_SCR_SEVONPEND_Pos               4                                            /*!< SCB SCR: SEVONPEND Position */
#define SCB_SCR_SEVONPEND_Msk              (1 << SCB_SCR_SEVONPEND_Pos)                 /*!< SCB SCR: SEVONPEND Mask */

#define SCB_SCR_SLEEPDEEP_Pos               2                                            /*!< SCB SCR: SLEEPDEEP Position */
#define SCB_SCR_SLEEPDEEP_Msk              (1 << SCB_SCR_SLEEPDEEP_Pos)                 /*!< SCB SCR: SLEEPDEEP Mask */

#define SCB_SCR_SLEEPONEXIT_Pos             1                                            /*!< SCB SCR: SLEEPONEXIT Position */
#define SCB_SCR_SLEEPONEXIT_Msk            (1 << SCB_SCR_SLEEPONEXIT_Pos)               /*!< SCB SCR: SLEEPONEXIT Mask */

/* SCB Configuration Control Register Definitions */
#define SCB_CCR_STKALIGN_Pos                9                                            /*!< SCB CCR: STKALIGN Position */
#define SCB_CCR_STKALIGN_Msk               (1 << SCB_CCR_STKALIGN_Pos)                  /*!< SCB CCR: STKALIGN Mask */

#define SCB_CCR_UNALIGN_TRP_Pos             3                                            /*!< SCB CCR: UNALIGN_TRP Position */
#define SCB_CCR_UNALIGN_TRP_Msk            (1 << SCB_CCR_UNALIGN_TRP_Pos)               /*!< SCB CCR: UNALIGN_TRP Mask */

/* SCB System Handler Control and State Register Definitions */
#define SCB_SHCSR_SVCALLPENDED_Pos         15                                            /*!< SCB SHCSR: SVCALLPENDED Position */
#define SCB_SHCSR_SVCALLPENDED_Msk         (1 << SCB_SHCSR_SVCALLPENDED_Pos)            /*!< SCB SHCSR: SVCALLPENDED Mask */

/* Auxiliary Control Register Definitions */
#define SCnSCB_ACTLR_ITCMUAEN_Pos            4                                           /*!< ACTLR: Instruction TCM Upper Alias Enable Position */
#define SCnSCB_ACTLR_ITCMUAEN_Msk           (1 << SCnSCB_ACTLR_ITCMUAEN_Pos)            /*!< ACTLR: Instruction TCM Upper Alias Enable Mask */

#define SCnSCB_ACTLR_ITCMLAEN_Pos            3                                           /*!< ACTLR: Instruction TCM Lower Alias Enable Position */
#define SCnSCB_ACTLR_ITCMLAEN_Msk           (1 << SCnSCB_ACTLR_ITCMLAEN_Pos)            /*!< ACTLR: Instruction TCM Lower Alias Enable Mask */

/* Memory mapping of SysTick Registers */
#define SysTick_CTRL_BASE                  (SysTick_BASE + 0x000)                       /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
#define SysTick_LOAD_BASE                  (SysTick_BASE + 0x004)                       /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
#define SysTick_VAL_BASE                   (SysTick_BASE + 0x008)                       /*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
#define SysTick_CALIB_BASE                 (SysTick_BASE + 0x00C)                       /*!< Offset: 0x00C (R/ )  SysTick Calibration Register */

/* SysTick Control / Status Register Definitions */
#define SysTick_CTRL_COUNTFLAG_Pos         16                                            /*!< SysTick CTRL: COUNTFLAG Position */
#define SysTick_CTRL_COUNTFLAG_Msk         (1 << SysTick_CTRL_COUNTFLAG_Pos)            /*!< SysTick CTRL: COUNTFLAG Mask */

#define SysTick_CTRL_CLKSOURCE_Pos          2                                            /*!< SysTick CTRL: CLKSOURCE Position */
#define SysTick_CTRL_CLKSOURCE_Msk         (1 << SysTick_CTRL_CLKSOURCE_Pos)            /*!< SysTick CTRL: CLKSOURCE Mask */

#define SysTick_CTRL_TICKINT_Pos            1                                            /*!< SysTick CTRL: TICKINT Position */
#define SysTick_CTRL_TICKINT_Msk           (1 << SysTick_CTRL_TICKINT_Pos)              /*!< SysTick CTRL: TICKINT Mask */

#define SysTick_CTRL_ENABLE_Pos             0                                            /*!< SysTick CTRL: ENABLE Position */
#define SysTick_CTRL_ENABLE_Msk            (1 /*<< SysTick_CTRL_ENABLE_Pos*/)           /*!< SysTick CTRL: ENABLE Mask */

/* SysTick Reload Register Definitions */
#define SysTick_LOAD_RELOAD_Pos             0                                            /*!< SysTick LOAD: RELOAD Position */
#define SysTick_LOAD_RELOAD_Msk            (0xFFFFFF /*<< SysTick_LOAD_RELOAD_Pos*/)    /*!< SysTick LOAD: RELOAD Mask */

/* SysTick Current Register Definitions */
#define SysTick_VAL_CURRENT_Pos             0                                            /*!< SysTick VAL: CURRENT Position */
#define SysTick_VAL_CURRENT_Msk            (0xFFFFFF /*<< SysTick_VAL_CURRENT_Pos*/)    /*!< SysTick VAL: CURRENT Mask */

/* SysTick Calibration Register Definitions */
#define SysTick_CALIB_NOREF_Pos            31                                            /*!< SysTick CALIB: NOREF Position */
#define SysTick_CALIB_NOREF_Msk            (1 << SysTick_CALIB_NOREF_Pos)               /*!< SysTick CALIB: NOREF Mask */

#define SysTick_CALIB_SKEW_Pos             30                                            /*!< SysTick CALIB: SKEW Position */
#define SysTick_CALIB_SKEW_Msk             (1 << SysTick_CALIB_SKEW_Pos)                /*!< SysTick CALIB: SKEW Mask */

#define SysTick_CALIB_TENMS_Pos             0                                            /*!< SysTick CALIB: TENMS Position */
#define SysTick_CALIB_TENMS_Msk            (0xFFFFFF /*<< SysTick_CALIB_TENMS_Pos*/)    /*!< SysTick CALIB: TENMS Mask */


/*******************************************************************************
 *                Hardware Abstraction Layer
  Core Function Interface contains:
  - Core NVIC Functions
  - Core SysTick Functions
  - Core Register Access Functions
 ******************************************************************************/

#define NVIC_USER_IRQ_OFFSET          16

/* The following EXC_RETURN values are saved the LR on exception entry */
#define EXC_RETURN_HANDLER         (0xFFFFFFF1)     /* return to Handler mode, uses MSP after return                               */
#define EXC_RETURN_THREAD_MSP      (0xFFFFFFF9)     /* return to Thread mode, uses MSP after return                                */
#define EXC_RETURN_THREAD_PSP      (0xFFFFFFFD)     /* return to Thread mode, uses PSP after return                                */

#endif /* __CORE_CM1_H */
