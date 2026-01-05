/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: future.c
 * Description: Support for future language features.
 */

#include "nsn.h"

typedef struct {
    const char *name;
    int mandatory_version;
} nsn_future_feature;

static nsn_future_feature _features[] = {
    {"nested_scopes", 1},
    {"generators", 2},
    {"division", 3},
    {NULL, 0}
};

int NsnFuture_Check(const char *name) {
    for (int i = 0; _features[i].name != NULL; i++) {
        if (strcmp(name, _features[i].name) == 0) {
            return _features[i].mandatory_version;
        }
    }
    return -1;
}
