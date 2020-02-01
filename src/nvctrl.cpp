#include <stdio.h>
#include "nvctrl.h"
Display *display;

char* get_attr_target_string(int attr, int target_type, int target_id) {
		display = XOpenDisplay(NULL);
        char* c;
        if (!XNVCTRLQueryTargetStringAttribute(display, target_type, target_id, 0, attr, &c)) {
                fprintf(stderr, "Failed to query attribute.");
                
        }
        return c;
}

void queryNVCtrl(){
        display = XOpenDisplay(NULL);
        int attr = NV_CTRL_STRING_GPU_UTILIZATION;
        char* utilization = get_attr_target_string(attr, NV_CTRL_TARGET_TYPE_GPU, 0);
        printf("%s\n", utilization);
		int temp;
		XNVCTRLQueryTargetAttribute(display,
						  NV_CTRL_TARGET_TYPE_GPU,
						  0,
						  0,
						  NV_CTRL_GPU_CORE_TEMPERATURE,
						  &temp);
		printf("temp: %i\n", temp);
		int memtotal;
				XNVCTRLQueryTargetAttribute(display,
						  NV_CTRL_TARGET_TYPE_GPU,
						  0,
						  0,
						  NV_CTRL_TOTAL_DEDICATED_GPU_MEMORY,
						  &memtotal);
		printf("mem total: %i\n", memtotal);
		int memused;
				XNVCTRLQueryTargetAttribute(display,
						  NV_CTRL_TARGET_TYPE_GPU,
						  0,
						  0,
						  NV_CTRL_USED_DEDICATED_GPU_MEMORY,
						  &memused);
		printf("mem used: %i\n", memused);
}