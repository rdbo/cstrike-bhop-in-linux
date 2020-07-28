#include "hack.hpp"

//Variables
mem::moduleinfo_t        cstrike::modules::hw;
mem::moduleinfo_t        cstrike::modules::client;
cstrike::game::CSPlayer* cstrike::game::local_player;
mem::dword_t*            cstrike::game::force_jump;

//Helper functions
bool is_key_down(KeySym key);
bool check_module(mem::moduleinfo_t modinfo);

//Hack
void* cstrike::hack(void* args)
{
    modules::hw     = mem::in::get_module_info(HW_MODNAME);
    modules::client = mem::in::get_module_info(CLIENT_MODNAME);
    if(!check_module(modules::hw) || !check_module(modules::client)) return (void*)-1;
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

bool check_module(mem::moduleinfo_t modinfo)
{
    return
        strcmp(modinfo.name.c_str(), "") &&
        strcmp(modinfo.path.c_str(), "") &&
        modinfo.base != (mem::voidptr_t)MEM_BAD_RETURN &&
        modinfo.end  != (mem::voidptr_t)MEM_BAD_RETURN;
}