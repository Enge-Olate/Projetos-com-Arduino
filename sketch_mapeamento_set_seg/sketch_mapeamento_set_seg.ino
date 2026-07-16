#define STATE_HIGH 1
#define STATE_LOW 0
#define NUM_TRANSISTORS (sizeof(transistors) / sizeof(transistors[0]))
typedef struct {
  uint8_t pin;         // Pinos dos segmentos(leds).
  uint8_t bit;         // Mapeamento dos bytes.
  uint8_t active_bit;  // Ligado/desligado.
} segment_t;

typedef struct {
  uint8_t pin;           // Pinos dos transistores.
  uint8_t active_level;  // Estado dos transistores.
} digit_t;

digit_t transistors[] = {
  { 2, STATE_HIGH },
  { 3, STATE_HIGH },
  { 4, STATE_HIGH },
  { 5, STATE_HIGH }
};
enum {
  SEG_A = 0,
  SEG_B,
  SEG_C,
  SEG_D,
  SEG_E,
  SEG_F,
  SEG_G,
  SEG_DP,
  NUM_SEGMENTS
};

segment_t segments[NUM_SEGMENTS] = {
  { 6, 0, STATE_HIGH },   // A
  { 7, 1, STATE_HIGH },   // B
  { 8, 2, STATE_HIGH },   // C
  { 9, 3, STATE_HIGH },   // D
  { 10, 4, STATE_HIGH },  // E
  { 11, 5, STATE_HIGH },  // F
  { 12, 6, STATE_HIGH },  // G
  { 13, 7, STATE_HIGH }   // DP
};


void transistors_off() {
  for (int i = 0; i < NUM_TRANSISTORS; i++) {
    digitalWrite(transistors[i].pin, transistors[i].active_level ? LOW : HIGH);
  }
}
void transistor_on(uint8_t idx) {
  if (idx >= NUM_TRANSISTORS) return;
  digitalWrite(transistors[idx].pin, transistors[idx].active_level ? HIGH : LOW);
}
void transistors_test() {
  for (int i = 0; i <= NUM_TRANSISTORS; i++) {
    transistors_off();
    transistor_on(i);
    delay(500);
  }
}

void segments_off() {
  for (int i = 0; i < NUM_SEGMENTS; i++) {
    digitalWrite(segments[i].pin, segments[i].active_bit ? LOW : HIGH);
  }
}

void transistor_msb(){
  digit_t t = transistors[0];
  digitalWrite(t.pin, t.active_level ? LOW:HIGH);
}

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < NUM_TRANSISTORS; i++) {
    pinMode(transistors[i].pin, OUTPUT);
    // Inicia os transistores desligados.
    digitalWrite(transistors[i].pin, transistors[i].active_level ? HIGH:LOW);
  }
  for (int i = 0; i < NUM_SEGMENTS; i++) {
    pinMode(segments[i].pin, OUTPUT);
    digitalWrite(segments[i].pin, segments[i].active_bit ? HIGH : LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  transistors_test();
}
