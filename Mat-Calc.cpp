#include <iostream>
#include <string>
#include <ctype.h>
#include <sstream>
#include <cstdlib>

using namespace std;

//Rows and columns counters for both input matrices and for the output matrix
static int mr1 = 1, mc1 = 1, mr2 = 1, mc2 = 1, mr, mc, detok = 0, marker;
static double detto = 0;

void add(double matin1[ ][ ], double matin2[ ][ ], double matout[ ][ ]);
void sub(double matin1[ ][ ], double matin2[ ][ ], double matout[ ][ ]);
void mult(double matin1[ ][ ], double matin2[ ][ ], double matout[ ][ ]);
void trans(double matin[ ][ ], double matout[ ][ ]);
void power(double matin[ ][ ], double matout[ ][ ], int up);
double det(double matin[ ][ ]);

int main() {
	//outmat is the resulting matrix, converted to a string at the end
	double outmat[100][100];
	//stupid becomes 1 if any error occurs
	int stupid = 0;
	//matcheck checks if all rows have same number of elements, useful for multiplication
	int matcheck[100];
	//Declaration of input matrices
	double matrix1[100][100], matrix2[100][100];

	//Convert input string into a 2d-array
	if (true) {
		string numstr = "0", sumstr = "0", input;
		getline(cin, input);
		int sumtok = 0, i = 0, j = 0, k = 0;
		double sumnum = 0;
		while (true) {
			if (input[j] >= '0' && input[j] <= '9' || input[j] == '.' || input[j] == '-') {
				numstr = input[j];
				if (sumtok != 0) sumstr += numstr;
				else sumstr = numstr;
				sumtok++;
			}
			else if (input[j] == ' ') {
				if (sumtok != 0) {
					sumnum = atof(sumstr.c_str());
					matrix1[i][k] = sumnum;
					sumtok = 0;
					k++;
					matcheck[mr1]++;
					if (i == 0)
						mc1++;
				}
			}
			else if (input[j] == 59) {
				if (sumtok != 0) {
					sumnum = atof(sumstr.c_str());
					matrix1[i][k] = sumnum;
					sumtok = 0;
					k++;
					mr1++;
					matcheck[mr1] = 0;
				}
				i++;
				k = 0;
			}
			else if (input[j] == ']') {
				if (sumtok != 0) {
					sumnum = atof(sumstr.c_str());
					matrix1[i][k] = sumnum;
					sumtok = 0;
					k++;
				}
				break;
			}
			else if (input[j] == '[') {
				matcheck[mr1] = 0;
			}
			else {
				cout << "ERROR";
				stupid = 1;
			}
			j++;
		}
		i++;
	}

	//Check if all rows have same number of elements
	for (int cc = 1; cc < mr1; cc++)
		if (matcheck[cc] != matcheck[cc + 1])
			stupid = 1;

	//Get the required operation
	if (stupid == 1) {
		cout << "ERROR";
		return 1;
	}
	char op;
	cin >> op;

	//This condition is true if the operation needs two matrices
	if (op == '+' || op == '-' || op == '*' || op == '/') {
		string numstr = "0", sumstr = "0", input;
		cin.ignore();
		getline(cin, input);
		int sumtok = 0, i = 0, j = 0, k = 0;
		double sumnum;
		while (true) {
			if (input[j] >= '0' && input[j] <= '9' || input[j] == '.' || input[j] == '-') {
				numstr = input[j];
				if (sumtok != 0) sumstr += numstr;
				else sumstr = numstr;
				sumtok++;
			}
			else if (input[j] == ' ') {
				if (sumtok != 0) {
					sumnum = atof(sumstr.c_str());
					matrix2[i][k] = sumnum;
					sumtok = 0;
					k++;
					if (i == 0)
						mc2++;
				}
			}
			else if (input[j] == 59) {
				if (sumtok != 0) {
					sumnum = atof(sumstr.c_str());
					matrix2[i][k] = sumnum;
					sumtok = 0;
					k++;
					mr2++;
				}
				i++;
				k = 0;
			}
			else if (input[j] == ']') {
				if (sumtok != 0) {
					sumnum = atof(sumstr.c_str());
					matrix2[i][k] = sumnum;
					sumtok = 0;
					k++;
				}
				break;
			}
			else if (input[j] == '[') {
				stupid = 0;
			}
			else
				stupid = 1;
			j++;
		}
		i++;
		if ((op == '+') && (mr1 == mr2) && (mc1 == mc2)) {
			mr = mr1;
			mc = mc1;
			for (int a = 0; a < mr; a++)
				for (int b = 0; b < mc; b++)
					add(matrix1, matrix2, outmat);
		}
		else if ((op == '-') && (mr1 == mr2) && (mc1 == mc2)) {
			mr = mr1;
			mc = mc1;
			for (int a = 0; a < mr; a++)
				for (int b = 0; b < mc; b++)
					sub(matrix1, matrix2, outmat);
		}
		else if ((op == '*') && (mc1 == mr2)) {
			mr = mr1;
			mc = mc2;
			for (int a = 0; a < mr; a++)
				for (int b = 0; b < mc; b++)
					mult(matrix1, matrix2, outmat);
		}
		else
			stupid = 1;
	}
	
	if (stupid == 1) {
		cout << "ERROR";
		return 1;
	}
	
	//This condition is true if the operation needs one matrix
	if (op == 'T' || op == 'I' || op == '^' || op == 'D') {
		if (op == 'T') {
			mr = mc1; mc = mr1;
			trans(matrix1, outmat);
		}
		else if (op == '^') {
			if (mr1 != mc1)
				stupid = 1;
			mr = mr1; mc = mc1;
			cin.ignore();
			int up;
			cin >> up;
			power(matrix1, outmat, up);
		}
		else if (op == 'D') {
			if (mr1 == mc1) {
				mc = mc1; mr = mr1;
				cout << det(matrix1);
				return 0;
			}
			else
				stupid = 1;
		}
	}

	//Print error if there is an error
	if (stupid == 1) {
		cout << "ERROR";
		return 1;
	}

	//Convert double matrix into string
	ostringstream mychar;
	for (int c1 = 0; c1 < mr; c1++) {
		for (int c2 = 0; c2 < mc; c2++) {
			mychar << outmat[c1][c2];
			if ((c2 + 1) != mc)
				mychar << " ";
		}
		if ((c1 + 1) != mr)
			mychar << ";";
	}
	//Output the matrix in the string form
	cout << "[" << mychar.str() << "]";
	return 0;
}
//This function gets two matrices as the first two parameters, adds them, and stores them in the last matrix
void add(double matin1[ ][ ], double matin2[ ][ ], double matout[ ][ ]) {
	for (int a = 0; a < mr; a++) {
		for (int b = 0; b < mc; b++) {
			matout[a][b] = matin1[a][b] + matin2[a][b];
		}
	}
}
//This function gets two matrices as the first two parameters, subtracts them, and stores them in the last matrix
void sub(double matin1[ ][ ], double matin2[ ][ ], double matout[ ][ ]) {
	for (int a = 0; a < mr; a++) {
		for (int b = 0; b < mc; b++) {
			matout[a][b] = matin1[a][b] - matin2[a][b];
		}
	}
}
//This function gets two matrices as the first two parameters, multiplies them, and stores them in the last matrix
void mult(double matin1[ ][ ], double matin2[ ][ ], double matout[ ][ ]) {
	double sumnow = 0;
	for (int a = 0; a < mr; a++) {
		for (int b = 0; b < mc; b++) {
			for (int c = 0; c < mc1; c++) {
				if (c == 0)
					sumnow = matin1[a][c] * matin2[c][b];
				else
					sumnow += (matin1[a][c] * matin2[c][b]);
			}
			matout[a][b] = sumnow;
			sumnow = 0;
		}
	}
}
//This function gets a matrix as input, finds its transpose, and stores it in the second parameter
void trans(double matin[ ][ ], double matout[ ][ ]) {
	for (int a = 0; a < mr; a++) {
		for (int b = 0; b < mc; b++) {
			matout[a][b] = matin[b][a];
		}
	}
}
//This function gets a matrix as input, raises it to a power up, and stores it in the second parameter
void power(double matin[ ][ ], double matout[ ][ ], int up) {
	double tempmat[100][100];
	if (up > 1) {
		for (int a = 0; a < mr; a++) {
			for (int b = 0; b < mc; b++) {
				matout[a][b] = matin[a][b];
				tempmat[a][b] = matin[a][b];
			}
		}
		for (int b = 1; b < up; b++) {
			mult(tempmat, matin, matout);
			for (int a = 0; a < mr; a++) {
				for (int b = 0; b < mc; b++) {
					tempmat[a][b] = matout[a][b];
				}
			}
		}
	}
	else if (up == 0) {
		for (int i = 0; i < mr; i++) {
			for (int j = 0; j < mc; j++) {
				if (i == j)
					matout[i][j] = 1;
				else
					matout[i][j] = 0;
			}
		}
	}
	else if (up == 1) {
		for (int i = 0; i < mr; i++) {
			for (int j = 0; j < mc; j++) {
				matout[i][j] = matin[i][j];
			}
		}
	}
}
//This function gets a matrix as input, finds its determinant, returns it
double det(double matin[ ][ ]) {
	int i1, j1, i2 = 0, j2 = 0, md = mr - detok;
	double matemp[100][100];


	if (detok == 0) {
		for (int a = 0; a < md; a++) {
			for (int b = 0; b < md; b++) {
				matemp[a][b] = matin[a][b];
			}
		}
	}
	else {
		for (i1 = 1; i1 < (md + 1); i1++) {
			for (j1 = 0; j1 < (md + 1); j1++) {
				if (j1 != marker) {
					matemp[i2][j2] = matin[i1][j1];
					j2++;
				}
			}
			i2++;
			j2 = 0;
		}
	}

	if (md == 2) {
		return(matemp[0][0] * matemp[1][1] - matemp[0][1] * matemp[1][0]);
	}
	else {
		detok++;
		for (marker = 0; marker < md; marker++) {
			if (marker % 2)
				detto += -(matemp[0][marker] * det(matemp));
			else
				detto += (matemp[0][marker] * det(matemp));
		}

	}
	return detto;
}
