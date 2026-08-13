#include <bits/stdc++.h>
using namespace std;

class caeserCipher{
    private:
        int shift = 5;
    public:
        string encrypt(string &inputString){
            string encryptedString = "";
            for(int i=0; i<inputString.size(); i++){
                char ch = inputString[i];
                if(ch >= 'a' && ch <= 'z'){
                    ch = (ch-'a' + shift) % 26 +'a';
                }else if(ch >= 'A' && ch <= 'Z'){
                    ch = (ch-'A' + shift) % 26 + 'A';
                }

                encryptedString += ch;
            }
            return encryptedString;
        }

        string decrypt(string &encryptedString){
            string decryptedString = "";
            for(int i=0; i<encryptedString.size(); i++){
                char ch = encryptedString[i];
                if(ch >= 'a' && ch <= 'z'){
                    ch = (ch-'a' - shift + 26) % 26 +'a';
                }else if(ch >= 'A' && ch <= 'Z'){
                    ch = (ch-'A' - shift + 26) % 26 + 'A';
                }
                decryptedString += ch;
            }
            return decryptedString;
        }

};
int main(){
    string inputString;
    cout<<"Enter the string:";
    cin>> inputString;

    caeserCipher c;

    string encryptedString = c.encrypt(inputString);
    cout<<"Encrypted String: "<<encryptedString<<endl;

    string decryptedString = c.decrypt(encryptedString);
    cout<<"Decrypted String: "<<decryptedString<<endl;
}