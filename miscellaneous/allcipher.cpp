// FCAI – Programming 1 – 2022 - Assignment 2 
// Program Name: cipher0.cpp
// Program Description: this program takes in an encryption key and a message, the user choose to either,
// encrypt or decrypt the message.
// Last Modification Date: xx/xx/2022
// Author1 and ID and Group: 
// Author2 and ID and Group: Mohammed Saleh Al-Mansori 20210729 s
// Author3 and ID and Group: Zeyad Atiya Shahin 20210150 s12
// Teaching Assistant: 
// Purpose : a collection of all the ciphers in the assignment. The user can choose which cipher to use, then choose a command to do, 
// The user can encrypt or a  decrypt a message entered.


#include <iostream>
#include <iomanip>
#include <string>
#include <tuple>
#include <map>
#include <set>
#include <algorithm>
#define all(x) begin(x),end(x)
using namespace std;

using ll = long long int;
using ull = long long int;

//the first map that use to encrypt in morse  code
unordered_map<char, string>m{{'A', ".-"},{'B', "-..."},{'C', "-.-."},{'D', "-.."},{'E', "."},
{'F', "..-."},{'G', "--."},{'H', "...."},{'I', ".."},{'J', ".---"},{'K', "-.-"},{'L', ".-.."},
{'M', "--"},{'N', "-."},{'O', "---"},{'P', ".--."},{'Q', "--.-"},{'R', ".-."},{'S', "..."},
{'T', "-"},{'U', "..-"},{'V', "...-"},{'W', ".--"},{'X', "-..-"},{'Y', "-.--"},{'Z', "--.."},
//numbers
{'0', "-----"},{'1', ".----"},{'2', "..---"},{'3', "...--"},{'4', "....-"},
{'5', "....."},{'6', "-...."},{'7', "--..."},{'8', "---.."},{'9', "----."},

// Punctuation
{' ', "   "},{'.', ".-.-.-"},{',', "--..--"},{':', "---..."},{'?', "..--.."},{'\'', ".----."},
{'-', "-....-"},{'/', "-..-."},{'(', "-.--."},{')', "-.--.-"},{'"', ".-..-."},{'=', "-...-"},
{'+', ".-.-."},{'!', "-.-.--"},{'&', ".-..."},{';', "-.-.-."},{'_', "..--.-"},{'$', "...-..-"},
{'@', ".--.-."},
};
//the second map that use to decrypt a morse code messsage
unordered_map<string, char>m2{
{".-", 'A'},{"-...", 'B'},{"-.-.", 'C'},{"-..", 'D'},{".", 'E'},{"..-.", 'F'},
{"--.", 'G'},{"....", 'H'},{"..", 'I'},{".---", 'J'},{"-.-", 'K'},{".-..", 'L'},
{"--", 'M'},{"-.", 'N'},{"---", 'O'},{".--.", 'P'},{"--.-", 'Q'},{".-.", 'R'},
{"...", 'S'},{"-", 'T'},{"..-", 'U'},{"...-", 'V'},{".--", 'W'},
{"-..-", 'X'},{"-.--", 'Y'},{"--..", 'Z'},
//numbers
{"-----", '0'},{".----", '1'},{"..---", '2'},{"...--", '3'},{"....-", '4'},{".....", '5'},
{"-....", '6'},{"--...", '7'},{"---..", '8'},{"----.", '9'},

// Punctuation
{"   ", ' '},{".-.-.-", '.'},{"--..--", ','},{"---...", ':'},{"..--..", '?'},{".----.", '\''},{"-....-", '-'},
{"-..-.", '/'},{"-.--.", '('},{"-.--.-", ')'},{".-..-.", '"'},{"-...-", '='},{".-.-.", '+'},{"-.-.--", '!'},
{".-...", '&'},{"-.-.-.", ';'},{"..--.-", '/'},{"...-..-", '$'},{".--.-.", '@'},
};

ull a, b,c;
ull integer_in();
enum mode
{
	ENCRYPTION,
	DECRYPTION
};

bool is_numeric_string(string message)
{
	for(char c : message)
		if(!isdigit(c))
			return 0;
	return 1;
}
//ensure integer input from user

//define a father cipher class for the others ciphers
class Cipher
{
public:
	//checks if the message is valid
	virtual bool is_valid_message(string message, int mode)
	{
		return 1;
	}
	//encrypts the message
	virtual string encrypt(string message)
	{
		return "";
	}
	//decrypts the message
	virtual string decrypt(string message)
	{
		return "";
	}
	//get key for cipher from user
	virtual void get_key()
	{}
	//local function: checks if all characters are letters
	bool isalpha_string(string message)
	{
		for(char c : message)
			if(!isalpha(c))
				return 0;
		return 1;
	}

	bool has_repeated_chars(string message)
	{
		set<char> my_set;
		for(char c : message)
			if(my_set.find(c) != my_set.end())
				return 1;
			else
				my_set.insert(c);
		return 0;
	}
};
//###################################################################################################################################################################

//cipher0 and its methods
//it uses the modular expression (a * x + b) % 26 ,where x is the ascii code of character, to encrypt the given message
//the decryption uses the expression (c * x - b) to decrypt the message, where c is the multiplicative inverse of a such that a*c % 26 = 1 
class Cipher0 : public Cipher
{
public:
	//the key
	int a, b, c;
	//takes a string and use the key enter to encrypt the message, it returns the new message
	string encrypt(string message)
	{
		for(int i = 0; i < message.size(); i++)

			if(isalpha(message[i]))
			{
				//ensures character is smallcase
				message[i] |= 32;
				message[i] = (a * (message[i] - 'a') + b) % 26 + 'a';
			}
		return message;
	}
	//takes a string and use the key enter to decrypt the message, it returns the new message
	string decrypt(string message)
	{
		for(int i = 0; i < message.size(); i++)
			if(isalpha(message[i]))
			{
				//ensures character is smallcase
				message[i] |= 32;
				message[i] = (c * ((message[i] - 'a') - b + 26)) % 26 + 'a';
			}
		return message;
	}
	//responsible for taking a valid key a b c from user
	void get_key()
	{
		cout << "Enter key encryption (ax+b) and decryption c(x -b) \n ";
		cout << "enter a : " ; 
		a = integer_in();
		cout << "enter b : ";
		b = integer_in();
		cout << "enter c : ";
		c = integer_in();
		while((c * a) % 26 != 1)
		{
			cout << "enter valid c such that (a*c)mod 26 = 1 : ";
			c = integer_in();
		}
	}
};

//######################################################################

//cipher2 and its methods
//it encrypt the given message where each letter with offset from the start corrosponds to a letter witht the same offset from the end
//it encyption and the decyption are the same; so the encypt method is implemented while the decrypt uses the encypt method
class Cipher2 : public Cipher
{
public:
	//encrypts the message 
	string encrypt(string message)
	{
		string encrypted;
		for(char c : message)
		{
			if(isalpha(c))
			{
				if(isupper(c))
					encrypted.push_back(26 - c + 2 * 'A' - 1);
				else
					encrypted.push_back(26 - c + 2 * 'a' - 1);
			}
			else
				encrypted.push_back(c);
		}
		return encrypted;
	}
	//decrypts the message
	string decrypt(string message)
	{
		return encrypt(message);
	}
};
//###################################################################################################################################################################


//cipher3 and its implementation
//it uses a repeated sequence of characters to encrypt the given message using the (message[i] + keyword[i % size()]) % 26 formula
//the formula gives us the a value that  could be offsetted by (keyword[i % size] - 'A') 5% 26 to get the letter'message position in the 
//alphabet, this is used to decrypt the message
class Cipher3 : public Cipher
{

	string keyword;

	//checks if the message has the right length
	bool is_valid_message(string message)
	{
		if(message.size() > 80)
			return 0;
		else 
			return 1;
	}
	//encrypts the message
	string encrypt(string message)
	{
		int i = 0;
		string encrypted;
		for(char c : message)
		{
			//convert to upper

			if(isalpha(c))
			{
				c &= ~32;
				encrypted.push_back((c + keyword[i]) % 26 + 'A');
			}
			else
				encrypted.push_back(c);
			i = (i + 1) % keyword.size();
		}
		return encrypted;
	}
	//decrypts the message
	string decrypt(string message)
	{
		int i = 0;
		string decrypted;
		for(char c : message)
		{
			//convert to uppercase
			if(isalpha(c))
			{
				c &= ~32;
				decrypted.push_back(((c - 'A') - (keyword[i] - 'A') % 26 + 26) % 26 + 'A');
			}
			else
				decrypted.push_back(c);
			i = (i + 1) % keyword.size();
		}
		return decrypted;
	}
	//get a valid keyword from user
	void get_key()
	{
		cout << "enter a encryption keyword: ";
		getline(cin, keyword);
		while(keyword == "" || !isalpha_string(keyword))
		{
			cout << "enter alphabetic keyword of length under 8: ";
			getline(cin, keyword);
		}
		for(int i = 0; i < keyword.size(); i++)
			keyword[i] &= ~32;
	}
};
//###################################################################################################################################################################


//cipher4
//takes a sequence of characters and convert it to binary representation starting from A : 0 to Z : 25
//the binary representation should consider 0 to be 'a' and 1 to be 'b';
//a slight improvement on the cipher, we can take a a binary sequence of size less than 32 from user and 
// do a  mod 26 on the integer,
class Cipher4 : public Cipher
{
	bool is_valid_message(string message, int mode)
	{
		if(mode == ENCRYPTION)
			return 1;
		else if(mode == DECRYPTION)
		{
			stringstream ss(message);
			string part;
			while(ss >> part)
			{
				if(part.size() >=  32)
					return 0;
				for(char c : part)
				{
					if(c != 'a' && c != 'b')
						return 0;
				}
			}
			return 1;
		}
		return 1;
	}
	//encrypts the message, if the message has a non-alphabetic character, we can ignore it
	string encrypt(string message)
	{
		string encrypted;
		for(char c : message)
		{
			if(isalpha(c))
			{
				c &= ~32;
				int value = c - 'A';
				for(int i = 1 << 4; i >= 1; i >>= 1)
				{
					if(i & value)
						encrypted.push_back('b');
					else
						encrypted.push_back('a');
				}
				encrypted.push_back(' ');
			}
		}
		return encrypted;
	}
	//decrypts the message
	string decrypt(string message)
	{
		string decrypted;
		stringstream ss(message);
		string letter;
		while(ss >> letter)
		{
			reverse(all(letter));
			int sum = 0, i = 1;
			for(char c : letter)
			{
				sum += (c - 'a') * i;
				i <<= 1;
			}
			decrypted.push_back(sum % 26 + 'A');
		}
		return decrypted;
	}

};
//###################################################################################################################################################################


//cipher5
// takes a key of a sequence of letters, the index of a letter respresents its position in the alphabet, and the letters itself is what is going
//to be subistituted with.
//decryption would work similarly
class Cipher5 : public Cipher
{
	string keyword;
	string encrypt(string message)
	{
		map<char, char> encryption_key;
		for(int i = 'a'; i <= 'z'; i++)
		{
			encryption_key[i] = keyword[i - 'a'];
		}
		string encrypted;
		for(char c : message)
		{
			if(isalpha(c))
			{
				c |= 32;
				encrypted.push_back(encryption_key[c]);
			}
			else
				encrypted.push_back(c);
		}
		return encrypted;
	}
	string decrypt(string message)
	{
		map<char, char> decryption_key;
		for(int i = 'a'; i <= 'z'; i++)
		{
			decryption_key[keyword[i - 'a']] = i;
		}
		string decrypted;
		for(char c : message)
		{
			if(isalpha(c))
			{
				c |= 32;
				decrypted.push_back(decryption_key[c]);
			}
			else
				decrypted.push_back(c);
		}
		return decrypted;
	}
	//takes a 26 unique letters in lowercase 
	void get_key()
	{
		cout << "enter encryption key: ";
		string alphabet = "abcdefghijklmnopqrstuvwxyz";
		getline(cin, keyword);
		while(keyword.size() != 5 || !isalpha_string(keyword) || has_repeated_chars(keyword))
		{
			cout << "enter valid keyword of uniques chars and length 5 \n keyword: ";
			getline(cin, keyword);
		}
		for(int i = 0; i < keyword.size(); i++)
		{
			keyword[i] |= 32;
			alphabet.erase(remove(all(alphabet), keyword[i]), end(alphabet));
		}
		keyword += alphabet;
	}
};

//###################################################################################################################################################################
//Each letter is replaced with two numbers  according to the 2d table where the col and row are determined by the key

class Cipher6 : public Cipher
{
	string keyword;
	char matrix[5][5];
	//check if the message contains pairs of adjecent digits
	bool is_valid_message(string message, int mode)
	{
		if(mode == ENCRYPTION)
			return 1;
		else if(mode == DECRYPTION)
		{
			for(int i = 0; i < message.size(); i++)
			{
				if(isdigit(message[i]))
				{
					if(i + 1 >= message.size())
						return 0;
					else if(!isdigit(message[i + 1]))
						return 0;
					else
						i++;
				}
			}
		}
		return 1;
	}
	string encrypt(string message)
	{
		map<char, string> encryption_key;
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				encryption_key[matrix[i][j]] += keyword[i];
				encryption_key[matrix[i][j]] += keyword[j];

			}
		}
		for(auto pr : encryption_key)
			cout << pr.first << ' ' << pr.second << endl;
		string encrypted;
		for(char c : message)
		{
			if(isalpha(c))
			{
				c |= 32;
				encrypted += (encryption_key[c]);
			}
			else
				encrypted.push_back(c);
		}
		return encrypted;
	}

	string decrypt(string message)
	{
		string decrypted;
		map<char, int> decryption_key;
		for(int i = 0; i < keyword.size(); i++)
			decryption_key[keyword[i]] = i;

		for(int i = 0; i < message.size(); i++)
		{
			if(isdigit(message[i]))
			{
				int y = decryption_key[message[i]];
				int x = decryption_key[message[i + 1]];
				decrypted.push_back(matrix[y][x]);
				i++;
			}
			else
				decrypted.push_back(message[i]);
		}
		return decrypted;
	}
	//construct the encryption matrix using keyword
	void construct_matrix()
	{
		for(int i = 0; i < 8; i++)
			matrix[i / 5][i % 5] = char(i + 'a');
		matrix[1][3] = 'i';
		for(int i = 9; i < 25; i++)
			matrix[ i / 5][i % 5] = char(i + 'b');
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
				cout << matrix[i][j] << ' ';
			cout << endl;
		}
	}

	bool all_under_six(string keyword)
	{
		for(char c : keyword)
			if(c-'0' > 5)
				return 0;
		return 1;
	}
	void get_key()
	{
		cout << "enter a number sequenc of length 5 as keyword: ";
		getline(cin, keyword);
		keyword.erase(remove(all(keyword), ' '), end(keyword));
		while (keyword.size() != 5 || !is_numeric_string(keyword) || !all_under_six(keyword))
		{
			cout << "enter numeric keyword under 6 of length 5\nkeyword : ";
			getline(cin, keyword);
			cout << keyword << endl;
		}
		construct_matrix();
	}
};

//###################################################################################################################################################################
class Cipher7 : public Cipher
{
	string encrypt(string message)
	{
		string q;
		for (char& j : message)
			j = j & ~32;

		for (char i : message)
		{
			auto it = m.find(i);
			if (it != end(m)) {
				q += it->second;
				q += ' ';
			}
		}
		return q;
	}
	string decrypt(string message)
	{


		stringstream string_stream(message);
		string decrypted;

		string q2;
		while (string_stream >> q2)
		{
			decrypted.push_back(m2[q2]);
		}
		return decrypted;
	}

};
//###################################################################################################################################################################
/*
Introduction
The railfence cipher is a very simple, easy to crack cipher.
It is a transposition cipher that follows a simple rule for mixing up
the characters in the plaintext to form the ciphertext.
The railfence cipher offers essentially no communication security,
and it will be shown that it can be easily broken even by hand.
Although weak on its own, it can be combined with other ciphers,
such as a substitution cipher,
the combination of which is more difficult to break than either cipher on it's own.
Many websites claim that the rail-fence cipher is a simpler "write down the columns,
read along the rows" cipher.
This is equivalent to using an un-keyed columnar transposition cipher.
*/
class Cipher9 : public Cipher
{
public:
	int key;
	string encrypt(string message)
	{
		message.erase(remove(begin(message), end(message), ' '), end(message));

		vector<string>str(key);
		int y = 0;
		int inc = 1;
		//here we have number key of string and we push back the first cahr on vector_[1] 
		// and the 2nd char on vector[2] and the 3 char on vector[3] then we mke inc=-1 to revers the hole opretion 
		// the 4th char on vector[2] ...
		for (size_t x = 0; x < size(message); ++x)
		{
			str[y].push_back(message[x]);
			if (y == key - 1)
				inc = -1;
			if (y == 0)
				inc = 1;
			y += inc;
		}
		//here we print all the string to gather
		string encrypted;
		for (auto h : str)
			encrypted += h;
		return encrypted;

	}
	string decrypt(string message)
	{
		//here we remove all space " " 
		message.erase(remove(begin(message), end(message), ' '), end(message));
		// we made string q as copy to message
		// and the tesult string is the taxt that we want
		string q = message;
		string result = "";
		//The idea in decryption here is that we encrypt
		//the encrypted word many times until it returns to its form in which it started,
		//after that we print the code that precedes the last	
		while (true)
		{
			result = q;
			q = encrypt(q);
			//here we chake if the string returns to its form in which it started
			if (q == message)
				return result;
		}
		return message;
	}
	void get_key()
	{
		cout << "please enter key: ";
		key = integer_in();
		while(key <= 0)
		{
			cout << "please enter a valid key: ";
			key = integer_in();
		}
	}
};
//###################################################################################################################################################################


ull integer_in()
{
	string message;
	getline(cin ,message );
	ull x;
	try
	{
		x = stoi(message);

	} catch(...)
	{
		cout << "Enter valid input:\n";
		return integer_in();
	}

	return x;
}

void print_commands()
{
	cout << "1- Cipher a message\n2- Decipher a message\n3- back\n";
	cout << "enter command index: ";
}

void print_ciphers()
{
	cout << "0 - Affine Cipher\n";
	cout << "1 - Caesar Cipher\n";
	cout << "2 - Atbash Cipher\n";
	cout << "3 - Vignere Cipher\n";
	cout << "4 - Baconian Cipher\n";
	cout << "5 - Simple Substitution Cipher\n";
	cout << "6 - Polybius Square Cipher\n";
	cout << "7 - Morse Code\n";
	cout << "8 - XOR Cipher\n";
	cout << "9 -  Rail-fence Cipher\n";
	cout << "10 -  Exit =(\n";

}

int main()
{
	string message;
	cout << "Hello, this is chiper from 0 to 9\n";
	while(true)
	{
		Cipher* cipher;
		print_ciphers();
		int cipher_command_index = 0;
		cout << "enter index : ";
		cipher_command_index = integer_in();
		while(cipher_command_index < 0 && cipher_command_index > 10)
		{
			cout << "enter a valid cipher index\n";
			cipher_command_index = integer_in();
		}
		if(cipher_command_index == 10)
			break;
		switch(cipher_command_index)
		{
			case 0:
			{

				Cipher0* c = new Cipher0();
				cipher = c;
				break;
			}
			case 1:
			{
				Cipher0* c = new Cipher0();
				cipher = c;
				break;
			}
			case 2:
			{
				Cipher2* c = new Cipher2();
				cipher = c;
				break;
			}
			case 3:
			{

				Cipher3* c = new Cipher3();
				cipher = c;
				break;
			}
			case 4:
			{
				Cipher4* c = new Cipher4();
				cipher = c;
				break;
			}
			case 5:
			{
				Cipher5* c = new Cipher5();
				cipher = c;
				break;
			}
			case 6:
			{
				Cipher6* c = new Cipher6();
				cipher = c;
				break;
			}
			case 7:
			{
				Cipher7* c = new Cipher7();
				cipher = c;
				break;
			}
			case 8:
			{

				Cipher0* c = new Cipher0();
				cipher = c;
				break;
			}
			case 9:
			{
				Cipher9* c = new Cipher9();
				cipher = c;
				break;
			}
		}

		while (true)
		{
			int command = 0;
			print_commands();
			command = integer_in();
			while(command > 3 && command <= 0)
			{
				cout << "enter valid command number: ";
				command = integer_in();
			}
			if(command == 3)
			{
				delete cipher;
				break;
			}
			switch(command)
			{
				case 1:
				{
					cipher->get_key();
					cout << "please enter the message to cipher: \n";
					getline(cin, message);
					while(message == "" || !cipher->is_valid_message(message, ENCRYPTION))
					{
						cout << "enter a valid message please:\n";
						getline(cin, message);
					}
					string encrypted = cipher->encrypt(message);

					cout << "encrypted message is \n\'"<< encrypted << "\'\n\n"; 
					break;
				}
				case 2:
				{
					cipher->get_key();
					cout << "please enter the message to decipher: \n";
					getline(cin, message);
					while(message == "" || !cipher->is_valid_message(message, DECRYPTION))
					{
						cout << "enter a valid message please:\n";
						getline(cin, message);
					}
					string decrypted = cipher->decrypt(message);

					cout << "decrypted message is \n\'"<< decrypted << "\'\n\n"; 

					break;
				}
				case 3:
					break;
			}
		}
	}
	
	cout << "Thanks for using ciphers";
}