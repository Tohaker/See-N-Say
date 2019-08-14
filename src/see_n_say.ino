#include <SD.h>
#include <TMRpcm.h>

#define SD_ChipSelectPin 10

TMRpcm tmrpcm;
int cb0, cb1, cb2, cb3, cb4;  // Column Buttons
int playbackBtn, randomiseBtn;      // Extra Buttons

int columnState[]      = {0, 0, 0, 0, 0};
int maxColumnState[]   = {7, 6, 6, 7, 6};
String column0Sounds[] = {"1/turkey.wav", 
                          "1/mom.wav", 
                          "1/dad.wav", 
                          "1/dog.wav", 
                          "1/teacher.wav", 
                          "1/elephant.wav", 
                          "1/cat.wav"};
String column1Sounds[] = {"2/sat_on.wav",
                          "2/ate.wav",
                          "2/danced.wav",
                          "2/saw.wav",
                          "2/doesnt.wav",
                          "2/kissed"}; 
String column2Sounds[] = {"3/funny.wav",
                          "3/scary.wav",
                          "3/goofy.wav",
                          "3/slimy.wav",
                          "3/barking.wav",
                          "3/fat.wav"};
String column3Sounds[] = {"4/goat.wav",
                          "4/monkey.wav",
                          "4/fish.wav",
                          "4/cow.wav",
                          "4/frog.wav",
                          "4/bug.wav",
                          "4/worm.wav"};
String column4Sounds[] = {"5/moon.wav",
                          "5/chair.wav",
                          "5/spag.wav",
                          "5/soup.wav",
                          "5/grass.wav",
                          "5/shoes.wav"};

void setup() {
  pinMode(3, INPUT); // D2
  pinMode(4, INPUT); // D3
  pinMode(5, INPUT); // D4
  pinMode(6, INPUT); // D5
  pinMode(7, INPUT); // D6
  pinMode(8, INPUT); // D7 - Playback
  pinMode(9, INPUT); // D7 - Randomise
  tmrpcm.speakerPin = 2;
  tmrpcm.volume(1);
  
  Serial.begin(9600);
  Serial.println("Buttons Ready! Connecting to SD Card...");

  if (!SD.begin(SD_ChipSelectPin)) {  // See if the SD Card is present and can be initialized.
    Serial.println("SD Card could not be initialised. Stopping...");
    return;
  } else
    Serial.println("SD Card ready!");

  randomSeed(analogRead(0));

  tmrpcm.play("1/turkey.wav");
}

void loop() {
//  cb0 = digitalRead(5);
//  cb1 = digitalRead(6);
//  cb2 = digitalRead(7);
//  cb3 = digitalRead(8);
//  cb4 = digitalRead(9);
//
//  playbackBtn = digitalRead(10);
//  randomiseBtn = digitalRead(11);
//
//  if (cb0 == HIGH) {
//    columnButton0();
//  } else if (cb1 == HIGH) {
//    columnButton1();
//  } else if (cb2 == HIGH) {
//    columnButton2();
//  } else if (cb3 == HIGH) {
//    columnButton3();
//  } else if (cb4 == HIGH) {
//    columnButton4();
//  } else if (playbackBtn == HIGH) {
//    playback();
//  } else if (randomiseBtn == HIGH) {
//    randomise();
//  }
}

void incrementColumnState(int column) {
  if (columnState[column] < maxColumnState[column]) {
    columnState[column]++;
  } else {
    columnState[column] = 1;
  }
}

char* convertToChar(String s){
    if(s.length()!=0){
        char *c = const_cast<char*>(s.c_str());
        return c;
    }
}

bool checkZero(int array[]) {
  for (int i = 0; i < 4; i++) {
      if(array[i] != 0) {
        return false;
      }
  }
  return true;
}

void columnButton0() {
  incrementColumnState(0);
  char* file = convertToChar(column0Sounds[columnState[0] - 1]);
  Serial.print("Playing file: ");
  Serial.println(file);
  tmrpcm.play(file);
}

void columnButton1() {
  incrementColumnState(1);
  char* file = convertToChar(column1Sounds[columnState[1] - 1]);
  Serial.print("Playing file: ");
  Serial.println(file);
  tmrpcm.play(file);
}

void columnButton2() {
  incrementColumnState(2);
  char* file = convertToChar(column2Sounds[columnState[2] - 1]);
  Serial.print("Playing file: ");
  Serial.println(file);
  tmrpcm.play(file);
}

void columnButton3() {
  incrementColumnState(3);
  char* file = convertToChar(column3Sounds[columnState[3] - 1]);
  Serial.print("Playing file: ");
  Serial.println(file);
  tmrpcm.play(file);
}

void columnButton4() {
  incrementColumnState(4);
  char* file = convertToChar(column4Sounds[columnState[4] - 1]);
  Serial.print("Playing file: ");
  Serial.println(file);
  tmrpcm.play(file);
}

void playback() {
  if (checkZero(columnState)) {
    randomise();
    return;
  }
  
  char* file0 = convertToChar(column0Sounds[columnState[0] - 1]);
  char* file1 = convertToChar(column1Sounds[columnState[1] - 1]);
  char* file2 = convertToChar(column2Sounds[columnState[2] - 1]);
  char* file3 = convertToChar(column3Sounds[columnState[3] - 1]);
  char* file4 = convertToChar(column4Sounds[columnState[4] - 1]);

  Serial.print("Playing files: ");
  Serial.println(file0);
  Serial.println(file1);
  Serial.println(file2);
  Serial.println(file3);
  Serial.println(file4);

  tmrpcm.play(file0);
  tmrpcm.play(file1);
  tmrpcm.play(file2);
  tmrpcm.play(file3);
  tmrpcm.play(file4);
}

void randomise() {
  int randomSounds[5];

  for (int i = 0; i < 5; i++) {
    randomSounds[i] = random(1, columnState[i]);
  }

  char* file0 = convertToChar(column0Sounds[randomSounds[0] - 1]);
  char* file1 = convertToChar(column1Sounds[randomSounds[1] - 1]);
  char* file2 = convertToChar(column2Sounds[randomSounds[2] - 1]);
  char* file3 = convertToChar(column3Sounds[randomSounds[3] - 1]);
  char* file4 = convertToChar(column4Sounds[randomSounds[4] - 1]);

  Serial.print("Playing files: ");
  Serial.println(file0);
  Serial.println(file1);
  Serial.println(file2);
  Serial.println(file3);
  Serial.println(file4);

  tmrpcm.play(file0);
  tmrpcm.play(file1);
  tmrpcm.play(file2);
  tmrpcm.play(file3);
  tmrpcm.play(file4);
}
