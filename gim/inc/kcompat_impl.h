#ifndef _KCOMPAT_IMPL_H_
#define _KCOMPAT_IMPL_H_

/* NEED_KMEM_CACHE_ALLOC_LRU
 *
 * Added in commit 88f2ef73fd66 ("mm: introduce kmem_cache_alloc_lru"),
 * later changed to macro.
 *
 * This improves memory usage, and fallbacks to old impl when lru is NULL,
 * or just when non "_lru" variant is called. We will do that.
 */
static inline void *
kmem_cache_alloc_lru(struct kmem_cache *s, struct list_lru *lru, gfp_t gfpflags)
{
	return kmem_cache_alloc(s, gfpflags);
}

#endif /* _KCOMPAT_IMPL_H_ */
