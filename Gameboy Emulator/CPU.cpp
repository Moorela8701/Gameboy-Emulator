#include "CPU.h"

// see CPU.h for details on functions




// register getters

short int CPU::getAF() const {

	short int paired = r.a;
	paired << 8;
	paired | flagToChar();

	return paired;

}
short int CPU::getBC() const {

	short int paired = r.b;
	paired << 8;
	paired | r.c;

	return paired;

}
short int CPU::getDE() const {

	short int paired = r.d;
	paired << 8;
	paired | r.e;

	return paired;

}
short int CPU::getHL() const {

	short int paired = r.h;
	paired << 8;
	paired | r.l;

	return paired;

}

// register setters

void CPU::setAF(short int pair) {

	r.a = pair & 0xFF00;
	r.f = charToFlag((pair & 0xFF));

}
void CPU::setBC(short int pair) {

	r.b = pair & 0xFF00;
	r.c = pair & 0xFF;

}
void CPU::setDE(short int pair) {

	r.d = pair & 0xFF00;
	r.e = pair & 0xFF;

}
void CPU::setHL(short int pair) {

	r.h = pair & 0xFF00;
	r.l = pair & 0xFF;

}

unsigned char CPU::flagToChar() const {
	unsigned char result = 0b0;
	
	if (fr.zero)
		result | 0b1000;
	if (fr.subtract)
		result | 0b0100;
	if (fr.halfCarry)
		result | 0b0010;
	if (fr.carry)
		result | 0b0001;

	//moving flags to 4 MSBs
	result << 4;

	return result;

}

CPU::flagRegister* CPU::charToFlag(unsigned char c) {

	CPU::flagRegister temp;
	// this seems like an arbitrary shift, but the flags will always be in the 4 MSBs
	// and since this is a byte, a shift of 4 will be the 4 MSBs
	c >> 4;

	temp.zero = c & 0b1000;
	temp.subtract = c & 0b100;
	temp.halfCarry = c & 0b10;
	temp.carry = c & 0b1;

	return &temp;
}






