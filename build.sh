if [ ! -d "build" ]; then
    echo "You have to exec configure.sh first!"
    exit
fi

cd nuttx-apps
ln -s ../modules external
cd ..

mkdir -p build/bin
gcc -o build/bin/gencromfs nuttx/tools/gencromfs.c

cmake --build build
rm nuttx-apps/external
