#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <ctime>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>
#include <sstream>

using namespace std;

string castEng[1000][4];
string costEng[50][2];
string costRom[50][2];
string foodEng[10][4];
string foodRom[10][4];
string costInDollars[50][2];
string foodRomanian[10][4], costRomanian[27][2];
int extraLastIndex;

void readInitialCast()
{
	ifstream initialCast;
    initialCast.open("wednesdayCast1Eng.csv");
    if(initialCast.fail())
    {
        cout << "error" << endl;
        exit(1);
	}
	
	for(int i = 0; i < 735; i ++)
	{
		getline(initialCast, castEng[i][0], ',');
		getline(initialCast, castEng[i][1], '\n');
	}
    initialCast.close();
    return;
}

int stoiRemade(string date)
{
	int number;
	stringstream container(date);
	container >> number;
	return number;
}

string ftosRemade(float number)
{
	stringstream container;
	container << number;
	string date = container.str();
	return date;
}

template <typename X>
X ceilTemplate(X value)
{
	if(value > int(value))
	{
		return (int(value) + 1);
	}
	else
	{
		if(value == int(value))
		{
			return value;
		}
	}
}

class CSV
{
	public:
		virtual void hello() = 0;
		friend class CSVRo;
};

class CSVRo
{
	public:
		void generateRomanianCSV(string costRom[27][2])
		{
			int index = 0, days[4] = {30, 45, 60, 100};
			char daysChar[3];
			for(int i = 0; i < 27; i ++)
			{
				if(i % 7 == 0)
				{
					itoa(days[index], daysChar, 10);
					costRom[i][0] = "Costuri pe " + string(daysChar) + " zile";
					index++;
				}
				if(i % 7 == 1)
				{
					costRom[i][0] = "Transport";
				}
				if(i % 7 == 2)
				{
					costRom[i][0] = "Cazare";
				}
				if(i % 7 == 3)
				{
					costRom[i][0] = "Machiaj";
				}
				if(i % 7 == 4)
				{
					costRom[i][0] = "Apa si mancare";
				}
				if(i % 7 == 5)
				{
					costRom[i][0] = "Inchiere spatiu";
				}
				if(i % 7 == 6)
				{
					costRom[i][0] = costInDollars[i][0];
				}
				costRom[i][1] = costInDollars[i][1];
			}
			
			ofstream wedCostRom;
		    wedCostRom.open("wednesdayCostRom.csv");
		    if (wedCostRom.fail())
		    {
		        cout << "error" << endl;
		        exit(1);
		    }
			for(int i = 0; i < 27; i++)
			{
				if(i % 7 != 6 && i % 7 != 0)
				{
					wedCostRom << costRom[i][0] << ",";
					wedCostRom << costRom[i][1] << "\n";
				}
				else
				{
					wedCostRom << costRom[i][0];
					wedCostRom << costRom[i][1] << "\n";
				}
			}
			wedCostRom.close();
		}
		void generateRomanianCSV(string foodRom[10][4])
		{
			string foodVegRom[3][3] = {{"Supa de rosii", "Supa de morcov prajit", "Supa de cartof dulce"}, {"Curry de ciuperci", "Tocana de legume", "Wellington vegetarian"}, {"Negresa", "Tort de banane", "Tarta de mere si prune"}};
			string foodAllRom[3][3] = {{"Supa de pui", "Supa de vita", "Supa de legume"}, {"Pizza tip lasagna", "Curcan bine-prajit", "Paste pesto cu pui"}, {"Tiramisu", "Mousse de ciocolata", "Creme Brulee"}};
			string foodPesRom[3][3] = {{"Supa de sparanghel si spanac", "Supa de fructe de mare", "Supa cremoasa de rosii si crab"}, {"Tocana de peste", "Placinta cu peste", "Lasagna creamoasa cu dovlecel"}, {"Briose cu afine", "Clatite cu zer", "Paine dulce cu banane si nuci"}};
			
			foodRom[0][0] = "Tipul de dieta";
			foodRom[0][1] = "Ziua 1";
			foodRom[0][2] = "Ziua 2";
			foodRom[0][3] = "Ziua 3";
			
			for(int i = 1; i < 10; i ++)
			{
				for(int j = 1; j < 4; j ++)
				{
					if(i < 4)
					{
						foodRom[i][j] = foodAllRom[i-1][j-1];
						foodRom[i][0] = "Apt sa manance orice";
					}
					else
					{
						if(i > 3 && i < 7)
						{
							foodRom[i][j] = foodVegRom[i-4][j-1];
							foodRom[i][0] = "Vegetarian";
						}
						else
						{
							if(i > 6 && i < 10)
							{
								foodRom[i][j] = foodPesRom[i-7][j-1];
								foodRom[i][0] = "Flexitarian";
							}
						}
					}
				}
			}
			
			ofstream menuRom;
		    menuRom.open("wednesdayMenuRom.csv");
		    if (menuRom.fail())
		    {
		        cout << "error" << endl;
		        exit(1);
		    }
			for(int i = 0; i < 10; i ++)
			{
				menuRom << foodRom[i][0] << ",";
				menuRom << foodRom[i][1] << ",";
				menuRom << foodRom[i][2] << ",";
				menuRom << foodRom[i][3] << "\n";
			}
			menuRom.close();	
		}
};

class Cost: public CSV
{
	public:
		//overriding
		void hello()
		{
			cout << "\nClass Cost is not abstract anymore.\n";
		}
		int calculateBusCost()
		{
			int busNumber = ceilTemplate<float>(extraLastIndex/50.0);
			/* for coming and leaving as well, so we double the amount */
			busNumber = busNumber * 2;
			int busCost = busNumber * 5680;
			return busCost;
		}
		int calculateMakeupCost()
		{
			int makeupCost = 0;
			int vIndex = 0, wIndex = 0, sIndex = 0, pIndex = 0, hIndex = 0;
			for(int i = 0; i < extraLastIndex; i ++)
			{
				if(castEng[i][2] == "vampire")
				{
					makeupCost += 230;
					vIndex++;
				}
				else
				{
					if(castEng[i][2] == "werewolf")
					{
						makeupCost += 555;
						wIndex++;
					}
					else
					{
						if(castEng[i][2] == "siren")
						{
							makeupCost += 345;
							sIndex++;
						}
						else
						{
							if(castEng[i][2] == "psychic")
							{
								makeupCost += 157;
								pIndex++;
							}
							else
							{
								if(castEng[i][2] == "human")
								{
									makeupCost += 55;
									hIndex++;
								}
							}
						}
					}
				}
			}
			return makeupCost;
		}
		int calculateFoodCost()
		{
			int foodCost = 0;
			int randomIndex;
			string dietType[3] = {"Not Picky", "Vegetarian", "Pescetarian"};
			for(int i = 0; i < extraLastIndex; i ++)
			{
				randomIndex = rand() % 3;
				castEng[i][3] = dietType[randomIndex];
				if(castEng[i][3] == "Not Picky")
				{
					foodCost += 40;
				}
				else
				{
					if(castEng[i][3] == "Vegetarian")
					{
						foodCost += 33;
					}
					else
					{
						if(castEng[i][3] == "Pescetarian")
						{
							foodCost += 46;
						}
					}
				}
			}

			int waterCost = ceilTemplate<int>(1 * extraLastIndex);
			waterCost = ceilTemplate<float>(waterCost/2.0)*6;
			int coffeeCost = ceilTemplate<float>(0.5 * extraLastIndex)*30;
			int juiceCost = ceilTemplate<float>(0.8 * extraLastIndex);
			juiceCost = ceilTemplate<float>(juiceCost/2.0)*8;
			int foodAndDrinksCost = foodCost + waterCost + coffeeCost + juiceCost;
			
			ofstream wedCast;
		    wedCast.open("wednesdayCast2Eng.csv");
		    if (wedCast.fail())
		    {
		        cout << "error" << endl;
		        exit(1);
		    }

			for(int i = 0; i < extraLastIndex; i ++)
            {
            	wedCast << castEng[i][0] << ",";    
//				wedCast << castEng[i][1] << ",";  
////				if(castEng[i][2] != "")
////				{
////					wedCast << castEng[i][2] << ","; 
////				}
////				wedCast << castEng[i][3] << "\n";  
				wedCast << castEng[i][1] << "\n";
			}
			wedCast.close();	
			return foodAndDrinksCost;			
		}
		int calculateHotelCost(int extraFirstIndex)
		{
			int hotelCost = ceilTemplate<float>(extraFirstIndex/2.0)*350 + ceilTemplate<float>((extraLastIndex - extraFirstIndex)/3.0)*420;
			return hotelCost;
		}
		int calculateCantacuzinoCost(int numberOfDays)
		{
			int discount = floor(numberOfDays/10);
			int cantacuzinoCost = 10000*numberOfDays;
			cantacuzinoCost -= discount * cantacuzinoCost / 100;
			return cantacuzinoCost;
		}
		void calculateCostInDollars()
		{	
			int costInt;
			float costFloat;
			string costString;
			for(int i = 0; i < 28; i ++)
			{
				costInDollars[i][0] = costEng[i][0];
				if(i % 7 > 0 && i % 7 < 6)
				{
					costInt = stoiRemade(costEng[i][1]);
					costFloat = float(costInt * 0.22);
					costString = ftosRemade(costFloat);
					costInDollars[i][1] = costString + "$";			
				}
			}
			
			ofstream wedCost;
		    wedCost.open("wednesdayCostEng.csv");
		    if (wedCost.fail())
		    {
		        cout << "error" << endl;
		        exit(1);
		    }
			for(int i = 0; i < 28; i++)
			{
				if(i % 7 != 6 && i % 7 != 0)
				{
					wedCost << costInDollars[i][0] << ",";
					wedCost << costInDollars[i][1] << "\n";
				}
				else
				{
					wedCost << costInDollars[i][0];
					wedCost << costInDollars[i][1] << "\n";
				}
			}
			wedCost.close();
		}
};

class Menu: public CSV
{
	public:
		//overriding
		void hello()
		{
			cout << "\nClass Menu is not abstract anymore.";
		}
		Menu()
		{
			cout << "\nMenu Object has been created. >>> constructor";
			
			string foodVeg[3][3] = {{"Tomato Soup", "Roasted Carrot Soup", "Sweet Potato Soup"}, {"Mushroom Curry", "Vegetable Stew", "Vegeterian Wellington"}, {"Brownies", "Banana Cake", "Plum and Appple Cobbler"}};
			string foodAll[3][3] = {{"Chicken Soup", "Beef Soup", "Vegetables Soup"}, {"Lasagna Flatbread", "Deep-fried Turkey", "Pesto Pasta with Chicken"}, {"Tiramisu", "Chocolate Mousse", "Creme Brulee"}};
			string foodPes[3][3] = {{"Asparagus and Spinach Soup", "Seafood Soup", "Creamy Tomato and Crab Soup"}, {"Fish Stew", "Fish Pie", "Creamy Courgette Lasagna"}, {"Blueberry Muffins", "Buttermilk Pancakes", "Sweet Banana and Walnut Loaf"}};
			
			foodEng[0][0] = "Diet type";
			foodEng[0][1] = "Day 1";
			foodEng[0][2] = "Day 2";
			foodEng[0][3] = "Day 3";
			
			for(int i = 1; i < 10; i ++)
			{
				for(int j = 1; j < 4; j ++)
				{
					if(i < 4)
					{
						foodEng[i][j] = foodAll[i-1][j-1];
						foodEng[i][0] = "Not picky";
					}
					else
					{
						if(i > 3 && i < 7)
						{
							foodEng[i][j] = foodVeg[i-4][j-1];
							foodEng[i][0] = "Vegetarian";
						}
						else
						{
							if(i > 6 && i < 10)
							{
								foodEng[i][j] = foodPes[i-7][j-1];
								foodEng[i][0] = "Pescetarian";
							}
						}
					}
				}
			}
			
			ofstream menu;
		    menu.open("wednesdayMenuEng.csv");
		    if (menu.fail())
		    {
		        cout << "error" << endl;
		        exit(1);
		    }
			for(int i = 0; i < 10; i ++)
			{
				menu << foodEng[i][0] << ",";
				menu << foodEng[i][1] << ",";
				menu << foodEng[i][2] << ",";
				menu << foodEng[i][3] << "\n";
			}
			menu.close();			
		}
		~Menu()
		{
			cout << "\nMenu Object has been deleted. >>> destructor";
		}
};

class Cast: public CSV
{
	private:
		int extraFirstIndex;
	public:
		//overriding
		void hello()
		{
			cout << "\nClass Cast is not abstract anymore.";
		}
		void setExtraIndex(int extraFirstIndex)
		{
			this->extraFirstIndex = extraFirstIndex;
		}
		int getExtraIndex()
		{
			return this->extraFirstIndex;
		}
		void assignMonster()
		{
			string monster[5] = {"vampire", "werewolf", "siren", "psychic", "human"};
			int randomIndex;
			for(int i = 0; i < extraLastIndex; i ++)
			{
				randomIndex = rand() % 5;
				if(castEng[i][1] == "extra" || castEng[i][1] == "actor")
				{
					castEng[i][2] = monster[randomIndex];
				}
			}
			
			ofstream wedCast;
		    wedCast.open("wednesdayCast2Eng.csv");
		    if (wedCast.fail())
		    {
		        cout << "error" << endl;
		        exit(1);
		    }
			for(int i = 0; i < extraLastIndex; i ++)
            {
            	wedCast << castEng[i][0] << ",";    
//				wedCast << castEng[i][1] << ",";  
//				wedCast << castEng[i][2] << "\n";  
				wedCast << castEng[i][1] << "\n";
			}
			wedCast.close();	
		}
};

class ExtraCast: public Cast
{
	public:
		int generateExtra(int extraFirstIndex)
		{
			string firstNameRandom[10] = {"Dragomir", "Neamtu", "Leon", "Partenie", "Silivestru", "Buraga", "Dumitrescu", "Micu", "Gradincia", "Corpaci"};
			string lastNameRandom[10] = {"Bia", "Crina", "Mina", "Marlena", "Sivi", "Andreea", "Denisa", "Roberta", "Roberto", "Luiza"};
			string firstNameExtra[132], lastNameExtra[132];
			int randomIndex, randomIndex2;
			int extraLastIndex = extraFirstIndex;
			for(int i = 0; i < 132; i ++)
			{
				randomIndex = rand() % 10;	
				randomIndex2 = rand() % 10;	
				firstNameExtra[i] = firstNameRandom[randomIndex];	
				lastNameExtra[i] = lastNameRandom[randomIndex2];	
				castEng[extraLastIndex][0] = firstNameExtra[i] + " " + lastNameExtra[i]; 
				castEng[extraLastIndex][1] = "extra";
				extraLastIndex++;
			}

			ofstream wedCast;
		    wedCast.open("wednesdayCast2Eng.csv");
		    if (wedCast.fail())
		    {
		        cout << "error" << endl;
		        exit(1);
		    }
			for(int i = 0; i < extraLastIndex; i ++)
            {
            	wedCast << castEng[i][0] << ",";    
				wedCast << castEng[i][1] << "\n";            	
			}
			wedCast.close();
			return extraLastIndex;			
		}
};

void checkUserResponse(int resp, string costForChosenLanguage[27][2])
{
	int possibleResponses[4] = {30, 45, 60, 100};
	int valid = 0;
	for(int i = 0; i < 4; i ++)
	{
		if(possibleResponses[i] == resp)
		{
			valid = resp;
		}
	}
	cout << endl;
	if(valid)
	{
		switch(resp)
		{
			case 30:
				for(int i = 0; i < 6; i ++)
				{
					cout << costForChosenLanguage[i][0] << "\t\t\t" << costForChosenLanguage[i][1] << endl; 
				}
				break;
			case 45:
				for(int i = 7; i < 13; i ++)
				{
					cout << costForChosenLanguage[i][0] << "\t\t\t" << costForChosenLanguage[i][1] << endl; 
				}
				break;
			case 60:
				for(int i = 14; i < 20; i ++)
				{
					cout << costForChosenLanguage[i][0] << "\t\t\t" << costForChosenLanguage[i][1] << endl; 
				}
				break;
			case 100:
				for(int i = 21; i < 27; i ++)
				{
					cout << costForChosenLanguage[i][0] << "\t\t\t" << costForChosenLanguage[i][1] << endl; 
				}
				break;
		}
	}
	else
	{
		throw "Error";
	}

}


int main()
{
	Cast cast;
	ExtraCast extraCast;
	Menu menu;
	Cost cost;
	
	cout << "\n\nDe-abstracting child classes of parent class(CSV)...";
	cast.hello();
	menu.hello();
	cost.hello();
	cast.setExtraIndex(735);
	
	readInitialCast();
	extraLastIndex = extraCast.generateExtra(cast.getExtraIndex());
	cast.assignMonster();
	
	int makeupCost = cost.calculateMakeupCost();
	int busCost = cost.calculateBusCost();
	int hotelCost = cost.calculateHotelCost(cast.getExtraIndex());
	int foodCost = cost.calculateFoodCost();
	char makeupCostString[10], busCostString[10], hotelCostString[10], cantacuzinoCostString[50], foodCostString[50];
	
	for(int i = 0; i < 4; i ++)
	{
		if(i == 0)
		{
			costEng[i*7][0] = "Expenses for a 30-days period of time";
			itoa(30 * makeupCost, makeupCostString, 10);
			costEng[i*7 + 3][1] = makeupCostString;
			itoa(30 * hotelCost, hotelCostString, 10);
			costEng[i*7 + 2][1] = hotelCostString;
			itoa(cost.calculateCantacuzinoCost(30), cantacuzinoCostString, 10);
			costEng[i*7 + 5][1] = cantacuzinoCostString;
			itoa(30 * foodCost, foodCostString, 10);
			costEng[i*7 + 4][1] = foodCostString;
		}
		else
		{
			if(i == 1)
			{
				costEng[i*7][0] = "Expenses for a 45-days period of time";
				itoa(45 * makeupCost, makeupCostString, 10);
				costEng[i*7 + 3][1] = makeupCostString;
				itoa(45 * hotelCost, hotelCostString, 10);
				costEng[i*7 + 2][1] = hotelCostString;
				itoa(cost.calculateCantacuzinoCost(45), cantacuzinoCostString, 10);
				costEng[i*7 + 5][1] = cantacuzinoCostString;
				itoa(45 * foodCost, foodCostString, 10);
				costEng[i*7 + 4][1] = foodCostString;
			}
			else
			{
				if(i == 2)
				{
					costEng[i*7][0] = "Expenses for a 60-days period of time";
					itoa(60 * makeupCost, makeupCostString, 10);
					costEng[i*7 + 3][1] = makeupCostString;
					itoa(60 * hotelCost, hotelCostString, 10);
					costEng[i*7 + 2][1] = hotelCostString;
					itoa(cost.calculateCantacuzinoCost(60), cantacuzinoCostString, 10);
					costEng[i*7 + 5][1] = cantacuzinoCostString;
					itoa(60 * foodCost, foodCostString, 10);
					costEng[i*7 + 4][1] = foodCostString;
				}
				else
				{
					if(i == 3)
					{
						costEng[i*7][0] = "Expenses for a 100-days period of time";
						itoa(100 * makeupCost, makeupCostString, 10);
						costEng[i*7 + 3][1] = makeupCostString;
						itoa(100 * hotelCost, hotelCostString, 10);
						costEng[i*7 + 2][1] = hotelCostString;
						itoa(cost.calculateCantacuzinoCost(100), cantacuzinoCostString, 10);
						costEng[i*7 + 5][1] = cantacuzinoCostString;
						itoa(100 * foodCost, foodCostString, 10);
						costEng[i*7 + 4][1] = foodCostString;
					}
				}
			}
		}
		costEng[i*7 + 1][0] = "Traveling";
		itoa(busCost, busCostString, 10);
		costEng[i*7 + 1][1] = busCostString;
		costEng[i*7 + 2][0] = "Housing";
		costEng[i*7 + 3][0] = "Make-up";
		costEng[i*7 + 4][0] = "Food and water";
		costEng[i*7 + 5][0] = "Castel renting";
		costEng[i*7 + 6][0] = " ";
	}
	
	cost.calculateCostInDollars();
	
	//here's the overloading
	CSVRo csvRo;
	string foodRomanian[10][4], costRomanian[27][2];
	csvRo.generateRomanianCSV(foodRomanian);
	csvRo.generateRomanianCSV(costRomanian);
	
	int response;
	string language;

	cout << "\nTastati 1 pentru Romana & Press 2 for English: ";
	cin >> language;
	try
	{
		if(stoiRemade(language) != 1 && stoiRemade(language) != 2)
		{
			throw "Wrong! Gresit!";
		}
	}
	catch(const char* msg)
	{
		cerr << endl << msg << endl;
	}	
	switch(stoiRemade(language))
	{
		case 1: 
			cout << "\nCe perioada de timp doriti sa verificati?\nRaspunsul dvs.: ";
			cin >> response;
			try
			{
				checkUserResponse(response, costRomanian);
			}
			catch(const char* msg)
			{
				cerr << msg << endl;
			}
			break;
		case 2: 
			cout << "\nWhat time period do you wish to check?\nYour response: ";
			cin >> response;
			try
			{
				checkUserResponse(response, costInDollars);
			}
			catch(const char* msg)
			{
				cerr << endl << msg << endl;
			}
			break;		
	}
	return 0;
}
