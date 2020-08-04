#include "hack.hpp"

//Variables
mem::module_t        cstrike::modules::hw;
mem::module_t        cstrike::modules::client;
cstrike::game::CSPlayer* cstrike::game::local_player;
mem::dword_t*            cstrike::game::force_jump;

//Helper functions
bool is_key_down(KeySym key);

//Hack
void* cstrike::hack(void* args)
{
    modules::hw     = mem::in::get_module(HW_MODNAME);
    modules::client = mem::in::get_module(CLIENT_MODNAME);
    if(!modules::hw.is_valid() || !modules::client.is_valid()) return (void*)-1;
    game::force_jump = (mem::dword_t*)((mem::uintptr_t)modules::client.end + offsets::dwForceJump);
    game::local_player = (game::CSPlayer*)((mem::uintptr_t)modules::hw.end + offsets::dwLocalPlayer);
    while(true)
    {
        bunnyhop();
    }
    return (void*)0;
}

void cstrike::bunnyhop()
{
    if(is_key_down(keys::bhop) && game::local_player->health > 0 && game::local_player->on_ground)
        *game::force_jump = 6;
}


//Helper function definitions
bool is_key_down(KeySym key)
{
    Display* display = XOpenDisplay(NULL);
    char keymap[32];
    XQueryKeymap(display, keymap);
    KeyCode kc = XKeysymToKeycode(display, key);
    bool key_pressed = !!(keymap[kc >> 3] & (1 << (kc & 7)));
    XCloseDisplay(display);
    return key_pressed;
}