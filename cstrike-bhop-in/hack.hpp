#pragma once
#ifndef CSTRIKE_BHOP_INTERNAL
#define CSTRIKE_BHOP_INTERNAL
#define HW_MODNAME     "/hw.so\n"
#define CLIENT_MODNAME "/client.so\n"
#include <pthread.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "mem/mem.hpp"

namespace cstrike
{
    void* hack(void* args);
    void bunnyhop();

    namespace offsets
    {
        //hw.so (end)
        const mem::uintptr_t dwLocalPlayer = 0x8f8280;

        //client.so (end)
        const mem::uintptr_t dwForceAttack = 0x25978;
        const mem::uintptr_t dwForceJump   = 0x25988;

        //Player
        const mem::uintptr_t dwHealth = 0x90;
        const mem::uintptr_t bOnGround = 0x54;
    }

    namespace keys
    {
        const KeySym bhop = XK_space;
    }

    namespace modules
    {
        extern mem::module_t hw;
        extern mem::module_t client;
    }

    namespace game
    {
        class CSPlayer
        {
            public:
            union
            {
                CREATE_UNION_MEMBER(mem::bool_t,  on_ground, offsets::bOnGround);
                CREATE_UNION_MEMBER(mem::dword_t, health, offsets::dwHealth);
            };
        };

        extern CSPlayer*     local_player;
        extern mem::dword_t* force_jump;
    }
}

#endif