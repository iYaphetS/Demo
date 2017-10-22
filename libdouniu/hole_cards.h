#ifndef _HOLE_CARDS_H_
#define _HOLE_CARDS_H_

#include <vector>
#include <algorithm>

#include "card.h"

using namespace std;

class HoleCards
{
public:
	HoleCards();
	
	void add_card(Card c);
	
	void sort();
	
	void analysis();
	
	int compare(HoleCards &hc);
	
	void set_card_type(int type);

	void clear() { cards.clear(); oldcards.clear(); card_type=0; ratio=0;};
	
	void copy_cards(std::vector<Card> &v);

	void copy_cards(std::vector<int> &v);

	int size() const;

	void debug();

	std::vector<Card> cards;
	Card kicker;
	std::vector<Card> oldcards;
	
	int card_type;
	int ratio;

    bool enable_jinniu;
    bool enable_wuxiaoniu;
    bool enable_zhadan;
};

#endif /* _HOLE_CARDS_H_ */
