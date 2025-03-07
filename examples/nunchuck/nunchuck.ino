#include <AALeC-V3.h>

void setup() {
    aalec.init();
}

bool buttonPressed = false;
bool showAccelerometer = false;

void loop() {
    aalec.read_Nunchuck_Data();
    uint8_t buttonState = aalec.get_button();  

    if (buttonState == 1 && !buttonPressed) {
        showAccelerometer = !showAccelerometer;
        buttonPressed = true;
        aalec.clear_display();
    }
    if (buttonState == 0) {
        buttonPressed = false;
    }

    if (showAccelerometer) {
        // Beschleunigungswerte anzeigen
        uint8_t AccelX = aalec.get_Nunchuck_Data(aalec.NunchuckValues::AccelX);
        uint8_t AccelY = aalec.get_Nunchuck_Data(aalec.NunchuckValues::AccelY);
        uint8_t AccelZ = aalec.get_Nunchuck_Data(aalec.NunchuckValues::AccelZ);

        aalec.print_line(1, "AccelX: " + (String)AccelX);
        aalec.print_line(2, "AccelY: " + (String)AccelY);
        aalec.print_line(3, "AccelZ: " + (String)AccelZ);
    } else {
        uint8_t joystickValueX = aalec.get_Nunchuck_Data(aalec.NunchuckValues::JoystickX);
        uint8_t joystickValueY = aalec.get_Nunchuck_Data(aalec.NunchuckValues::JoystickY);
        uint8_t ButtonZ = aalec.get_Nunchuck_Data(aalec.NunchuckValues::ButtonZ);
        uint8_t ButtonC = aalec.get_Nunchuck_Data(aalec.NunchuckValues::ButtonC);
        uint8_t Roll = aalec.get_Nunchuck_Data(aalec.NunchuckValues::Roll);
        uint8_t Pitch = aalec.get_Nunchuck_Data(aalec.NunchuckValues::Pitch);

        aalec.print_line(1, "JoyX: " + (String)joystickValueX + ", JoyY: " + (String)joystickValueY);
        aalec.print_line(2, "BtnZ: " + (String)ButtonZ + ", BtnC: " + (String)ButtonC);
        aalec.print_line(3, "Roll: " + (String)Roll);
        aalec.print_line(4, "Pit: " + (String)Pitch);
    }
}
