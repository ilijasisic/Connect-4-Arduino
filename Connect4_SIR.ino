#include <Adafruit_NeoPixel.h>
#define PIN D1
#define BRIGHTNESS 5
#define NUM_PIXELS 42
#define DELAY_ 200
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

int tkoJeNaRedu = 1;
const int rows = 6;
const int columns = 7;
int S[6][7] = {

  {0, 1, 2, 3, 4, 5, 6},
  {13, 12, 11, 10, 9, 8, 7},
  {14, 15, 16, 17, 18, 19, 20},
  {27, 26, 25, 24, 23, 22, 21},
  {28, 29, 30, 31, 32, 33, 34},
  {41, 40, 39, 38, 37, 36, 35},

};
//int S[6][7] = {
//
//  {41, 40, 39, 38, 37, 36, 35},
//  {28, 29, 30, 31, 32, 33, 34},
//  {27, 26, 25, 24, 23, 22, 21},
//  {14, 15, 16, 17, 18, 19, 20},
//  {13, 12, 11, 10, 9, 8, 7},
//  {0, 1, 2, 3, 4, 5, 6},
//
//};
int K[6][7] = {
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0},
};
int x1 = -1, x2 = -1, x3 = -1, x4 = -1, x5 = -1, x6 = -1, x7 = -1;
int *X[7] = {&x1, &x2, &x3, &x4, &x5, &x6, &x7};
int AI_piece = 1;
int player_piece = 2;
bool flag_e = false, flag_h = false;
int y = 0, br_poteza = 0;
int St1 = digitalRead(D3);
int St2 = digitalRead(D2);
int St3 = digitalRead(D4);
int St4 = digitalRead(D5);
int St5 = digitalRead(D6);
int St6 = digitalRead(D7);
int St7 = digitalRead(D8);

//**************************************************************************
void setup() {
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);

  pinMode(D0, INPUT);

  //   pinMode(buttonPin, INPUT_PULLUP);
  //   pinMode(buttonPin, INPUT_PULLUP);


  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();
}
//**************************************************************************
void loop() {
  St1 = digitalRead(D3);
  St2 = digitalRead(D2);
  St3 = digitalRead(D4);
  St4 = digitalRead(D5);
  St5 = digitalRead(D6);
  St6 = digitalRead(D7);
  St7 = digitalRead(D8);
  //  Serial.println(analogRead(A0));

  //     int COMP = digitalRead(D0);
  //
  //
  //  //Serial.println(St8);


  if ((analogRead(A0) > 800) && (analogRead(A0) < 850)) {
    changePlayer();
  }
  if ((analogRead(A0) > 950) && (analogRead(A0) < 1000)) {
    if (flag_h) {
      flag_h = !flag_h;
    }
    flag_e = !flag_e;
  }
  if ((analogRead(A0) > 850) && (analogRead(A0) < 920)) {
    if (flag_e) {
      flag_e = !flag_e;
    }
    flag_h = !flag_h;
  }
  if ((flag_e) && (tkoJeNaRedu == AI_piece) && (!provjeriPobjedu(AI_piece)) && (!provjeriPobjedu(player_piece))) {
    AI_Play(AI_Easy());
  }
  if ((flag_h) && (tkoJeNaRedu == AI_piece) && (!provjeriPobjedu(AI_piece)) && (!provjeriPobjedu(player_piece))) {
    AI_Play(AI_Hard());
  }
  if (St1 == LOW) {

    x1 = x1 + 1;
    y = 0;
    if (x1 < 6) {
      odigrajPotez(x1, y);
    }
  }
  else if (St2 == LOW) {
    x2 = x2 + 1;
    y = 1;
    if (x2 < 6) {
      odigrajPotez(x2, y);
    }
  }
  else if (St3 == LOW) {
    x3 = x3 + 1;
    y = 2;
    if (x3 < 6) {
      odigrajPotez(x3, y);
    }
  }
  else if (St4 == LOW) {
    x4 = x4 + 1;
    y = 3;
    if (x4 < 6) {
      odigrajPotez(x4, y);
    }
  }
  else if (St5 == LOW) {
    x5 = x5 + 1;
    y = 4;
    if (x5 < 6) {
      odigrajPotez(x5, y);
    }
  }
  else if (St6 == LOW) {
    x6 = x6 + 1;
    y = 5;
    if (x6 < 6) {
      odigrajPotez(x6, y);
    }
  }
  else if (((analogRead(A0) > 700) && (analogRead(A0) < 800))) {
    x7 = x7 + 1;
    y = 6;
    if (x7 < 6) {
      odigrajPotez(x7, y);
    }
  }

  //  for(int i=0; i<NUM_PIXELS; i++) {
  //    strip.setPixelColor(i, 0, 0, 0, 0);
  //  }
  //  strip.show();
  //  for(int i=0; i<NUM_PIXELS; i++) {
  //    strip.setPixelColor(i, 155, 0, 0);
  //    strip.show();
  //    delay(DELAY_);
  //  }

}
//**************************************************************************
void printArray( const int a[][ columns ] ) {
  // loop through array's rows
  for ( int i = 0; i < rows; ++i ) {
    // loop through columns of current row
    for ( int j = 0; j < columns; ++j )
      Serial.print (a[ i ][ j ] );
    Serial.print (" ");
    Serial.println (" " ) ; // start new line of output
  }
}
//**************************************************************************
void odigrajPotez(int x, int y) {
  if (tkoJeNaRedu == 1) {
    K[x][y] = 1;
    br_poteza++;
    for (int i = 5; i > x; i--) {
      strip.setPixelColor(S[i][y], 155, 0, 0);
      strip.show();
      delay(20);
      strip.setPixelColor(S[i][y], 0, 0, 0);
      strip.show();
    }
    strip.setPixelColor(S[x][y], 155, 0, 0);
    strip.show();
    delay(DELAY_);

    tkoJeNaRedu = 2;
    //    for (int i = 0; i < 6; i++) {
    //      for (int j = 0; j < 7; j++) {
    //
    //        Serial.print(K[i][j]);
    //        Serial.print(" ");
    //      }
    //      Serial.println();
    //    }
    if (provjeriPobjedu(1)) {
      delay(1000);
      greenScreen();
    }
    else if (br_poteza >= 42) {
      drawScreen();
    }
  }
  else {
    K[x][y] = 2;
    br_poteza++;
    for (int i = 5; i > x; i--) {
      strip.setPixelColor(S[i][y], 0, 155, 0);
      strip.show();
      delay(20);
      strip.setPixelColor(S[i][y], 0, 0, 0);
      strip.show();
    }
    strip.setPixelColor(S[x][y], 0, 155, 0);
    strip.show();
    delay(DELAY_);
    tkoJeNaRedu = 1;
    if (provjeriPobjedu(2)) {
      delay(1000);
      redScreen();
    }
    else if (br_poteza >= 42) {
      drawScreen();
    }
  }

  //  Serial.println(score_ploca(1));
  //  Serial.println("Odigraj potez Xs");
  //  for (int i = 0; i < 7; i++) {
  //
  //    Serial.print(i);
  //    Serial.print("=");
  //    Serial.print(*X[i]);
  //    Serial.print(" ");
  //  }
}

//**************************************************************************
bool provjeriPobjedu(int player) {

  // horizontalCheck
  for (int j = 0; j < 7 - 3 ; j++ ) {
    for (int i = 0; i < 6; i++) {
      if (K[i][j] == player && K[i][j + 1] == player && K[i][j + 2] == player && K[i][j + 3] == player) {
        return true;
      }
    }
  }
  // verticalCheck
  for (int i = 0; i < 6 - 3 ; i++ ) {
    for (int j = 0; j < 7; j++) {
      if (K[i][j] == player && K[i + 1][j] == player && K[i + 2][j] == player && K[i + 3][j] == player) {
        return true;
      }
    }
  }
  // ascendingDiagonalCheck
  for (int i = 3; i < 6; i++) {
    for (int j = 0; j < 7 - 3; j++) {
      if (K[i][j] == player && K[i - 1][j + 1] == player && K[i - 2][j + 2] == player && K[i - 3][j + 3] == player)
        return true;
    }
  }
  // descendingDiagonalCheck
  for (int i = 3; i < 6; i++) {
    for (int j = 3; j < 7; j++) {
      if (K[i][j] == player && K[i - 1][j - 1] == player && K[i - 2][j - 2] == player && K[i - 3][j - 3] == player)
        return true;
    }
  }
  return false;
}
//**************************************************************************
void greenScreen() {

  for (int i = 0; i < NUM_PIXELS; i++) {
    strip.setPixelColor(i, 155, 0, 0);
    strip.show();
    delay(100);
  }
  delay(500);
  strip.setPixelColor(0, 0, 0, 155);
  strip.show();
  while (1) {
    St1 = digitalRead(D3);
    if (St1 == LOW) {
      resetGame();
      changePlayer();
      delay(500);
      return;
    }
    yield();
  }
}
//**************************************************************************
void redScreen() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    strip.setPixelColor(i, 0, 155, 0);
    strip.show();
    delay(100);
  }
  delay(500);
  strip.setPixelColor(0, 0, 0, 155);
  strip.show();
  while (1) {
    St1 = digitalRead(D3);
    if (St1 == LOW) {
      resetGame();
      changePlayer();
      delay(500);
      return;
    }
    yield();
  }
}
//**************************************************************************
void drawScreen() {
  for (int i = 0; i < NUM_PIXELS; i++) {
    strip.setPixelColor(i, 0, 155, 155);
    strip.show();
    delay(100);
  }
  delay(500);
  strip.setPixelColor(0, 0, 0, 155);
  strip.show();
  while (1) {
    St1 = digitalRead(D3);
    if (St1 == LOW) {
      resetGame();
      changePlayer();
      delay(500);
      return;
    }
    yield();
  }
  //if(button) then reset

}

void resetGame() {
  br_poteza = 0;
  for (int i = 0; i < NUM_PIXELS; i++)
  {
    strip.setPixelColor(i, 0, 0, 0);
    strip.show();
  }
  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      K[i][j] = 0;
      *X[i] = -1;
    }
  }

}
//**************************************************************************
void changePlayer() {
  int temp;
  temp = AI_piece;
  AI_piece = player_piece;
  player_piece = temp;
}
//**************************************************************************
int AI_Easy () {
  int stupac;

  stupac = AI_1();
  if (stupac != -1) {
    return stupac;
  }
  stupac = AI_3();
  if (stupac != -1) {
    return stupac;
  }
  stupac = AI_2();
  if (stupac != -1) {
    return stupac;
  }
  stupac = AI_Random();
  return stupac;

}
//**************************************************************************
int AI_Hard() {
  int x = najboljiPotezAlphaBeta(7); //15 sekundi po potezu(depth 8), 5sec depth 7
  //int x = najboljiPotez(5);
  return x;
}




//**************************************************************************
void AI_Play(int a) {
  if (a == 0) {
    x1 = x1 + 1;
    y = 0;
    if (x1 < 6) {
      odigrajPotez(x1, y);
    }
  }
  else if (a == 1) {
    x2 = x2 + 1;

    y = 1;
    if (x2 < 6) {
      odigrajPotez(x2, y);
    }
  }
  else if (a == 2) {
    x3 = x3 + 1;

    y = 2;
    if (x3 < 6) {
      odigrajPotez(x3, y);
    }
  }
  else if (a == 3) {
    x4 = x4 + 1;

    y = 3;
    if (x4 < 6) {
      odigrajPotez(x4, y);
    }
  }
  else if (a == 4) {
    x5 = x5 + 1;

    y = 4;
    if (x5 < 6) {
      odigrajPotez(x5, y);
    }
  }
  else if (a == 5) {
    x6 = x6 + 1;

    y = 5;
    if (x6 < 6) {
      odigrajPotez(x6, y);
    }
  }
  else if (a == 6) {
    x7 = x7 + 1;

    y = 6;
    if (x7 < 6) {
      odigrajPotez(x7, y);
    }
  }
}


//**************************************************************************
int AI_Random() {

  int randomNum = random(0, 7);
  while (K[5][randomNum] > 0) {
    randomNum = random(0, 7);
  }
  return randomNum;

}
//**************************************************************************
int AI_1()
{
  int pot = -1;
  for (int i = 0; i < 7; i++) {
    if ((*X[i] + 1) < 6) {
      K[*X[i] + 1][i] = AI_piece;
      if (provjeriPobjedu(AI_piece)) {
        K[*X[i] + 1][i] = 0;
        return i;
      }
      if (provjeriPobjedu(AI_piece)) {
        K[*X[i] + 1][i] = 0;
        pot = i;
      }
      K[*X[i] + 1][i] = player_piece;
      if (provjeriPobjedu(AI_piece)) {
        K[*X[i] + 1][i] = 0;
        return i;
      }
      if (provjeriPobjedu(player_piece)) {
        K[*X[i] + 1][i] = 0;
        pot = i;
      }

      K[*X[i] + 1][i] = 0;
    }

  }
  return pot;
}
//**************************************************************************
int AI_2() {
  int i = 0;
  while (i < 50) {
    int stupac = AI_Random();

    if ((*X[stupac] + 2) < 6) {


      if (tkoJeNaRedu == AI_piece) {
        K[*X[stupac] + 2][stupac] = player_piece;
        if (!provjeriPobjedu(player_piece)) {
          K[*X[stupac] + 2][stupac] = 0;
          return stupac;
        }
        else {
          K[*X[stupac] + 2][stupac] = 0;
          i++;
        }
      }
      if (tkoJeNaRedu == player_piece) {
        K[*X[stupac] + 2][stupac] = AI_piece;
        if (!provjeriPobjedu(AI_piece)) {
          K[*X[stupac] + 2][stupac] = 0;
          return stupac;
        }
        else {
          K[*X[stupac] + 2][stupac] = 0;
          i++;
        }
      }
    }


  }
  return -1;
}
//**************************************************************************
int AI_3() {
  for (int i = 0; i < 6; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (tkoJeNaRedu == player_piece) {
        // kombinacije 1-3
        if (K[i] [j] == 0 && K[i] [j + 1] == 0 && K[i][ j + 2] == AI_piece && K[i] [j + 3] == AI_piece && K[i][ j + 4] == 0)
        {
          if ((i == 0) || (i > 0 && K[i - 1][ j] != 0 && K[i - 1][ j + 1] != 0 && K[i - 1][ j + 4] != 0))
            return j + 1;
        }
        // kombinacije 4-6
        if (K[i][ j] == 0 && K[i][ j + 1] == AI_piece && K[i][ j + 2] == 0 && K[i ][ j + 3] == AI_piece && K[i ][ j + 4] == 0)
        {
          if ((i == 0) || (i > 0 && K[i - 1][ j] != 0 && K[i - 1][ j + 2] != 0 && K[i - 1][ j + 4] != 0))
            return j + 2;
        }
        // kombinacije 7-9
        if (K[i][ j] == 0 && K[i ][ j + 1] == AI_piece && K[i][j + 2] == AI_piece && K[i][ j + 3] == 0 && K[i][ j + 4] == 0)
        {
          if ((i == 0) || (i > 0 && K[i - 1][ j] != 0 && K[i - 1][ j + 3] != 0 && K[i - 1][ j + 4] != 0))
            return j + 3;
        }
      }
      else if (tkoJeNaRedu == AI_piece) {
        // kombinacije 1-3
        if (K[i] [j] == 0 && K[i] [j + 1] == 0 && K[i][ j + 2] == player_piece && K[i] [j + 3] == player_piece && K[i][ j + 4] == 0)
        {
          if ((i == 0) || (i > 0 && K[i - 1][ j] != 0 && K[i - 1][ j + 1] != 0 && K[i - 1][ j + 4] != 0))
            return j + 1;
        }
        // kombinacije 4-6
        if (K[i][ j] == 0 && K[i][ j + 1] == player_piece && K[i][ j + 2] == 0 && K[i ][ j + 3] == player_piece && K[i ][ j + 4] == 0)
        {
          if ((i == 0) || (i > 0 && K[i - 1][ j] != 0 && K[i - 1][ j + 2] != 0 && K[i - 1][ j + 4] != 0))
            return j + 2;
        }
        // kombinacije 7-9
        if (K[i][ j] == 0 && K[i ][ j + 1] == player_piece && K[i][j + 2] == player_piece && K[i][ j + 3] == 0 && K[i][ j + 4] == 0)
        {
          if ((i == 0) || (i > 0 && K[i - 1][ j] != 0 && K[i - 1][ j + 3] != 0 && K[i - 1][ j + 4] != 0))
            return j + 3;
        }
      }
    }
  }
  return -1;
}
//**************************************************************************
int evaluate() {

  if (provjeriPobjedu(AI_piece)) {
    return 10000;
  }
  else if (provjeriPobjedu(player_piece))
  {
    return -10000;
  }
  else if (!imaLiPoteza()) {
    return 0;
  }
  else return -1;
}
//**************************************************************************
bool imaLiPoteza() {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      if (K[i][j] == 0) {
        return true;
      }
    }
  }
  return false;
}


//**************************************************************************
int miniMax(int depth, int maximisingPlayer) {
  yield();
  int krajnjiList = evaluate();
  //  Serial.println(krajnjiList);
  //  yield();
  if (krajnjiList != -1) {
    return krajnjiList;
  }
  else if (depth == 0) {
    return score_ploca(AI_piece);
  }





  if (maximisingPlayer == player_piece) {                             //***MAX***

    int bestScore = -1000000;
    for (int i = 0; i < 7; i++) {
      if (*X[i] < 5) {
        if ( K[*X[i] + 1][i] == 0) {


          K[*X[i] + 1][i] = player_piece;
          *X[i] = *X[i] + 1;
          br_poteza++;
          int score = miniMax(depth - 1, AI_piece);
          bestScore = max(bestScore, score);
          //Serial.print("MAX");Serial.println(bestScore);
          br_poteza--;
          *X[i] = *X[i] - 1;
          K[*X[i] + 1][i] = 0;

        }
      }
    }
    return bestScore;

  }
  else if (maximisingPlayer == AI_piece) {                                          //***MIN***
    int bestScore = 1000000;
    for (int i = 0; i < 7; i++) {
      if (*X[i] < 5) {
        if ( K[*X[i] + 1 ][i] == 0) {


          K[*X[i] + 1][i] = AI_piece;
          *X[i] = *X[i] + 1;
          br_poteza++;
          int score = miniMax(depth - 1, player_piece);
          bestScore = min(bestScore, score);
          //Serial.print("MIN");Serial.println(bestScore);
          br_poteza--;
          *X[i] = *X[i] - 1;
          K[*X[i] + 1 ][i] = 0;

        }
      }
    }
    return bestScore;
  }
}


//**************************************************************************

int najboljiPotez(int depth) {
  int stupac = 0;
  int bestVal = -10000001;
  for (int i = 0; i < 7; i++) {
    if (*X[i] < 5) {
      if ( K[*X[i] + 1][i] == 0) {

        K[*X[i] + 1][i] = AI_piece;
        *X[i] = *X[i] + 1;
        int moveVal = miniMax(depth, AI_piece);  //SCORE - MOVEVAL
        // int moveVal = alphaBeta(depth, -10000000, 10000000, AI_piece);

        *X[i] = *X[i] - 1;
        K[*X[i] + 1][i] = 0;

        if (moveVal > bestVal) {
          stupac = i;
          bestVal = moveVal;
        }
      }
    }
  }
  return stupac;
}
//**************************************************************************
int score_ploca(int player) {
  int br = 0;
  int  score = 0;
  //*************************************Center
  for (int i = 0; i < 6; i++) {
    int    j = 3;

    if (K[i][j] == player) {
      br++;
    }
  }
  score = score + (br * 3);


  for (int i = 0; i < 6; i++) {
    for (int j = 1; j < 7 - 4; j++) {
      if (K[i][j - 1] == 0 && K[i][j] == player && K[i][j + 1] == player && K[i][j + 2] == player && K[i][j + 3] == 0) {
        score = score + 20;
      }
    }
  }

  //**************************************Horizontal
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7 - 3; j++) {
      if (K[i][j] == player && K[i][j + 1] == player && K[i][j + 2] == player && K[i][j + 3] == player) {
        score = score + 100;
      }
      else if (K[i][j] == player && K[i][j + 1] == player && K[i][j + 2] == player && K[i][j + 3] == 0
               || K[i][j] == player && K[i][j + 1] == player && K[i][j + 2] == 0 && K[i][j + 3] == player
               || K[i][j] == player && K[i][j + 1] == 0 && K[i][j + 2] == player && K[i][j + 3] == player
               || K[i][j] == 0 && K[i][j + 1] == player && K[i][j + 2] == player && K[i][j + 3] == player) {
        score = score + 5;
      }
      else if (K[i][j] == player && K[i][j + 1] == player && K[i][j + 2] == 0 && K[i][j + 3] == 0
               || K[i][j] == player && K[i][j + 1] == 0 && K[i][j + 2] == 0 && K[i][j + 3] == player
               || K[i][j] == 0 && K[i][j + 1] == player && K[i][j + 2] == player && K[i][j + 3] == 0
                       || K[i][j] == 0 && K[i][j + 1] == 0 && K[i][j + 2] == player && K[i][j + 3] == player

                       || K[i][j] == player && K[i][j + 1] == 0 && K[i][j + 2] == player && K[i][j + 3] == 0
                       || K[i][j] == 0 && K[i][j + 1] == player && K[i][j + 2] == 0 && K[i][j + 3] == player)
      {
        score = score + 2;
      }
      if (K[i][j] == player_piece && K[i][j + 1] == player_piece && K[i][j + 2] == player_piece && K[i][j + 3] == 0
          || K[i][j] == player_piece && K[i][j + 1] == player_piece && K[i][j + 2] == 0 && K[i][j + 3] == player_piece
          || K[i][j] == player_piece && K[i][j + 1] == 0 && K[i][j + 2] == player_piece && K[i][j + 3] == player_piece
          || K[i][j] == 0 && K[i][j + 1] == player_piece && K[i][j + 2] == player_piece && K[i][j + 3] == player_piece) {
        score = score - 80;
      }
    }
  }
  //*************************************Vertical
  for (int i = 0; i < 6 - 3 ; i++ ) {
    for (int j = 0; j < 7; j++) {
      if (K[i][j] == player && K[i + 1][j] == player && K[i + 2][j] == player && K[i + 3][j] == player) {
        score = score + 100;
      }
      else if (K[i][j] == player && K[i + 1][j] == player && K[i + 2][j] == player && K[i + 3][j] == 0
               || K[i][j] == player && K[i + 1][j] == player && K[i + 2][j] == 0 && K[i + 3][j] == player
               || K[i][j] == player && K[i + 1][j] == 0 && K[i + 2][j] == player && K[i + 3][j] == player
               || K[i][j] == 0 && K[i + 1][j] == player && K[i + 2][j] == player && K[i + 3][j] == player)
      {
        score = score + 5;
      }
      else if (K[i][j] == player && K[i + 1][j] == player && K[i + 2][j] == 0 && K[i + 3][j] == 0
               || K[i][j] == 0 && K[i + 1][j] == player && K[i + 2][j] == player && K[i + 3][j] == 0
               || K[i][j] == 0 && K[i + 1][j] == 0 && K[i + 2][j] == player && K[i + 3][j] == player
                       || K[i][j] == 0 && K[i + 1][j] == player && K[i + 2][j] == 0 && K[i + 3][j] == player
                       || K[i][j] == player && K[i + 1][j] == 0 && K[i + 2][j] == player && K[i + 3][j] == 0
                       || K[i][j] == player && K[i + 1][j] == 0 && K[i + 2][j] == 0 && K[i + 3][j] == player)

      {
        score = score + 2;
      }
      if (K[i][j] == player_piece && K[i + 1][j] == player_piece && K[i + 2][j] == player_piece && K[i + 3][j] == 0
          || K[i][j] == player_piece && K[i + 1][j] == player_piece && K[i + 2][j] == 0 && K[i + 3][j] == player_piece
          || K[i][j] == player_piece && K[i + 1][j] == 0 && K[i + 2][j] == player_piece && K[i + 3][j] == player_piece
          || K[i][j] == 0 && K[i + 1][j] == player_piece && K[i + 2][j] == player_piece && K[i + 3][j] == player_piece) {
        score = score - 80;

      }
    }
  }
  //***************************************** ascendingDiagonal
  for (int i = 3; i < 6; i++) {
    for (int j = 0; j < 7 - 3; j++) {
      if (K[i][j] == player && K[i - 1][j + 1] == player && K[i - 2][j + 2] == player && K[i - 3][j + 3] == player) {
        score = score + 100;
      }
      else if (K[i][j] == player && K[i - 1][j + 1] == player && K[i - 2][j + 2] == player && K[i - 3][j + 3] == 0
               || K[i][j] == player && K[i - 1][j + 1] == player && K[i - 2][j + 2] == 0 && K[i - 3][j + 3] == player
               || K[i][j] == player && K[i - 1][j + 1] == 0 && K[i - 2][j + 2] == player && K[i - 3][j + 3] == player
               || K[i][j] == 0 && K[i - 1][j + 1] == player && K[i - 2][j + 2] == player && K[i - 3][j + 3] == player) {
        score = score + 5;
      }

      else if (K[i][j] == player && K[i - 1][j + 1] == player && K[i - 2][j + 2] == 0 && K[i - 3][j + 3] == 0
               || K[i][j] == 0 && K[i - 1][j + 1] == 0 && K[i - 2][j + 2] == player && K[i - 3][j + 3] == player
               || K[i][j] == 0 && K[i - 1][j + 1] == player && K[i - 2][j + 2] == player && K[i - 3][j + 3] == 0
                     || K[i][j] == player && K[i - 1][j + 1] == 0 && K[i - 2][j + 2] == 0 && K[i - 3][j + 3] == player
                     || K[i][j] == 0 && K[i - 1][j + 1] == player && K[i - 2][j + 2] == 0 && K[i - 3][j + 3] == player
                     || K[i][j] == player && K[i - 1][j + 1] == 0 && K[i - 2][j + 2] == player && K[i - 3][j + 3] == 0)
      {
        score = score + 2;
      }
      if (K[i][j] == player_piece && K[i - 1][j + 1] == player_piece && K[i - 2][j + 2] == player_piece && K[i - 3][j + 3] == 0
          || K[i][j] == player_piece && K[i - 1][j + 1] == player_piece && K[i - 2][j + 2] == 0 && K[i - 3][j + 3] == player_piece
          || K[i][j] == player_piece && K[i - 1][j + 1] == 0 && K[i - 2][j + 2] == player_piece && K[i - 3][j + 3] == player_piece
          || K[i][j] == 0 && K[i - 1][j + 1] == player_piece && K[i - 2][j + 2] == player_piece && K[i - 3][j + 3] == player_piece) {
        score = score - 80;
      }
    }
  }
  //*************************************** descendingDiagonal
  for (int i = 3; i < 6; i++) {
    for (int j = 3; j < 7; j++) {
      if (K[i][j] == player && K[i - 1][j - 1] == player && K[i - 2][j - 2] == player && K[i - 3][j - 3] == player) {
        score = score + 100;
      }
      else if (K[i][j] == player && K[i - 1][j - 1] == player && K[i - 2][j - 2] == player && K[i - 3][j - 3] == 0
               || K[i][j] == player && K[i - 1][j - 1] == player && K[i - 2][j - 2] == 0 && K[i - 3][j - 3] == player
               || K[i][j] == player && K[i - 1][j - 1] == 0 && K[i - 2][j - 2] == player && K[i - 3][j - 3] == player
               || K[i][j] == 0 && K[i - 1][j - 1] == player && K[i - 2][j - 2] == player && K[i - 3][j - 3] == player) {
        score = score + 5;
      }
      else if (K[i][j] == player && K[i - 1][j - 1] == player && K[i - 2][j - 2] == 0 && K[i - 3][j - 3] == 0
               || K[i][j] == 0 && K[i - 1][j - 1] == 0 && K[i - 2][j - 2] == player && K[i - 3][j - 3] == player
               || K[i][j] == 0 && K[i - 1][j - 1] == player && K[i - 2][j - 2] == player && K[i - 3][j - 3] == 0
                       || K[i][j] == player && K[i - 1][j - 1] == 0 && K[i - 2][j - 2] == 0 && K[i - 3][j - 3] == player
                       || K[i][j] == 0 && K[i - 1][j - 1] == player && K[i - 2][j - 2] == 0 && K[i - 3][j - 3] == player
                       || K[i][j] == player && K[i - 1][j - 1] == 0 && K[i - 2][j - 2] == player && K[i - 3][j - 3] == 0)
      {
        score = score + 2;
      }
      if (K[i][j] == player_piece && K[i - 1][j - 1] == player_piece && K[i - 2][j - 2] == player_piece && K[i - 3][j - 3] == 0
          || K[i][j] == player_piece && K[i - 1][j - 1] == player_piece && K[i - 2][j - 2] == 0 && K[i - 3][j - 3] == player_piece
          || K[i][j] == player_piece && K[i - 1][j - 1] == 0 && K[i - 2][j - 2] == player_piece && K[i - 3][j - 3] == player_piece
          || K[i][j] == 0 && K[i - 1][j - 1] == player_piece && K[i - 2][j - 2] == player_piece && K[i - 3][j - 3] == player_piece) {
        score = score - 80;
      }
    }
  }



  return score;
}

//**************************************************************************
//ALPHA-BETA

int alphaBeta(int depth, int alpha, int beta, int maximisingPlayer) {
  yield();
  int krajnjiList = evaluate();
  //  Serial.println(krajnjiList);
  //  yield();
  if (krajnjiList != -1) {
    return krajnjiList;
  }
  else if (depth == 0) {
    return score_ploca(AI_piece);
  }



  if (maximisingPlayer == player_piece) {                             //***MAX***

    int bestScore = -1000000;
    for (int i = 0; i < 7; i++) {
      if (*X[i] < 5) {
        if ( K[*X[i] + 1][i] == 0) {


          K[*X[i] + 1][i] = player_piece;
          *X[i] = *X[i] + 1;
          br_poteza++;
          int score = alphaBeta(depth - 1, alpha, beta, AI_piece);
          bestScore = max(bestScore, score);
          alpha = max(alpha, bestScore);
          if (alpha >= beta) {
            br_poteza--;
            *X[i] = *X[i] - 1;
            K[*X[i] + 1][i] = 0;
            break;
          }
          //Serial.print("MAX");Serial.println(bestScore);
          br_poteza--;
          *X[i] = *X[i] - 1;
          K[*X[i] + 1][i] = 0;

        }
      }
    }
    return bestScore;

  }
  else if (maximisingPlayer == AI_piece) {                                          //***MIN***
    int bestScore = 1000000;
    for (int i = 0; i < 7; i++) {
      if (*X[i] < 5) {
        if ( K[*X[i] + 1 ][i] == 0) {


          K[*X[i] + 1][i] = AI_piece;
          *X[i] = *X[i] + 1;
          br_poteza++;
          int score = alphaBeta(depth - 1, alpha, beta, player_piece);
          bestScore = min(bestScore, score);
          beta = min(beta, bestScore);
          if (alpha >= beta) {
            br_poteza--;
            *X[i] = *X[i] - 1;
            K[*X[i] + 1 ][i] = 0;
            break;
          }
          //Serial.print("MIN");Serial.println(bestScore);
          br_poteza--;
          *X[i] = *X[i] - 1;
          K[*X[i] + 1 ][i] = 0;

        }
      }
    }
    return bestScore;
  }
}
//**************************************************************************

int najboljiPotezAlphaBeta(int depth) {
  int stupac = 0;
  int bestVal = -10000001;
  for (int i = 0; i < 7; i++) {
    if (*X[i] < 5) {
      if ( K[*X[i] + 1][i] == 0) {

        K[*X[i] + 1][i] = AI_piece;
        *X[i] = *X[i] + 1;
        //int moveVal = miniMax(depth, AI_piece);  //SCORE - MOVEVAL
        int moveVal = alphaBeta(depth, -10000000, 10000000, AI_piece);

        *X[i] = *X[i] - 1;
        K[*X[i] + 1][i] = 0;

        if (moveVal > bestVal) {
          stupac = i;
          bestVal = moveVal;
        }
      }
    }
  }
  return stupac;
}
