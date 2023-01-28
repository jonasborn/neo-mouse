Import("env")

print(env.Dump())

board_config = env.BoardConfig()
# should be array of VID:PID pairs
board_config.update("build.hwids", [
  ["0x17ef", "0x600e"]
])

board_config.update("vendor", "Lenovo")
board_config.update("build.usb_product", "Lenovo USB Optical Mouse")
