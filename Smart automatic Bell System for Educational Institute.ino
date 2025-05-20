#include <LiquidCrystal.h>*

// LCD Pins: RS, E, D4–D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Buzzer
const int bellPin = 8;

// Button pins
const int resetButtonPin = A0;
const int skipPeriodPin = A1;
const int skipDayPin = A2;

// Schedule: 5 days x 8 periods x [Teacher, Subject]
const char* routine[5][8][2] = {
 
    
  {
    {"Sir=CK.nxt=CA.", "Math nxt=ENG"},
    {"Sir=CA.nxt=SCI.", "ENG nxt=SCI"},
    {"Sir=SCI.nxt=HIS.", "SCI nxt=HIS"},
    {"Sir=HIS.nxt=GEO.", "HIS nxt=GEO"},
    {"Sir=GEO.nxt=RG.", "GEO nxt=RG"},
    {"Sir=RG.nxt=EVS.", "RG nxt=EVS"},
    {"Sir=EVS.nxt=Draw.", "EVS nxt=DRAW"},
    {"Sir=Draw.nxt=END.", "DRAW nxt=END"}
  },
  {
    {"Sir=MRK.nxt=LNK.", "PHY nxt=CHEM"},
    {"Sir=LNK.nxt=COM.", "CHEM nxt=CS"},
    {"Sir=COM.nxt=ART.", "CS nxt=ART"},
    {"Sir=ART.nxt=PHY.", "ART nxt=PE"},
    {"Sir=PHY.nxt=MTH.", "PE nxt=MATH"},
    {"Sir=MTH.nxt=GEO.", "MATH nxt=GEO"},
    {"Sir=GEO.nxt=BIO.", "GEO nxt=BIO"},
    {"Sir=BIO.nxt=END.", "BIO nxt=END"}
  },
  {
    {"Sir=DAV.nxt=NMT.", "MATH nxt=ENG"},
    {"Sir=NMT.nxt=HIS.", "ENG nxt=HIS"},
    {"Sir=HIS.nxt=SCI.", "HIS nxt=SCI"},
    {"Sir=SCI.nxt=CHE.", "SCI nxt=CHEM"},
    {"Sir=CHE.nxt=TRA.", "CHEM nxt=TRG"},
    {"Sir=TRA.nxt=MTH.", "TRG nxt=MATH"},
    {"Sir=MTH.nxt=GEO.", "MATH nxt=GEO"},
    {"Sir=GEO.nxt=END.", "GEO nxt=END"}
  },
  {
    {"Sir=ASH.nxt=POO.", "PHY nxt=ENG"},
    {"Sir=POO.nxt=RHE.", "ENG nxt=SCI"},
    {"Sir=RHE.nxt=ART.", "SCI nxt=ART"},
    {"Sir=ART.nxt=DAN.", "ART nxt=DANCE"},
    {"Sir=DAN.nxt=EVS.", "DANCE nxt=EVS"},
    {"Sir=EVS.nxt=COM.", "EVS nxt=CS"},
    {"Sir=COM.nxt=Draw.", "CS nxt=DRAW"},
    {"Sir=Draw.nxt=END.", "DRAW nxt=END"}
  },
  {
    {"Sir=VIK.nxt=MEG.", "MATH nxt=ENG"},
    {"Sir=MEG.nxt=JAM.", "ENG nxt=SCI"},
    {"Sir=JAM.nxt=ARP.", "SCI nxt=HIS"},
    {"Sir=ARP.nxt=KUN.", "HIS nxt=GEO"},
    {"Sir=KUN.nxt=TRG.", "GEO nxt=RG"},
    {"Sir=RG.nxt=SNE.", "TRG nxt=BIO"},
    {"Sir=SNE.nxt=ART.", "BIO nxt=ART"},
    {"Sir=ART.nxt=END.", "ART nxt=END"}
  

  }};

// State tracking
int currentDay = 0;
int currentPeriod = 0;

unsigned long lastPeriodTime = 0;
const unsigned long periodInterval = 20000; // 20 seconds
bool bellRung = false;

void setup() {
  pinMode(bellPin, OUTPUT);
  pinMode(resetButtonPin, INPUT_PULLUP);
  pinMode(skipPeriodPin, INPUT_PULLUP);
  pinMode(skipDayPin, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.print("System Starting...");
  delay(1500);
  lcd.clear();

  showCurrentPeriod();
  lastPeriodTime = millis();
}

void loop() {
  unsigned long now = millis();

  // Reset button
  if (digitalRead(resetButtonPin) == LOW) {
    currentDay = 0;
    currentPeriod = 0;
    lcd.clear(); lcd.print("Resetting...");
    delay(1000);
    showCurrentPeriod();
    lastPeriodTime = millis();
    bellRung = false;
  }

  // Skip period
  if (digitalRead(skipPeriodPin) == LOW) {
    skipPeriod();
    delay(500);
  }

  // Skip day
  if (digitalRead(skipDayPin) == LOW) {
    skipDay();
    delay(500);
  }

  // Bell ON 10 seconds before period change
  if (!bellRung && now - lastPeriodTime >= (periodInterval - 10000)) {
    ringBell(10000);  // ring for 10 seconds
    bellRung = true;
  }

  // Auto period change after 20 seconds
  if (now - lastPeriodTime >= periodInterval) {
    skipPeriod(); // Move to next period
    lastPeriodTime = now;
    bellRung = false;
  }
}

void skipPeriod() {
  currentPeriod++;
  if (currentPeriod >= 8) {
    currentPeriod = 0;
    currentDay++;
    if (currentDay >= 5) {
      currentDay = 0;
    }
  }
  showCurrentPeriod();
}

void skipDay() {
  currentDay++;
  if (currentDay >= 5) {
    currentDay = 0;
  }
  currentPeriod = 0;
  lcd.clear();
  lcd.print("Skipping to next");
  lcd.setCursor(0, 1);
  lcd.print("day...");
  delay(1000);
  showCurrentPeriod();
}

void ringBell(int duration) {
  digitalWrite(bellPin, HIGH);
  delay(duration);
  digitalWrite(bellPin, LOW);
}

void showCurrentPeriod() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(routine[currentDay][currentPeriod][0]); // Teacher
  lcd.setCursor(0, 1);
  lcd.print(routine[currentDay][currentPeriod][1]); // Subject
}
 
