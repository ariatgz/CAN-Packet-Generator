#include <iostream>
#include <cassert>


using namespace std;

void kelly_1_generator(short direction, unsigned short speed,short error_code);
void kelly_2_generator();

void kelly_1_collector();
void kelly_2_collector();

const unsigned int MAX_SPEED{ 5000 };

int main() {

	int selected_motor;

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


void kelly_2_generator() {


}

void kelly_1_collector() {


	short direction;
	unsigned int speed;
	short error;


	cout << "What will be the direction of the motor?" << endl;
	cout << "1) Forward" << endl;
	cout << "2) Reverse" << endl;
	cout << "3) Neutral" << endl;
	cin >> direction;

	cout << "What will be the RPM in decimal? less than "<<MAX_SPEED << endl;
	cin >> speed;

	cout << "Any Error codes? 0 by default for no errors" << endl;
	cin >> error;

	kelly_1_generator(direction,speed,error);




}

void kelly_1_generator(short direction, unsigned int speed, short error_code) {

	cout << "CAN payload is " << "00000000" << std::hex << error_code << speed << direction << endl;

	cout << "Frame is {" << endl;
	cout << "ID: CAN_ID_EXT" << endl;
	cout << "data_length: sizeof(data)" << endl;



}

void kelly_2_collector() {


}

