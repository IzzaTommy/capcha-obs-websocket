// Added by Thomas Joel on 03/25/25
#include "Display.h"

static BOOL CALLBACK enum_display(HMONITOR handle, HDC hdc, LPRECT rect, LPARAM param)
{
	struct display_info **display_list_head_ptr = (struct display_info **)param;
    struct display_info *temp = NULL;
    MONITORINFOEXA info;
    DISPLAY_DEVICEA device;

    info.cbSize = sizeof(info);
    device.cb = sizeof(device);

    if (!(*display_list_head_ptr)) {
        (*display_list_head_ptr) = (struct display_info *)malloc(sizeof(struct display_info));

        if (*display_list_head_ptr) {
            (*display_list_head_ptr) -> next = NULL;
            (*display_list_head_ptr) -> prev = NULL;
        }
        else {
            return FALSE;
        }
    }
    else {
        temp = (*display_list_head_ptr);
        (*display_list_head_ptr) -> next = (struct display_info *)malloc(sizeof(struct display_info));

        if (*display_list_head_ptr) {
            (*display_list_head_ptr) = (*display_list_head_ptr) -> next;
            (*display_list_head_ptr) -> next = NULL;
            (*display_list_head_ptr) -> prev = temp;
        }
        else {
            (*display_list_head_ptr) = temp;

            return FALSE;
        }
    }

    if (GetMonitorInfoA(handle, (LPMONITORINFO)&info) && EnumDisplayDevicesA(info.szDevice, 0, &device, EDD_GET_DEVICE_INTERFACE_NAME)) {
        strcpy_s((*display_list_head_ptr) -> device_id, sizeof((*display_list_head_ptr) -> device_id), device.DeviceID);

        (*display_list_head_ptr) -> rect = *rect;
    }
    else {
        free((*display_list_head_ptr));

        if (!temp) {
            (*display_list_head_ptr) = NULL;
        }
        else {
            (*display_list_head_ptr) = temp;
        }

        return FALSE;
    }

	UNUSED_PARAMETER(hdc);

	return TRUE;
}

void get_displays(struct display_info **display_list_head_ptr)
{
	EnumDisplayMonitors(NULL, NULL, enum_display, (LPARAM)display_list_head_ptr);
}
// End of addition