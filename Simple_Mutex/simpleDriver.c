#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kthread.h>
#include<linux/delay.h>

MODULE_AUTHOR("kalyan");
MODULE_LICENSE("GPL");

static struct task_struct *char_thread;
static struct task_struct *char_thread1;
int my_thread_fun(void *p)
{
	while(!kthread_should_stop())
	{
		printk(KERN_INFO"My thread 1 is started");
		Msleep(1000);
	}
	return 0;
}

static int __init my_simpledriver_init(void)
{
	printk(KERN_INFO"My simple driver is started");
	
	char_thread=kthread_run(my_thread_fun,NULL,"my char thread");
	
	if(char_thread)
	{
		printk(KERN_INFO"thread is created");
		//wake_up_process(char_thread);
	}
	else
	{
		printk(KERN_INFO"unable to create the thread");
	}
	return 0;

}

static void __exit my_simpledriver_exit(void)
{
	printk(KERN_INFO"MY sample driver exit\n");
	kthread_stop(char_thread);

}


module_init(my_simpledriver_init);
module_exit(my_simpledriver_exit);

