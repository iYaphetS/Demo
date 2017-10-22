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
	
	void analysis(); // flag_333 == 1 333最大，flag_ratio == 1 有倍数
	
	int compare(HoleCards &hc);
	
	void clear() { cards.clear(); card_type = 0; gong = 0; ratio = 0;};
	
	void copy_cards(std::vector<Card> &v);

	void copy_cards(std::vector<int> &v);

	void debug();

	std::vector<Card> cards;
	Card kicker;
	
	int card_type;
	int gong;
	int ratio;
	bool bao_zi_enable;
	bool bao_san_enable;
};

#endif /* _HOLE_CARDS_H_ */
