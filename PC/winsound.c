/*
 * NSN (Network Security Navigator)
 * Copyright (c) NSN Contributors
 * Licensed under MIT License
 *
 * File: winsound.c
 * Description: Windows Sound API implementation.
 */

#include "nsn.h"
#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>

static nsn_object *winsound_Beep(nsn_object *self, nsn_object *args) {
    /* TODO: Parse freq, duration */
    Beep(1000, 100);
    return Nsn_None;
}

static nsn_object *winsound_MessageBeep(nsn_object *self, nsn_object *args) {
    MessageBeep(MB_OK);
    return Nsn_None;
}

static nsn_object *winsound_PlaySound(nsn_object *self, nsn_object *args) {
    /* TODO: Implement PlaySoundA */
    return Nsn_None;
}

static nsn_method winsound_methods[] = {
    {"Beep", winsound_Beep},
    {"MessageBeep", winsound_MessageBeep},
    {"PlaySound", winsound_PlaySound},
    {NULL, NULL}
};

void _nsn_init_winsound(void) {
    nsn_object *m = nsn_module_new("winsound");
}
#endif
