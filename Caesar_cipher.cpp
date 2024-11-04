#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// encryption
string caesarCipher(const string& text, int shift, bool encrypt = true) {
	string result = text;

	// decryption
	if (!encrypt) {
		shift = -shift;
	}
	// cyclic shift for the English alphabet

	for (char& c : result) {
		if (isalpha(c)) {
			char base = islower(c) ? 'a' : 'A';
			c = static_cast<char>((c - base + shift + 26) % 26 + base);
		}
	}

	return result;
}

string readFile(const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Failed to open file to read: " << filename << endl;
		exit(1);
	}

	string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	file.close();
	return text;
}


void writeFile(const string& filename, const string& text) {
	ofstream file(filename);
	if (!file.is_open()) {
		cerr << "Failed to open file to write: " << filename << endl;
		exit(1);
	}

	file << text;
	file.close();
}

int main() {
	string filename;
	int shift;
	char mode;

	cout << "File name ";
	cin >> filename;

	cout << "Key: ";
	cin >> shift;
	// if the offset number is too large
	shift = shift % 26;


	cout << "Chose mode e - encryption, d - decryption): ";
	cin >> mode;

	// read data from the file
	string text = readFile(filename);

	// start encryption\decryption
	bool encrypt = (mode == 'e');
	string result = caesarCipher(text, shift, encrypt);

	//writing the result to a file
	writeFile(filename, result);

	encrypt ? cout << "Encryption completed." << endl : cout << "Decryption completed." << endl;

	return 0;
}