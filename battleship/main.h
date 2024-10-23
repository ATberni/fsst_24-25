#define CLOSE 0
#define OPEN 1
#define OFF 0
#define ON 1

enum SPIELFELD {
    WIDTH = 100,
    HEIGHT = 100,
    ROWS = WIDTH / 10,
    COLS = HEIGHT / 10,
};

enum BORDER {
    A = 65,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
};

enum ITEMS {
    WATER = 0,
    BOAT,
    BORDER,
};

enum BOOTE {
    EINS = 1,
    ZWEI,
    DREI,
    VIER,
};

enum KEYS {
    SPACE = 32,
    ESCAPE = 27,
};

bool gameover = false;

//What4: Array befüllen
//IN: 2d array
void fillArray(int **array);

//What4: Erstellen / Löschen von Dyn. Speicher
//IN: 1: OPEN oder CLOSE
//IN: 2: 2d array
void speicher(int c, int **array);

//What4: Initialisiert das Spielfeld
//IN: 1: 2d array
//IN: 2: Rows vom Spielfeld
//IN: 3: Cols vom Spielfeld
void spielfeldInit(int **array, int rows, int cols);

//What4: Ausgabe vom Spielfeld
//IN: 1: 2d array
//IN: 2: Rows vom Spielfeld
//IN: 3: Cols vom Spielfeld
void spielfeldAusgabe(int **array, int rows, int cols);

//What4: Platziert das Boot
//IN: 1: 2d array
//IN: 2: Rows vom Spielfeld
//IN: 3: Cols vom Spielfeld
//IN: 4: Type des Bootes (1, 2, 3 oder 4er schiff)
void placeBoat(int **array, int rows, int cols);

//What4: Platziert das Boot
//IN: 1: 2d array
//IN: 2: Rows vom Spielfeld
//IN: 3: Cols vom Spielfeld
//IN: 4: Type des Bootes (1, 2, 3 oder 4er schiff)
void placeBoatManually(int **array, int rows, int cols, int type);
