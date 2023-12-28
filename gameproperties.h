#ifndef GAMEPROPERTIES_H
#define GAMEPROPERTIES_H
#include <QString>

const int GAME_TICK_MS = 20;
const int ZOMBIE_YPOS = 460;
const int ZOMBIE_STEP_SIZE = 5;
const QString ALLOWED_CHARACTERS = "asdfjkl;";
const int FONT_SIZE = 50;
const int ANIMATION_TICK_DECIMATION = 10;
const int ZOMBIE_SELDOMNESS = 100; //The higher this value the more seldomly the zombies get generated.
const int ALIEN_POSITION = 850;
const int MAX_NUM_ALIEN_HITS = 5;
#endif // GAMEPROPERTIES_H
