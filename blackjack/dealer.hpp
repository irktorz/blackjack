#ifndef DEALER_H_
#define DEALER_H_

#include <vector>
#include "card.hpp"

class Dealer : public Card {
    public:
        Dealer();
        ~Dealer();

        void show();
        void show_2();
        int getTotal();
        void check17();
        int addScore();
        int getScore();


    private:
        std::vector<int> hand_;
        int total_;
        int aces_;
        int score_;
};

#endif