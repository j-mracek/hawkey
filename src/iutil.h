#ifndef HY_IUTIL_H
#define HY_IUTIL_H

// libsolv
#include <solv/bitmap.h>
#include <solv/queue.h>
#include <solv/repo.h>
#include <solv/rules.h>
#include <solv/transaction.h>

// hawkey
#include "packagelist.h"
#include "sack.h"

#define CHKSUM_BYTES 32

// log levels (see also SOLV_ERROR etc. in <solv/pool.h>)
#define HY_LL_INFO  (1 << 20)
#define HY_LL_ERROR (1 << 21)

#define HY_LOG_INFO(...) sack_log(sack, HY_LL_INFO, __VA_ARGS__)
#define HY_LOG_ERROR(...) sack_log(sack, HY_LL_ERROR, __VA_ARGS__)

/* crypto utils */
int checksum_cmp(const unsigned char *cs1, const unsigned char *cs2);
int checksum_fp(unsigned char *out, FILE *fp);
int checksum_read(unsigned char *csout, FILE *fp);
int checksum_stat(unsigned char *out, FILE *fp);
int checksum_write(const unsigned char *cs, FILE *fp);
void checksum_dump(const unsigned char *cs);
int checksum_type2length(int type);
int checksumt_l2h(int type);

/* filesystem utils */
int is_readable_rpm(const char *fn);
int mkcachedir(char *path);
char *this_username(void);

/* misc utils */
unsigned count_nullt_array(const char **a);
int str_endswith(const char *haystack, const char *needle);
int str_startswith(const char *haystack, const char *needle);
char *pool_tmpdup(Pool *pool, const char *s);
char *hy_strndup(const char *s, size_t n);

/* libsolv utils */
void repo_internalize_trigger(Repo *r);
Id str2archid(Pool *pool, const char *s);
void queue2plist(HySack sack, Queue *q, HyPackageList plist);
Id what_upgrades(Pool *pool, Id p);
Id what_downgrades(Pool *pool, Id p);

/* package version utils */
unsigned long pool_get_epoch(Pool *pool, const char *evr);
void pool_split_evr(Pool *pool, const char *evr, char **epoch, char **version,
			char **release);

/* debug utils */
int dump_jobqueue(Pool *pool, Queue *job);
int dump_map(Pool *pool, Map *m);

#endif
