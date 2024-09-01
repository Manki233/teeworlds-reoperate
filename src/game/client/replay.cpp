#include "replay.h"
#include <conio.h>

#include "gameclient.h"
#include <game/client/components/controls.h>

#include <game/generated/protocol.h>
#include <base/system.h>

#include <fstream>

void CReplay :: OnInputSnap () {
    if (Status == 1) {
        File. open ("rec.ins", std :: ios :: in | std :: ios :: out | std :: ios :: trunc);
        Status = 0;
        Frame = 0;
    }

    if (Status == 0) { // record mode
        File << Frame << " ";
        File << pControl -> m_aInputDirectionLeft[g_Config.m_ClDummy] << " ";
        File << pControl -> m_aInputDirectionRight[g_Config.m_ClDummy] << " ";
        File << pControl -> m_aInputData[g_Config.m_ClDummy].m_Jump << " ";
        File << pControl -> m_aMousePos[g_Config.m_ClDummy]. x << " ";
        File << pControl -> m_aMousePos[g_Config.m_ClDummy]. y << " ";
        File << pControl -> m_aInputData[g_Config.m_ClDummy].m_Fire << " ";
        File << pControl -> m_aInputData[g_Config.m_ClDummy].m_Hook << " ";
        File << g_Config.m_ClDummy << "\n";

        Frame ++;
    }

    if (Status == 2) {
        File << -1 << "\n";

        File. close ();
        File. open ("rec.ins", std :: ios :: in | std :: ios :: out);
        Status = 3;
    }

    if (Status == 3) { // load mode
        File >> Frame;
        if (Frame == -1) {
            Frame ++;
            Status = -1;
        }

        File >> pControl -> m_aInputDirectionLeft[g_Config.m_ClDummy];
        File >> pControl -> m_aInputDirectionRight[g_Config.m_ClDummy];
        File >> pControl -> m_aInputData[g_Config.m_ClDummy].m_Jump;
        File >> pControl -> m_aMousePos[g_Config.m_ClDummy]. x;
        File >> pControl -> m_aMousePos[g_Config.m_ClDummy]. y;
        File >> pControl -> m_aInputData[g_Config.m_ClDummy].m_Fire;
        File >> pControl -> m_aInputData[g_Config.m_ClDummy].m_Hook;
        File >> g_Config.m_ClDummy;
    }
}