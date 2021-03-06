#ifdef ARM9
#include "arm9/source/common.h"
#include "arm9/source/hid.h"
#else
#include <3ds.h>
#endif
#include <time.h>

#include "config.h"
#include "draw.h"
#include "menu.h"
#include "utility.h"

void keyLeft(int index) {

    switch (index) {
        case 0:
            if (config->timeout > -1)
                config->timeout--;
            break;
        case 1:
            if (config->index > 0)
                config->index--;
            else
                config->index = config->count - 1;
            break;
        case 2:
            if (config->recovery > 0)
                config->recovery--;
            else
                config->recovery = 11;
            break;
        case 3:
            if (config->autobootfix > 0)
                config->autobootfix--;
            break;
    }
}

void keyRight(int index) {

    switch (index) {
        case 0:
            config->timeout++;
            break;
        case 1:
            if (config->index < config->count - 1)
                config->index++;
            else
                config->index = 0;
            break;
        case 2:
            if (config->recovery < 11)
                config->recovery++;
            else
                config->recovery = 0;
            break;
        case 3:
            config->autobootfix++;
            break;
    }
}

int menu_config() {
#ifdef ARM9
    int menu_count = 3, menu_index = 0;
#else
    int menu_count = 4, menu_index = 0;
#endif
    // key repeat timer
    time_t t_start = 0, t_end = 0, t_elapsed = 0;

    while (aptMainLoop()) {

        hidScanInput();
        u32 kHeld = hidKeysHeld();
        u32 kDown = hidKeysDown();

#ifndef ARM9
        if (hidKeysUp()) {
            time(&t_start); // reset held timer
        }
#endif
        if (kDown & KEY_DOWN) {
            menu_index++;
            if (menu_index >= menu_count)
                menu_index = 0;
        }
        else if (kDown & KEY_UP) {
            menu_index--;
            if (menu_index < 0)
                menu_index = menu_count - 1;
        }

        if (kDown & KEY_LEFT) {
            keyLeft(menu_index);
            time(&t_start);
        } else if (kHeld & KEY_LEFT) {
            time(&t_end);
            t_elapsed = t_end - t_start;
            if (t_elapsed > 0) {
                keyLeft(menu_index);
                svcSleep(100);
            }
        }

        if (kDown & KEY_RIGHT) {
            keyRight(menu_index);
            time(&t_start);
        } else if (kHeld & KEY_RIGHT) {
            time(&t_end);
            t_elapsed = t_end - t_start;
            if (t_elapsed > 0) {
                keyRight(menu_index);
                svcSleep(100);
            }
        }

        if (kDown & KEY_B) {
            configSave();
            return 0;
        }

        drawBg();
        drawTitle("*** Boot configuration ***");

        drawItem(menu_index == 0, 0, "Timeout:  %i", config->timeout);
        drawItem(menu_index == 1, 16, "Default:  %s", config->entries[config->index].title);
        drawItem(menu_index == 2, 32, "Recovery key:  %s", get_button(config->recovery));
#ifndef ARM9
        drawItem(menu_index == 3, 48, "Bootfix:  %i", config->autobootfix);
        drawInfo("CtrBootManager v2.1.1");
#else
        drawInfo("CtrBootManager9 v2.1.1");    
#endif

        swapFrameBuffers();
    }
    return -1;
}
