build_path="./build/PSP GCC/Debug/"
psp-cmake -S . -B "$build_path"
cd "$build_path"
echo "Making!!"
make && \
cd ./bin/psp
PPSSPPSDL ./Hello.prx