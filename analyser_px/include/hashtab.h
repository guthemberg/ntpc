/* $Id: hashtab.h,v 1.1.1.1 2006/09/15 14:06:30 guto Exp $ */
#ifndef MUCK_HASHTAB_H
#define MUCK_HASHTAB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Comparison function used to check if two hash table entries are the same each other.
   Should return 0 if true, non-zero number otherwise. */
typedef int (*compare_function)(const void *, const void *);

/* Key generating function.  Return the key for a hash table entry. */
typedef unsigned long (*key_function)(const void *);

/* Function to be called when a hash entry is deleted. */
typedef void (*delete_function)(void *);

struct hash_tab;
typedef struct hash_tab hash_tab;

extern void free_hash_table(hash_tab *table);
extern int compare_generic_hash(const void *entry1, const void *entry2);
extern unsigned long make_key_generic_hash(const void *entry);
extern void delete_generic_hash(void *entry);
extern void *find_hash_entry(hash_tab *table, const void *match);
extern int add_hash_entry(hash_tab *table, const void *data);
extern void clear_hash_entry(hash_tab *table, const void *data);
extern void clear_hash_table(hash_tab *table);
extern hash_tab *init_hash_table(const char *id, compare_function cmpfn, key_function keyfn, delete_function delfn, unsigned long size);
extern void init_hash_walk(hash_tab *table);
extern void *next_hash_walk(hash_tab *table);
extern void dump_hashtab_stats(hash_tab *table);
extern long total_hash_entries(void);
extern long num_hash_entries(hash_tab *table);
extern void init_hash_entries(const long count);

#ifdef __cplusplus
}
#endif

#endif /* MUCK_HASHTAB_H */
