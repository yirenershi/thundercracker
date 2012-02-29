/* -*- mode: C; c-basic-offset: 4; intent-tabs-mode: nil -*-
 *
 * Copyright <c> 2012 Sifteo, Inc. All rights reserved.
 */
 
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Puzzle.h"
	
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace Sifteo;

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Buddies {

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

Puzzle::Puzzle(
    const char *chapterTitle,
    const char *cutsceneTextStart,
    const char *cutsceneTextEnd,
    const char *clue,
    unsigned int numBuddies,
    const unsigned int buddyIds[],
    unsigned int numShuffles,
    const Piece startState[kMaxBuddies][NUM_SIDES],
    const Piece endState[kMaxBuddies][NUM_SIDES])
    : mChapterTitle(chapterTitle)
    , mCutsceneTextStart(cutsceneTextStart)
    , mCutsceneTextEnd(cutsceneTextEnd)
    , mClue(clue)
    , mNumBuddies(numBuddies)
    , mBuddyIds()
    , mNumShuffles(numShuffles)
    , mStartState()
    , mEndState()
{
    for (unsigned int i = 0; i < numBuddies; ++i)
    {
        mBuddyIds[i] = buddyIds[i];
    }
    
    for (unsigned int i = 0; i < kMaxBuddies; ++i)
    {
        for (unsigned int j = 0; j < NUM_SIDES; ++j)
        {
            mStartState[i][j] = startState[i][j];
            mEndState[i][j] = endState[i][j];
        }
    }
}    

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

const char *Puzzle::GetChapterTitle() const
{
    return mChapterTitle;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

const char *Puzzle::GetCutsceneTextStart() const
{
    return mCutsceneTextStart;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

const char *Puzzle::GetCutsceneTextEnd() const
{
    return mCutsceneTextEnd;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

const char *Puzzle::GetClue() const
{
    return mClue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int Puzzle::GetNumBuddies() const
{
    return mNumBuddies;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int Puzzle::GetBuddyId(unsigned int buddyIdIndex) const
{
    return mBuddyIds[buddyIdIndex];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int Puzzle::GetNumShuffles() const
{
    return mNumShuffles;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

const Piece &Puzzle::GetStartState(unsigned int buddy, Cube::Side side) const
{
    ASSERT(buddy < arraysize(mStartState));
    ASSERT(side < int(arraysize(mStartState[buddy])));
    return mStartState[buddy][side];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

const Piece &Puzzle::GetEndState(unsigned int buddy, Cube::Side side) const
{
    ASSERT(buddy < arraysize(mEndState));
    ASSERT(side < int(arraysize(mEndState[buddy])));
    return mEndState[buddy][side];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
