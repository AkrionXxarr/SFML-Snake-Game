#ifndef _ASCII_TILE_SET_HPP_
#define _ASCII_TILE_SET_HPP_

#include "SFML_Include.hpp"
#include "General_Include.hpp"
#include "TileSet.hpp"

class AsciiTileSet : public TileSet
{
public:
    AsciiTileSet(std::string filePath) : TileSet(filePath, 16, 16)
    {
    }

public:
    sf::Sprite GetCharacter(u8 c);
};

namespace ascii
{

    enum ASCII_NUMBER
    {
        ZERO    = ((3 * 16) + 0),
        ONE     = ((3 * 16) + 1),
        TWO     = ((3 * 16) + 2),
        THREE   = ((3 * 16) + 3),
        FOUR    = ((3 * 16) + 4),
        FIVE    = ((3 * 16) + 5),
        SIX     = ((3 * 16) + 6),
        SEVEN   = ((3 * 16) + 7),
        EIGHT   = ((3 * 16) + 8),
        NINE    = ((3 * 16) + 9)
    };

    enum ASCII_ALPHABET
    {
        A = ((4 * 16) + 1),  a = ((6 * 16) + 1),
        B = ((4 * 16) + 2),  b = ((6 * 16) + 2),
        C = ((4 * 16) + 3),  c = ((6 * 16) + 3),
        D = ((4 * 16) + 4),  d = ((6 * 16) + 4),
        E = ((4 * 16) + 5),  e = ((6 * 16) + 5),
        F = ((4 * 16) + 6),  f = ((6 * 16) + 6),
        G = ((4 * 16) + 7),  g = ((6 * 16) + 7),
        H = ((4 * 16) + 8),  h = ((6 * 16) + 8),
        I = ((4 * 16) + 9),  i = ((6 * 16) + 9),
        J = ((4 * 16) + 10), j = ((6 * 16) + 10),
        K = ((4 * 16) + 11), k = ((6 * 16) + 11),
        L = ((4 * 16) + 12), l = ((6 * 16) + 12),
        M = ((4 * 16) + 13), m = ((6 * 16) + 13),
        N = ((4 * 16) + 14), n = ((6 * 16) + 14),
        O = ((4 * 16) + 15), o = ((6 * 16) + 15),
        P = ((5 * 16) + 0),  p = ((7 * 16) + 0),
        Q = ((5 * 16) + 1),  q = ((7 * 16) + 1),
        R = ((5 * 16) + 2),  r = ((7 * 16) + 2),
        S = ((5 * 16) + 3),  s = ((7 * 16) + 3),
        T = ((5 * 16) + 4),  t = ((7 * 16) + 4),
        U = ((5 * 16) + 5),  u = ((7 * 16) + 5),
        V = ((5 * 16) + 6),  v = ((7 * 16) + 6),
        W = ((5 * 16) + 7),  w = ((7 * 16) + 7),
        X = ((5 * 16) + 8),  x = ((7 * 16) + 8),
        Y = ((5 * 16) + 9),  y = ((7 * 16) + 9),
        Z = ((5 * 16) + 10), z = ((7 * 16) + 10)
    };

    enum ASCII_PUNCTUATION
    {
        EXCLAMATION  = ((2 * 16) + 1),
        DOUBLE_QUOTE = ((2 * 16) + 2),
        APOSTROPHE   = ((2 * 16) + 7),
        COMMA        = ((2 * 16) + 12),
        PERIOD       = ((2 * 16) + 14),
        COLON        = ((3 * 16) + 10),
        SEMICOLON    = ((3 * 16) + 11),
        QUESTION     = ((3 * 16) + 15)
    };

    enum ASCII_BRACKETS
    {
        LEFT_PAREN   = ((2 * 16) + 8),
        RIGHT_PAREN  = ((2 * 16) + 9),
        LEFT_ANGLE   = ((3 * 16) + 12),
        RIGHT_ANGLE  = ((3 * 16) + 14),
        LEFT_SQUARE  = ((5 * 16) + 11),
        RIGHT_SQUARE = ((5 * 16) + 13),
        LEFT_CURLY   = ((7 * 16) + 11),
        RIGHT_CURLY  = ((7 * 16) + 13)
    };

    enum ASCII_SYMBOLS
    {
        SPACE           = ((2 * 16) + 0),
        HASH            = ((2 * 16) + 3),
        DOLLAR          = ((2 * 16) + 4),
        PERCENT         = ((2 * 16) + 5),
        ANPERSAND       = ((2 * 16) + 6),
        ASTERISK        = ((2 * 16) + 10),
        PLUS            = ((2 * 16) + 11),
        DASH            = ((2 * 16) + 13),
        FORWARD_SLASH   = ((2 * 16) + 15),
        EQUALS          = ((3 * 16) + 13),
        AT              = ((4 * 16) + 0),
        BACK_SLASH      = ((5 * 16) + 12),
        CIRCUMFLEX      = ((5 * 16) + 14),
        UNDER_SCORE     = ((5 * 16) + 15),
        GRAVE           = ((6 * 16) + 0),
        PIPE            = ((7 * 16) + 12),
        TILDE           = ((7 * 16) + 14)
    };
}

#endif