# I am unable to get the board automatically because I am using USB to Serial :/
# https://github.com/arduino/arduino-cli/commit/bf7a3194bb6388a1a29949fe0d7407981786bcf6
USB_PATH = "/dev/ttyUSB0"
BOARD_TYPE = "arduino:avr:nano"
BAUD_RATE = 115200  # Is this really baud rate>

# Need to figure out how to auto-install module dependencies.
# arduino-cli lib install LiquidCrystal
# arduino-cli lib install RotaryEncoder

push: frequencyGenerator.ino
	@echo "Building project and uploading"
	@arduino-cli compile -b $(BOARD_TYPE) -u -p $(USB_PATH)
	@echo "Build and upload complete"

# XXX Need to make the output of arduino-cli in some "build" dir, then make this dependent on that.
# Currently I can't run make -jX when X > 1 because monitor doesn't have the build files as dependencies, I think
monitor:
	@echo "Setting TTY"
	@stty -F $(USB_PATH) raw $(BAUD_RATE)
	@echo "Monitoring $(USB_PATH)"
	@cat $(USB_PATH)

pushMonitor: push monitor
