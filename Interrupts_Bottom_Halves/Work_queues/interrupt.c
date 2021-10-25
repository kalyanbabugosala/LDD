/*#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>


#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fcntl.h> /*Helps fix O_ACCMODE*/
#include <linux/sched.h> /*Helps fix TASK_UNINTERRUPTIBLE */
#include <linux/fs.h> /*Helps fix the struct intializer */

#include<linux/slab.h>                 //kmalloc()
#include<linux/uaccess.h>              //copy_to/from_user()
#include <linux/ioctl.h>

#include <linux/proc_fs.h>    // proc file system
#include <linux/compiler.h>
#include <linux/types.h>
#include <linux/proc_ns.h>

#include <linux/kobject.h>

#include <linux/interrupt.h>

#include <linux/kthread.h> // therad 
#include <linux/delay.h>   // sleep 
#include <linux/sched.h>               //task_struct

#include <linux/timer.h>
#include <linux/jiffies.h>

#include <linux/workqueue.h> // Required for workqueues

#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <asm/uaccess.h>



#define SHARED_IRQ 19
static int irq = SHARED_IRQ, my_dev_id, irq_counter = 0;
module_param (irq, int, S_IRUGO);



void workq_fn(struct work_struct *work); 
DECLARE_WORK(workq,workq_fn); 

void workq_fn(struct work_struct *work)
{
	
	//long c;
	printk(KERN_INFO"my work queue static function");
	
	if(in_interrupt())
        printk(KERN_INFO "Running as an interrupt");
	else
		 printk(KERN_INFO "Running as an processt");
	
	atomic_long_set(&(workq.data),10);	
	printk(KERN_INFO "In workq function %u",atomic_long_read(&(workq.data)));
	
	
}



static irqreturn_t my_interrupt (int irq, void *dev_id)
{
	printk (KERN_INFO "Started ISR:\n");
	schedule_work(&workq);
	printk (KERN_INFO "Stopped ISR:\n");
    
    return IRQ_NONE;            /* we return IRQ_NONE because we are just observing */
}

static int __init my_init (void)
{
    if (request_irq(irq, my_interrupt, IRQF_SHARED, "my_interrupt", &my_dev_id))
        return -1;
    printk (KERN_INFO "Successfully loading ISR handler\n");
    
    	
	
    return 0;
}

static void __exit my_exit (void)
{
	flush_scheduled_work();
	printk(KERN_INFO"My workqueue exit  static function");
    	synchronize_irq (irq);
    	free_irq (irq, &my_dev_id);
    	printk (KERN_INFO "Successfully unloading \n");
}

module_init (my_init);
module_exit (my_exit);

MODULE_AUTHOR ("Kalyan");
MODULE_DESCRIPTION ("work queue  driver");
MODULE_LICENSE ("GPL");
