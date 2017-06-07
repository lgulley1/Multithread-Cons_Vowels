//Prints words from text file, indicating whether they are a consonant or vowel
//Luke Gulley
//October 02, 2016

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

//indicates end of file for functions
bool shutdown = false;

//indicates status of word's first letter
bool vowFlag = false;
bool conFlag = false;

bool readNextWordFlag = false;
std::string currWord;

//determines first letter of a word's status
bool checkVowel(std::string word) {
    char vowels[10] = {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'};
    for(int i = 0; i < 10; i++) {
        if(word[0] == vowels[i]) {
            return true;
        }
    }
    return false;
}

//prints if a word is a consonant
void cons(std::string& currWord) {
    while(!shutdown) {
        while(!conFlag) {
            std::this_thread::yield();
        }
        conFlag = false;
        std::cout << "cons: " << currWord << "\n";
        readNextWordFlag = true;
    }
}

//prints if a word is a vowel
void vow(std::string& currWord) {
    while(!shutdown) {
        while(!vowFlag) {
            std::this_thread::yield();
        }
        vowFlag = false;
        std::cout << "vow: " << currWord << "\n";
        readNextWordFlag = true;
    }
}

int main() {
    std::ifstream input;
    input.open("phrase.txt");
    
    if(input.is_open()) {
        
        std::thread vowThread(vow, std::ref(currWord));
        std::thread consThread(cons, std::ref(currWord));
        
        while(!input.eof()) { //for every word
            input >> currWord;
            if(checkVowel(currWord)) {
                vowFlag = true;
                conFlag = false;
            }
            else {
                vowFlag = false;
                conFlag = true;
            }
            while(!readNextWordFlag) {
                std::this_thread::yield();
            }
            readNextWordFlag = false;
        }
        shutdown = true; //prevents threads from being re-run from conext switching
        
        //detaches threads because they have completed, allowing the main thread to finish
        vowThread.detach();
        consThread.detach();
    }
    else {
        std::cout << "Error, phrase.txt not found.\n";
    }
    return 0;
}

bool checkVowel(std::string);
void cons(std::string&);
void vow(std::string&);