#include "card.h"
#include "deck.h"
#include "hole_cards.h"
#include <string.h>
#include <map>


map<string, int> cardmap;

static const char *card_type_str[] = 
{
	(char *)"CARD_TYPE_NONNIU",
	(char *)"CARD_TYPE_NIUDING",
	(char *)"CARD_TYPE_NIUER",
	(char *)"CARD_TYPE_NIUSAN",
	(char *)"CARD_TYPE_NIUSI",
	(char *)"CARD_TYPE_NIUWU",
	(char *)"CARD_TYPE_NIULIU",
	(char *)"CARD_TYPE_NIUQI",
	(char *)"CARD_TYPE_NIUBA",
	(char *)"CARD_TYPE_NIUJIU",
	(char *)"CARD_TYPE_NIUNIU",
    (char *)"CARD_TYPE_ZHADAN",
	(char *)"CARD_TYPE_JINNIU",	
	(char *)"CARD_TYPE_WUXIAONIU"
};

/**
 * suit  0  方块  1 梅花   2  红桃    3黑桃
 * 	
 0x01, 0x11, 0x21, 0x31, (1, 17, 33, 49)  //A 1
 0x02, 0x12, 0x22, 0x32, (2, 18, 34, 50)  //2 2
 0x03, 0x13, 0x23, 0x33, (3, 19, 35, 51)  //3 3
 0x04, 0x14, 0x24, 0x34, (4, 20, 36, 52)  //4 4
 0x05, 0x15, 0x25, 0x35, (5, 21, 37, 53)  //5 5
 0x06, 0x16, 0x26, 0x36, (6, 22, 38, 54)  //6 6
 0x07, 0x17, 0x27, 0x37, (7, 23, 39, 55)  //7 7
 0x08, 0x18, 0x28, 0x38, (8, 24, 40, 56)  //8 8
 0x09, 0x19, 0x29, 0x39, (9, 25, 41, 57)  //9 9
 0x0A, 0x1A, 0x2A, 0x3A, (10, 26, 42, 58) //10 10
 0x0B, 0x1B, 0x2B, 0x3B, (11, 27, 43, 59) //J 11
 0x0C, 0x1C, 0x2C, 0x3C, (12, 28, 44, 60) //Q 12
 0x0D, 0x1D, 0x2D, 0x3D, (13, 29, 45, 61) //K 13
 *
 */
void initCardMap()
{
    cardmap["方块A"] = 0x01;
    cardmap["梅花A"] = 0x11;
    cardmap["红桃A"] = 0x21;
    cardmap["黑桃A"] = 0x31;

    cardmap["方块2"] = 0x02;
    cardmap["梅花2"] = 0x12;
    cardmap["红桃2"] = 0x22;
    cardmap["黑桃2"] = 0x32;

    cardmap["方块3"] = 0x03;
    cardmap["梅花3"] = 0x13;
    cardmap["红桃3"] = 0x23;
    cardmap["黑桃3"] = 0x33;

    cardmap["方块4"] = 0x04;
    cardmap["梅花4"] = 0x14;
    cardmap["红桃4"] = 0x24;
    cardmap["黑桃4"] = 0x34;

    cardmap["方块5"] = 0x05;
    cardmap["梅花5"] = 0x15;
    cardmap["红桃5"] = 0x25;
    cardmap["黑桃5"] = 0x35;

    cardmap["方块6"] = 0x06;
    cardmap["梅花6"] = 0x16;
    cardmap["红桃6"] = 0x26;
    cardmap["黑桃6"] = 0x36;

    cardmap["方块7"] = 0x07;
    cardmap["梅花7"] = 0x17;
    cardmap["红桃7"] = 0x27;
    cardmap["黑桃7"] = 0x37;

    cardmap["方块8"] = 0x08;
    cardmap["梅花8"] = 0x18;
    cardmap["红桃8"] = 0x28;
    cardmap["黑桃8"] = 0x38;

    cardmap["方块9"] = 0x09;
    cardmap["梅花9"] = 0x19;
    cardmap["红桃9"] = 0x29;
    cardmap["黑桃9"] = 0x39;

    cardmap["方块10"] = 0x0A;
    cardmap["梅花10"] = 0x1A;
    cardmap["红桃10"] = 0x2A;
    cardmap["黑桃10"] = 0x3A;

    cardmap["方块J"] = 0x0B;
    cardmap["梅花J"] = 0x1B;
    cardmap["红桃J"] = 0x2B;
    cardmap["黑桃J"] = 0x3B;

    cardmap["方块Q"] = 0x0C;
    cardmap["梅花Q"] = 0x1C;
    cardmap["红桃Q"] = 0x2C;
    cardmap["黑桃Q"] = 0x3C;

    cardmap["方块K"] = 0x0D;
    cardmap["梅花K"] = 0x1D;
    cardmap["红桃K"] = 0x2D;
    cardmap["黑桃K"] = 0x3D;

}

void test()
{
    HoleCards hole_cards;
	HoleCards hole_cards1;

	Card card;
	card.set_value(cardmap["黑桃J"]);
	hole_cards.add_card(card);
	card.set_value(cardmap["红桃J"]);
	hole_cards.add_card(card);
	card.set_value(cardmap["梅花J"]);
	hole_cards.add_card(card);
	hole_cards.debug();

	card.set_value(cardmap["黑桃3"]);
	hole_cards1.add_card(card);
	card.set_value(cardmap["红桃3"]);
	hole_cards1.add_card(card);
	card.set_value(cardmap["梅花A"]);
	hole_cards1.add_card(card);
	hole_cards1.debug();

	
	int ret = hole_cards.compare(hole_cards1);

	printf("result[%d]\n", ret);
}


void test_card_type(Deck &deck, int count, int card_type)
{
	for (int i = 0; i < count; i++)
	{
		HoleCards hole_cards;
		switch (card_type)
		{
		case CARD_TYPE_ZERO:
			deck.get_hole_cards(hole_cards, card_type);
			break;
		case CARD_TYPE_ONE:
			deck.get_hole_cards(hole_cards, card_type);
			break;
		case CARD_TYPE_TWO:
			deck.get_hole_cards(hole_cards, card_type);
			break;
		case CARD_TYPE_THREE:
			deck.get_hole_cards(hole_cards, card_type);
			break;
		case CARD_TYPE_FOUR:
			deck.get_hole_cards(hole_cards, card_type);
			break;
		case CARD_TYPE_FIVE:
			deck.get_hole_cards(hole_cards, card_type);
			break;
		case CARD_TYPE_SIX:
			deck.get_hole_cards(hole_cards, card_type);
			break;
		case CARD_TYPE_SEVEN:
			deck.get_hole_cards(hole_cards, card_type);
			break;
		case CARD_TYPE_EIGHT:
			deck.get_hole_cards(hole_cards, card_type);
			break;
		case CARD_TYPE_NINE:
			deck.get_hole_cards(hole_cards, card_type);
			break;
		case CARD_TYPE_SANGONG:
			deck.get_hole_cards(hole_cards, card_type);
			break;
		case CARD_TYPE_BAOZI:
			deck.get_hole_cards(hole_cards, card_type);
			break;
		case CARD_TYPE_333:
			deck.get_hole_cards(hole_cards, card_type);
			break;
		default:
			deck.get_hole_cards(hole_cards);
			break;
		}
		printf("[%d] ", i);
		hole_cards.debug();
	}
}
int main(int argc, char *argv[])
{
	//initCardMap();
	//test();
	Deck deck;
	for (int i = 0; i < 2; i++)
	{
		deck.fill();
		deck.shuffle(1);
		//test_card_type(deck, 2, CARD_TYPE_ZERO);
		//test_card_type(deck, 2, CARD_TYPE_ONE);
		//test_card_type(deck, 2, CARD_TYPE_TWO);
		//test_card_type(deck, 2, CARD_TYPE_THREE);
		//test_card_type(deck, 2, CARD_TYPE_FOUR);
		test_card_type(deck, 2, CARD_TYPE_FIVE);
		//test_card_type(deck, 2, CARD_TYPE_NINE);
		//test_card_type(deck, 2, CARD_TYPE_SANGONG);
		//test_card_type(deck, 2, CARD_TYPE_BAOZI);
		//test_card_type(deck, 2, CARD_TYPE_333);
	}
	getchar();
	return 0;
}

