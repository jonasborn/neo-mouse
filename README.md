# Mouse Jiggler for Adafruit Neo Trinkey

This project enables you to turn your Adafruit Neo Trinkey into a mouse jiggler, which simulates small mouse movements to prevent your computer from going into sleep mode or activating a screensaver. The Neo Trinkey will be detected as a "Lenovo USB Mouse" by the computer it is connected to. The two buttons are used to enable and disable the mouse simulation.

## Hardware Requirements

- Adafruit Neo Trinkey

## Software Requirements

- PlatformIO

## Importing the Project into PlatformIO

To import the Mouse Jiggler project into PlatformIO, follow these steps:

1. Install PlatformIO: Visit the [PlatformIO website](https://platformio.org/install) and follow the instructions to install the PlatformIO Core.

2. Connect the Neo Trinkey: Connect your Adafruit Neo Trinkey to your computer.

3. Build and upload the project: In the command prompt or terminal, navigate to the root directory of your project and run the following command:

   ```
   pio run -t upload
   ```

   This command will compile the project and upload it to the Neo Trinkey.

4. Verify the functionality: After the upload is complete, the Neo Trinkey will start working as a mouse jiggler, preventing your computer from going into sleep mode or activating a screensaver. Press one of the buttons, if successfull, the LEDs should turn green or red.

## Disclaimer

Please note that using this Mouse Jiggler software may violate the terms of service or policies of some systems or organizations. Ensure that you are authorized to use such software before deploying it. The Mouse Jiggler is intended for legitimate purposes, such as preventing a computer from sleeping during presentations or long processes, and should not be used for any malicious activities. The creators of this project are not responsible for any misuse or damage caused by its usage.

## License

The Mouse Jiggler project is released under the [MIT License](LICENSE). Feel free to modify and distribute it according to the terms of the license.
