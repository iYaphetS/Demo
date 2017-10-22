#include <time.h>
#include <algorithm>
#include "deck.h"

static int card_arr[] = {
0x01, 0x11, 0x21, 0x31,		//A 14 
0x02, 0x12, 0x22, 0x32,		//2 15
0x03, 0x13, 0x23, 0x33,		//3 3
0x04, 0x14, 0x24, 0x34,		//4 4
0x05, 0x15, 0x25, 0x35,		//5 5
0x06, 0x16, 0x26, 0x36,		//6 6
0x07, 0x17, 0x27, 0x37,		//7 7
0x08, 0x18, 0x28, 0x38,		//8 8
0x09, 0x19, 0x29, 0x39,		//9 9
0x0A, 0x1A, 0x2A, 0x3A,		//10 10
0x0B, 0x1B, 0x2B, 0x3B,		//J 11
0x0C, 0x1C, 0x2C, 0x3C,		//Q 12
0x0D, 0x1D, 0x2D, 0x3D,		//K 13
};

Deck::Deck()
{
    flower_card_flag = 1;
    enable_jinniu = true;
    enable_wuxiaoniu = true;
    enable_zhadan = true;
}

Deck::~Deck()
{

}

void Deck::fill()
{
	cards.clear();
	
	for (unsigned int i = 0; i < 52; i++)
    {
        if (flower_card_flag == 0 && i >= 40)
        {
            return;
        }

		Card c(card_arr[i]);
		push(c);
	}
}

void Deck::empty()
{
	cards.clear();
}

int Deck::count() const
{
	return cards.size();
}

bool Deck::push(Card card)
{
	cards.push_back(card);
	return true;
}

bool Deck::pop(Card &card)
{
	if (!count())
		return false;
	
card = cards.back();
cards.pop_back();
return true;
}

bool Deck::shuffle(int seed)
{
	srand((unsigned int)time(NULL) + seed);
	random_shuffle(cards.begin(), cards.end());
	return true;
}

void Deck::get_hole_cards(HoleCards &holecards)
{
	Card card;

	holecards.clear();
	holecards.enable_jinniu = enable_jinniu;
	holecards.enable_wuxiaoniu = enable_wuxiaoniu;
	holecards.enable_zhadan = enable_zhadan;

	for (int i = 0; i < 5; i++)
	{
		pop(card);
		holecards.add_card(card);
	}
}

void Deck::get_hole_cards(HoleCards &holecards, int card_type)
{
	holecards.clear();
	holecards.enable_jinniu = enable_jinniu;
	holecards.enable_wuxiaoniu = enable_wuxiaoniu;
	holecards.enable_zhadan = enable_zhadan;

	switch (card_type)
	{
	case CARD_TYPE_NONNIU:
		get_noniu_hole_cards(holecards);
		break;
	case CARD_TYPE_NIUDING:
		get_niuding_hole_cards(holecards);
		break;
	case CARD_TYPE_NIUER:
		get_niuer_hole_cards(holecards);
		break;
	case CARD_TYPE_NIUSAN:
		get_niusan_hole_cards(holecards);
		break;
	case CARD_TYPE_NIUSI:
		get_niusi_hole_cards(holecards);
		break;
	case CARD_TYPE_NIUWU:
		get_niuwu_hole_cards(holecards);
		break;
	case CARD_TYPE_NIULIU:
		get_niuliu_hole_cards(holecards);
		break;
	case CARD_TYPE_NIUQI:
		get_niuqi_hole_cards(holecards);
		break;
	case CARD_TYPE_NIUBA:
		get_niuba_hole_cards(holecards);
		break;
	case CARD_TYPE_NIUJIU:
		get_niujiu_hole_cards(holecards);
		break;
	case CARD_TYPE_NIUNIU:
		get_niuniu_hole_cards(holecards);
		break;
	case CARD_TYPE_ZHADAN:
		get_zhadan_hole_cards(holecards);
		break;
	case CARD_TYPE_JINNIU:
		get_jinniu_hole_cards(holecards);
		break;
	case CARD_TYPE_WUXIAONIU:
		get_wuxiaoniu_hole_cards(holecards);
		break;
	default:
		get_hole_cards(holecards);
		break;
	}
}

void Deck::get_noniu_hole_cards(HoleCards &holecards)
{
	for (unsigned int i = 0; i < cards.size(); i++)
	{
		Card card1 = cards[i];
		for (unsigned int j = i + 1; j < cards.size(); j++)
		{
			Card card2 = cards[j];
			for (unsigned int k = j + 1; k < cards.size(); k++)
			{
				Card card3 = cards[k];
				if ((card1.point + card2.point + card3.point) % 10 == 0)
					continue;
				for (unsigned int m = k + 1; m < cards.size(); m++)
				{
					Card card4 = cards[m];
					if ((card4.point + card1.point + card2.point) % 10 == 0 ||
						(card4.point + card1.point + card3.point) % 10 == 0 ||
						(card4.point + card2.point + card3.point) % 10 == 0)
						continue;
					for (unsigned int n = m + 1; n < cards.size(); n++)
					{
						Card card5 = cards[n];
						if ((card5.point + card1.point + card2.point) % 10 == 0 ||
							(card5.point + card1.point + card3.point) % 10 == 0 ||
							(card5.point + card2.point + card3.point) % 10 == 0 ||
							(card5.point + card1.point + card4.point) % 10 == 0 ||
							(card5.point + card2.point + card4.point) % 10 == 0 ||
							(card5.point + card3.point + card4.point) % 10 == 0)
							continue;
						holecards.clear();
						holecards.add_card(card1);
						holecards.add_card(card2);
						holecards.add_card(card3);
						holecards.add_card(card4);
						holecards.add_card(card5);
						delete_cards(holecards.cards);
						return;
					}
				}
			}
		}		
	}
	get_hole_cards(holecards);
}

void Deck::get_niun_hole_cards(HoleCards &holecards, int num)
{
	int isniu = 0, flag1 = 0, flag2 = 0, flag3 = 0;
	for (unsigned int i = 0; i < cards.size(); i++)
	{
		Card seed1 = cards[i];
		for (unsigned int j = i + 1; j < cards.size(); j++)
		{
			Card seed2 = cards[j];
			if ((seed1.point + seed2.point) % 10 == num)
				flag3 = 1;
			for (unsigned int k = j + 1; k < cards.size(); k++)
			{
				Card seed3 = cards[k];
				if ((seed1.point + seed2.point + seed3.point) % 10 == 0)
					isniu = 1;
				if ((seed1.point + seed3.point) % 10 == num)
					flag2 = 1;
				if ((seed2.point + seed3.point) % 10 == num)
					flag1 = 1;
				if (isniu != 1 && flag1 != 1 && flag2 != 1 && flag3 != 1)
					continue;
				holecards.clear();
				holecards.add_card(seed1);
				holecards.add_card(seed2);
				holecards.add_card(seed3);
				for (unsigned int m = k + 1; m < cards.size(); m++)
				{
					Card card1 = cards[m];
					for (unsigned int n = m + 1; n < cards.size(); n++)
					{
						Card card2 = cards[n];
						if (card1.face > 10 && card2.face > 10 &&
							seed1.face > 10 && seed2.face > 10 && seed3.face > 10)
							continue;
						if ((card1.face == card2.face && card2.face == seed1.face && seed1.face == seed2.face) ||
							(card1.face == card2.face && card2.face == seed1.face && seed1.face == seed3.face) ||
							(card1.face == card2.face && card2.face == seed3.face && seed3.face == seed2.face) ||
							(card1.face == seed3.face && seed3.face == seed1.face && seed1.face == seed2.face) ||
							(card2.face == seed3.face && seed3.face == seed1.face && seed1.face == seed2.face))
							continue;
						if (isniu)
						{
							if ((card1.point + card2.point) % 10 == num)
							{
								holecards.add_card(card1);
								holecards.add_card(card2);
								delete_cards(holecards.cards);
								return;
							}
						}
						else if (flag1)
						{
							if ((card1.point + card2.point + seed1.point) % 10 == 0)
							{
								holecards.add_card(card1);
								holecards.add_card(card2);
								delete_cards(holecards.cards);
								return;
							}
						}
						else if (flag2)
						{
							if ((card1.point + card2.point + seed2.point) % 10 == 0)
							{
								holecards.add_card(card1);
								holecards.add_card(card2);
								delete_cards(holecards.cards);
								return;
							}
						}
						else if (flag3)
						{
							if ((card1.point + card2.point + seed3.point) % 10 == 0)
							{
								holecards.add_card(card1);
								holecards.add_card(card2);
								delete_cards(holecards.cards);
								return;
							}
						}

					}
				}
			}
		}		
	}
	get_hole_cards(holecards);
}
void Deck::get_niuding_hole_cards(HoleCards &holecards)
{
	get_niun_hole_cards(holecards, 1);
}

void Deck::get_niuer_hole_cards(HoleCards &holecards)
{
	get_niun_hole_cards(holecards, 2);
}

void Deck::get_niusan_hole_cards(HoleCards &holecards)
{
	get_niun_hole_cards(holecards, 3);
}

void Deck::get_niusi_hole_cards(HoleCards &holecards)
{
	get_niun_hole_cards(holecards, 4);
}
void Deck::get_niuwu_hole_cards(HoleCards &holecards)
{
	get_niun_hole_cards(holecards, 5);
}

void Deck::get_niuliu_hole_cards(HoleCards &holecards)
{
	get_niun_hole_cards(holecards, 6);
}
void Deck::get_niuqi_hole_cards(HoleCards &holecards)
{
	get_niun_hole_cards(holecards, 7);
}

void Deck::get_niuba_hole_cards(HoleCards &holecards)
{
	get_niun_hole_cards(holecards, 8);
}
void Deck::get_niujiu_hole_cards(HoleCards &holecards)
{
	get_niun_hole_cards(holecards, 9);
}

void Deck::get_niuniu_hole_cards(HoleCards &holecards)
{
	get_niun_hole_cards(holecards, 0);
}

void Deck::get_zhadan_hole_cards(HoleCards &holecards)
{
	int flag = 0;
	int mark1 = 1;
	int mark2 = 1;
	for (unsigned int i = 0; i < cards.size(); i++)
	{
		Card seed1 = cards[i];
		for (unsigned int j = i + 1; j < cards.size(); j++)
		{
			Card seed2 = cards[j];
			if (seed1.face == seed2.face)
				flag = 1;
			holecards.add_card(seed1);
			holecards.add_card(seed2);
			for (unsigned int k = j + 1; k < cards.size(); k++)
			{
				Card card = cards[k];
				if (flag)
				{
					if (holecards.size() == 4)
					{
						holecards.add_card(card);
					}
					else if (card.face == seed1.face)
					{
						holecards.add_card(card);
					}
				}
				else
				{
					if (card.face == seed1.face && mark1 == 1)
					{
						holecards.add_card(card);
						mark2 = 0;
					}
					else if (card.face == seed2.face && mark2 == 1)
					{
						holecards.add_card(card);
						mark1 = 0;
					}
				}

				if (holecards.size() == 5)
				{
					delete_cards(holecards.cards);
					return;
				}
			}
		}		
	}
	get_hole_cards(holecards);
}

void Deck::get_jinniu_hole_cards(HoleCards &holecards)
{
	for (unsigned int i = 0; i < cards.size(); i++)
	{
		Card card1 = cards[i];
		if (card1.face <= 10)
			continue;
		for (unsigned int j = i + 1; j < cards.size(); j++)
		{
			Card card2 = cards[j];
			if (card2.face <= 10)
				continue;
			for (unsigned int k = j + 1; k < cards.size(); k++)
			{
				Card card3 = cards[k];
				if (card3.face <= 10)
					continue;
				for (unsigned int m = k + 1; m < cards.size(); m++)
				{
					Card card4 = cards[m];
					if (card4.face <= 10)
						continue;
					for (unsigned int n = m + 1; m < cards.size(); n++)
					{
						Card card5 = cards[n];
						if (card5.face <= 10)
							continue;
						holecards.add_card(card1);
						holecards.add_card(card2);
						holecards.add_card(card3);
						holecards.add_card(card4);
						holecards.add_card(card5);
						delete_cards(holecards.cards);
						return;

					}
				}
			}
		}
	}
	get_hole_cards(holecards);
}

void Deck::get_wuxiaoniu_hole_cards(HoleCards &holecards)
{
	for (unsigned int i = 0; i < cards.size(); i++)
	{
		Card card1 = cards[i];
		if (card1.face >= 5)
			continue;
		for (unsigned int j = i + 1; j < cards.size(); j++)
		{
			Card card2 = cards[j];
			if (card2.face >= 5 || card1.face + card2.face > 10 ||
				(card1.face > 3 && card2.face > 3))
				continue;
			for (unsigned int k = j + 1; k < cards.size(); k++)
			{
				Card card3 = cards[k];
				if (card3.face >= 5 ||
					card1.face + card2.face + card3.face > 10 ||
					(card1.face > 2 && card2.face > 2 && card3.face > 2))
					continue;
				for (unsigned int m = k + 1; m < cards.size(); m++)
				{
					Card card4 = cards[m];
					if (card4.face >= 5 || card1.face + card2.face + card3.face + card4.face > 10)
						continue;
					for (unsigned int n = m + 1; n < cards.size(); n++)
					{
						Card card5 = cards[n];
						if (card5.face >= 5)
							continue;
						if ((card1.face + card2.face + card3.face + card4.face + card5.face) <= 10)
						{
							holecards.add_card(card1);
							holecards.add_card(card2);
							holecards.add_card(card3);
							holecards.add_card(card4);
							holecards.add_card(card5);
							delete_cards(holecards.cards);
							return;
						}
					}
				}
			}
		}
		
	}
	get_hole_cards(holecards);
}

void Deck::change_hole_cards(int pos, HoleCards &holecards)
{
	Card card;
	holecards.cards.erase(holecards.cards.begin() + pos);
	pop(card);
	holecards.cards.push_back(card);
    holecards.analysis();
}

bool  Deck::has_hole_cards()
{
    if (count() < 5)
    {
        return false;
    }
    else
    {
        return true;
    }
}
void Deck::delete_cards(std::vector<Card> &tmp)
{
	for (std::vector<Card>::iterator it = cards.begin(); it != cards.end();)
	{
		if (it->value == tmp[0].value || it->value == tmp[1].value
			|| it->value == tmp[2].value || it->value == tmp[3].value ||
			it->value == tmp[4].value)
		{
			it = cards.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void Deck::debug()
{
	Card::dump_cards(cards);
}


void Deck::set_flow_card_flag(int flag)
{
    flower_card_flag = flag;
}

void Deck::set_wuxiaoniu(bool enable)
{
    enable_wuxiaoniu = enable;
}

void Deck::set_jinniu(bool enable)
{
    enable_jinniu = enable;
}

void Deck::set_zhadan(bool enable)
{
    enable_zhadan = enable;
}

