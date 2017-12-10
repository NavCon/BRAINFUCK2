// AUTHOR: navcon
// DATE  : 12/10/2017

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
using namespace std;

int main() {
	while (true) {

		int pcounter = 0;
		int nextpcounter = 0;

		int pointer = 0;
		byte outarray[100];

		string code = "";

		bool run_flag = true;

		char input = '0';

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

			printf("pcounter: %5i   pointer: %3i   instruction: %c   value:  before: %3i   ", pcounter, pointer, code[pcounter], outarray[pointer]);


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
				cout << outarray[pointer];
				break;

			case 'i':
			case ',':
				pcounter++;
				cout << endl << "Value of " << pointer << ": ";
				input = _getch();
				cout << input << endl;
				outarray[pointer] = input;
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
					while (code[nextpcounter] != '[') {
						nextpcounter--;
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
					while (code[nextpcounter] != '[') {
						nextpcounter--;
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

			printf("after: %3i\n", outarray[pointer]);
		}

		cout << endl;

		for (int i = 0; i < sizeof(outarray); i++)
		{
			if (i % 10 == 0) cout << endl;
			printf(" %03i", outarray[i]);
		}

		cout << endl;


		cout << "Run again? (Y/n):";
		char c = _getch();
		if (c == 'n' || c == 'N') return 0;
		else system("cls");
	}
}