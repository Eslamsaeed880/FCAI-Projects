// FCAI - Structured programming - 2024 - Assignment 2

// Program Name : CS112_A2_T4_S18_20230060_S17_20230069_S17_20230043.cpp

// Program Discription : This program do Encryption and Decryption in all cipher programs in assignment 2

// Last Modification Date : 17/3/2024

// Author1 : Eslam Saeed    ID : 20230060     Group : 18

// Teaching Assistant : Ahmed Fouad M. Farid Lotfy

// Eslam E-mail  : eslamsaeed298@gmail.com


#include <bits/stdc++.h>

using namespace std;

bool chooseString(string& message)
{
    for(int i = 0; i < message.length(); i++)
    {
        if(message[i] == ' ') {
            continue;
        }
        message[i] = toupper(message[i]);
        if(!isalpha(message[i])) {
            return true;
        }
    }
    return false;
}

void checkVariables(int& a, int& b, int& c)
{
    // Continue looping until the equation is satisfied
    while ((a * c) % 26 != 1)
    {
        // Prompt the user to enter three numbers satisfying the equation
        cout << "\nEnter three numbers a, b, and c that satisfy this equation: (a * c) mod 26 = 1\n";

        // Loop to input 'a' and validate it
        while (true)
        {
            cout << "\na: ";
            if (cin >> a)
            {
                break; // Break out of the loop if input is valid
            }
            else
            {
                // Prompt the user for a numeric value if the input is invalid
                cout << "Invalid input. Please enter a numeric value.\n";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the invalid input
            }
        }

        // Loop to input 'b' and validate it (not used in the equation, just included for completeness)
        while (true)
        {
            cout << "\nb: ";
            if (cin >> b)
            {
                break; // Break out of the loop if input is valid
            }
            else
            {
                // Prompt the user for a numeric value if the input is invalid
                cout << "Invalid input. Please enter a numeric value.\n";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the invalid input
            }
        }

        // Loop to input 'c' and validate it
        while (true)
        {
            cout << "\nc: ";
            if (cin >> c)
            {
                break; // Break out of the loop if input is valid
            }
            else
            {
                // Prompt the user for a numeric value if the input is invalid
                cout << "Invalid input. Please enter a numeric value.\n";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the invalid input
            }
        }
    }
}

void affinecipher()
{
    string message;
    cout << "\nPlease enter the message to cipher:";
    getline(cin,message);
    while (true) {
        if (!chooseString(message)) {
            break;
        }
        cout << "\nInvalid input message! Enter alphabet letters only.\n";
        cout << "Please, Enter message: ";

        getline(cin, message);
    }
    cin.clear();
    int a = 2, b = 2, c = 1;
    checkVariables(a,b,c);
    for(int i = 0; i < message.length(); i++) {
        if(message[i] == ' ') {
            continue;
        }
        message[i] = (a * ((int) message[i] - 65) + b) % 26 + 65;
    }

    cout << "\nCiphered message: " << message;
}

void affinedecipher()
{
    string message;
    cout << "\nPlease enter the message to be deciphered:";
    getline(cin,message);

    // Loop until a valid message consisting of only alphabet letters is entered
    while (true)
    {
        if (!chooseString(message)) // Assuming chooseString checks if the input message consists of only alphabet letters
        {
            break; // Break out of the loop if a valid message is entered
        }

        // Inform the user about invalid input and prompt to enter a new message
        cout << "\nInvalid input message! Enter alphabet letters only.\n";
        cout << "Please, Enter message: ";
        getline(cin, message); // Get the new input message
    }

    cin.clear(); // Clear the error flag from the input stream

    int a = 2, b = 2, c = 2; // Initialize values for the affine cipher parameters
    checkVariables(a ,b ,c); // Call checkVariables to ensure a and c satisfy the equation (a * c) mod 26 = 1

    // Iterate through each character in the message
    for(int i = 0; i < message.length(); i++)
    {
        // Ignore spaces in the message
        if(message[i] == ' ')
        {
            continue;
        }

        // Apply affine cipher decryption formula to each character
        message[i] = (c * (message[i] - 65 - b)) % 26 + 65;

        // Handle cases where the result is less than 'A'
        if(message[i] < 65)
            message[i] +=26;
    }

    cout << "\nDeciphered message: " << message;
}



void route_cipher()
{
    string message, s;

    // Get the message from the user
    cout << "\nPlease enter the message to cipher:";
    getline(cin, message);

    // Remove non-alphabetic characters and store in 's'
    for (int i = 0; i < message.length(); i++)
    {
        if (isalpha(message[i]))
        {
            s += message[i];
        }
    }

    int cols;

    // Get the number of columns for the cipher
    cout << "Columns: ";
    while (!(cin >> cols))
    {
        cout << "\nInvalid input. Please enter an integer: ";
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Discard the invalid input
    }

    cout << endl;
    int rows = ceil((double)s.length() / cols), p = 0;
    char form[rows][cols];

    // Fill the matrix 'form' with characters from 's'
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (p < s.length())
            {
                form[i][j] = toupper(s[p++]);
            }
            else
            {
                form[i][j] = 'X'; // Fill empty spaces with 'X'
            }
        }
    }

    // Display the matrix
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << form[i][j] << ' ';
        }
        cout << endl;
    }

    string cipher_text;
    int start_row = 0, end_row = rows - 1, start_col = cols - 1, end_col = 0;

    // Perform the route cipher
    while (start_row <= end_row && start_col >= end_col)
    {
        for (int i = start_row; i <= end_row; i++)
        {
            cipher_text += form[i][start_col];
        }
        start_col--;

        for (int j = start_col; j >= end_col; j--)
        {
            cipher_text += form[end_row][j];
        }
        end_row--;

        if (start_row <= end_row)
        {
            for (int i = end_row; i >= start_row; i--)
            {
                cipher_text += form[i][end_col];
            }
            end_col++;
        }

        if (start_col >= end_col)
        {
            for (int j = end_col; j <= start_col; j++)
            {
                cipher_text += form[start_row][j];
            }
            start_row++;
        }
    }

    // Display the cipher text
    cout << "\nCipher text: ";
    if (cols > s.length())
    {
        for (int i = 0; i <= cipher_text.length() / 2; i++)
        {
            cout << cipher_text[i];
        }
    }
    else
    {
        if (cipher_text.length() % cols)
        {
            for (int i = 0; i <= cipher_text.length() % cols; i++)
            {
                cipher_text.pop_back();
            }
        }
        cout << cipher_text;
    }
}


bool rightkey(string key, string text)
{
    for(int i = 0; i < key.length(); i++)
    {
        if(!isdigit(key[i]))
        {
            return false;
        }
    }
    if(text.length() % stoi(key))
    {
        return false;
    }
    return true;
}

bool right_text(string text)
{
    for(int i = 0; i < text.length(); i++)
    {
        if(!isalpha(text[i]))
        {
            return false;
        }
    }
    return true;
}

void route_decipher()
{
// WARNING: NO validation
    // -------------------------------------------
    string ciphertext;
    cout << "Ciphertext: ";
    getline(cin, ciphertext);

    while(!right_text(ciphertext))
    {
        cout << "\nPlease enter an appropriate cipher text: ";
        getline(cin, ciphertext);
    }

    string key_input;
    cout << "Columns: ";
    getline(cin, key_input);

    while(!rightkey(key_input,ciphertext))
    {
        cout << "Please input an appropriate integer: ";
        getline(cin,key_input);
    }

    int key = stoi(key_input);
    int length = ciphertext.length();


    // ---------------------------------------------

    int n_cols = key;
    int n_rows = ceil(length / key);

    vector <char> init_row (n_cols, '.');
    vector <vector <char>> grid (n_rows, init_row);

    for (int l = 0, i = 0, i_inc = 1, j = n_cols - 1, j_inc = 0; l < length; l++, i += i_inc, j += j_inc)
    {
        grid[i][j] = ciphertext[l];

        for (auto row : grid) {for (auto cell : row) {cout << cell << " ";} cout << "\n";}
        cout << endl;

        // down stop, go left
        if ((i == n_rows - 1 || grid[i+1][j] != '.') && (i_inc == 1 && j_inc == 0))
        {
            i_inc = 0;
            j_inc = -1;
        }
            // left stop, go up
        else if ((j == 0 || grid[i][j-1] != '.') && (i_inc == 0 && j_inc == -1))
        {
            i_inc = -1;
            j_inc = 0;
        }
            // up stop, go right
        else if ((i == 0 || grid[i-1][j] != '.') && (i_inc == -1 && j_inc == 0))
        {
            i_inc = 0;
            j_inc = 1;
        }
            // right stop, go down
        else if ((j == n_cols -1 || grid[i][j+1] != '.') && (i_inc == 0 && j_inc == 1))
        {
            i_inc = 1;
            j_inc = 0;
        }
    }

    cout << "Plaintext: ";
    for (int i = 0; i < n_rows; i++)
    {
        for (int j = 0; j < n_cols; j++)
        {
            cout << grid[i][j];
        }
    }
}



string keepAlphaOnly(string s)
{
    up:
    string ret = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (isalpha(s[i]))
            ret += s[i];
    }
    while (!ret.size())
    {
        cout << "Please enter a text containing at least 1 alphabetical character: ";
        getline(cin, s);
        goto up; // Go back to the label 'up' to recheck and get input with alphabetical characters
    }
    return ret;
}

// Function to convert text to uppercase
void upperCase(string &text)
{
    for (int i = 0; i < text.size(); i++)
    {
        if (isalpha(text[i]))
            text[i] = toupper(text[i]);
    }
}

// Function to perform Atbash cipher on text
string atbash(string text)
{
    string calpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string cipher = "";
    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            int steps = text[i] - 'A';
            cipher += calpha[25 - steps];
        }
        else
            cipher += text[i];
    }
    return cipher;
}

// Function to perform Atbash cipher and decipher (version 1)
void atbashCipherDecipherV1()
{
    string text;
    cout << "\nEnter your text: ";
    getline(cin, text);
    text = keepAlphaOnly(text); // Keep only alphabetical characters
    upperCase(text); // Convert text to uppercase

    // Perform Atbash cipher
    string calpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string cipher = "";
    for (int i = 0; i < text.size(); i++)
    {
        if (isalpha(text[i]))
        {
            int steps = text[i] - 'A';
            cipher += calpha[25 - steps];
        }
        else
            cipher += text[i];
    }
    cout << "\nresult: " << cipher << endl; // Display the result
}

// Function to perform Atbash cipher and decipher (version 2)
void atbashCipherDecipherV2()
{
    string name, name1, name2;
    cout << "\nEnter your text: ";
    getline(cin, name);

    name = keepAlphaOnly(name); // Keep only alphabetical characters
    upperCase(name); // Convert text to uppercase

    // Split the text into two parts and perform Atbash cipher on each part
    name1 = name.substr(0, name.size() / 2);
    name2 = name.substr(name.size() / 2, name.size());

    name1 = atbash(name1);
    name2 = atbash(name2);

    cout << "\nresult: " << name2 << ' ' << name1 << endl; // Display the result
}



void checkInput(string &c)
{
    while (c.size() > 1)
    {
        cout << "Please enter only one number that represents the choice's number!";
        cin >> c;
    }
    while (!isdigit(c[0]) || (c[0] < '1' || c[0] > '3'))
    {
        cout << "Please enter only one number from [1, 2, 3]";
        cin >> c;
    }
}

// Function to check and validate the length of the message
void checkMessage(string &m)
{
    while (m.size() > 80)
    {
        cout << "Please enter a message of size that doesn't exceed 80 characters" << endl;
        getline(cin, m);
        cin.ignore();
    }
}

// Function to check and validate the length and content of the key
void checkKey(string &k)
{
    here:
    while (k.size() > 8)
    {
        cout << "Please enter a key that doesn't exceed 8 characters" << endl;
        getline(cin, k);
        cin.ignore();
    }
    for (int i = 0; i < k.size(); ++i)
    {
        if (!isalpha(k[i]))
        {
            cout << "Please enter a key that contains only alphabetic characters" << endl;
            getline(cin, k);
            cin.ignore();
            goto here;
        }
    }
}

// Function to perform Vigenère cipher encryption
void vignereCipher()
{
    string keyword, message; // Variables to store the keyword and message
    cout << "\nPlease enter the message to cipher:";
    getline(cin, message);

    cout << "\nKey word:";
    getline(cin, keyword);

    checkMessage(message); // Validate the message
    checkKey(keyword); // Validate the keyword

    // Convert the message and keyword to uppercase
    upperCase(message);
    upperCase(keyword);

    int keyIndx = 0; // Initialize the keyword index
    // Iterate through each character in the message
    for (int i = 0; i < message.size(); i++)
    {
        if (isalpha(message[i])) // Check if the character is an alphabet
        {
            // Encrypt the character using Vigenère cipher formula
            int messageIndx = ((int)message[i] + (int)keyword[keyIndx]) % 26;
            message[i] = char('A' + messageIndx); // Update the character in the message
        }

        keyIndx++; // Move to the next character in the keyword

        // Wrap around the keyword index if it reaches the end of the keyword
        if (keyIndx == keyword.size())
            keyIndx = 0;
    }

    cout << "Ciphered Text: " << message;
}

// Function to perform Vigenère cipher decryption
void vignereDecipher()
{
    string keyword, message; // Variables to store the keyword and message
    cout << "\nPlease enter the message to be deciphered:";
    getline(cin, message);

    cout << "\nKey word:";
    getline(cin, keyword);

    checkKey(keyword); // Validate the keyword
    checkMessage(message); // Validate the message

    // Convert the message and keyword to uppercase
    upperCase(message);
    upperCase(keyword);

    int keyIndx = 0; // Initialize the keyword index
    // Iterate through each character in the message
    for (int i = 0; i < message.size(); i++)
    {
        if (isalpha(message[i])) // Check if the character is an alphabet
        {
            // Decrypt the character using Vigenère cipher formula
            int messageIndx = (message[i] - keyword[keyIndx] + 26) % 26;
            message[i] = char('A' + messageIndx); // Update the character in the message
        }

        keyIndx++; // Move to the next character in the keyword

        // Wrap around the keyword index if it reaches the end of the keyword
        if (keyIndx == keyword.size())
            keyIndx = 0;
    }

    cout << "\nPlain text:" << message;
}



deque<int> decToBin(int dec)
{
    deque<int> bin;
    while (dec)
    {
        int digit = dec % 2;
        bin.push_front(digit); // Add the digit to the front of the deque
        dec /= 2;
    }
    while (bin.size() < 5)
        bin.push_front(0); // Pad with zeros to ensure 5-bit representation

    return bin;
}

// Function to convert a 5-bit binary string to decimal character
int binToDecChar(string bin)
{
    int dec = 0;
    for (int i = 0; i < bin.size(); i++)
    {
        if (bin[i] == 'a')
            dec *= 2; // Multiply by 2 for 'a'
        else
            dec = dec * 2 + 1; // Multiply by 2 and add 1 for 'b'
    }
    return dec;
}

// Function to remove spaces from a string
void DeleteSpaces(string &text)
{
    string text2;
    for (int i = 0; i < text.length(); i++)
    {
        if (!isspace(text[i]))
        {
            text2 += text[i];
        }
    }
    text = text2;
}

// Function to perform Baconian cipher encryption
string baconianCipher()
{
    string plain;
    cout << "\nPlaintext: ";
    getline(cin, plain);

    // Validate the plaintext to ensure it contains only alphabetic characters
    while (chooseString(plain))
    {
        cout << "\nPlease enter a valid plaintext:";
        getline(cin, plain);
    }

    DeleteSpaces(plain); // Remove spaces from the plaintext

    string cipher = "";

    upperCase(plain); // Convert plaintext to uppercase

    deque<int> carry(5);

    for (int i = 0; i < plain.size(); i++)
    {
        int letter = plain[i] - 'A'; // Convert character to corresponding integer
        carry = decToBin(letter); // Convert integer to 5-bit binary using decToBin function

        for (auto it : carry)
        {
            if (it == 0)
                cipher += 'a'; // Represent binary 0 as 'a'
            else
                cipher += 'b'; // Represent binary 1 as 'b'
        }
    }
    cout << "\nCiphered text: ";
    return cipher;
}

// Function to check if a string contains only 'a' and 'b'
bool RightBinary(string text)
{
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] != 'a' && text[i] != 'b')
        {
            return false;
        }
    }
    return true;
}

// Function to perform Baconian cipher decryption
string baconianDecipher()
{
    string decrypt;
    cout << "\nCiphered text:";
    getline(cin, decrypt);

    // Validate the ciphertext to ensure it contains only 'a' and 'b' and is a multiple of 5
    while (!RightBinary(decrypt) || decrypt.length() % 5 != 0)
    {
        cout << "\nPlease enter a valid Ciphered text:";
        getline(cin, decrypt);
    }

    vector<int> dec;
    int begin = 0, end = 5;

    // Split the ciphertext into 5-bit binary chunks and convert each chunk to decimal
    while (end <= decrypt.size())
    {
        string carry;
        carry = decrypt.substr(begin * 5, 5); // Extract a 5-bit chunk
        dec.push_back(binToDecChar(carry)); // Convert the chunk to decimal
        begin++;
        end += 5;
    }
    string plain = "";
    for (auto it : dec)
    {
        plain += (char)('A' + it); // Convert decimal values back to characters
    }
    cout << "\nPlain text: ";
    return plain;
}



bool is_right_key(string key)
{
    // Check if the key contains 5 unique alphabetic characters
    for(int i = 0; i < key.length(); i++)
    {
        for(int j = 0; j < key.length(); j++)
        {
            if(!isalpha(key[i]) || (key[i] == key[j] && i != j) || key.length() != 5)
            {
                return false;
            }
        }
    }
    return true;
}

// Function to create a valid cipher text based on the key
void make_cipher_text(string& cipher_text , string& key)
{
    // Remove characters from the key that are already present in the cipher text
    for(char c : cipher_text)
    {
        bool isgood = true;
        for(char k : key)
        {
            if(c == k)
            {
                isgood = false;
            }
        }
        if(isgood)
        {
            key+=c;
        }
    }
}

// Function to perform simple substitution cipher encryption
void simple_substitution_cipher()
{
    string text;
    cout << "\nPlain text:";
    getline(cin, text);

    string key = "aa"; // Default key to avoid uninitialized use

    // Prompt the user to enter a valid key
    while(!is_right_key(key))
    {
        cout << "\nPlease enter a key of 5 unique letters:";
        getline(cin,key);
    }

    // Convert the key to lowercase if necessary
    for(int i = 0; i < key.length(); i++)
    {
        if(isalpha(key[i]) && key[i] < 'a')
        {
            key[i] += 32;
        }
    }

    string cipher_text = "abcdefghijklmnopqrstuvwxyz"; // Default cipher text
    make_cipher_text(cipher_text,key); // Create a valid cipher text based on the key

    cout << "\nCiphered text:";
    for(char t : text)
    {
        if(isupper(t))
            t += 32;
        if(isalpha(t))
            cout << key[t - 'a']; // Encrypt each character in the text using the key
        else
            cout << t;
    }
}

// Function to perform simple substitution cipher decryption
void simple_substitution_decipher()
{
    string text;
    cout << "\nEnter your text: ";
    getline(cin, text);

    string key = "aa"; // Default key to avoid uninitialized use

    // Prompt the user to enter a valid key
    while(!is_right_key(key))
    {
        cout << "\nPlease enter a key of 5 unique letters: ";
        getline(cin,key);
    }

    // Convert the key to lowercase if necessary
    for(int i = 0; i < key.length(); i++)
    {
        if(isalpha(key[i]) && key[i] < 'a')
        {
            key[i] += 32;
        }
    }

    string cipher_text = "abcdefghijklmnopqrstuvwxyz"; // Default cipher text
    make_cipher_text(cipher_text,key); // Create a valid cipher text based on the key

    cout << "\nPlain text: ";

    for(int i = 0; i < text.length();i++)
    {
        if(isupper(text[i]))
            text[i]+=32;
        if(isalpha(text[i]))
            for(int j = 0; j < cipher_text.length(); j++)
            {
                if(key[j] == text[i])
                {
                    cout << cipher_text[j]; // Decrypt each character in the text using the key
                    break;
                }
            }
        else
        {
            cout << text[i];
        }
    }
}



void polybius_cipher(string text, string key)
{
    string ciphertext = "";
    cout << "\nPlaintext to be ciphered: ";
    for (auto c : text)
        if (isalpha(c) || c == ' ')
            cout << (char) toupper(c);
    cout << endl;

    for (char c : text)
    {
        if (c == ' ')
        {
            ciphertext += " "; // Add space as is
        }
        else if (isalpha(c))
        {
            int square_no = ((int) tolower(c)) - 96;
            if (square_no >= 10)
                square_no--;

            // Calculate row and column indices in the Polybius square
            int row_index = floor((square_no - 1) / 5);
            int column_index = (square_no - 1) % 5;
            ciphertext += key[row_index]; // Add row character
            ciphertext += key[column_index]; // Add column character
        }
    }
    cout << "\nCiphertext: " << ciphertext;
}

// Function to perform Polybius cipher decryption
void polybius_decipher(string text, string key)
{
    string plaintext;
    for (int i = 0; i < text.length(); i += 2)
    {
        while (text[i] == ' ')
        {
            plaintext += " "; // Add space as is
            i++;
        }

        // Find cell corresponding to the number in the Polybius square
        int row_index;
        for (int j = 0; j < 5; j++)
            if (text[i] == key[j])
                row_index = j;
        int col_index;
        for (int j = 0; j < 5; j++)
            if (text[i + 1] == key[j])
                col_index = j;

        int order = (row_index) * 5 + col_index + 1;
        if (order >= 10)
            order++;
        plaintext += toupper((char) (96 + order)); // Convert back to uppercase character
    }
    cout << "\nPlaintext: " << plaintext;
}

// Function to run the Polybius cipher based on the action (ciphering or deciphering)
void run_polybius(string action)
{
    string text;
    if (action == "A")
    {
        cout << "\nPlaintext:";
        getline(cin, text);
    }
    else
    {
        while (true)
        {
            cout << "\nCiphertext: ";
            getline(cin, text);

            bool valid = true;
            for (int i = 0; i < text.length() && valid; i += 2)
            {
                while (text[i] == ' ')
                {
                    i++;
                }

                if (!(isdigit(text[i]) && isdigit(text[i + 1])))
                {
                    valid = false;
                }
            }
            if (!valid)
            {
                cout << "\nInvalid Ciphertext, please try again" << "\n";
            }
            else
            {
                break;
            }
        }
    }

    string key;
    while (true)
    {
        cout << "\nKey: ";
        getline(cin, key);

        string sorted_key = key;
        sort(sorted_key.begin(), sorted_key.end()); // Sort the key
        if (sorted_key != "12345")
        {
            cout << "\nInvalid Key, please enter the numbers 1 to 5 in any order" << "\n";
        }
        else
        {
            break;
        }
    }

    if (action == "A")
    {
        polybius_cipher(text, key);
    }
    else if (action == "B")
    {
        polybius_decipher(text, key);
    }
    cout << "\n";
}



// Morse code mapping
map<char, string> morse_code = {
        {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."}, {'F', "..-."},
        {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
        {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."},
        {'S', "..."}, {'T', "-"}, {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
        {'Y', "-.--"}, {'Z', "--.."},
        {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
        {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."},
};

// Function to check if the input is valid
bool isvalid(string& s, int j)
{
    if (j) {
        // Check for valid Morse code
        for (int i = 0; i < s.length(); i++) {
            if (s[i] != '.' && s[i] != '-' && s[i] != ' ')
                return false;
        }
        return true;
    } else {
        // Check for valid alphanumeric characters and spaces
        for (int i = 0; i < s.length(); i++) {
            if (!isalnum(s[i]) && !isspace(s[i]))
                return false;
        }
        return true;
    }
}

// Function to perform Morse code encryption
void morse_code_cipher()
{
    string message;
    cout << "\nPlain text:";
    getline(cin, message);

    // Validate input
    while (!isvalid(message, 0)) {
        cout << "\nPlease enter digits or letters only without any special characters\n";
        getline(cin, message);
    }

    cout << "\nCiphered text: ";
    for (int i = 0; i < message.length(); i++) {
        message[i] = toupper(message[i]);
        if (isalnum(message[i])) {
            cout << morse_code[message[i]] << ' '; // Print Morse code for alphanumeric characters
        } else if (isspace(message[i])) {
            cout << "    "; // Print space in Morse code
        }
    }
}

// Function to perform Morse code decryption
void morse_code_decipher()
{
    string message;
    cout << "\nCiphered text:";
    getline(cin, message);

    // Validate input
    while (!isvalid(message, 1)) {
        cout << "\nPlease enter a valid Morse code";
        getline(cin, message);
    }

    int spaces = 0;

    cout << "\nPlain text: ";
    for (int i = 0; i < message.length(); ++i) {
        string letter = "";

        if (message[i] == ' ') {
            spaces++;
            if (spaces > 2) {
                cout << " "; // Print space for consecutive spaces
                spaces = 0;
                continue;
            }
            continue;
        } else
            spaces = 0;

        // Read Morse code for each letter
        while (i < message.length() && message[i] != ' ') {
            letter += message[i];
            ++i;
        }

        // Find the corresponding letter in Morse code mapping
        for (const auto& j : morse_code) {
            if (j.second == letter) {
                cout << j.first; // Print the decoded letter
                break;
            }
        }
    }
}



string dec_int_to_bin(int n)
{
    string binary = "";
    while (n != 0)
    {
        binary = (n % 2 == 0 ? "0" : "1") + binary;
        n /= 2;
    }
    // Pad with zeros to make it 8 bits long
    for (int i = 0, b = binary.length(); i < 8 - b; i++)
    {
        binary = "0" + binary;
    }
    return binary;
}

// Function to perform XOR operation on two binary strings
string bin_xor(string bin_str1, string bin_str2)
{
    string xor_str = "";
    for (int i = 0; i < bin_str1.length(); i++)
    {
        if (bin_str1[i] != bin_str2[i]) xor_str += "1";
        else xor_str += "0";
    }
    return xor_str;
}

// Function to convert binary string to hexadecimal string
string bin_int_to_hex(string bin_str)
{
    string hex = "";
    for (int i = 0; i < bin_str.length(); i += 4)
    {
        int value = 0;
        for (int j = 0; j < 4; j++)
        {
            value += ((int)bin_str[i + j] - 48) * pow(2, 4 - (j + 1));
        }

        char hex_digit;
        // Convert value to hexadecimal digit
        if (0 <= value && value <= 9)
            hex_digit = (char)(value + 48);
        else
        {
            switch (value)
            {
                case 10: hex_digit = 'A'; break;
                case 11: hex_digit = 'B'; break;
                case 12: hex_digit = 'C'; break;
                case 13: hex_digit = 'D'; break;
                case 14: hex_digit = 'E'; break;
                case 15: hex_digit = 'F'; break;
            }
        }

        hex += hex_digit;
    }
    return hex;
}

// Function to convert hexadecimal string to binary string
string hex_int_to_bin(string spaced_hex)
{
    map<char, string> hex_in_bin
            {
                    {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
                    {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
                    {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
                    {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
            };

    string bin_str;
    // Convert each hexadecimal digit to binary and add to bin_str
    for (int i = 0; i < spaced_hex.length(); i += 3)
    {
        bin_str += hex_in_bin[(isalpha(spaced_hex[i]) ? toupper(spaced_hex[i]) : spaced_hex[i])];
        bin_str += hex_in_bin[(isalpha(spaced_hex[i + 1]) ? toupper(spaced_hex[i + 1]) : spaced_hex[i + 1])];
        bin_str += " ";
    }
    return bin_str;
}

// Function to convert binary text to normal text
string bin_text_to_normal_text(string spaced_binary)
{
    string plaintext = "";
    // Convert each 8-bit binary substring to decimal and then to corresponding character
    for (int i = 0; i < spaced_binary.length(); i += 9)
    {
        int dec = 0;
        for (int j = 0; j < 8; j++)
        {
            if (spaced_binary[i + j] == '1')
            {
                dec += pow(2, 8 - (j + 1));
            }
        }
        // Check if decimal value corresponds to a printable character
        if (isprint(dec))
        {
            plaintext += (char)dec;
        }
    }

    return plaintext;
}

// Function to perform XOR encryption
void xor_cipher(string text, vector<string> key_binaries)
{
    string binary_text = "";
    string hex = "";
    // Perform XOR operation on each character and append to binary_text and hex
    for (int i = 0; i < text.length(); i++)
    {
        string character_binary = dec_int_to_bin((int)text[i]);
        binary_text += (bin_xor(character_binary, key_binaries[i % key_binaries.size()])) + " ";
        hex += bin_int_to_hex(bin_xor(character_binary, key_binaries[i % key_binaries.size()])) + " ";
    }
    // Convert binary text to normal text and display
    string normal_text = bin_text_to_normal_text(binary_text);
    cout << "\nPrintable Ciphertext: " << normal_text << endl;
    cout << "\nHex: " << hex << endl;
}

// Function to perform XOR decryption
void xor_decipher(string text, vector<string> key_binaries)
{
    // Convert hexadecimal ciphertext to binary
    string input_binary = hex_int_to_bin(text);
    string xor_binary_res = "";
    // Perform XOR operation on each 8-bit block and append to xor_binary_res
    for (int i = 0; i < input_binary.length(); i += 9)
    {
        xor_binary_res += bin_xor(input_binary.substr(i, 8), key_binaries[(i / 9) % key_binaries.size()]) + " ";
    }
    // Convert binary text to normal text and display
    string plaintext = bin_text_to_normal_text(xor_binary_res);
    cout << "\nPrintable Plaintext: " << plaintext;
}

// Function to run XOR encryption or decryption based on user input
void run_xor(string action)
{
    string text;
    bool valid = false;
    // Prompt user for input until valid input is provided
    while (!valid)
    {
        valid = true;
        string hex_chars = "0123456789ABCDEF";
        if (action == "A")
        {
            cout << "\nText: " << " (spaces are valid characters) ";
            getline(cin, text);
        }
        else if (action == "B")
        {
            cout << "\n" << "Please enter the ciphertext in hexadecimal, (Must start with a hexadecimal number, " << "\n"
                 << "all hexadecimal numbers must be separated by exactly 1 space and be exactly 2 characters long) " << "\n"
                 << "\nHex: ";
            getline(cin, text);
            // Validate the input ciphertext
            for (int i = 0; i < text.length(); i++)
            {
                if ((i + 1) % 3 == 0) { if (text[i] != ' ') valid = false; }
                else if (find(hex_chars.begin(), hex_chars.end(), (isalpha(text[i]) ? toupper(text[i]) : text[i])) == hex_chars.end()) valid = false;
            }

            if (!valid) cout << "\nInvalid input, please try again." << "\n";
        }
    }

    string key;
    cout << "\nKey: (space-sensitive) ";
    getline(cin, key);

    vector<string> key_binaries(key.length(), "");
    // Convert key characters to binary and store in key_binaries vector
    for (int i = 0; i < key_binaries.size(); i++) key_binaries[i] = dec_int_to_bin((int)key[i]);
    // Perform XOR encryption or decryption based on action
    if (action == "A") xor_cipher(text, key_binaries);
    else if (action == "B") xor_decipher(text, key_binaries);
    cout << "\n\n";

}



void rail_fence_cipher(string text, int key)
{
    string plaintext = "";
    for (char c : text) if (isalpha(c)) plaintext += toupper(c);
    cout << "\nPlaintext to be ciphered: " << plaintext << "\n";

    int n_row = key;
    int n_col = plaintext.length();

    vector <char> row (n_col, '.');
    vector <vector <char>> rows (n_row, row);

    // Fill the grid in a zigzag shape
    for (int i = 0, j = 0, increment = 1; j < n_col; i += increment, j++)
    {
        rows[i][j] = plaintext[j];

        if (i == n_row - 1) increment = -1;
        else if (i == 0 && j != 0) increment = 1;
    }

    // Read the ciphertext row by row
    string ciphertext;
    for (int i = 0; i < n_row; i++)
    {
        for (int j = 0; j < n_col; j++)
        {
            if (rows[i][j] != '.') ciphertext += rows[i][j];
        }
    }

    cout << "\nCiphertext: " << ciphertext;
}

void rail_fence_decipher(string text, int key)
{
    // Prepare the ciphertext (remove non-alphabetic characters and capitalize)
    string ciphertext = "";
    for (char c : text)
        if (isalpha(c))
            ciphertext += toupper(c);

    // Print ciphertext
    cout << "\nCiphertext to be deciphered: " << ciphertext << "\n";

    cin.ignore();
    // Initialize variables for the number of rows and columns in the rail fence grid
    int n_row = key;
    int n_col = ciphertext.length();

    // Calculate where each row begins from the cipher text
    vector<int> lengths_prefix_sum(key, 0);
    for (int i = 0; i < key; i++)
    {
        lengths_prefix_sum[i] += lengths_prefix_sum[i - 1];

        int chunk_size = (2 * key - 2);
        int second_element_index = chunk_size - i;
        int n_chunks = floor((n_col - i) / chunk_size);
        int remainder = n_col - (chunk_size * n_chunks);

        lengths_prefix_sum[i] += (i == 0 || i == key - 1) ? n_chunks : 2 * n_chunks;
        if (i == 0)
        {
            if (remainder != 0)
                lengths_prefix_sum[i] += 1;
        }
        else if (i == key - 1)
        {
            if (remainder >= key)
                lengths_prefix_sum[i] += 1;
        }
        else
        {
            if (i <= remainder - 1 && remainder - 1 < second_element_index)
                lengths_prefix_sum[i] += 1;
            else if (remainder - 1 >= second_element_index)
                lengths_prefix_sum[i] += 2;
        }
    }

    // Split the ciphertext into strings, 1 for each row
    vector<int> counters(key, 0);
    vector<string> substrings(key, "");
    for (int i = 0; i < key; i++)
    {
        int start_index = i != 0 ? lengths_prefix_sum[i - 1] : 0;
        for (int j = start_index; j < lengths_prefix_sum[i]; j++)
        {
            substrings[i] += ciphertext[j];
        }
    }

    // Fill the grid in a zigzag shape
    vector<char> row(n_col, '.');
    vector<vector<char>> rows(n_row, row);
    for (int i = 0, j = 0, increment = 1; j < n_col; i += increment, j++)
    {
        rows[i][j] = substrings[i][counters[i]];
        counters[i]++;

        // Change direction if reaching the top or bottom row
        if (i == n_row - 1)
            increment = -1;
        else if (i == 0 && j != 0)
            increment = 1;
    }

    // Read the plaintext left to right (column by column)
    string plaintext = "";
    for (int i = 0; i < n_col; i++)
    {
        for (int j = 0; j < n_row; j++)
        {
            if (rows[j][i] != '.')
                plaintext += rows[j][i];
        }
    }

    // Print the resulting plaintext
    cout << "\nPlaintext: " << plaintext;
}

void run_rail_fence(string action)
{
    string text;
    cout << "\nText: ";
    getline(cin,text);

    int key; // Variable to store the key for the cipher/decipher process

    // Keep asking the user for input until a valid key is provided
    while (true)
    {
        try
        {
            // Prompt the user to enter the key
            cout << "\n" << "Key: ";
            string input;
            getline(cin, input); // Get the entire line of input from the user

            // Convert the input string to a floating-point number
            float key_f = stof(input);

            // Check if the key is not an integer
            if (key_f != (int) key_f)
            {
                cout << "Not an integer, please try again." << "\n";
                continue; // Continue to the next iteration of the loop
            }

            // Convert the key to an integer
            key_f = (int) key_f;

            // Check if the key is not positive
            if (key_f <= 0)
                cout << "Not positive, please enter a positive integer" << "\n";
            else
            {
                key = key_f; // Assign the key
                break; // Exit the loop since a valid key is provided
            }
        }
        catch(...) // Catch any exceptions thrown during the input conversion
        {
            cout << "Not a number, please try again." << "\n";
        }
    }

    // Perform the specified action based on the user input
    if (action == "A")
    {
        rail_fence_cipher(text,  key); // Call the rail fence cipher function
    }
    else if (action == "B")
    {
        rail_fence_decipher(text, key); // Call the rail fence decipher function
    }

    cout << "\n\n"; // Add extra newline for clarity
}



int main()
{
    // Display a welcome message and ask the user for their choice
    cout << "Ahlan ya user ya habibi."
            "\nWhat do you like to do today?";

    while(true)
    {
        string choice = "5", choice2, choose;
        // Display menu options
        cout << "\n1-Cipher message\n"
                "2-Decipher message\n"
                "3-End\n";

        // Validate the user's choice
        while(choice != "1" && choice != "2" && choice != "3")
        {
            cout << "\nPlease enter a valid choice: ";
            cin >> choice;
        }

        // Process user's choice
        if(choice == "1" || choice == "2")
        {
            // Display cipher options
            cout << "\nWhich cipher do you like to choose\n";
            cout << "1-Affine Cipher\n"
                    "2-Route Cipher\n"
                    "3-Atbash Cipher\n"
                    "4-Vignere Cipher\n"
                    "5-Baconian Cipher\n"
                    "6-Simple Substitution Cipher\n"
                    "7-Polybius Square Cipher\n"
                    "8-Morse Code Cipher\n"
                    "9-XOR Cipher\n"
                    "10-Rail-fence Cipher\n"
                    "11-Return\n";

            do
            {
                // Get user's choice for cipher
                cout << "\nenter a valid choice: ";
                cin >> choice2;
            }
            while (choice2 != "1" && choice2 != "2" && choice2 != "3" && choice2 != "4" && choice2 != "5" && choice2 != "6" && choice2 != "7" && choice2 != "8" && choice2 != "9" && choice2 != "10" && choice2 != "11");

            cin.ignore();

            if(choice == "1")
            {
                // Process affine cipher
                switch(stoi(choice2))
                {
                    case 1:
                        affinecipher();
                        break;
                    case 2:
                        route_cipher();
                        break;
                    case 3:
                        // Process Atbash cipher based on user's version choice
                        cout << "\nWhat is the version do you want to use (1 , 2)\n";
                        getline(cin, choose);
                        while(choose != "1" && choose != "2")
                        {
                            cout << "Please, choose 1 or 2\n";
                            getline(cin, choose);
                        }
                        if(choose == "1")
                        {
                            atbashCipherDecipherV1();
                        }
                        else
                        {
                            atbashCipherDecipherV2();
                        }
                        break;
                        // Process other ciphers based on user's choice
                    case 4:
                        vignereCipher();
                        break;
                    case 5:
                        cout << baconianCipher();
                        break;
                    case 6:
                        simple_substitution_cipher();
                        break;
                    case 7:
                        run_polybius("A");
                        break;
                    case 8:
                        morse_code_cipher();
                        break;
                    case 9:
                        run_xor("A");
                        break;
                    case 10:
                        run_rail_fence("A");
                        break;

                    default:
                        cout << "Good bye!";
                        return 0;
                }
            }

            if(choice == "2")
            {
                // Process deciphering based on user's choice
                switch(stoi(choice2))
                {
                    case 1:
                        affinedecipher();
                        break;
                    case 2:
                        route_decipher();
                        break;
                    case 3:
                        // Process Atbash deciphering based on user's version choice
                        cout << "\nWhat is the version do you want to use (1 , 2)\n";
                        getline(cin, choose);
                        while(choose != "1" && choose != "2")
                        {
                            cout << "Please, choose 1 or 2\n";
                            getline(cin, choose);
                        }
                        if(choose == "1")
                        {
                            atbashCipherDecipherV1();
                        }
                        else
                        {
                            atbashCipherDecipherV2();
                        }
                        break;
                        // Process other deciphering based on user's choice
                    case 4:
                        vignereDecipher();
                        break;
                    case 5:
                        cout << baconianDecipher();
                        break;
                    case 6:
                        simple_substitution_decipher();
                        break;
                    case 7:
                        run_polybius("B");
                        break;
                    case 8:
                        morse_code_decipher();
                        break;
                    case 9:
                        run_xor("B");
                        break;
                    case 10:
                        run_rail_fence("B");
                        break;

                    default:
                        cout << "Good bye!";
                        return 0;
                }
            }
        }

        if(choice == "3")
        {
            // End the program
            cout << "Good bye!";
            return 0;
        }
        cout << '\n';
    }
}
