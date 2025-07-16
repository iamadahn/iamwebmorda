if [ ! -d "output" ]; then
    echo "You have to exec configure.sh first!"
    exit
fi

cd nuttx-apps
ln -s ../modules external
cd ..

mkdir -p output/bin
gcc -o output/bin/gencromfs nuttx/tools/gencromfs.c

cmake --build output
rm nuttx-apps/external

size output/nuttx
