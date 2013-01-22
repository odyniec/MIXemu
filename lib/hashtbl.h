#ifndef _HASHTBL_H
#define _HASHTBL_H 1

typedef struct _el {
    char *key;
    void *data;
    struct _el *next;
} hashelem_t;

typedef struct _htbl {
    int n;
    hashelem_t **buckets;
    unsigned (*hashfunc)(struct _htbl *, char *);
} hashtbl_t;


void hashtbl_init(hashtbl_t **tbl, int n);

int hashtbl_put(hashtbl_t *tbl, char *key, void *data);

void * hashtbl_get(hashtbl_t *tbl, char *key);

void hashtbl_free(hashtbl_t *tbl);

void hashtbl_foreach(hashtbl_t *tbl, void (*doelem)(hashelem_t *));


unsigned hashtbl_hashpjw(hashtbl_t *tbl, char *key);

#endif /* hashtbl.h */
