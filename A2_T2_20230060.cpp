// FCAI - Structured programming - 2024 - Assignment 2

// Program Name : CS112_A2_T2_S18_20230060_S17_20230069_S17_20230043.cpp

// Program Discription : This program do Encryption and Decryption in Affine Cipher, Vingere Cipher, Rail Fence Cipher

// Last Modification Date : 10/3/2024

// Author1 : Eslam Saeed    ID : 20230060     Group : 18

// Author2 : Adham Hamdy    ID : 20230043     Group : 17

// Author3 : Andrew Wafae   ID : 20230069     Group : 17

// Teaching Assistant : Ahmed Fouad M. Farid Lotfy
// Eslam Saeed : Affine Cipher
// Adham Hamdy : Vingere Cipher
// Andrew Wafae : Rail Fence Cipher


#include<bits/stdc++.h>
using namespace std;

void rail_fence_cipher(string text, int key)
{
    string plaintext = "";
    for (char c : text) if (isalpha(c)) plaintext += toupper(c);
    cout << "\n(All spaces and non-alphabetical characters "
         << "from the input string are ignored, Input is capitalized\n\n";
    cout << "Plaintext to be ciphered: " << plaintext << "\n";

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

    cout << "Ciphertext: " << ciphertext;
}

void rail_fence_decipher(string text, int key)
{
    // Prepare the ciphertext (remove non-alphabetic characters and capitalize)
    string ciphertext = "";
    for (char c : text)
        if (isalpha(c))
            ciphertext += toupper(c);

    // Print ciphertext
    cout << "\n(All spaces and non-alphabetical characters "
         << "from the input string are ignored, Input is capitalized\n\n";
    cout << "Ciphertext to be deciphered: " << ciphertext << "\n";

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
    cout << "Plaintext: " << plaintext;
}

void run_rail_fence(string action, string& text)
{
    int key; // Variable to store the key for the cipher/decipher process

    // Keep asking the user for input until a valid key is provided
    while (true)
    {
        try
        {
            cin.ignore(); // Ignore any remaining characters in the input buffer

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

void upperCase(string &text)
{
    for (int i = 0; i < text.size(); i++) {
        if (isalpha(text[i]))
            text[i] = toupper(text[i]);
    }
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

void checkMessage(string &m)
{
    while (m.size() > 80)
    {
        cout << "Please enter a message of size doesn't exceed 80 characters" << endl;
        getline(cin, m);
        cin.ignore();
    }
}

void checkKey(string &k)
{
    here : {};
    while (k.size() > 8)
    {
        cout << "Please enter a key of size doesn't exceed 8 characters" << endl;
        getline(cin, k);
        cin.ignore();
    }
    for (int i = 0; i < k.size(); ++i) {
        if (!isalpha(k[i]))
        {
            cout << "Please enter a key contains only alphabetic characters" << endl;
            getline(cin, k);
            cin.ignore();
            goto here;
        }
    }
}

void vignereCipher(string &message)
{
    string keyword; // Variable to store the keyword for the Vigenère cipher

    // Prompt the user to enter the keyword
    cout << "\nKey word:";
    cin.ignore(); // Ignore any remaining characters in the input buffer
    getline(cin, keyword); // Get the entire line of input for the keyword

    // Function calls to validate the message and keyword
    checkMessage(message); // Assuming this function validates the message
    checkKey(keyword); // Assuming this function validates the keyword

    // Convert the message and keyword to uppercase
    upperCase(message);
    upperCase(keyword);

    int keyIndx = 0; // Initialize the index for the keyword
    // Iterate through each character in the message
    for (int i = 0; i < message.size(); i++)
    {
        // Check if the character is an alphabet
        if (isalpha(message[i]))
        {
            // Calculate the index for the encrypted character using Vigenère cipher formula
            int messageIndx = ((int)message[i] + (int)keyword[keyIndx]) % 26;
            message[i] = char('A' + messageIndx); // Update the character in the message
        }

        keyIndx++; // Move to the next character in the keyword

        // Wrap around the keyword index if it reaches the end of the keyword
        if (keyIndx == keyword.size())
            keyIndx = 0;
    }
}

void vignereDecipher(string &message)
{
    string keyword; // Variable to store the keyword for the Vigenère cipher

    // Prompt the user to enter the keyword
    cout << "\nKey word:";
    cin.ignore(); // Ignore any remaining characters in the input buffer
    getline(cin, keyword); // Get the entire line of input for the keyword

    // Function calls to validate the keyword and message
    checkKey(keyword); // Assuming this function validates the keyword
    checkMessage(message); // Assuming this function validates the message

    // Convert the message and keyword to uppercase
    upperCase(message);
    upperCase(keyword);

    int keyIndx = 0; // Initialize the index for the keyword
    // Iterate through each character in the message
    for (int i = 0; i < message.size(); i++)
    {
        // Check if the character is an alphabet
        if (isalpha(message[i]))
        {
            // Calculate the index for the decrypted character using Vigenère cipher formula
            int messageIndx = (message[i] - keyword[keyIndx] + 26) % 26;
            message[i] = char('A' + messageIndx); // Update the character in the message
        }

        keyIndx++; // Move to the next character in the keyword

        // Wrap around the keyword index if it reaches the end of the keyword
        if (keyIndx == keyword.size())
            keyIndx = 0;
    }
}


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

void affinecipher(string& message)
{
    cin.ignore();
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
}

void affinedecipher(string& message)
{
    cin.ignore(); // Ignore any remaining characters in the input buffer

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
}

int main()
{
    cout << "Ahlan ya user ya habibi."; // Welcome message

    // Main loop to continuously prompt the user for actions
    while (true)
    {
        // Prompt the user to choose an action
        cout << "\nWhat do you like to do?"
             << "\n1- Cipher a message\n"
                "2- Decipher a message\n"
                "3- End\n";

        string n = "5"; // Initialize the choice variable

        // Loop until a valid choice is entered (1, 2, or 3)
        while(n != "1" && n != "2" && n != "3")
        {
            cout << "\nPlease, Enter a valid choice: ";
            cin >> n;
        }

        // If the user chooses to end the program
        if(n == "3")
        {
            return 0; // Exit the program
        }

        string message; // Variable to store the message entered by the user

        cout << "\nPlease, Enter message: "; // Prompt the user to enter a message
        cin.ignore(); // Ignore any remaining characters in the input buffer
        getline(cin, message); // Get the entire line of input as the message

        cout << "\n1-Affine Cipher\n2-Vigenere Cipher\n3-Rail fence Cipher\n";
        string choice = "5"; // Initialize the choice variable for the cipher type

        // Loop until a valid choice is entered (1, 2, or 3)
        while(choice != "1" && choice != "2" && choice != "3")
        {
            cout << "\nPlease, Enter a valid choice: ";
            cin >> choice;
        }

        // If the user chooses to decipher a message
        if(n == "2")
        {
            // Perform the chosen decryption method based on the cipher type
            if(choice == "1")
            {
                affinedecipher(message); // Call the affine decipher function
                cout << "\nPlain Text: " << message; // Print the deciphered message
            }
            if(choice == "2")
            {
                vignereDecipher(message); // Call the Vigenere decipher function
                cout << "\nPlain Text: " << message; // Print the deciphered message
            }
            if(choice == "3")
            {
                run_rail_fence("B", message); // Call the rail fence decipher function
            }
        }

        // If the user chooses to cipher a message
        if(n == "1")
        {
            // Perform the chosen encryption method based on the cipher type
            if(choice == "1")
            {
                affinecipher(message); // Call the affine cipher function
                cout << "\nCiphered Text: " << message; // Print the encrypted message
            }
            if(choice == "2")
            {
                vignereCipher(message); // Call the Vigenere cipher function
                cout << "\nCiphered Text: " << message; // Print the encrypted message
            }
            if(choice == "3")
            {
                run_rail_fence("A", message); // Call the rail fence cipher function
            }
        }
    }
}