#include "nsn.h"

/*
 * NSN Version Information
 */

const char *nsn_get_version(void) {
    return NSN_VERSION;
}

const char *nsn_get_platform(void) {
#ifdef _WIN32
    return "windows";
#elif defined(__ANDROID__)
    return "android";
#elif defined(__APPLE__)
    return "macos";
#else
    return "linux";
#endif
}

const char *nsn_get_copyright(void) {
    return "Copyright (c) 2026 NSN Team. MIT License.";
}
