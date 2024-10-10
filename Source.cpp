#include <iostream>
#include <cassert>
#include <cstdlib>


using namespace std;

void kelly_1_generator(short direction, unsigned int speed,short error_code);
void kelly_2_generator(unsigned short voltage, unsigned short current, unsigned short temp_m, unsigned short temp_c);

void kelly_1_collector();
void kelly_2_collector();

const unsigned int MAX_SPEED{ 5000 };
const unsigned int MAX_TEMP{ 100 };
const unsigned int MAX_VOLTAGE{ 173 };
const unsigned int MAX_CURRENT{ 600 };
const int MIN_TEMP{ -40 };

int main() {

	int selected_motor;

	

		try
		{
			cout << "Which motor do you want create a packet for?" << endl;
			cout << "1) Kelly 1" << endl;
			cout << "2) Kelly 2" << endl;

			cin >> selected_motor;

			assert(selected_motor == 1 || selected_motor == 2);

			if (selected_motor == 1) {
				kelly_1_collector();
			}
			else if (selected_motor == 2) {
				kelly_2_collector();
			}

		}
		catch (const std::exception&)
		{
			cout << "Some value was invalid!!" << endl;
			
		}

		

	

	





}



void kelly_1_collector() {


	short direction;
	unsigned int speed;
	short error;

	try {
		cout << "What will be the direction of the motor?" << endl;
		cout << "1) Forward" << endl;
		cout << "2) Reverse" << endl;
		cout << "3) Neutral" << endl;
		cin >> direction;

		cout << "What will be the RPM in decimal? less than " << MAX_SPEED << endl;
		cin >> speed;

		cout << "Any Error codes? 0 by default for no errors" << endl;
		cin >> error;


	}
	catch (const exception& e) {

		cout<< e.what()<<endl;
		throw;
	}

	
	kelly_1_generator(direction,speed,error);




}

void kelly_1_generator(short direction, unsigned int speed, short error_code = 0) {

	
	if (direction == 3) {
		direction = 0;
		
	}

	

	cout << " ***************" << endl;
	cout << "Payload: 0x00000000";
	printf("%02x", error_code);
	printf("%04x", speed);
	printf("%02x", direction);
	cout << endl << " ***************" << endl;



}

void kelly_2_collector() {

	unsigned short voltage{};
	unsigned short current{};
	unsigned short motor_temp{};
	unsigned short controller_temp{};

	cout << "What will be the voltage in decimal? less than " << MAX_TEMP << endl;
	cin >> voltage;

	cout << "What will be the current in decimal? less than " << MAX_CURRENT << endl;
	cin >> current;

	cout << "What will be the temperature of the motor in decimal? less than " << MAX_TEMP << endl;
	cin >> motor_temp;

	cout << "What will be the temperature of the controller in decimal? less than " << MAX_TEMP << endl;
	cin >> controller_temp;

	kelly_2_generator(voltage, current, motor_temp, controller_temp);

}

void kelly_2_generator(unsigned short  voltage, unsigned short  current, unsigned short  temp_m, unsigned short  temp_c)
{

	voltage *= 10;
	current *= 10;
	temp_m *= 10;
	temp_c *= 10;

	cout << " ***************" << endl;
	cout << "Payload: 0x";
	printf("%04x", temp_c);
	printf("%04x", temp_m);
	printf("%04x", current);
	printf("%04x", voltage);
	cout <<endl<< " ***************" << endl;
}

