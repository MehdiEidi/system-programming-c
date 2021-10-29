#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/param.h>
#include <linux/jiffies.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

// name of the /proc entry that will be created by loading the module.
#define PROC_NAME "uptime_mod"

static ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t *pos);

static struct proc_ops fproc_ops = {
    .proc_read = proc_read,
};

// mod_init runs when module loads on the kernel
static int mod_init(void) {
    proc_create(PROC_NAME, 0, NULL, &fproc_ops);

    printk(KERN_INFO "/proc/%s created\n", PROC_NAME);

	return 0;
}

// mod_exit runs when module exits from the kernel
static void mod_exit(void) {
    remove_proc_entry(PROC_NAME, NULL);

    printk( KERN_INFO "/proc/%s removed\n", PROC_NAME);
}

// proc_read will be called when the /proc entry created by the module is been called.
static ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos) {
    long long seconds;
    seconds = (jiffies - INITIAL_JIFFIES) / HZ;

    char buffer[100];
    int r = 0;
        
    static int completed = 0;

    if (completed) {
       completed = 0;
       return 0;
    }

    completed = 1;

    // logic below will convert the seconds to more readable hour/minute/second format.
    int m;
    int h;
    int s;

    m = seconds / 60;
    s = seconds - m * 60;

    h = m / 60;
    m = m - h * 60;

    r = snprintf(buffer, 100, "%d hours %d minutes %d seconds passed...\n", h, m, s, seconds);

    copy_to_user(usr_buf, buffer, r);

    return r;
}

module_init(mod_init);
module_exit(mod_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Compute and display the OS uptime");
MODULE_AUTHOR("MehdiEidi");
