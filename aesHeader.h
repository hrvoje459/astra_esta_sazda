
// SUBSTITUIRAJ
void byteSub(unsigned char** cypherText);
void inverseByteSub(unsigned char** cypherText);

unsigned char izSboxa(unsigned char ulaz);
unsigned char izSboxaInverz(unsigned char ulaz);

// POSMAKNI REDOVE
void posmakni(unsigned char* cypherText);
void rowShift(unsigned char** cypherText);
void inverseRowShift(unsigned char** unCypherText);

// IZMJESAJ STUPCE
void columnMix(unsigned char** cypherText);
void inverseColumnMix(unsigned char** unCypherText);

// DODAJ KLJUCEVE
void RoundKeyAdd(unsigned char** cypherText, unsigned char** prosireniKljuc, int i);
void inverseRoundKeyAdd(unsigned char** cypherText, unsigned char** prosireniKljuc, int i);

// KEY SCHEDULE
void keySchedule(unsigned char** kljuc, unsigned char** prosireniKljuc);

// GPolje
unsigned short int gPoljePomnozi(unsigned short a, unsigned short b);
unsigned short int podijeliPolinomski(unsigned short int djeljenik, unsigned short int djelitelj);
unsigned short int pomnoziPolinomski(unsigned short int a, unsigned short int b);
