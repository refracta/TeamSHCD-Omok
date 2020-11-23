#ifndef BEEPUTILS_H
#define BEEPUTILS_H

#include <Windows.h>
#include <math.h>

#define OCTAVE_0 16
#define OCTAVE_1 33
#define OCTAVE_2 65
#define OCTAVE_3 131
#define OCTAVE_4 262
#define OCTAVE_5 523
#define OCTAVE_6 1047
#define OCTAVE_7 2093
#define OCTAVE_8 4186

#define VALUE_DO 0
#define VALUE_RE 2
#define VALUE_MI 4
#define VALUE_FA 5
#define VALUE_SOL 7
#define VALUE_RA 9
#define VALUE_SI 11

#define PLAY_BEEP(o, v, t) BEEP((int)((o) * pow(1.06f, v)), t)

#define DO(o, t) PLAYER_BEEP(o, VALUE_DO, t)
#define RE(o, t) PLAYER_BEEP(o, VALUE_RE, t)
#define MI(o, t) PLAYER_BEEP(o, VALUE_MI, t)
#define FA(o, t) PLAYER_BEEP(o, VALUE_FA, t)
#define SOL(o, t) PLAYER_BEEP(o, VALUE_SOL, t)
#define RA(o, t) PLAYER_BEEP(o, VALUE_RA, t)
#define SI(o, t) PLAYER_BEEP(o, VALUE_SI, t)
#endif