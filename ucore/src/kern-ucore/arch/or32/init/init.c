#include <types.h>
#include <stdio.h>
#include <string.h>
#include <console.h>
#include <gpio.h>
#include <picirq.h>
#include <trap.h>
#include <clock.h>
#include <intr.h>
#include <pmm.h>
#include <vmm.h>
#include <ide.h>
#include <fs.h>
#include <swap.h>
#include <proc.h>
#include <sched.h>
#include <or32.h>

int kern_init(void) __attribute__((noreturn));

int
kern_init(void) {
    extern char edata[], end[];
    memset(edata, 0, end - edata);
	
    cons_init();                // init the console

    const char *message = "(THU.CST) os is loading ...";
    cprintf ("%s\n\n", message);

	pmm_init();                 // init physical memory management

    pic_init();                 // init interrupt controller

	vmm_init();                 // init virtual memory management
    sched_init();               // init scheduler
	proc_init();                // init process table
    sync_init();                // init sync struct
	
	ide_init();                 // init ide devices
    swap_init();                // init swap
    fs_init();                  // init fs

    clock_init();               // init clock interrupt
    intr_enable();              // enable irq interrupt    

    cpu_idle();                 // run idle process
}
