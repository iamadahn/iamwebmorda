openocd -f interface/stlink.cfg -f openocd.cfg -c init -c halt -c "flash write_image erase build/nuttx.bin 0x90000000" -c reset -c shutdown
