#ifndef GAMEPROPERTIES_H
#define GAMEPROPERTIES_H
#include <QString>

extern int GAME_TICK_MS;
extern int ZOMBIE_YPOS;
extern int ZOMBIE_STEP_SIZE;
extern QString ALLOWED_CHARACTERS;
extern int FONT_SIZE;
extern int ANIMATION_TICK_DECIMATION;
extern int ZOMBIE_SELDOMNESS;
extern int ALIEN_POSITION;
extern int MAX_NUM_ALIEN_HITS;

//TODO: add to settings
extern int MINIMUM_ZOMBIE_INTERVAL_MS;
extern int BULLET_REGAIN_AFTER_HIT;
extern int NUM_BULLETS;
#endif // GAMEPROPERTIES_H
