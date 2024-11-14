#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;

// Function Prototypes
// Generates a CAN payload for the Kelly 1 motor using direction, speed, and error code.
void kelly_1_generator(short direction, unsigned int speed, short error_code);
// Generates a CAN payload for the Kelly 2 motor using voltage, current, motor temperature, and controller temperature.
void kelly_2_generator(unsigned short voltage, unsigned short current, unsigned short temp_m, unsigned short temp_c);

// Functions to collect user input and pass it to the corresponding generator function
void kelly_1_collector();
void kelly_2_collector();

// Constants defining maximum allowable values for motor parameters
const unsigned int MAX_SPEED{ 5000 };
const unsigned int MAX_TEMP{ 100 };
const unsigned int MAX_VOLTAGE{ 173 };
const unsigned int MAX_CURRENT{ 600 };
const int MIN_TEMP{ -40 };

int main() {
    int selected_motor;

    try {
        // Ask user to select which motor to create a packet for
        cout << "Which motor do you want to create a packet for?" << endl;
        cout << "1) Kelly 1" << endl;
        cout << "2) Kelly 2" << endl;

        cin >> selected_motor;

        // Ensure the selected motor is either 1 or 2
        assert(selected_motor == 1 || selected_motor == 2);

        // Call the corresponding function based on the motor type selected
        if (selected_motor == 1) {
            kelly_1_collector();
        } else if (selected_motor == 2) {
            kelly_2_collector();
        }
    }
    catch (const std::exception&) {
        cout << "Some value was invalid!!" << endl;
    }
}

// Function to collect user input for Kelly 1 motor and pass it to the generator
void kelly_1_collector() {
    short direction;
    unsigned int speed;
    short error;

    try {
        // Collect motor direction input from the user
        cout << "What will be the direction of the motor?" << endl;
        cout << "1) Forward" << endl;
        cout << "2) Reverse" << endl;
        cout << "3) Neutral" << endl;
        cin >> direction;

        // Collect speed input, with a maximum limit
        cout << "What will be the RPM in decimal? less than " << MAX_SPEED << endl;
        cin >> speed;

        // Collect error code, 0 by default if no errors
        cout << "Any Error codes? 0 by default for no errors" << endl;
        cin >> error;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        throw;
    }

    // Call the generator function with the collected inputs
    kelly_1_generator(direction, speed, error);
}

// Function to generate the payload for the Kelly 1 motor
void kelly_1_generator(short direction, unsigned int speed, short error_code = 0) {
    cout << " ***************" << endl;
    cout << "Payload: 0x00000000";
    // Print the error code, speed, and direction as part of the payload in hexadecimal format
    printf("%02x", error_code);
    printf("%04x", speed);
    printf("%02x", direction);
    cout << endl << " ***************" << endl;
}

// Function to collect user input for Kelly 2 motor and pass it to the generator
void kelly_2_collector() {
    unsigned short voltage{};
    unsigned short current{};
    unsigned short motor_temp{};
    unsigned short controller_temp{};

    // Collect voltage input, with a maximum limit
    cout << "What will be the voltage in decimal? less than " << MAX_VOLTAGE << endl;
    cin >> voltage;

    // Collect current input, with a maximum limit
    cout << "What will be the current in decimal? less than " << MAX_CURRENT << endl;
    cin >> current;

    // Collect motor temperature, within the allowed range
    cout << "What will be the temperature of the motor in decimal? less than " << MAX_TEMP << endl;
    cin >> motor_temp;

    // Collect controller temperature, within the allowed range
    cout << "What will be the temperature of the controller in decimal? less than " << MAX_TEMP << endl;
    cin >> controller_temp;

    // Call the generator function with the collected inputs
    kelly_2_generator(voltage, current, motor_temp, controller_temp);
}

// Function to generate the payload for the Kelly 2 motor
void kelly_2_generator(unsigned short voltage, unsigned short current, unsigned short temp_m, unsigned short temp_c) {
    // Convert each parameter to a scaled value (multiplied by 10)
    voltage *= 10;
    current *= 10;
    temp_m *= 10;
    temp_c *= 10;

    cout << " ***************" << endl;
    cout << "Payload: 0x";
    // Print the controller temperature, motor temperature, current, and voltage in hexadecimal format
    printf("%04x", temp_c);
    printf("%04x", temp_m);
    printf("%04x", current);
    printf("%04x", voltage);
    cout << endl << " ***************" << endl;
}
