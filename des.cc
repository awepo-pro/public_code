#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <bitset>
#include <algorithm>
#include <numeric>
using namespace std;

vector<int> PC_1 = {
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4
};

vector<int> shift_table = {
	1, 1, 2, 2,
	2, 2, 2, 2,
	1, 2, 2, 2,
	2, 2, 2, 1
};

vector<int> PC_2 = {
	14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

vector<int> IP = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

vector<int> E_table = {
	32, 1, 2, 3, 4, 5, 4, 5,
	6, 7, 8, 9, 8, 9, 10, 11,
	12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21,
	22, 23, 24, 25, 24, 25, 26, 27,
	28, 29, 28, 29, 30, 31, 32, 1
};

vector<int> P_table = {
	16, 7, 20, 21,
	29, 12, 28, 17,
	1, 15, 23, 26,
	5, 18, 31, 10,
	2, 8, 24, 14,
	32, 27, 3, 9,
	19, 13, 30, 6,
	22, 11, 4, 25
};

vector<vector<vector<int>>> sbox = {
	{
		{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
		{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
		{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
		{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
	},

	{
		{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
		{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
		{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
		{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
	},

	{
		{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
		{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
		{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
		{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
	},

	{
		{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
		{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
		{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
		{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
	},

	{
		{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
		{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
		{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
		{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
	},

	{
		{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
		{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
		{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
		{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
	},

	{
		{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
		{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
		{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
		{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
	},

	{
		{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
		{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
		{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
		{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
	}
};

vector<int> IP_REV = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25
};


string to_bin(int val, int num = -1) {
    string sol;

    while (val) {
        sol += "01"[val % 2];
        val /= 2;
        num--;
    }

    while (num-- > 0)
        sol = sol + '0';

    return {sol.rbegin(), sol.rend()};
};

string to_bin(char x) {
	if (isdigit(x))
		return to_bin(x - '0', 4);
	return to_bin(x - 'A' + 10, 4);
}

string hex2bin(const string &k) {
	string result;

	for (auto x : k)
		result += to_bin(x);

	return result;
}

string permute(const string &k, const vector<int> &table) {
	string result;

	for (auto x : table)
		result += k[x - 1];

	return result;
}

string left_shift(const string &str, int shift) {
	string result;

	for (int i = 0; i < str.size(); i++) {
		int next = i + shift;
		result += str[(next % str.size())];
	}

	return result;
}

vector<string> generate_K(const string &key) {
	vector<string> K(16);

	// string binary_key = hex2bin(key);
	string binary_key = key;
	assert(binary_key.size() == 64);

	binary_key = permute(binary_key, PC_1);

	for (int i = 0; i < shift_table.size(); i++) {		
		string left = binary_key.substr(0, 28);
		string right = binary_key.substr(28);

		assert(left.size() == 28 && right.size() == 28);

		left = left_shift(left, shift_table[i]);
		right = left_shift(right, shift_table[i]);

		binary_key = left + right;

		K[i] = permute(binary_key, PC_2);
	}

	assert(K.size() == 16);
	return K;
}

string string_xor(const string &left, const string &right) {
	string result;
	assert(left.size() == right.size());

	for (int i = 0; i < left.size(); i++)
		result += (left[i] == right[i] ? '0' : '1');

	return result;
}

int bin2dec(string &str) {
	int result = 0;

	for (int i = str.size() - 1; i >= 0; i--)
		result += (str[i] - '0') * pow(2, str.size() - 1 - i);

	return result;
}

string s_transformation(string &str) {
	string result;

	for (int i = 0; i < sbox.size(); i++) {
		string two_bits = string(1, str[i * 6]) + string(1, str[i * 6 + 5]);	
		string four_bits = str.substr(i * 6 + 1, 4);

		int first = bin2dec(two_bits);
		int second = bin2dec(four_bits);

		result += bitset<4>(sbox[i][first][second]).to_string();
	}

	assert(result.size() == 32);
	return result;
}

string f_transformation(string &R, string &k) {
	string result;

	R = permute(R, E_table);
	result = string_xor(R, k);

	result = s_transformation(result);
	result = permute(result, P_table);

	return result;
}

string encrypt(const string &plaintext, vector<string> &K) {
	// string text = hex2bin(plaintext);
	string text = plaintext;
	assert(text.size() == 64);

	text = permute(text, IP);
	string left = text.substr(0, 32);
	string right = text.substr(32);

	cout << "output of f function: " << '\n';

	for (int i = 0; i < 16; i++) {
		auto t = left;
		left = right;

		auto ft = f_transformation(right, K[i]);
		cout << "Round " << i + 1 << ": " << ft << '\n';

		right = string_xor(t, ft);

		if (i != 15) {
			cout << "left: " << left << ' ' << "right: " << right << '\n';
			cout << '\n';
		}
	}

	swap(left, right);
	cout << "left: " << left << ' ' << "right: " << right << '\n';
	cout << '\n';

	text = permute(left + right, IP_REV);
	return text;
}

string decrypt(const string &cipher, vector<string> K) {
	reverse(K.begin(), K.end());

	return encrypt(cipher, K);
}

string bin2hex(const string &x) {
	string result;

	for (int i = 0; i < x.size(); i += 4) {
		auto chunk = x.substr(i, 4);
		int val = bin2dec(chunk);

		if (val < 10) {
			result += '0' + val;
			continue;
		}

		val -= 10;
		result += 'A' + val;
	}

	return result;
}

int main() {
	// string plaintext = "0123456789ABCDEF";
	// string key = "133457799BBCDFF1";

	string ciphertext = "1100101011101101101000100110010101011111101101110011100001110011";
	string key = "0100110001001111010101100100010101000011010100110100111001000100";

	cout << "ciphertext: " << ciphertext << '\n';
	cout << "key: " << key << '\n';
	cout << '\n';

	cout << "generated round keys: " << '\n';

	auto K = generate_K(key);

	for (int i = 0; i < 16; i++)
		cout << "Round " << i + 1 << ": " << K[i] << '\n';
	cout << '\n';


	// auto cipher = encrypt(ciphertext, K);
	// cipher = bin2hex(cipher);
	// cout << "cipher: " << cipher << '\n';

	auto text = decrypt(ciphertext, K);
	cout << "decrypted message: " << text << '\n';
}