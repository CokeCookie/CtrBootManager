#ifndef _anim_h_
#define _anim_h_

#include "config.h"
#include "movie.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int frameSize;
    
    void* file;
    int fileOffset;
    int curFrame;
    int framesCount;
    
    comp_manager_s* comp;

    int curLoop;
    int loopsToDo;
    
    int loopFramesCount;

    int loopStreamType;
    char* loopStream;
    int loopStreamSize;
    int loopReverse;
    
    char* loopStartFrameStream;
    int loopStartFrame;
    int loopTimeOnStartFrame;

    char* loopEndFrameStream;
    int loopEndFrame;
    int loopTimeOnEndFrame;
} movie_state_s;

typedef struct {
    int timer;
    int active;

    u8 bgTop1[3];
    u8 bgTop2[3];
    u8 bgBot[3];
    u8 highlight[4];
    u8 borders[4];
    u8 fntDef[4];
    u8 fntSel[4];
    
    movie_state_s topMovie;
    movie_state_s botMovie;
} anim_state_s;

anim_state_s* anim;

void animInit();
void animSetup();
void incrementAnimTime();
int readTopMovie(u8* fb);
int readBotMovie(u8* fb);
void animExit();

#ifdef __cplusplus
}
#endif

#endif
