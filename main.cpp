// AUTHOR : navcon
// DATE   : 12/10/2017
// LICENSE: GPLv3.0

// THANKS TO Skurmedel (https://github.com/skurmedel) for the colours!


#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <iomanip>
using namespace std;




enum colour { DARKBLUE = 1, DARKGREEN, DARKTEAL, DARKRED, DARKPINK, DARKYELLOW, GRAY, DARKGRAY, BLUE, GREEN, TEAL, RED, PINK, YELLOW, WHITE };

struct setcolour
{
	colour _c;
	HANDLE _console_handle;


	setcolour(colour c, HANDLE console_handle)
		: _c(c), _console_handle(0)
	{
		_console_handle = console_handle;
	}
};

// We could use a template here, making it more generic. Wide streams won't
// work with this version.
basic_ostream<char> &operator<<(basic_ostream<char> &s, const setcolour &ref)
{
	SetConsoleTextAttribute(ref._console_handle, ref._c);
	return s;
}



int main() {

	HANDLE chandle = GetStdHandle(STD_OUTPUT_HANDLE);

	while (true) {

		int pcounter = 0;
		int nextpcounter = 0;

		int pointer = 0;
		byte outarray[100];

		string code = " ";

		int open_parentheses = 0;

		bool run_flag = true;
		bool step_mode = true;
		bool fast_mode = false;
		bool very_fast_mode = false;

		string input = "";
		int input_int = 0;

		string output = "";

		cout << "--BRAINFUCK2 INTERPRETER--" << endl << endl << endl;
		cout << "SUPPORTED COMMANDS:" << endl;
		cout << " > - shift pointer to the right" << endl
			<< " < - shift pointer to the left" << endl
			<< " + - increase value at pointer by 1" << endl
			<< " - - decrease value at pointer by 1" << endl
			<< " [ - marks the start of a loop" << endl
			<< " ] - loop, if value at pointer is not 0" << endl
			<< " ) - loop, if value at pointer IS 0" << endl
			<< " , - request user input" << endl
			<< " . - output value at pointer" << endl
			<< " * - mulitply value at pointer with value at (pointer + 1)" << endl
			<< " / - divide value at pointer by value at (pointer + 1) (STOPS EXECUTION if value at (pointer + 1) is 0" << endl << endl << endl << "code: ";


		// Get Code from user
		cin >> code;

		// INIT outarray
		for (int i = 0; i < sizeof(outarray) / sizeof(byte); i++) {
			outarray[i] = 0;
		}


		//MAIN LOOP
		while (code[pcounter] != '\0' && pcounter >= 0 && run_flag) {
			char instr = code[pcounter]; //DEBUG
			//printf("pcounter: %5i   pointer: %3i   instruction: %c   value:  before: %3i   ", pcounter, pointer, code[pcounter], outarray[pointer]);

			system("cls");

			// OUTPUT CODE AT TOP
			for (int j = 0; j < code.length(); j++)
			{
				if (pcounter == j) cout << setcolour(RED, chandle);
				else cout << setcolour(GRAY, chandle);
				printf("%c", code[j]);
			}


			// MAIN INTERPRETING PART
			switch (code[pcounter]) {
			case 'n':
			case '>':
				pcounter++;
				pointer++;
				break;

			case 'p':
			case '<':
				pcounter++;
				pointer--;
				break;

			case '+':
				pcounter++;
				outarray[pointer]++;
				break;

			case '-':
				pcounter++;
				outarray[pointer]--;
				break;

			case 'o':
			case '.':
				pcounter++;
				output += to_string(outarray[pointer]) + " ";
				break;

			case 'i':
			case ',':
				pcounter++;
				input_int = -1;
				while (input_int == -1) {
					cout << endl << "Value of " << pointer << ": ";
					cin >> input;

					try {
						input_int = stoi(input);
					}
					catch (invalid_argument) {
						input_int = -1;
					}
				}

				cout << input << endl;
				outarray[pointer] = (byte)input_int;
				break;

			case '[':
				pcounter++;
				break;

			case ']':
				if (outarray[pointer] == 0) {
					pcounter++;
					break;
				}
				else {
					nextpcounter = pcounter;
					open_parentheses = 1;
					while (open_parentheses) {
						nextpcounter--;
						instr = code[nextpcounter];
						if (code[nextpcounter] == ')' || code[nextpcounter] == ']') open_parentheses++;
						else if (code[nextpcounter] == '[') open_parentheses--;
					}
					pcounter = nextpcounter;
				}
				break;

			case ')':
				if (outarray[pointer] != 0) {
					pcounter++;
					break;
				}
				else {
					nextpcounter = pcounter;
					open_parentheses = 1;
					while (open_parentheses) {
						nextpcounter--;
						instr = code[nextpcounter];
						if (code[nextpcounter] == ')' || code[nextpcounter] == ']') open_parentheses++;
						else if (code[nextpcounter] == '[') open_parentheses--;
					}
					pcounter = nextpcounter;
				}
				break;

			case '*':
				pcounter++;
				outarray[pointer] *= outarray[pointer + 1];
				break;

			case '/':
				pcounter++;
				if (outarray[pointer + 1] == 0) {
					run_flag = false;
					break;
				}
				else outarray[pointer] /= outarray[pointer + 1];
				break;

			default:
				pcounter++;
				break;

			}

			if (pointer >= sizeof(outarray) / sizeof(byte)) {
				break;
			}

			// SHOW
			cout << endl << endl;

			for (int i = 0; i < sizeof(outarray); i++)
			{
				if (i % 10 == 0) cout << endl;
				if (pointer == i) cout << setcolour(RED, chandle);
				else cout <<  setcolour(GRAY, chandle);
				printf(" %03i", outarray[i]);
			}
			
			cout << endl << endl << "  " + output << endl;

			if(step_mode) cout << endl << endl << "Press any key to continue... or (r)unmode / (f)astmode / (v)eryfastmode";

			if (!step_mode && !very_fast_mode) Sleep(fast_mode?150:500);
			else if (very_fast_mode) Sleep(25);
			else {
				char c1 = _getch();
				if (c1 == 'r') step_mode = false;
				else if (c1 == 'f') {
					step_mode = false;
					fast_mode = true;
				}
				else if (c1 == 'v') {
					step_mode = false;
					very_fast_mode = true;
				}
			}
		}

		cout << endl;

		system("cls");

		cout << code << endl << endl;

		for (int i = 0; i < sizeof(outarray); i++)
		{
			if (i % 10 == 0) cout << endl;
			printf(" %03i", outarray[i]);
		}

		cout << endl << endl << setcolour(RED, chandle);
		for (int i = 0; i < 40 - output.length() + 1; i++) cout << " ";
		cout << output;
		cout << setcolour(GRAY, chandle) << endl;

		cout << endl << endl;


		cout << "Run again? (Y/n):";
		char c = _getch();
		if (c == 'n' || c == 'N') return 0;
		else system("cls");


	}
}