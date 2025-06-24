cd nuttx-apps
ln -s ../modules external
cd ..
cmake --build build
rm nuttx-apps/external
