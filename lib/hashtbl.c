#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hashtbl.h"

void hashtbl_init(hashtbl_t **tbl, int n)
{
    int i;

    *tbl = (hashtbl_t *)malloc(sizeof(hashtbl_t));
    assert(*tbl != NULL);

    (*tbl)->n = n;
    (*tbl)->buckets = (hashelem_t **)malloc(n * sizeof(hashelem_t *));
    assert((*tbl)->buckets != NULL);

    (*tbl)->hashfunc = &hashtbl_hashpjw;

    for (i = 0; i < n; i++)
        (*tbl)->buckets[i] = NULL;
}

int hashtbl_put(hashtbl_t *tbl, char *key, void *data)
{
    hashelem_t *el, *pel = NULL;
    hashelem_t *nel = (hashelem_t *)malloc(sizeof(hashelem_t));
    int h, c;

    h = tbl->hashfunc(tbl, key);

    el = tbl->buckets[h];
  
    if (el != NULL) {
        while (el != NULL) {
            if ((c = strcmp(el->key, key)) > 0)
                break;
            else if (c == 0)
                /* Can't add the same key more than once */
                return 1;
            pel = el;
            el = el->next;
        }
    }
  
    nel->key = strdup(key);
    nel->data = data;
    nel->next = el;

    if (pel != NULL)
        pel->next = nel;
    else
        tbl->buckets[h] = nel;

    return 0;
}

void* hashtbl_get(hashtbl_t *tbl, char *key)
{
    hashelem_t *el = tbl->buckets[tbl->hashfunc(tbl, key)];

    while (el != NULL)
        if (strcmp(key, el->key) == 0)
            return el->data;
        else
            el = el->next;

    return NULL;
}

void hashtbl_free(hashtbl_t *tbl)
{
    int i;

    for (i = 0; i < tbl->n; i++)
        if (tbl->buckets[i] != NULL) {
            hashelem_t *el = tbl->buckets[i], *nel;
            nel = el->next;

            while (el != NULL) {
                free(el->key);
                /* We assume nel->data is already free */
                free(el);
                if ((el = nel) != NULL)
                    nel = nel->next;
            }
        }

    free(tbl->buckets);
    free(tbl);
}

void hashtbl_foreach(hashtbl_t *tbl, void (*doelem)(hashelem_t *))
{   
    int i;

    for (i = 0; i < tbl->n; i++)
        if (tbl->buckets[i] != NULL) {
            hashelem_t *el = tbl->buckets[i];

            while (el != NULL) {
                (*doelem)(el);
                el = el->next;
            }
        }
}

unsigned hashtbl_hashpjw(hashtbl_t *tbl, char *key)
{
    char *p;
    unsigned h = 0, g;

    for (p = key; *p != '\0'; p++) {
        h = (h << 4) + (*p);
        if (g = h & 0xf0000000) {
            h = h ^ (g >> 24);
            h = h ^ g;
        }
    }

    return h % (tbl->n);
}
