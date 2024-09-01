#include "replay.h"
#include <conio.h>

#include "gameclient.h"
#include <game/client/components/controls.h>

#include <game/generated/protocol.h>
#include <base/system.h>

#include <fstream>

void CReplay :: OnInputSnap () {
    if (Status == 1) {
        File. open ("rec.ins", std :: ios :: in | std :: ios :: out);
        Status = 0;
    }

    if (Status == 0) { // record mode
        File << pControl -> m_aInputDirectionLeft[0] << " ";
        File << pControl -> m_aInputDirectionRight[0] << " ";
        File << pControl -> m_aInputData[0].m_Jump << " ";
        File << pControl -> m_aMousePos[0]. x << " ";
        File << pControl -> m_aMousePos[0]. y << " ";
        File << pControl -> m_aInputData[0].m_Fire << " ";
        File << pControl -> m_aInputData[0].m_Hook << "\n";;
    }

    if (Status == 2) {
        File. close ();
        File. open ("rec.ins", std :: ios :: in | std :: ios :: out);
        Status = 3;
    }

    if (Status == 3) { // load mode
        File >> pControl -> m_aInputDirectionLeft[0];
        File >> pControl -> m_aInputDirectionRight[0];
        File >> pControl -> m_aInputData[0].m_Jump;
        File >> pControl -> m_aMousePos[0]. x;
        File >> pControl -> m_aMousePos[0]. y;
        File >> pControl -> m_aInputData[0].m_Fire;
        File >> pControl -> m_aInputData[0].m_Hook;

        dbg_msg ("load", "loaded a frame %d, eof = %d", File.is_open(), pControl -> m_aInputData[0].m_Fire);
    }
}