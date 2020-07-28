#include "hack.hpp"

__attribute__((constructor))
void dl_main()
{
    pthread_t thread;
    pthread_create(&thread, NULL, (void*(*)(void*))cstrike::hack, (void*)NULL);
}