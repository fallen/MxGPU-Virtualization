#ifndef _KCOMPAT_H_
#define _KCOMPAT_H_

#include "kcompat_xarray.h"
#include <linux/module.h>

void kc_xarray_global_init(void);
static int __init kc_module_init_impl(void)
{
	kc_xarray_global_init();
	return 0;
}

#if GCC_VERSION >= 90100
#ifndef __copy
#define __copy(symbol)                 __attribute__((__copy__(symbol)))
#endif
#endif

#define ___ADDRESSABLE(sym, __attrs)						\
	static void * __used __attrs						\
	__UNIQUE_ID(__PASTE(addressable_, sym)) = (void *)(uintptr_t)&sym;

#undef module_init
#define orig_module_init(initfn)	\
	static inline initcall_t __maybe_unused __inittest(void)\
	{ return initfn; }					\
	int init_module(void) __copy(initfn)			\
		__attribute__((alias(#initfn)));		\
	___ADDRESSABLE(init_module, __initdata);

#define module_init(driver_init_fn)			\
static int __init kc_module_init_fn(void)		\
{							\
	kc_module_init_impl();				\
	return driver_init_fn();			\
}							\
orig_module_init(kc_module_init_fn)

/*****************************************************************************/
/*
 * Load the implementations file which actually defines kcompat backports.
 * Legacy backports still exist in this file, but all new backports must be
 * implemented using kcompat_*defs.h and kcompat_impl.h
 */
#include "kcompat_impl.h"

#endif
