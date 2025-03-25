// Added by Thomas Joel on 03/25/25
#pragma once

#include "../../../../libobs/util/c99defs.h"
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

struct display_info {
    char device_id[128];
	RECT rect;
    struct display_info *next;
    struct display_info *prev;
};

extern void get_displays(struct display_info **display_list_head_ptr);

#ifdef __cplusplus
}
#endif
// End of addition