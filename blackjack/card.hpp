#ifndef CARD_HPP
#define CARD_HPP

#pragma once

class Card {
    public:
        Card();
        ~Card();

        int getValue();
        bool isAce();

    private:
        int value_;
        int ace_;
};

#endif 