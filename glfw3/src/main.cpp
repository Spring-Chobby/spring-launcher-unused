/*
 * This file is part of MXE. See LICENSE.md for licensing information.
 */

#include "chobby_config.h"
#include "gui.h"

int main(void)
{
    ChobbyConfig::initialize();

    GUI gui;
    gui.Loop();
    return 0;
}
