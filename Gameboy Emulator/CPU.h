#ifndef CPU_H
#define CPU_H



	class CPU {

	private:

		// The flag register represents 'f' in the registers struct
		// There are 4 flags; zero, subtract, half carry, and carry
		// These are special instructions for the CPU
		// The four flags are in the four most significant bits of the 'f' register


		struct flagRegister {
			unsigned char ZERO_FLAG_POS = 7;
			unsigned char SUBTRACT_FLAG_POS = 6;
			unsigned char HALF_CARRY_FLAG_POS = 5;
			unsigned char CARRY_FLAG_POS = 4;

			bool zero, subtract, halfCarry, carry;

			flagRegister* operator=(unsigned char c) {

				c >> 4;

				this->zero = c & 0b1000;
				this->subtract = c & 0b100;
				this->halfCarry = c & 0b10;
				this->carry = c & 0b1;

				return this;
			};

			unsigned char operator= (const flagRegister& fr) {

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

			};

		};
		
		
		// These represent the 'registers' that the CPU has on the die
		// these registers are 1 byte of storage each
		struct registers {
			unsigned char a, b, c, d, e, h, l;
			flagRegister f;
		};


		

		registers r;
		flagRegister fr;

	public:

		CPU() {


		}



		// while registers can only hold 8 bits on their own, they can 'join' to hold 16 bits
		// there are four different two-byte variants: af, bc, de, and hl
		// therefore, I need functions to split this 16-bit number between the paired registers

		//TODO: Refactor paired register code, I really don't like having multiple functions for the same job.

		short int getAF() const;
		short int getBC() const;
		short int getDE() const;
		short int getHL() const;

		//setters for pairs

		void setAF(short int pair);
		void setBC(short int pair);
		void setDE(short int pair);
		void setHL(short int pair);


		//at some point, we may need to convert our flagRegister to a byte, or the other way around.
		unsigned char flagToChar() const;
		flagRegister* charToFlag(unsigned char);
	};


#endif
