/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: _datetimemodule.c
 * Description: Date and time utilities for the NSN interpreter.
 */

#include "nsn.h"
#include <time.h>
#include <string.h>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

/* --- Internal Helpers --- */

typedef struct { NSN_OBJECT_HEAD nsn_object **items; int size; } nsn_list_view;
typedef struct { NSN_OBJECT_HEAD char *data; } nsn_string_object;
typedef struct { NSN_OBJECT_HEAD double dval; } nsn_float_object;
typedef struct { NSN_OBJECT_HEAD long lval; } nsn_int_object;

static long get_int_arg(nsn_object *obj) {
    if (strcmp(obj->ob_type->tp_name, "int") == 0) {
        return ((nsn_int_object *)obj)->lval;
    }
    return 0;
}

static double get_float_arg(nsn_object *obj) {
    if (strcmp(obj->ob_type->tp_name, "float") == 0) {
        return ((nsn_float_object *)obj)->dval;
    } else if (strcmp(obj->ob_type->tp_name, "int") == 0) {
        return (double)((nsn_int_object *)obj)->lval;
    }
    return 0.0;
}

/* --- Module Methods --- */

/**
 * now() -> int
 * Returns the current Unix timestamp.
 */
static nsn_object *datetime_now(nsn_object *self, nsn_object *args) {
    time_t t = time(NULL);
    return nsn_int_from_long((long)t);
}

/**
 * sleep(seconds: float|int) -> None
 * Suspends execution for the given number of seconds.
 */
static nsn_object *datetime_sleep(nsn_object *self, nsn_object *args) {
    nsn_list_view *list = (nsn_list_view *)args;
    if (list->size < 1) {
        NsnErr_SetString(NsnExc_TypeError, "sleep() requires 1 argument");
        return NULL;
    }

    double seconds = get_float_arg(list->items[0]);
    
#ifdef WIN32
    Sleep((DWORD)(seconds * 1000));
#else
    if (seconds >= 1.0) {
        sleep((unsigned int)seconds);
    }
    // Simple microsecond sleep for fractional part
    usleep((useconds_t)((seconds - (long)seconds) * 1000000));
#endif

    Nsn_INCREF(Nsn_None);
    return Nsn_None;
}

/**
 * format(timestamp: int, format: string) -> string
 * Formats a Unix timestamp using strftime.
 */
static nsn_object *datetime_format(nsn_object *self, nsn_object *args) {
    nsn_list_view *list = (nsn_list_view *)args;
    if (list->size < 2) {
        NsnErr_SetString(NsnExc_TypeError, "format() requires 2 arguments (timestamp, format)");
        return NULL;
    }

    long ts = get_int_arg(list->items[0]);
    const char *fmt = "%Y-%m-%d %H:%M:%S";
    
    if (strcmp(list->items[1]->ob_type->tp_name, "string") == 0) {
        fmt = ((nsn_string_object *)list->items[1])->data;
    }

    time_t t = (time_t)ts;
    struct tm *tm_info = localtime(&t);
    char buffer[256];
    
    if (strftime(buffer, sizeof(buffer), fmt, tm_info) == 0) {
        NsnErr_SetString(NsnExc_RuntimeError, "strftime failed");
        return NULL;
    }

    return nsn_string_from_cstring(buffer);
}

/**
 * ctime(timestamp: int) -> string
 * Returns a human-readable string representation of the timestamp.
 */
static nsn_object *datetime_ctime(nsn_object *self, nsn_object *args) {
    nsn_list_view *list = (nsn_list_view *)args;
    long ts = 0;
    
    if (list->size > 0) {
        ts = get_int_arg(list->items[0]);
    } else {
        ts = (long)time(NULL);
    }

    time_t t = (time_t)ts;
    char *s = ctime(&t);
    if (!s) {
        NsnErr_SetString(NsnExc_RuntimeError, "ctime failed");
        return NULL;
    }
    
    // Remove newline
    size_t len = strlen(s);
    if (len > 0 && s[len-1] == '\n') s[len-1] = '\0';

    return nsn_string_from_cstring(s);
}

/* --- Module Registration --- */

typedef struct {
    const char *name;
    nsn_object *(*func)(nsn_object *, nsn_object *);
} nsn_method;

static nsn_method datetime_methods[] = {
    {"now", datetime_now},
    {"sleep", datetime_sleep},
    {"format", datetime_format},
    {"ctime", datetime_ctime},
    {NULL, NULL}
};

void _nsn_init_datetime(void) {
    nsn_object *m = nsn_module_new("datetime");
    if (!m) return;

    for (int i = 0; datetime_methods[i].name; i++) {
        // nsn_module_add_function(m, datetime_methods[i].name, datetime_methods[i].func);
    }
}
