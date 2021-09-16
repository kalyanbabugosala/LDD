#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x19fdd0c3, "module_layout" },
	{ 0x37a0cba, "kfree" },
	{ 0xed3264a3, "class_destroy" },
	{ 0x1501b61a, "device_destroy" },
	{ 0xd1ff3d1f, "kmem_cache_alloc_trace" },
	{ 0x5f3af44c, "kmalloc_caches" },
	{ 0xf2204d2a, "device_create" },
	{ 0x1446a138, "__class_create" },
	{ 0x65022fd0, "cdev_del" },
	{ 0xaf610163, "cdev_add" },
	{ 0x804ff8b3, "cdev_init" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x5b057f3c, "cdev_alloc" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xe1afa723, "module_refcount" },
	{ 0xa16e68a5, "current_task" },
	{ 0xc5850110, "printk" },
	{ 0x21271fd0, "copy_user_enhanced_fast_string" },
	{ 0x1f199d24, "copy_user_generic_string" },
	{ 0xecdcabd2, "copy_user_generic_unrolled" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "466858074AF318CD2FE7212");
