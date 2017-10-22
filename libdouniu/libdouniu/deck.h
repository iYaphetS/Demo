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
	
	void get_hole_cards(HoleCards &holecards);
	void get_hole_cards(HoleCards &holecards, int card_type);
	void change_hole_cards(int pos, HoleCards &holecards);
    bool has_hole_cards();
    void set_flow_card_flag(int flag);
    void set_wuxiaoniu(bool enable);
    void set_jinniu(bool enable);
    void set_zhadan(bool enable);	
	void debug();
	
public:
	vector<Card> cards;
    int flower_card_flag;
    bool enable_jinniu;
    bool enable_wuxiaoniu;
    bool enable_zhadan;

private:
	void get_noniu_hole_cards(HoleCards &holecards);

	void get_niun_hole_cards(HoleCards &holecards, int n);
	void get_niuding_hole_cards(HoleCards &holecards);
	void get_niuer_hole_cards(HoleCards &holecards);
	void get_niusan_hole_cards(HoleCards &holecards);
	void get_niusi_hole_cards(HoleCards &holecards);
	void get_niuwu_hole_cards(HoleCards &holecards);
	void get_niuliu_hole_cards(HoleCards &holecards);
	void get_niuqi_hole_cards(HoleCards &holecards);
	void get_niuba_hole_cards(HoleCards &holecards);
	void get_niujiu_hole_cards(HoleCards &holecards);
	void get_niuniu_hole_cards(HoleCards &holecards);
	void get_zhadan_hole_cards(HoleCards &holecards);
	void get_jinniu_hole_cards(HoleCards &holecards);
	void get_wuxiaoniu_hole_cards(HoleCards &holecards);

	void delete_cards(std::vector<Card> &tmp);
};

#endif /* _DECK_H_ */
