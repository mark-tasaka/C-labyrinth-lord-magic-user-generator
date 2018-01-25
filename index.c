# define _CRT_SECURE_NO_WARNINGS

/*Created to for security and to avoid magic numbers*/
#define ARRAY_SIZE 250
#define ARRAY_SIZE_SMALL 5

/*
Magic User Generator - Labyrinth Lord
Labyrinth Lord is a product to Goblinoid Games
Generator Designed by Mark Tasaka, 2018
*/

/*Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*Function Prototypes*/
unsigned generateAbilityScores();
int abilityModifier(unsigned abilityScore);
char* addSign(int modifier);
unsigned generateHitPoints(int conModifier);
unsigned startingWealth();
int baseAC(int dexMod);
unsigned thaco(int modifier);
char* primeReqBonus(unsigned intelligence);
int modifiedArmourClass(int acBase);
char* reactionMorale(unsigned charisma);


/*Main - program entry*/
int main(void)
{
	/*Holds the Magic-User's name*/
	char magicUserName[ARRAY_SIZE];

	/*Holds the Magic-User's alignment*/
	char alignment[ARRAY_SIZE] = "";

	/*The core ability scores*/
	unsigned strength = 0;
	unsigned dexterity = 0;
	unsigned constitution = 0;
	unsigned intelligence = 0;
	unsigned wisdom = 0;
	unsigned charisma = 0;

	/*Ability Score modifiers*/
	int strModifier = 0;
	int dexModifier = 0;
	int conModifier = 0;
	int intModifier = 0;
	int wisModifier = 0;
	int charModifier = 0;

	/*Modifer Signs*/
	char strSign[ARRAY_SIZE_SMALL] = "";
	char dexSign[ARRAY_SIZE_SMALL] = "";
	char conSign[ARRAY_SIZE_SMALL] = "";
	char intSign[ARRAY_SIZE_SMALL] = "";
	char wisSign[ARRAY_SIZE_SMALL] = "";
	char charSign[ARRAY_SIZE_SMALL] = "";


	/*Saving throws*/
	unsigned breathAttacks = 16;
	unsigned poisonDeath = 13;
	unsigned petrifyParalyze = 13;
	unsigned wands = 13;
	unsigned spells = 14;

	/*hit points*/
	unsigned hitPoints;

	/*Armour Class without Armour*/
	int armourClassBase;

	/*Armour Class with Armour*/
	int acModified;

	/*THACO for melee and ranged attacks*/
	unsigned meleeTHACO;
	unsigned rangeTHACO;

	/*prime requisite bonus*/
	char primeRequisiteBonus[ARRAY_SIZE] = "";

	/*reaction, morale and retainers*/
	char charismaReaction[ARRAY_SIZE] = "";

	/*starting gold*/
	unsigned gold;

	/*For yes and no values*/
	int noYes = 0;

	/*For Weapons and Gear*/
	int choice = 0;

	/*Temporarly used to store item expense*/
	int expense = 0;

	/*temporarly used to store armour value*/
	int armourValue = 0;

	/*Stores weapons*/
	char weapons[ARRAY_SIZE] = "";

	/*Stores gear*/
	char gear[ARRAY_SIZE] = "Spellbook, ";


	/*Save file name*/
	char saveFile[ARRAY_SIZE] = "";

	/*Introduction text*/
	printf_s("Welcome to the Labyrinth Lord Magic-User Generators.\n", ARRAY_SIZE);

	/*prompt user to enter Magic-User's name*/
	printf_s("\nEnter the name of your Magic-User: \n", ARRAY_SIZE);

	scanf_s("%[^\n]s", magicUserName, ARRAY_SIZE);

	/*displays the name user entered*/
	printf_s("\nThe name you entered is: %s\n", magicUserName, ARRAY_SIZE);

	printf_s("\nDo you want to keep this name?\n1. Yes\n2. No\n(select 1 (yes) or 2 (no))\n", ARRAY_SIZE);

	scanf("%d", &noYes);

	while (noYes != 1)
	{
		/*initalize noYes back to 0*/
		noYes = 0;

		printf_s("\nEnter the name of your Magic-User: \n", ARRAY_SIZE);

		scanf_s(" %[^\n]s", magicUserName, ARRAY_SIZE);

		printf_s("\nThe name you entered is: %s\n", magicUserName, ARRAY_SIZE);

		printf_s("\nDo you want to keep this name?\n1. Yes\n2. No\n(select 1 or 2)\n", ARRAY_SIZE);

		scanf(" %d", &noYes);

	}

	do {

		noYes = 0;

		printf_s("\nSelect an alignment:\n1. Lawful\n2. Neutral\n3. Chaotic\n(please select 1, 2 or 3)\n", ARRAY_SIZE);

		scanf(" %d", &choice);

		switch (choice)
		{
		case 1:
			strcpy(alignment, "Lawful");
			break;

		case 2:
			strcpy(alignment, "Neutral");
			break;

		case 3:
			strcpy(alignment, "Chaotic");
			break;

		default:
			printf_s("\nPlease enter 1 (lawful), 2 (neutral) or 3 (chaotic).\n", ARRAY_SIZE);
			break;
		}

		printf_s("\nDo you want to keep this alignment (%s)?\n1. Yes\n2. No\n(please enter 1 (yes) or 2 (no))\n", alignment, ARRAY_SIZE);

		scanf(" %d", &noYes);

	} while (noYes == 2);


	/*From t class to allow for randomization*/
	time_t t;

	do {

		noYes = 0;

		/* Intializes random number generator */
		srand((unsigned)time(&t));

		strength = generateAbilityScores();
		dexterity = generateAbilityScores();
		constitution = generateAbilityScores();
		intelligence = generateAbilityScores();

		/*if statement used to ensure intelligence is minimum of 9 as magicUser
		class requirement*/
		if (intelligence < 9)
		{
			intelligence = 9;
		}

		wisdom = generateAbilityScores();
		charisma = generateAbilityScores();

		strModifier = abilityModifier(strength);
		dexModifier = abilityModifier(dexterity);
		conModifier = abilityModifier(constitution);
		intModifier = abilityModifier(intelligence);
		wisModifier = abilityModifier(wisdom);
		charModifier = abilityModifier(charisma);

		strcpy(strSign, addSign(strModifier));
		strcpy(dexSign, addSign(dexModifier));
		strcpy(conSign, addSign(conModifier));
		strcpy(intSign, addSign(intModifier));
		strcpy(wisSign, addSign(wisModifier));
		strcpy(charSign, addSign(charModifier));


		armourClassBase = baseAC(dexModifier);
		acModified = modifiedArmourClass(armourClassBase);

		hitPoints = generateHitPoints(conModifier);

		meleeTHACO = thaco(strModifier);
		rangeTHACO = thaco(dexModifier);


		strcpy(primeRequisiteBonus, primeReqBonus(intelligence));

		strcpy(charismaReaction, reactionMorale(charisma));

		gold = startingWealth();

		printf_s("\n**********LABRYNTH LORD: Character Record Sheet***********\n", ARRAY_SIZE);

		printf_s("\nName: %-15s              Class: Magic-User\n", magicUserName, ARRAY_SIZE);
		printf_s("Alignment: %-15s           Level: 1\n", alignment, ARRAY_SIZE);

		printf_s("Armour Class: %d (%d)            Hit Points: %u\n", acModified, armourClassBase, hitPoints, ARRAY_SIZE);

		printf_s("\nABILITY SCORES", ARRAY_SIZE);

		printf_s("\nSTR: %-3u  (%s%d)\n", strength, strSign, strModifier, ARRAY_SIZE);
		printf_s("DEX: %-3u  (%s%d)\n", dexterity, dexSign, dexModifier, ARRAY_SIZE);
		printf_s("CON: %-3u  (%s%d)\n", constitution, conSign, conModifier, ARRAY_SIZE);
		printf_s("INT: %-3u  (%s%d)\n", intelligence, intSign, intModifier, ARRAY_SIZE);
		printf_s("WIS: %-3u  (%s%d)\n", wisdom, wisSign, wisModifier, ARRAY_SIZE);
		printf_s("CHA: %-3u  (%s%d)\n", charisma, charSign, charModifier, ARRAY_SIZE);


		printf_s("\nSAVING THROWS\n", ARRAY_SIZE);
		printf_s("%u vs Breath Attacks\n", breathAttacks, ARRAY_SIZE);
		printf_s("%u vs Posion or Death\n", poisonDeath, ARRAY_SIZE);
		printf_s("%u vs Petrify or Paralyze\n", petrifyParalyze, ARRAY_SIZE);
		printf_s("%u vs Breath Attacks\n", wands, ARRAY_SIZE);
		printf_s("%u vs Posion or Death\n", spells, ARRAY_SIZE);


		printf_s("\nTHACO (melee): %u                THACO (range): %u", meleeTHACO, rangeTHACO, ARRAY_SIZE);
		printf_s("\nWEALTH: %u gold\n", gold, ARRAY_SIZE);
		printf_s("SPELLS: 1 Level Spell\n", ARRAY_SIZE);
		printf_s("WEAPONS: %s\n", weapons, ARRAY_SIZE);
		printf_s("GEAR: %s\n", gear, ARRAY_SIZE);

		printf_s("\nNotes: %s%s", primeRequisiteBonus, charismaReaction, ARRAY_SIZE);
		    
		printf_s("\n***********************************************************\n", ARRAY_SIZE);

		printf_s("\nDo you want to keep these stats?\n1.yes\n2.no\n(please enter 1 (yes) or 2 (no))\n", ARRAY_SIZE);

		scanf(" %d", &noYes);

	} while (noYes == 2);


	printf_s("\nYou have %u gold pieces (gp) to spend on your Magic-User.  Now it is time to buy some weapons and gear.\n\n", gold, ARRAY_SIZE);

	/*
	do
	{
		printf_s("Gold: %u    AC:%d      Armour: %s\n", gold, acModified, armour, ARRAY_SIZE);

		printf_s("\nARMOUR          Cost      AC Adj\n", ARRAY_SIZE);

		printf_s("1. Leather          6 gp      -1\n", ARRAY_SIZE);
		printf_s("2. Studded Leather  30 gp     -2\n", ARRAY_SIZE);
		printf_s("3. Scale mail       50 gp     -3\n", ARRAY_SIZE);
		printf_s("4. Chainmail        70 gp     -4\n", ARRAY_SIZE);
		printf_s("5. Splint Mail      75 gp     -5\n", ARRAY_SIZE);
		printf_s("6. No Armour\n", ARRAY_SIZE);
		printf_s("Please select 1 to 6\n", ARRAY_SIZE);

		scanf(" %d", &choice);

		switch (choice)
		{
		case 1:
			if (gold > 6)
			{
				expense = 6;
				gold -= expense;
				strcpy(armour, "Leather");
				armourValue = 1;
				acModified -= armourValue;
				printf_s("\nYou have purchased Leather Armour\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for the armour\n", ARRAY_SIZE);
			}

			break;

		case 2:
			if (gold > 30)
			{
				expense = 30;
				gold -= expense;
				strcpy(armour, "Studded Leather");
				armourValue = 2;
				acModified -= armourValue;
				printf_s("\nYou have purchased Studded Leather Armour\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for the armour\n", ARRAY_SIZE);
			}

			break;

		case 3:
			if (gold > 50)
			{
				expense = 50;
				gold -= expense;
				strcpy(armour, "Scale mail");
				armourValue = 3;
				acModified -= armourValue;
				printf_s("\nYou have purchased Scale mail Armour\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for the armour\n", ARRAY_SIZE);
			}

			break;

		case 4:
			if (gold > 70)
			{
				expense = 70;
				gold -= expense;
				strcpy(armour, "Chainmail");
				armourValue = 4;
				acModified -= armourValue;
				printf_s("\nYou have purchased Chainmail Armour\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for the armour\n", ARRAY_SIZE);
			}

			break;

		case 5:
			if (gold > 75)
			{
				expense = 75;
				gold -= expense;
				strcpy(armour, "Splint mail");
				armourValue = 5;
				acModified -= armourValue;
				printf_s("\nYou have purchased Splint mail Armour\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for the armour\n", ARRAY_SIZE);
			}

			break;

		case 6:
			printf_s("\nYou have decided not to pruchase any armour\n", ARRAY_SIZE);
			break;

		default:
			printf_s("\nIncorrection selection. Please choose 1 to 6.\n", ARRAY_SIZE);

		}*/

		/*Displays current inventory and gold*/
/*
		printf_s("\nGold: %u    AC:%d (%d)      Armour: %s\n", gold, acModified, armourClassBase, armour, ARRAY_SIZE);

		printf_s("Would you like to keep the %s?\n1.yes\n2.no\n(please select 1 (yes) or 2 (no).\n", armour, ARRAY_SIZE);

		scanf(" %d", &noYes);

		if (noYes == 2)
		{
			gold += expense;
			acModified += armourValue;
			armourValue;
			strcpy(armour, "  ");

		}

		expense = 0;

	} while (noYes == 2);
	*/
	/*End of dowhile loop*/


	/*Displays added armour and updated gold*/
	//printf_s("\nGold: %u    AC:%d (%d)      Armour: %s\n", gold, acModified, armourClassBase, armour, ARRAY_SIZE);

	/*Option of purchasing a shield if magicUser has at least 10 gp*/
/*	if (gold >= 10)
	{
		noYes = 0;
		printf_s("Would you like to add a shield for 10 gp (AC -1)?\n1.yes\n2.no\n(please select 1 (yes) or 2 (no).\n", ARRAY_SIZE);
		scanf(" %d", &noYes);

		if (noYes == 1)
		{
			expense = 10;
			gold -= expense;
			strcat(armour, ", Shield");
			armourValue = 1;
			acModified -= armourValue;
			printf_s("\nYou have purchased a shield.\n", ARRAY_SIZE);

			printf_s("\nGold: %u    AC:%d (%d)      Armour: %s\n", gold, acModified, armourClassBase, armour, ARRAY_SIZE);
		}
	}
	*/

	//printf_s("\nNow, let's purchase some weapons for your magicUser.\n", ARRAY_SIZE);

	/*Function for adding weapons for magicUser*/
	do
	{
		choice = 0;

		printf_s("\nGold: %u\n", gold, ARRAY_SIZE);

		printf_s("\nWEAPON           Cost       Damage\n", ARRAY_SIZE);

		printf_s("1. Dagger           3 gp      1d4\n", ARRAY_SIZE);
		printf_s("2. Silver Dagger   25 gp      1d4\n", ARRAY_SIZE);
		printf_s("3. No Weapons\n", ARRAY_SIZE);
		printf_s("Please select 1 to 11\n", ARRAY_SIZE);

		scanf(" %d", &choice);

		switch (choice)
		{
		case 1:
			if (gold > 3)
			{
				expense = 3;
				gold -= expense;
				strcat(weapons, "Dagger");
				printf_s("\nYou have purchased a Dagger\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for the Dagger\n", ARRAY_SIZE);
			}

			break;

		case 2:
			if (gold > 30)
			{
				expense = 30;
				gold -= expense;
				strcat(weapons, "Silver Dagger");
				printf_s("\nYou have purchased a Silver Dagger\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for the Silver Dagger\n", ARRAY_SIZE);
			}

			break;

	

		case 3:
			printf_s("\nYou have decided not to purchase a weapon\n", ARRAY_SIZE);
			break;

		default:
			printf_s("\nIncorrect selection. Please choose 1 to 11.\n", ARRAY_SIZE);
			break;

		}


		printf_s("\nGold: %u\nWeapons: %s\n", gold, weapons, ARRAY_SIZE);
		noYes = 0;

		printf_s("\nWould you like to purchase another weapon?\n1.yes\n2.no\n(please select 1 (yes) or 2 (no).\n", ARRAY_SIZE);
		scanf(" %d", &noYes);

		if (noYes == 1)
		{
			strcat(weapons, ", ");
		}

	} while (noYes != 2);



	/*Function for adding gear for magicUser*/
	do
	{
		choice = 0;

		printf_s("\nGold: %u\n", gold, ARRAY_SIZE);

		printf_s("\nGear                     Cost\n", ARRAY_SIZE);

		printf_s("1. Backpack (empty)        2 gp\n", ARRAY_SIZE);
		printf_s("2. Crowbar                 2 gp\n", ARRAY_SIZE);
		printf_s("3. Flint & Steel           2 gp\n", ARRAY_SIZE);
		printf_s("4. Grappling Hook          1 gp\n", ARRAY_SIZE);
		printf_s("5. Lantern                 9 gp\n", ARRAY_SIZE);
		printf_s("6. Mirror (sm steel)      10 gp\n", ARRAY_SIZE);
		printf_s("7. Pick (miner's)          3 gp\n", ARRAY_SIZE);
		printf_s("8. 10 ft. Pole             1 gp\n", ARRAY_SIZE);
		printf_s("9. Rations (1 week)        2 gp\n", ARRAY_SIZE);
		printf_s("10. Torches (12)           1 gp\n", ARRAY_SIZE);
		printf_s("11. No Gear\n", ARRAY_SIZE);
		printf_s("Please select 1 to 11\n", ARRAY_SIZE);

		scanf(" %d", &choice);

		switch (choice)
		{
		case 1:
			if (gold > 2)
			{
				expense = 2;
				gold -= expense;
				strcat(gear, "Backpack (empty)");
				printf_s("\nYou have purchased a Backpack (empty)\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for the Backpack (empty)\n", ARRAY_SIZE);
			}

			break;

		case 2:
			if (gold > 2)
			{
				expense = 2;
				gold -= expense;
				strcat(gear, "Crowbar");
				printf_s("\nYou have purchased a Crowbar\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for the Crowbar\n", ARRAY_SIZE);
			}

			break;

		case 3:
			if (gold > 2)
			{
				expense = 2;
				gold -= expense;
				strcat(gear, "Flint & Steel");
				printf_s("\nYou have purchased Flint & Steel\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for Flint & Steel\n", ARRAY_SIZE);
			}

			break;

		case 4:
			if (gold > 1)
			{
				expense = 1;
				gold -= expense;
				strcat(gear, "Grappling Hook");
				printf_s("\nYou have purchased a Grappling Hook\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for the Grappling Hook\n", ARRAY_SIZE);
			}

			break;

		case 5:
			if (gold > 9)
			{
				expense = 9;
				gold -= expense;
				strcat(gear, "Lantern");
				printf_s("\nYou have purchased a Lantern\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for the Lantern\n", ARRAY_SIZE);
			}

			break;

		case 6:
			if (gold > 10)
			{
				expense = 10;
				gold -= expense;
				strcat(gear, "Mirror (sm steel)");
				printf_s("\nYou have purchased a Mirror (sm steel)\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for the Mirror (sm steel)\n", ARRAY_SIZE);
			}

			break;

		case 7:
			if (gold > 3)
			{
				expense = 3;
				gold -= expense;
				strcat(gear, "Pick (miner's)");
				printf_s("\nYou have purchased a Pick (miner's)\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for the Pick (miner's)\n", ARRAY_SIZE);
			}

			break;

		case 8:
			if (gold > 1)
			{
				expense = 1;
				gold -= expense;
				strcat(gear, "10 ft. Pole");
				printf_s("\nYou have purchased a 10 ft. Pole\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for the 10 ft. Pole\n", ARRAY_SIZE);
			}

			break;

		case 9:
			if (gold > 2)
			{
				expense = 2;
				gold -= expense;
				strcat(gear, "Rations (1 week)");
				printf_s("\nYou have purchased Rations (1 week)\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for Rations (1 week)\n", ARRAY_SIZE);
			}

			break;

		case 10:
			if (gold > 1)
			{
				expense = 1;
				gold -= expense;
				strcat(gear, "Torches (12)");
				printf_s("\nYou have purchased Torches (12)\n", ARRAY_SIZE);
			}
			else
			{
				printf_s("\nYou do not have enough gold for Torches (12)\n", ARRAY_SIZE);
			}

			break;

		case 11:
			printf_s("\nYou have decided not to purchase any items\n", ARRAY_SIZE);
			break;

		default:
			printf_s("\nIncorrect selection. Please choose 1 to 11.\n", ARRAY_SIZE);
			break;

		}

		printf_s("\nGold: %u\nGear: %s\n", gold, gear, ARRAY_SIZE);
		noYes = 0;

		printf_s("\nWould you like to purchase more gear?\n1.yes\n2.no\n(please select 1 (yes) or 2 (no).\n", ARRAY_SIZE);
		scanf(" %d", &noYes);

		if (noYes == 1)
		{
			strcat(gear, ", ");
		}

	} while (noYes != 2);

	printf_s("\nHere is an update of your Magic-User:\n", ARRAY_SIZE);

	printf_s("\n**********LABRYNTH LORD: Character Record Sheet***********\n", ARRAY_SIZE);

	printf_s("\nName: %-15s              Class: Magic-User\n", magicUserName, ARRAY_SIZE);
	printf_s("Alignment: %-15s       Level: 1\n", alignment, ARRAY_SIZE);

	printf_s("Armour Class: %d (%d)              Hit Points: %u\n", acModified, armourClassBase, hitPoints, ARRAY_SIZE);

	printf_s("\nABILITY SCORES", ARRAY_SIZE);

	printf_s("\nSTR: %-3u  (%s%d)\n", strength, strSign, strModifier, ARRAY_SIZE);
	printf_s("DEX: %-3u  (%s%d)\n", dexterity, dexSign, dexModifier, ARRAY_SIZE);
	printf_s("CON: %-3u  (%s%d)\n", constitution, conSign, conModifier, ARRAY_SIZE);
	printf_s("INT: %-3u  (%s%d)\n", intelligence, intSign, intModifier, ARRAY_SIZE);
	printf_s("WIS: %-3u  (%s%d)\n", wisdom, wisSign, wisModifier, ARRAY_SIZE);
	printf_s("CHA: %-3u  (%s%d)\n", charisma, charSign, charModifier, ARRAY_SIZE);


	printf_s("\nSAVING THROWS\n", ARRAY_SIZE);
	printf_s("%u vs Breath Attacks\n", breathAttacks, ARRAY_SIZE);
	printf_s("%u vs Posion or Death\n", poisonDeath, ARRAY_SIZE);
	printf_s("%u vs Petrify or Paralyze\n", petrifyParalyze, ARRAY_SIZE);
	printf_s("%u vs Breath Attacks\n", wands, ARRAY_SIZE);
	printf_s("%u vs Posion or Death\n", spells, ARRAY_SIZE);


	printf_s("\nTHACO (melee): %u                THACO (range): %u", meleeTHACO, rangeTHACO, ARRAY_SIZE);
	printf_s("\nWEALTH: %u gold\n", gold, ARRAY_SIZE);
	printf_s("SPELLS: 1 Level Spell\n", ARRAY_SIZE);
	printf_s("WEAPONS: %s\n", weapons, ARRAY_SIZE);
	printf_s("GEAR: %s\n", gear, ARRAY_SIZE);

	printf_s("\nNotes: %s%s", primeRequisiteBonus, charismaReaction, ARRAY_SIZE);

	printf_s("\n***********************************************************\n", ARRAY_SIZE);


	/*Saving File as a text file*/
	printf_s("\nDo you want to save your magicUser (%s) to a text files?\n1.yes\n2.no\n(please select 1 (yes) or 2 (no)\n", magicUserName, ARRAY_SIZE);

	scanf(" %d", &noYes);

	if (noYes == 1)
	{
		printf_s("\nPlease a name (no spaces, please) for the file you want to save the Magic-User's information to: ", ARRAY_SIZE);

		scanf_s(" %s", saveFile, ARRAY_SIZE);

		printf_s("\nYour data will be saved to %s\n", saveFile, ARRAY_SIZE);

		strcat(saveFile, ".txt");

		FILE *ptrFile;

		if ((ptrFile = fopen(saveFile, "w+")) == NULL)
		{
			printf_s("\nFile could not be created\n", ARRAY_SIZE);
		}
		else
		{
			fprintf_s(ptrFile, "\n**********LABRYNTH LORD: Character Record Sheet***********\n", ARRAY_SIZE);

			fprintf_s(ptrFile, "\nName: %-15s              Class: Magic-User\n", magicUserName, ARRAY_SIZE);
			fprintf_s(ptrFile, "Alignment: %-15s         Level: 1\n", alignment, ARRAY_SIZE);

			fprintf_s(ptrFile, "Armour Class: %d (%d)                Hit Points: %u\n", acModified, armourClassBase, hitPoints, ARRAY_SIZE);

			fprintf_s(ptrFile, "\nABILITY SCORES", ARRAY_SIZE);

			fprintf_s(ptrFile, "\nSTR: %-3u  (%s%d)\n", strength, strSign, strModifier, ARRAY_SIZE);
			fprintf_s(ptrFile, "DEX: %-3u  (%s%d)\n", dexterity, dexSign, dexModifier, ARRAY_SIZE);
			fprintf_s(ptrFile, "CON: %-3u  (%s%d)\n", constitution, conSign, conModifier, ARRAY_SIZE);
			fprintf_s(ptrFile, "INT: %-3u  (%s%d)\n", intelligence, intSign, intModifier, ARRAY_SIZE);
			fprintf_s(ptrFile, "WIS: %-3u  (%s%d)\n", wisdom, wisSign, wisModifier, ARRAY_SIZE);
			fprintf_s(ptrFile, "CHA: %-3u  (%s%d)\n", charisma, charSign, charModifier, ARRAY_SIZE);


			fprintf_s(ptrFile, "\nSAVING THROWS\n", ARRAY_SIZE);
			fprintf_s(ptrFile, "%u vs Breath Attacks\n", breathAttacks, ARRAY_SIZE);
			fprintf_s(ptrFile, "%u vs Posion or Death\n", poisonDeath, ARRAY_SIZE);
			fprintf_s(ptrFile, "%u vs Petrify or Paralyze\n", petrifyParalyze, ARRAY_SIZE);
			fprintf_s(ptrFile, "%u vs Breath Attacks\n", wands, ARRAY_SIZE);
			fprintf_s(ptrFile, "%u vs Posion or Death\n", spells, ARRAY_SIZE);


			fprintf_s(ptrFile, "\nTHACO (melee): %u                THACO (range): %u", meleeTHACO, rangeTHACO, ARRAY_SIZE);
			fprintf_s(ptrFile, "\nWEALTH: %u gold\n", gold, ARRAY_SIZE);
			fprintf_s(ptrFile, "SPELLS: 1 Level Spell\n", ARRAY_SIZE);
			fprintf_s(ptrFile, "WEAPONS: %s\n", weapons, ARRAY_SIZE);
			fprintf_s(ptrFile, "GEAR: %s\n", gear, ARRAY_SIZE);

			fprintf_s(ptrFile, "\nNotes: %s%s", primeRequisiteBonus, charismaReaction, ARRAY_SIZE);

			fprintf_s(ptrFile, "\n***********************************************************\n", ARRAY_SIZE);

		}


	}




	printf("Enter any number of Exit\n");
	scanf(" %d", &noYes);


	return 0;

}
/*End of Main*/

/*Randomly generates core statistic values
STR, DEX, CON, INT, WIS, CHA*/
unsigned generateAbilityScores()
{
	/*The number of dice rolled*/
	unsigned dice = 3;

	/*loop counter*/
	size_t counter = 0;

	/*holds the value for the Ability Score*/
	unsigned abilityScore = 0;

	for (; counter < dice; counter++)
	{

		abilityScore += rand() % 6 + 1;
	}

	return abilityScore;
}

int abilityModifier(unsigned abilityScore)
{
	int modifier = 0;

	if (abilityScore == 3)
	{
		modifier = -3;
	}
	else if (abilityScore >= 4 && abilityScore <= 5)
	{
		modifier = -2;
	}
	else if (abilityScore >= 6 && abilityScore <= 8)
	{
		modifier = -1;
	}
	else if (abilityScore >= 9 && abilityScore <= 12)
	{
		modifier = 0;
	}
	else if (abilityScore >= 13 && abilityScore <= 15)
	{
		modifier = 1;
	}
	else if (abilityScore >= 16 && abilityScore <= 17)
	{
		modifier = 2;
	}
	else if (abilityScore == 18)
	{
		modifier = 3;
	}

	return modifier;
}

/*Adds + sign if modifer is >= 0*/
char* addSign(int modifier)
{
	char sign[ARRAY_SIZE_SMALL] = "";

	if (modifier >= 0)
	{
		strcpy(sign, "+");
	}

	return sign;
}


/*Randomly generates the Magic-User's hit points
Constitution modifier is added to hp total*/
unsigned generateHitPoints(int conModifier)
{
	unsigned hitPoints = 1;

	hitPoints += rand() % 4;

	hitPoints + conModifier;

	if (hitPoints < 1)
	{
		hitPoints = 1;
	}

	return hitPoints;

}

/*randomly generates starting wealth which is 3d8 x 10 gold pieces.*/
unsigned startingWealth()
{
	unsigned gold = 0;
	unsigned diceRolled = 3;
	unsigned counter = 0;

	for (; counter < diceRolled; counter++)
	{
		gold += ((rand() % 8) * 10) + 10;

	}

	return gold;
}


/*Calculates the base armour class, which is 9 +/- the
dexterity modifier*/
int baseAC(int dexMod)
{
	int armourClass = 9;
	int armourClassAjustment = 0;

	armourClassAjustment = (dexMod * -1);

	armourClass += armourClassAjustment;

	return armourClass;
}

/*calculates THACO for melee attacks*/
unsigned thaco(int modifier)
{
	unsigned thaco = 19;
	thaco += (modifier * -1);

	return thaco;
}

/*displays the prime requisite bonus for magicUser*/
char* primeReqBonus(unsigned intelligence)
{
	char primeReq[ARRAY_SIZE] = " ";

	if (intelligence >= 13)
	{
		strcpy(primeReq, "\n+5% Experience Adjustment");
	}
	else if (intelligence >= 16)
	{
		strcpy(primeReq, "\n+10% Experience Adjustment");
	}

	return primeReq;
}

/*displays reaction adjustment, retainers and morale of retainers*/
char* reactionMorale(unsigned charisma)
{
	char reaction[ARRAY_SIZE] = "";

	if (charisma == 3)
	{
		strcpy(reaction, "\n+2 Reaction Adjustment; 1 (max) Retainer; Retainer Morale 4.");
	}
	else if (charisma >= 4 && charisma <= 5)
	{
		strcpy(reaction, "\n+1 Reaction Adjustment; 2 (max) Retainers; Retainer Morale 5.");
	}
	else if (charisma >= 6 && charisma <= 8)
	{
		strcpy(reaction, "\n+1 Reaction Adjustment; 3 (max) Retainers; Retainer Morale 6.");
	}
	else if (charisma >= 9 && charisma <= 12)
	{
		strcpy(reaction, "\n+0 Reaction Adjustment; 4 (max) Retainers; Retainer Morale 7.");
	}
	else if (charisma >= 13 && charisma <= 15)
	{
		strcpy(reaction, "\n-1 Reaction Adjustment; 5 (max) Retainers; Retainer Morale 8.");
	}
	else if (charisma >= 16 && charisma <= 17)
	{
		strcpy(reaction, "\n-1 Reaction Adjustment; 6 (max) Retainers; Retainer Morale 9.");
	}
	else
	{
		strcpy(reaction, "\n-2 Reaction Adjustment; 7 (max) Retainers; Retainer Morale 10.");
	}

	return reaction;
}

int modifiedArmourClass(int acBase)
{
	int modifiedAC = acBase;
	return modifiedAC;
}

