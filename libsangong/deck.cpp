#include <algorithm>
#include <time.h>
#include "deck.h"


Deck::Deck()
{
	bao_zi_enable = true;
	bao_san_enable = true;
}

Deck::~ Deck()
{

}

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

void Deck::fill()
{
	cards.clear();
	
	for (int i = 0; i < 52; i++) {
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
	holecards.bao_zi_enable = bao_zi_enable;
	holecards.bao_san_enable = bao_san_enable;

	for (int i = 0; i < 3; i++)
	{
		pop(card);
		holecards.add_card(card);
	}
}

void Deck::get_hole_cards(HoleCards &holecards, int card_type)
{
	holecards.clear();
	holecards.bao_zi_enable = bao_zi_enable;
	holecards.bao_san_enable = bao_san_enable;
	switch (card_type)
	{
	case CARD_TYPE_ZERO:
		get_zero_hole_cards(holecards);
		break;
	case CARD_TYPE_ONE:
		get_one_hole_cards(holecards);
		break;
	case CARD_TYPE_TWO:
		get_two_hole_cards(holecards);
		break;
	case CARD_TYPE_THREE:
		get_three_hole_cards(holecards);
		break;
	case CARD_TYPE_FOUR:
		get_four_hole_cards(holecards);
		break;
	case CARD_TYPE_FIVE:
		get_five_hole_cards(holecards);
		break;
	case CARD_TYPE_SIX:
		get_six_hole_cards(holecards);
		break;
	case CARD_TYPE_SEVEN:
		get_seven_hole_cards(holecards);
		break;
	case CARD_TYPE_EIGHT:
		get_eight_hole_cards(holecards);
		break;
	case CARD_TYPE_NINE:
		get_nine_hole_cards(holecards);
		break;
	case CARD_TYPE_SANGONG:
		get_sangong_hole_cards(holecards);
		break;
	case CARD_TYPE_BAOZI:
		get_baozi_hole_cards(holecards);
		break;
	case CARD_TYPE_333:
		get_333_hole_cards(holecards);
		break;
	default:
		get_hole_cards(holecards);
		break;
	}
}

void Deck::get_n_hole_cards(HoleCards &holecards, int n)
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
				if ((card1.face == card2.face && card2.face == card3.face) ||
					(card1.face > 10 && card2.face > 10 && card3.face > 10))
					continue;
				if ((card1.point + card2.point + card3.point) % 10 == n)
				{
					holecards.add_card(card1);
					holecards.add_card(card2);
					holecards.add_card(card3);
					delete_cards(holecards.cards);
					return;
				}
			}
		}
	}
	get_hole_cards(holecards);
}

void Deck::get_zero_hole_cards(HoleCards &holecards)
{
	get_n_hole_cards(holecards, 0);
}

void Deck::get_one_hole_cards(HoleCards &holecards)
{
	get_n_hole_cards(holecards, 1);
}

void Deck::get_two_hole_cards(HoleCards &holecards)
{
	get_n_hole_cards(holecards, 2);
}

void Deck::get_three_hole_cards(HoleCards &holecards)
{
	get_n_hole_cards(holecards, 3);
}

void Deck::get_four_hole_cards(HoleCards &holecards)
{
	get_n_hole_cards(holecards, 4);
}

void Deck::get_five_hole_cards(HoleCards &holecards)
{
	get_n_hole_cards(holecards, 5);
}
void Deck::get_six_hole_cards(HoleCards &holecards)
{
	get_n_hole_cards(holecards, 6);
}

void Deck::get_seven_hole_cards(HoleCards &holecards)
{
	get_n_hole_cards(holecards, 7);
}

void Deck::get_eight_hole_cards(HoleCards &holecards)
{
	get_n_hole_cards(holecards, 8);
}

void Deck::get_nine_hole_cards(HoleCards &holecards)
{
	get_n_hole_cards(holecards, 9);
}

void Deck::get_sangong_hole_cards(HoleCards &holecards)
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
				holecards.add_card(card1);
				holecards.add_card(card2);
				holecards.add_card(card3);
				delete_cards(holecards.cards);
				return;
			}
		}
	}
	get_hole_cards(holecards);
}
void Deck::get_baozi_hole_cards(HoleCards &holecards)
{
	for (unsigned int i = 0; i < cards.size(); i++)
	{
		Card card1 = cards[i];
		for (unsigned int j = i + 1; j < cards.size(); j++)
		{
			Card card2 = cards[j];
			if (card2.face != card1.face)
				continue;
			for (unsigned int k = j + 1; k < cards.size(); k++)
			{
				Card card3 = cards[k];
				if (card3.face != card2.face)
					continue;
				holecards.add_card(card1);
				holecards.add_card(card2);
				holecards.add_card(card3);
				delete_cards(holecards.cards);
				return;
			}
		}
	}
	get_hole_cards(holecards);
}

void Deck::get_333_hole_cards(HoleCards &holecards)
{
	for (unsigned int i = 0; i < cards.size(); i++)
	{
		Card card1 = cards[i];
		if (card1.face != 3)
			continue;
		for (unsigned int j = i + 1; j < cards.size(); j++)
		{
			Card card2 = cards[j];
			if (card2.face != 3)
				continue;
			for (unsigned int k = j + 1; k < cards.size(); k++)
			{
				Card card3 = cards[k];
				if (card3.face != 3)
					continue;
				holecards.add_card(card1);
				holecards.add_card(card2);
				holecards.add_card(card3);
				delete_cards(holecards.cards);
				return;
			}
		}
	}
	get_hole_cards(holecards);
}


void Deck::delete_cards(std::vector<Card> &tmp)
{
	for (std::vector<Card>::iterator it = cards.begin(); it != cards.end();)
	{
		if (it->value == tmp[0].value || it->value == tmp[1].value
			|| it->value == tmp[2].value)
		{
			it = cards.erase(it);
		}
		else
		{
			it++;
		}
	}
}

bool  Deck::has_hole_cards()
{
    if (count() < 3)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Deck::set_bao_zi(bool enable)
{
	bao_zi_enable = enable;
}

void Deck::set_bao_san(bool enable)
{
	bao_san_enable = enable;
}

void Deck::debug()
{
	Card::dump_cards(cards);
}
