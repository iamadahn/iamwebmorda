cd nuttx-apps
ln -s ../modules external
cd ..
cmake nuttx -B output -DBOARD_CONFIG=../board/configs/iamwebmorda -GNinja
rm nuttx-apps/external
