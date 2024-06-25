#include <stdio.h>
#include <string.h>

#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/avconfig.h> 
#include <psp2/registrymgr.h>
#include <psp2/appmgr.h> 
#include <psp2/kernel/threadmgr.h> 



#include "debugScreen.h"

#define printf psvDebugScreenPrintf

#define REG_DISPLAY_CATEGORY "/CONFIG/DISPLAY/"
#define REG_KEY_CSM "color_space_mode"
#define REG_PSP_DISPLAY_CATEGORY "/CONFIG/PSPEMU/SETTINGS/"
#define REG_PSP_KEY_CSM "color_space"
#define REG_KEY_BRIGHTNESS "brightness"

int csm;

int getRegMgrKeyInt(char *path, char *keyName) {
    int value = -1, returnOf = 0;

    returnOf = sceRegMgrGetKeyInt(path, keyName, &value);

    if (returnOf < 0)
        return returnOf;
    else
        return value;
}

void toggleLcdEmu() {
    csm = getRegMgrKeyInt(REG_DISPLAY_CATEGORY, REG_KEY_CSM);

    sceKernelDelayThread(1 * 100000);

    sceRegMgrSetKeyInt(REG_DISPLAY_CATEGORY, REG_KEY_CSM, 1 - csm);
    sceRegMgrSetKeyInt(REG_PSP_DISPLAY_CATEGORY, REG_PSP_KEY_CSM, 1 - csm);
    sceAVConfigSetDisplayColorSpaceMode(1 - csm);
}

void closeAdrenalineAfterDelay() {
    //todo
}

void launchAndTerminatePspEmu() {
    sceAppMgrLaunchAppByUri(0xFFFFF, "psgm:play?titleid=PSPEMUCFW");
}

int main(int argc, char *argv[]) {
    psvDebugScreenInit();

    toggleLcdEmu();

    launchAndTerminatePspEmu();

    return 0;
}
