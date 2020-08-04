if [ ! -d build ]; then
    mkdir build
fi

clang++ -m32 -shared -fPIC cstrike-bhop-in/main.cpp cstrike-bhop-in/hack.cpp cstrike-bhop-in/mem/mem.cpp -o build/libcshack.so -ldl -pthread