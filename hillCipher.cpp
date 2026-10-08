#include <bits/stdc++.h>
using namespace std;

class HillCipher {
private:
    // 2x2 Key Matrix: {{K11, K12}, {K21, K22}}
    // Matrix chosen: {{3, 3}, {2, 5}}
    // Determinant = (3*5 - 3*2) = 9 (coprime with 26)
    int key[2][2] = {
        {3, 3},
        {2, 5}
    };
    int invKey[2][2];
    bool padded = false;

    // Helper to find modular multiplicative inverse of 'a' under mod 26
    int modInverse(int a, int m = 26) {
        a = (a % m + m) % m;
        for (int x = 1; x < m; x++) {
            if ((a * x) % m == 1) return x;
        }
        return -1;
    }

    // Computes the modular inverse matrix for decryption
    void calculateInverseMatrix() {
        int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
        det = (det + 26) % 26;

        int detInv = modInverse(det, 26);

        // Adjugate matrix mod 26:
        // [ d  -b]
        // [-c   a]
        invKey[0][0] = ( key[1][1] * detInv) % 26;
        invKey[0][1] = ((-key[0][1] % 26 + 26) * detInv) % 26;
        invKey[1][0] = ((-key[1][0] % 26 + 26) * detInv) % 26;
        invKey[1][1] = ( key[0][0] * detInv) % 26;
    }

public:
    HillCipher() {
        calculateInverseMatrix();
    }

    string encrypt(string inputString) {
        padded = false;
        // Pad with 'X' if length is odd
        if (inputString.length() % 2 != 0) {
            inputString += 'X';
            padded = true;
        }
        // Pad with 'X' if length is odd
        if (inputString.length() % 2 != 0) {
            inputString += 'X';
        }

        string encryptedString = "";
        for (size_t i = 0; i < inputString.length(); i += 2) {
            int p1 = toupper(inputString[i]) - 'A';
            int p2 = toupper(inputString[i + 1]) - 'A';

            // Vector-matrix multiplication mod 26
            int c1 = (key[0][0] * p1 + key[0][1] * p2) % 26;
            int c2 = (key[1][0] * p1 + key[1][1] * p2) % 26;

            encryptedString += (char)(c1 + 'A');
            encryptedString += (char)(c2 + 'A');
        }
        return encryptedString;
    }

    string decrypt(string encryptedString) {
        string decryptedString = "";
        for (size_t i = 0; i < encryptedString.length(); i += 2) {
            int c1 = toupper(encryptedString[i]) - 'A';
            int c2 = toupper(encryptedString[i + 1]) - 'A';

            // Decryption using inverse key matrix
            int p1 = (invKey[0][0] * c1 + invKey[0][1] * c2) % 26;
            int p2 = (invKey[1][0] * c1 + invKey[1][1] * c2) % 26;

            decryptedString += (char)(p1 + 'A');
            decryptedString += (char)(p2 + 'A');
        }
        if (padded && !decryptedString.empty()) {
            decryptedString.pop_back();
        }
        return decryptedString;
    }
};

int main() {
    string inputString;
    cout << "Enter the string: ";
    cin >> inputString;

    HillCipher h;

    string encryptedString = h.encrypt(inputString);
    cout << "Encrypted String: " << encryptedString << endl;

    string decryptedString = h.decrypt(encryptedString);
    cout << "Decrypted String: " << decryptedString << endl;

    return 0;
}