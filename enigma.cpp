#include <bits/stdc++.h>
using namespace std;

vector<int> rotorPosition(3, 0);
vector<char> notch = {'Q','E','V'};

string R1 = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
string R2 = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
string R3 = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
string reflect = "YRUHQSLDPXNGOKMIEBFZCWVJAT";

// TODO
// 1. Add the plugboard settings : all the 10 wire pairings
// 2. Add the ring settings : Modifies the wire indexing
// 3. Let the user select all the settings, via the input args.

void nextRotorPos() {
    if (rotorPosition[1]%26 + 'A' == notch[1]) rotorPosition[0] = (rotorPosition[0]+1)%26;
    if (rotorPosition[2]%26 + 'A' == notch[2]) rotorPosition[1] = (rotorPosition[1]+1)%26;
    rotorPosition[2] = (rotorPosition[2]+1)%26;
}

int forward(string &rotor, int turns, int x) {
    int shifted = (x + turns) % 26;
    int out = (rotor[shifted]-'A');
    return (out - turns + 26) % 26;
}


int backward(string &rotor, int turns, int x) {
    int shifted = (x + turns) % 26;
    // int out = (rotor[shifted]-'A');
    int index = rotor.find(shifted+'A');
    return (index - turns + 26) % 26;
}

char enigma(char c) {
    if (!isalpha(c)) return c;

    nextRotorPos();
    int x = toupper(c) - 'A';

    x = forward(R3, rotorPosition[2], x);
    x = forward(R2, rotorPosition[1], x);
    x = forward(R1, rotorPosition[0], x);
    x = reflect[x]-'A';
    x = backward(R1, rotorPosition[0], x);
    x = backward(R2, rotorPosition[1], x);
    x = backward(R3, rotorPosition[2], x);
    return x+'A';
}


int main(int argc, char *argv[]) {
    for (int i = 0; i<argc; i++) {
        for (char j : string(argv[i])) cout << enigma(j);
        cout << " ";
    }
    cout << endl;
    return 0;
}