#ifndef _DECK_H_
#define _DECK_H_

#include <vector>

#include "card.h"
#include "hole_cards.h"

using namespace std;

class Deck
{
public:
	Deck();
	~ Deck();
	void fill();
	void empty();
	int count() const;
	
	bool push(Card card);
	bool pop(Card &card);
	bool shuffle(int seed);
	
	void set_bao_zi(bool enable);
	void set_bao_san(bool enable);

	void get_hole_cards(HoleCards &holecards);
	void get_hole_cards(HoleCards &holecards, int card_type);
    bool has_hole_cards();
	
	void debug();
	
public:
	vector<Card> cards;
	bool bao_zi_enable;
	bool bao_san_enable;

private:
	void get_n_hole_cards(HoleCards &holecards, int n);
	void get_zero_hole_cards(HoleCards &holecards);
	void get_one_hole_cards(HoleCards &holecards);
	void get_two_hole_cards(HoleCards &holecards);
	void get_three_hole_cards(HoleCards &holecards);
	void get_four_hole_cards(HoleCards &holecards);
	void get_five_hole_cards(HoleCards &holecards);
	void get_six_hole_cards(HoleCards &holecards);
	void get_seven_hole_cards(HoleCards &holecards);
	void get_eight_hole_cards(HoleCards &holecards);
	void get_nine_hole_cards(HoleCards &holecards);
	void get_sangong_hole_cards(HoleCards &holecards);
	void get_baozi_hole_cards(HoleCards &holecards);
	void get_333_hole_cards(HoleCards &holecards);

	void delete_cards(std::vector<Card> &tmp);

};

#endif /* _DECK_H_ */
