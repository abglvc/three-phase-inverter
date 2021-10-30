// 50Hz sinus, 1000Hz zigzag
int MAX_PODATAKA = 119;

// {cekaj X uS, flip fazu Y}
// koeficijenti/podaci generisani sa generated_coefficients.py skriptom
int PODACI [119][2] = {{32, 3}, {239, 1}, {176, 2}, {112, 2}, {137, 1}, {298, 3}, {11, 3}, {348, 1}, {40, 2}, {229, 2}, 
                    {6, 1}, {371, 3}, {2, 3}, {327, 2}, {94, 1}, {147, 1}, {132, 2}, {278, 3}, {43, 3}, {234, 2}, {216, 1}, 
                    {54, 1}, {259, 2}, {154, 3}, {129, 3}, {116, 2}, {313, 1}, {6, 1}, {363, 2}, {17, 3}, {234, 2}, {17, 3}, 
                    {363, 1}, {6, 1}, {313, 3}, {116, 2}, {129, 2}, {154, 3}, {259, 1}, {54, 1}, {216, 3}, {234, 2}, {43, 2}, 
                    {278, 3}, {132, 1}, {147, 1}, {94, 3}, {327, 2}, {2, 2}, {371, 1}, {6, 3}, {229, 3}, {40, 1}, {348, 2}, 
                    {11, 2}, {298, 1}, {137, 3}, {112, 3}, {176, 1}, {239, 2}, {67, 2}, {197, 1}, {251, 3}, {33, 3}, {297, 1}, 
                    {109, 2}, {166, 2}, {73, 1}, {339, 3}, {0, 3}, {362, 2}, {28, 1}, {207, 1}, {63, 2}, {332, 3}, {17, 3}, 
                    {283, 2}, {158, 1}, {96, 1}, {197, 2}, {218, 3}, {81, 3}, {178, 2}, {267, 1}, {25, 1}, {315, 2}, {86, 3}, 
                    {186, 3}, {51, 2}, {700, 3}, {51, 2}, {186, 2}, {86, 3}, {315, 1}, {25, 1}, {267, 3}, {178, 2}, {81, 2}, 
                    {218, 3}, {197, 1}, {96, 1}, {158, 3}, {283, 2}, {17, 2}, {332, 3}, {63, 1}, {207, 1}, {28, 3}, {362, 2}, 
                    {0, 2}, {339, 1}, {73, 3}, {166, 3}, {109, 1}, {297, 2}, {33, 2}, {251, 1}, {197, 3}, {35, 0}}; 
                    //0 ne dirati nista samo cekati 35 uS jer pocinje novi ciklus

unsigned int k = -1;
int CLAN [2];
int NEGIRANI [] = {4, 5, 6};
int neg;

void setup(){
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

void loop(){
  CLAN[0] = PODACI[++k % MAX_PODATAKA][0];
  CLAN[1] = PODACI[k % MAX_PODATAKA][1];
  delayMicroseconds(CLAN[0]);
  if(CLAN[1]!=0){
    digitalWrite(CLAN[1], !digitalRead(CLAN[1]));
    neg = NEGIRANI[CLAN[1]-1];
    // moglo se i fizicki na shemi direktno negirati ali bi nam trebala dodatna 3 gate upravljacka tranzistora
    digitalWrite(neg, !digitalRead(neg));
  }
}
