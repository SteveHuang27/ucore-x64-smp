#include <arch.h>
#include <console.h>
#include <intr.h>
#include <host_signal.h>
#include <pmm.h>
#include <kio.h>
#include <vmm.h>
#include <proc.h>
#include <sched.h>
#include <mp.h>

void
host_exit (int sig)
{
	cons_dtor ();
	syscall1 (__NR_exit, 0);
}

/**
 * The entry.
 */
int main (int argc, char* argv[], char* envp[])
{
	if (ginfo->status == STATUS_DEBUG)
		raise (SIGTRAP);
	
	cons_init ();
	intr_init ();
	ide_init ();

	host_signal_init ();

	/* Only to initialize lcpu_count. */
	mp_init ();

	pmm_init ();
	vmm_init ();
    sched_init();
	proc_init ();
	
	swap_init ();
	//fs_init ();
    //sync_init();

	//device_init_post ();
	//cpu_idle ();

	host_exit (SIGINT);
	
	return 0;
}

