////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2012 - TRACER. All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "PuzzleData.h"
#include "Puzzle.h"
#include "Piece.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Buddies { namespace {

////////////////////////////////////////////////////////////////////////////////////////////////////
// These arrays represent different configurations of the puzzle space. The first dimension of
// the array is the number of cubes in play, the second dimension are the sides of the cube.
//  
// So in other words, each side of each cube is assigned a instance of a "Piece" class. A Piece
// represents a part of the face (holding which buddy it originated from, which face part it is,
// whether or not the piece must be in place to solve the puzzle and which attribute it has). 
// 
// For example: Piece(1, 2, true, ATTR_HIDDEN) would be the mouth of Buddy 1 (the blue cat),
// it is necessary to be in the right spot to solve the puzzle, but it is a tricky hidden piece!
// Attributes default to ATTR_NONE.
// 
// Define each possible configuation puzzles can have up here. We will assign them to the 
// start and end state of puzzle below.
////////////////////////////////////////////////////////////////////////////////////////////////////

// The default configuration: all buddies with their parts in the proper place
Piece kDefaultState[kMaxBuddies][NUM_SIDES] =
{
    {
        Piece(0, 0, true),
        Piece(0, 1, true),
        Piece(0, 2, true),
        Piece(0, 3, true),
    },
    {
        Piece(1, 0, true),
        Piece(1, 1, true),
        Piece(1, 2, true),
        Piece(1, 3, true),
    },
    {
        Piece(2, 0, true),
        Piece(2, 1, true),
        Piece(2, 2, true),
        Piece(2, 3, true),
    },
    {
        Piece(3, 0, true),
        Piece(3, 1, true),
        Piece(3, 2, true),
        Piece(3, 3, true),
    },
    {
        Piece(4, 0, true),
        Piece(4, 1, true),
        Piece(4, 2, true),
        Piece(4, 3, true),
    },
    {
        Piece(5, 0, true),
        Piece(5, 1, true),
        Piece(5, 2, true),
        Piece(5, 3, true),
    },
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Piece(BuddyId, PartId, MustSolve, Attribute = ATTR_NONE)
// - BuddyId = [0...kNumCubes)
// - PartId = [0...NUM_SIDES)
// - MustSolve = true/false
// - Attribute = [Piece::ATTR_NONE, Piece::ATTR_FIXED, Piece::ATTR_HIDDEN]
////////////////////////////////////////////////////////////////////////////////////////////////////

Piece kStartStateAttributeTest[kNumCubes][NUM_SIDES] =
{
    // Buddy 0
    {
        Piece(0, 0, true),                      // Top (Hair)
        Piece(0, 1, true),                      // Left (Left Eye)
        Piece(0, 2, true, Piece::ATTR_HIDDEN),  // Bottom (Mouth)
        Piece(0, 3, true),                      // Right (Right Eye)
    },
    // Buddy 1
    {   
        Piece(1, 0, true),
        Piece(1, 1, true, Piece::ATTR_FIXED),
        Piece(1, 2, true),
        Piece(1, 3, true, Piece::ATTR_FIXED),
    },
};

Piece kAuthoredEndStateMouths[kMaxBuddies][NUM_SIDES] =
{
    {
        Piece(0, 0, false),
        Piece(0, 1, false),
        Piece(1, 2, true),
        Piece(0, 3, false),
    },
    {
        Piece(1, 0, false),
        Piece(1, 1, false),
        Piece(0, 2, true),
        Piece(1, 3, false),
    },
};

Piece kAuthoredEndStateHair[kMaxBuddies][NUM_SIDES] =
{
    {
        Piece(1, 0, true),
        Piece(0, 1, false),
        Piece(0, 2, false),
        Piece(0, 3, false),
    },
    {
        Piece(0, 0, true),
        Piece(1, 1, false),
        Piece(1, 2, false),
        Piece(1, 3, false),
    },
};

Piece kAuthoredEndStateEyes[kMaxBuddies][NUM_SIDES] =
{
    {
        Piece(0, 0, false),
        Piece(1, 1, true),
        Piece(0, 2, false),
        Piece(1, 3, true),
    },
    {
        Piece(1, 0, false),
        Piece(0, 1, true),
        Piece(1, 2, false),
        Piece(0, 3, true),
    },
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// This is the default state (all buddies with their original parts in the right position).
////////////////////////////////////////////////////////////////////////////////////////////////////

const unsigned int kBuddyIdsDefault[] = {0, 1, 2, 3, 4, 5};
const Puzzle kPuzzleDefault =
    Puzzle(
        "Default",
        "Default",
        "Default",
        "Default",
        kNumCubes,
        kBuddyIdsDefault,
        0,
        kDefaultState,
        kDefaultState);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Here are all of our puzzles. Each puzzle has the number of cubes it uses, a string for
// instrunctions, the start state, and the end state. Just use kNumCubes for the number of buddies
// for now. Be aware that the instructions currently only support two lines of 16 characters each.
//
// Puzzle(
//     CHAPTER_TITLE,
//     CUTSCENE_TEXT_START,
//     CUTSCENE_TEXT_END,
//     CLUE,
//     NUMBER_OF_CUBES,
//     NUMBER_OF_SHUFFLES,
//     START_STATE,
//     END_STATE);
//
// Just add new puzzles to this array to throw them into play. Puzzle mode starts at the first
// puzzle and rotate through them all after each solve. It currently just loops back to puzzle 0 if
// all are solved.
////////////////////////////////////////////////////////////////////////////////////////////////////

const unsigned int kBuddyIdsTest0[] = {0, 1};
const unsigned int kBuddyIdsTest1[] = {1, 2};
const unsigned int kBuddyIdsTest2[] = {3, 4};
const unsigned int kBuddyIdsTest3[] = {5, 0};
const unsigned int kBuddyIdsTest4[] = {1, 3};

const Puzzle kPuzzles[] =
{
    Puzzle(
        "Big Mouth",
        "Gimme a kiss!",
        "Muuuahhh",
        "Swap Mouths",
        2,
        kBuddyIdsTest0,
        0,
        kDefaultState,
        kAuthoredEndStateMouths),
    Puzzle(
        "All Mixed Up",
        "Let's get\nCRAZY!",
        "My head\nhurts.",
        "Unscramble",
        2,
        kBuddyIdsTest1,
        3,
        kDefaultState,
        kDefaultState),
    Puzzle(
        "Bad Hair Day",
        "How do I get\ncool hair\nlike you?",
        "That's much\nbetter.",
        "Swap Hair",
        2,
        kBuddyIdsTest2,
        0,
        kDefaultState,
        kAuthoredEndStateHair),
    Puzzle(
        "Private Eyes",
        "See the world\nfrom my eyes!",
        "That's much\nbetter.",
        "Swap Eyes",
        2,
        kBuddyIdsTest3,
        0,
        kDefaultState,
        kAuthoredEndStateEyes),
    Puzzle(
        "Attribute\nTest",
        "This is\nweird...",
        "SO WEIRD\nright?",
        "Swap Mouths",
        2,
        kBuddyIdsTest4,
        0,
        kStartStateAttributeTest,
        kAuthoredEndStateMouths),
};

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int GetNumPuzzles()
{
    return arraysize(kPuzzles);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

const Puzzle &GetPuzzleDefault()
{
    return kPuzzleDefault;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

const Puzzle &GetPuzzle(unsigned int puzzleIndex)
{
    ASSERT(puzzleIndex < arraysize(kPuzzles));
    return kPuzzles[puzzleIndex];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
