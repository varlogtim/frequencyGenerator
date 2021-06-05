# I am unable to get the board automatically because I am using USB to Serial :/
# https://github.com/arduino/arduino-cli/commit/bf7a3194bb6388a1a29949fe0d7407981786bcf6
USB_PATH = /dev/ttyUSB0
BOARD_TYPE = arduino:avr:nano

# Need to figure out how to auto-install module dependencies.
# arduino-cli lib install LiquidCrystal

push: frequencyGenerator.ino
	@echo "Building project and uploading"
	arduino-cli compile -b $(BOARD_TYPE) -u -p $(USB_PATH)
