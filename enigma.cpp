#include <bits/stdc++.h>
using namespace std;

struct Plugboard {
  int map[26];
};

Plugboard initPlugboard(vector<pair<char,char>> pairs) {
  Plugboard p;
  for (int i = 0; i<26; i++) {
    p.map[i] = i;
  }
  for (auto [a,b]:pairs) {
    if (p.map[a-'a'] == a-'a' && p.map[b-'a'] == b-'a') {
      p.map[a-'a'] = b-'a';
      p.map[b-'a'] = a-'a';
    }
  }
  return p;
}

int getP(int x, Plugboard &p) {
  return p.map[x];
}

struct Rotor {
  int wiring[26];
  int invWiring[26];
  int pos;
  int notch;
};

void getInv(Rotor &r) {
  for (int i = 0; i<26; i++) {
    r.invWiring[r.wiring[i]] = i;
  }
}

int rotorForward(int x, Rotor& r) {
  int t = r.wiring[(x + r.pos) % 26];
  return (t - r.pos + 26) % 26;
}

int rotorBackward(int x, Rotor &r) {
  int t = r.invWiring[(x+r.pos)%26];
  return (t - r.pos + 26) % 26;
}

struct Reflector {
  int map[26];
};

int reflect(int x, Reflector &r) {
  return r.map[x];
}

void rotorStep(Rotor&L, Rotor&M, Rotor&R) {
  if (M.pos == M.notch) {
    L.pos = (L.pos+1)%26;
    M.pos = (M.pos+1)%26;
  } 
  if (R.pos == R.notch) {
    M.pos = (M.pos+1)%26;
  }
  R.pos = (R.pos+1)%26;
}

struct Enigma {
  Plugboard p;
  Rotor L,M,R;
  Reflector ref;
};

char enc(char c, Enigma &e) {
  if (c >= 'a' && c <= 'z') c -= 'a' - 'A';
  if (c < 'A' || c > 'Z') return c;

  rotorStep(e.L, e.M, e.R);

  int x = c - 'A';
  x = getP(x, e.p);
  x = rotorForward(x, e.R);
  x = rotorForward(x, e.M);
  x = rotorForward(x, e.L);

  x = reflect(x, e.ref);

  x = rotorBackward(x, e.L);
  x = rotorBackward(x, e.M);
  x = rotorBackward(x, e.R);
  x = getP(x, e.p);

  return x + 'A';
  
}

string encrypt(const string &text, Enigma &e) {
  string ans;
  for (char c: text) {
    ans += enc(c, e);
  }
  return ans;
}

int main(int argc, char *argv[]) {
  Rotor rotorI = {{
      4,10,12,5,11,6,3,16,21,25,13,19,14,
      22,24,7,23,20,18,15,0,8,1,17,2,9
  }, {}, 0, 'Q' - 'A'};

  Rotor rotorII = {{
      0,9,3,10,18,8,17,20,23,1,11,7,22,
      19,12,2,16,6,25,13,15,24,5,21,14,4
  }, {}, 0, 'E' - 'A'};

  Rotor rotorIII = {{
      1,3,5,7,9,11,2,15,17,19,23,21,25,
      13,24,4,8,22,6,0,10,12,20,18,16,14
  }, {}, 0, 'V' - 'A'};

  getInv(rotorI); getInv(rotorII); getInv(rotorIII);

  Reflector reflectorB = {{
      24,17,20,7,16,18,11,3,15,23,13,
      6,14,10,12,8,4,1,5,25,2,22,21,9,0,19
  }};

  Plugboard p = initPlugboard({
      {'A','Z'}, {'B','T'}, {'C','F'}
  });

  Enigma enigma;
  enigma.L = rotorI;
  enigma.M = rotorII;
  enigma.R = rotorIII;
  enigma.ref = reflectorB;
  enigma.p = p;

  enigma.L.pos = 0;
  enigma.M.pos = 0;
  enigma.R.pos = 0;

  for (int i = 1; i<argc; i++) {
    // cout << encrypt(string(argv[i]), enigma);
    // cout << " ";
    // Enigma copy = enigma;
    cout << encrypt(argv[i], enigma) << " ";
  }
  cout << endl;
  return 0;
}