#include <iostream>
#include <vector>
#include "card.cpp"
#include "dealer.cpp"


int main() {
    
    std::cout << "\n";

    // Generate dealer's hand and display only the first two cards
    Dealer cards = Dealer();
    cards.show_2();

    // Generate player's first two cards
    std::cout << "\n";
    Card card_one = Card();
    Card card_two = Card();

    // variable to keep track of how many aces (11) the player has
    int aces = 0;

    std::vector<int> hand;

    hand.push_back(card_one.getValue());
    hand.push_back(card_two.getValue());

    // hand sum total
    int hand_t = 0;

    // Add first two cards together and keep track if there is an ace in the hand.
    hand_t = card_one.getValue() + card_two.getValue();
    if (card_one.isAce()) {
        aces++;
    }
    if (card_two.isAce()) {
        aces++;
    }
    if (card_one.isAce() && card_two.isAce()) {
        hand_t = hand_t - 10;
        aces--;
        hand[0] = 1;
    }
    

    // Blackjack case immedieately ends the game
    if (hand_t == 21) {
        std::cout << "BLACKJACK!" << std::endl;
        //std::cout << cards.addScore() << std::endl;
        int play;
        std::cout << "Play again? Y(0)/N(1) : ";
        std::cin >> play;
        if (play == 0) {
            main();
        }
        else {
            std::cout << "gg" << std::endl;
        }
    }

    // If the sum total of player's hand is less than 21
    // prompt to hit or stay.
    while (hand_t < 21) {

        std::cout << "Your hand: ";
        for (int i = 0; i < hand.size(); i++) {
            std::cout << hand.at(i) << " ";
        }
        std::cout << "\n";

        // Prompt for adding a card or ending your turn
        int hos;
        std::cout << "Hit(0) or Stay(1)? : ";
        std::cin >> hos;
        std::cout << "\n";


        if (hos == 0) {
            // Generates new card and adds its value to the total
            Card next_card = Card();
            hand.push_back(next_card.getValue());
            hand_t = hand_t + next_card.getValue();
            
            if (next_card.isAce()) {
                aces++;
            }

            // if the hand total is greater than 21, check for aces
            while (hand_t > 21) {
                if (aces > 0) {
                    hand_t = hand_t - 10;
                    aces--;

                    // changes one 11 from the hand to a 1
                    for (int i = 0; i < hand.size(); i++) {
                        if (hand[i] == 11) {
                            hand[i] = 1;
                            break;
                        }
                    }
                }

                // if the hand is greater than 21 and there are no aces
                // then the loop will break
                else {
                    break;
                }
            }

            // after hitting, your hand equals 21
            if (hand_t == 21) {
                
                // show hand
                std::cout << "Your hand: ";
                for (int i = 0; i < hand.size(); i++) {
                std::cout << hand.at(i) << " ";
                }
                std::cout << "\n";

                // show dealer's hand and have it play now
                cards.show();
                cards.check17();

                // tie if player's hand is equal to dealer's hand                
                if (hand_t == cards.getTotal()) {
                    std::cout << "Tie!" << std::endl;
                    //std::cout << cards.getScore() << std::endl;
                }

                // win otherwise
                // if a lose prompt is created, it is possible the dealer could win even if they bust.
                else {
                    std::cout << "You win!" << std::endl;
                    //std::cout << cards.addScore() << std::endl;
                }

                // play again prompt
                int play;
                std::cout << "Play again? Y(0)/N(1) : ";
                std::cin >> play;
                if (play == 0) {
                    main();
                    return 0;
                }

                else {
                    std::cout << "gg" << std::endl;
                    return 0;
                }
            }
        }

        // If player chooses to stay:
        else if (hos == 1) {

            // show dealer's hand 
            cards.show();
            cards.check17();
            std::cout << cards.getTotal() << std::endl;

            // win if player's hand is greater than dealer's hand
            if ((hand_t > cards.getTotal()) || ((hand_t < cards.getTotal()) && (cards.getTotal() > 21))) {
                std::cout << "You win!" << std::endl;
                //std::cout << cards.addScore() << std::endl;
            }

            // lose if player's hand is less than dealer's hand
            else if ((hand_t < cards.getTotal()) && (cards.getTotal() < 21)) {
                std::cout << "You lose!" << std::endl;
                //std::cout << cards.getScore() << std::endl;
            }

            // tie if player's hand is equal to dealer's hand
            else if (hand_t == cards.getTotal()) {
                std::cout << "Tie!" << std::endl;
                //std::cout << cards.getScore() << std::endl;
            }


            // play again prompt
            int play;
            std::cout << "Play again? Y(0)/N(1) : ";
            std::cin >> play;
            if (play == 0) {
                main();

                // return 0 was specifically placed here to avoid having hands that don't reach 21 from
                // being played again after future hands are finished. However, I placed it in other play
                // again prompts for the sake of consistency.
                return 0; 
            }
            else if (play == 1) {
                std::cout << "gg" << std::endl;
                return 0;
            }
        }
    }

    if (hand_t > 21) {
        std::cout << "Your hand: ";
        for (int i = 0; i < hand.size(); i++) {
            std::cout << hand.at(i) << " ";
        }
        std::cout << "\n" << "\n";

        cards.show();
        cards.check17();

        std::cout << "You lose!" << std::endl;
        //std::cout << cards.getScore() << std::endl;

        // play again prompt
        int play;
        std::cout << "Play again? Y(0)/N(1) : ";
        std::cin >> play;
        if (play == 0) {
            main();
            return 0;
        }
        else {
            std::cout << "gg" << std::endl;
            return 0;
        }
    }
}

/*

    PROBLEMS:

            (SOLVED)
        - If a game is lost after staying and the player prompts to play again, the hand will be
          saved. The player will be prompted to hit or stay on all those decks after asking to not
          play again.
            - The player has to lose a game by staying for the hand to be saved
            - This is probably because the hand is still less than 21, so the loop continues after
              ending future main calls.
            - This could probably be fixed if I made the game in its own class and just called functions
              in main instead of coding the whole game in main.
            - Or I could just return 0 after calling main again and it just works...
        

            (SOLVED)
        - If the player starts with two 11s, the dealer is automatically prompted to check17().
            - The player should be dealt 11 and 1 in this case and asked if they want to hit or stay
            - This happens because the check for aces only happens while the hand total is less than 21.
            - Two 11s are not less than 21.
            - Check for double aces before starting the game.

        - If the player is asked to press 0 or 1, then the program will understand 0 as it needs to and
          any other key as 1 
            - If asked to hit or stay, if the player hits a key that isn't a number, the program will end.
            - If asked to play again, if the player hits a key that isn't a number, the program will freak out
            - Otherwise, the program reads other inputs as 0.
            SOLUTION: don't press non-integer keys
        
        - If the dealer hits past 21, and the player has stayed, the game will assume the dealer won
            - There is no code to check if the dealer busted, only if the player busted.

*/
