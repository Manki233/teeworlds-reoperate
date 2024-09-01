#ifndef F_REPLAY_H
#define F_REPLAY_H

#include <fstream>
#include <string>
#include <game/generated/protocol.h>
#include <game/client/components/controls.h>

class CControls;

class CReplay { public: 
    CControls *pControl;

    void CReplay :: OnInputSnap ();

    int Status = -1;
    int Frame = 0;

    std :: string FileName;
    std :: fstream File;
};

#endif