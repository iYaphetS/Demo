#include "card.h"
#include "card_type.h"
#include "hole_cards.h"

static const char *card_type_str[] = 
{
	(char *)"CARD_TYPE_ZERO",
	(char *)"CARD_TYPE_ONE",
	(char *)"CARD_TYPE_TWO",
	(char *)"CARD_TYPE_THREE",
	(char *)"CARD_TYPE_FOUR",
	(char *)"CARD_TYPE_FIVE",
	(char *)"CARD_TYPE_SIX",
	(char *)"CARD_TYPE_SEVEN",
	(char *)"CARD_TYPE_EIGHT",
	(char *)"CARD_TYPE_NINE",
	(char *)"CARD_TYPE_SANGONG",
	(char *)"CARD_TYPE_BAOZI",
    (char *)"CARD_TYPE_333"
};

HoleCards::HoleCards()
{
	cards.clear();
	card_type = 0;
	ratio = 0;

	bao_zi_enable = true;
	bao_san_enable = true;
}

void HoleCards::add_card(Card card)
{
	cards.push_back(card);
}

void HoleCards::sort()
{
	Card::sort_by_descending(cards);
}

void HoleCards::analysis()
{
    Card::sort_by_ascending(cards);
    kicker.set_value(cards[2].value);
	
	if (cards[0].face > 10)
	{
		gong = 3;
	} 
	else if (cards[1].face > 10)
	{
		gong = 2;
	}
	else if (cards[2].face > 10)
	{
		gong = 1;
	}
	else
	{
		gong = 0;
	}
	
	if (cards[0].face == cards[1].face &&
		cards[1].face == cards[2].face)
	{
		if (bao_san_enable && cards[0].face == 3)
		{
			card_type = CARD_TYPE_333;
			ratio = CARD_RATIO_333;
			return ;
		}
		if (bao_zi_enable)
		{
			card_type = CARD_TYPE_BAOZI;
			ratio = CARD_RATIO_BAOZI;
			return ;
		}
	}
	
	if (gong > 2)
	{
		card_type = CARD_TYPE_SANGONG;
		ratio = CARD_RATIO_SANGONG;
		return;
	}
	
	card_type = (cards[0].point + cards[1].point + cards[2].point) % 10;
	switch (card_type) 
	{
	case 0:
		card_type = CARD_TYPE_ZERO;
		ratio = CARD_RATIO_LESS;
		break;
	case 1:
		card_type = CARD_TYPE_ONE;
		ratio = CARD_RATIO_LESS;
		break;
	case 2:
		card_type = CARD_TYPE_TWO;
		ratio = CARD_RATIO_LESS;
		break;
	case 3:
		card_type = CARD_TYPE_THREE;
		ratio = CARD_RATIO_LESS;
		break;
	case 4:
		card_type = CARD_TYPE_FOUR;
		ratio = CARD_RATIO_LESS;
		break;
	case 5:
		card_type = CARD_TYPE_FIVE;
		ratio = CARD_RATIO_LESS;
		break;
	case 6:
		card_type = CARD_TYPE_SIX;
		ratio = CARD_RATIO_LESS;
		break;
	case 7:
		card_type = CARD_TYPE_SEVEN;
		ratio = CARD_RATIO_LESS;
		break;
	case 8:
		card_type = CARD_TYPE_EIGHT;
		ratio = CARD_RATIO_EIGHT;
		break;
	case 9:
		card_type = CARD_TYPE_NINE;
		ratio = CARD_RATIO_NINE;
		break;
	}
	return;
}

int HoleCards::compare(HoleCards &hc)
{
	if (card_type > hc.card_type)
		return 1;
	else if (card_type < hc.card_type)
		return -1;

	if (gong > hc.gong)
		return 1;
	else if (gong < hc.gong)
		return -1;

	if (kicker.face > hc.kicker.face)
		return 1;
	else if (kicker.face < hc.kicker.face)
		return -1;

	if (kicker.suit > hc.kicker.suit)
		return 1;
	else if (kicker.suit < hc.kicker.suit)
		return -1;

	return 0;
}

void HoleCards::copy_cards(std::vector<Card> &v)
{
	v = cards;
}

void HoleCards::copy_cards(std::vector<int> &v)
{
	for (unsigned int i = 0; i < cards.size(); i++)
	{
		v.push_back(cards[i].value);
	}
}

void HoleCards::debug()
{
	analysis();
	Card::dump_cards(cards);
	printf("cardtype: %s gong: %d ratio: %d\n", card_type_str[card_type], gong, ratio);
}
