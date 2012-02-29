/* -*- mode: C; c-basic-offset: 4; intent-tabs-mode: nil -*-
 *
 * Copyright <c> 2012 Sifteo, Inc. All rights reserved.
 */
 
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef BUDDIES_PUZZLE_H_
#define BUDDIES_PUZZLE_H_

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <sifteo/cube.h>
#include "Config.h"
#include "Piece.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Buddies {

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

class Puzzle
{
public:
    Puzzle(
        const char *chapterTitle,
        const char *cutsceneTextStart,
        const char *cutsceneTextEnd,
        const char *clue,
        unsigned int numBuddies,
        const unsigned int buddyIds[],
        unsigned int numShuffles,
        const Piece startState[kMaxBuddies][NUM_SIDES],
        const Piece endState[kMaxBuddies][NUM_SIDES]);
    
    const char *GetChapterTitle() const;
    const char *GetCutsceneTextStart() const;
    const char *GetCutsceneTextEnd() const;
    const char *GetClue() const;
    
    unsigned int GetNumBuddies() const;
    unsigned int GetBuddyId(unsigned int buddyIdIndex) const;
    unsigned int GetNumShuffles() const;
    
    const Piece &GetStartState(unsigned int buddy, Sifteo::Cube::Side side) const;
    const Piece &GetEndState(unsigned int buddy, Sifteo::Cube::Side side) const;
    
private:
    const char *mChapterTitle;
    const char *mCutsceneTextStart;
    const char *mCutsceneTextEnd;
    const char *mClue;
    unsigned int mNumBuddies;
    unsigned int mBuddyIds[kMaxBuddies];
    unsigned int mNumShuffles;
    Piece mStartState[kMaxBuddies][NUM_SIDES];
    Piece mEndState[kMaxBuddies][NUM_SIDES];    
};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
