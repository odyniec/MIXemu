#ifndef _MIX_DEV_H
#define _MIX_DEV_H 1

#include <stdio.h>
#include "mix_types.h"


/* Set device file pointer */
int mix_dev_set_fp(int n, FILE *fp);

/* Set device position */
int mix_dev_set_pos(int n, long pos);

/* Set device position relatively to current */
int mix_dev_rel_pos(int n, long pos);

/* Read data block from a device */
int mix_dev_read(int n, mix_addr_t addr);

/* Write data block to a device */
int mix_dev_write(int n, mix_addr_t addr);


#endif   /* mix_dev.h */
