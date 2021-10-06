#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>

#define SHARED_IRQ1 19
#define SHARED_IRQ2 20

spinlock_t etx_spinlock;

static int irq1 = SHARED_IRQ1,irq2=SHARED_IRQ2, my_dev_id, irq_counter = 0;
module_param (irq1, int, S_IRUGO);
module_param (irq2, int, S_IRUGO);

static irqreturn_t my_interrupt1 (int irq, void *dev_id)
{
    spin_lock(&etx_spinlock);
    irq_counter++;
    printk (KERN_INFO "In the ISR routine1: counter = %d\n", irq_counter);
    spin_unlock(&etx_spinlock);
    return IRQ_NONE;            /* we return IRQ_NONE because we are just observing */
}
static irqreturn_t my_interrupt2 (int irq, void *dev_id)
{
    spin_lock(&etx_spinlock);
    irq_counter++;
    printk (KERN_INFO "In the ISR routine2: counter = %d\n", irq_counter);
    spin_unlock(&etx_spinlock);
    return IRQ_NONE;            /* we return IRQ_NONE because we are just observing */
}

static int __init my_init (void)
{
	spin_lock_init(&etx_spinlock);
    if (request_irq(irq1, my_interrupt1, IRQF_SHARED, "my_interrupt1", &my_dev_id))
        return -1;
    printk (KERN_INFO "Successfully loading ISR handler1\n");
    
    if (request_irq(irq2, my_interrupt2, IRQF_SHARED, "my_interrupt2", &my_dev_id))
        return -1;
    printk (KERN_INFO "Successfully loading ISR handler2\n");
    
    return 0;
}

static void __exit my_exit (void)
{
    synchronize_irq (irq1);
    synchronize_irq (irq2);
    free_irq (irq1, &my_dev_id);
    free_irq (irq2, &my_dev_id);
    printk (KERN_INFO "Successfully unloading \n");
}

module_init (my_init);
module_exit (my_exit);

MODULE_AUTHOR ("Kalyan");
MODULE_DESCRIPTION ("Interrupt Handler Test");
MODULE_LICENSE ("GPL");
