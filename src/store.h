#ifndef __STORE_H__
#define __STORE_H__

#include "./type.h"

struct _store {
    Vector2i windowSize;
};
typedef struct _store Store;

extern Store store;

void InitStore();

#endif /* __STORE_H__ */
