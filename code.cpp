#include <iostream>
#include <cstdlib>

using namespace std;



class building
{

private:

	int* area;
	int totalFloors, totalApartments, totalRooms;



	//////////////////////////// Utility Functions //////////////////////////////



	////Gets the room areas from the user
	void getAreasOfRooms()
	{
		int roomPosition = 0;

		cout << "\nStoring the areas of the rooms in column major order.";
		cout << "\nInput areas for the rooms of the building :\n\n";
		//Column Major Order Offset Calculation
		for (int k = 0; k < totalRooms; ++k)
		{
			for (int j = 0; j < totalApartments; ++j)
			{
				for (int i = 0; i < totalFloors; ++i)
				{
					//Calculating the position where the room area is to be placed
					//in 1D Array (viz. Area)
					roomPosition = (k * totalApartments * totalFloors) + (j * totalFloors) + i;

					cout << "Enter the area of the room \""<<k+1<<"\" at apartment \""<<j+1<<"\" of floor \""<<i+1<<"\" : ";

					cin >> area[roomPosition];
				}
			}
		}

		cout << "\nThe areas have been entered successfully.\n";
	}



	//Copies the room areas from the old array to the newly created array
	//which has changed (new) dimensions
	void copyAreasToNewArray(int* temp, int nFloors, int nApartments)  //Here 'n' means "new" e.g "nFloors means New Floors"
	{
		int roomPosition, nRoomPosition = 0;

		int min_floors     = min (totalFloors,nFloors);
		int min_apartments = min (totalApartments,nApartments);

		//Column Major Order Offset Calculation

		for (int k = 0; k < totalRooms; ++k) //totalRooms in an appartment never changes.
		{
			for (int j = 0; j < min_apartments; ++j)
			{
				for (int i = 0; i < min_floors; ++i)
				{
					//Calculating Room Position for Old Array
					roomPosition  = (k * totalApartments * totalFloors) + (j * totalFloors) + i;

					//Calculating Room Position for New Array with Changed Dimensions
					nRoomPosition = (k * nApartments * nFloors) + (j * nFloors) + i;

					temp[nRoomPosition] = area[roomPosition];
				}
			}
		}
	}



public:

	//Overloaded Constructor for initializing the building dynamically
	//with given dimensions
	building (int floors,int appartments,int rooms)
	{
		totalFloors = floors;
		totalApartments = appartments;
		totalRooms = rooms;

		area = new int [totalFloors * totalApartments * totalRooms];

		getAreasOfRooms ();
	}



	//This functions adds a new floor in the building
	void addFloor (int **new_floor)
	{
		int* temp = new int [ (totalFloors + 1) * totalApartments * totalRooms ];

		//Copying the room areas of the old array to the
		//new array
		copyAreasToNewArray (temp, totalFloors+1, totalApartments);

		//Updating the Total Floors
		totalFloors = totalFloors + 1;

		int roomPosition = 0;

		//Copying the room areas of the newly made Floor to the
		//new array
		for (int k = 0; k < totalRooms; ++k)
		{
			for (int j = 0; j < totalApartments; ++j)
			{
				//Calculating the positions for the newly made Rooms
				roomPosition        = (k * totalApartments * totalFloors) + (j * totalFloors) + (totalFloors-1);

				temp [roomPosition] = new_floor[j][k];
			}
		}

		cout <<"\nThe floor has been added successfully.";

		delete[] area;
		area = temp;
	}



	//This function removes the top floor from the building
	bool removeTopFloor ()
	{
		if (totalFloors != 0)
		{	
			int* temp = new int [ (totalFloors-1) * totalApartments * totalRooms];

			copyAreasToNewArray (temp, totalFloors-1, totalApartments);

			//Updating the Total Floors
			totalFloors = totalFloors - 1;

			cout << "\nThe top floor \""<<totalFloors+1<<"\" has been removed successfully.";
			delete[] area;
			area = temp;

			return true;
		}
		else
			cout <<"\nCurrently the building has no floor.\n";

		return false;
	}



	//This functions adds a new apartment with 'r'
	//rooms to each floor
	bool expandEachFloor (int **new_apartment)
	{
		if(totalFloors != 0)
		{
			int* temp = new int [totalFloors * (totalApartments+1) * totalRooms];

			copyAreasToNewArray (temp, totalFloors, totalApartments+1);

			//Updating the Total Apartments
			totalApartments = totalApartments + 1;

			int roomPosition = 0;

			for (int k = 0; k < totalRooms; ++k)
			{
				for (int j = 0; j < totalFloors; ++j)
				{
					//Calculating the roomPosition for the newly expanded building
					roomPosition = (k * totalApartments * totalFloors) + ((totalApartments-1) * totalFloors) + j;

					temp[roomPosition] = new_apartment[j][k];
				}
			}

			cout << "\nThe building has been expanded successfully.";
			delete[] area;
			area = temp;

			return true;
		}
		else
			cout << "\nThe building has no floor. So it couldn't be expanded.";
		
		return false;
	}



	//Returns the specified room's area
	int getRoomArea(int currFloor, int currApartment, int currRoom)
	{
		int room_Area = -1;

		if (totalFloors != 0)
		{
			if ( (currFloor <= totalFloors && currFloor > 0) && (currApartment <= totalApartments && currApartment > 0) && (currRoom <= totalRooms && currRoom > 0))
				room_Area = area [ ((currRoom-1) * totalApartments * totalFloors) + ((currApartment-1) * totalFloors) + (currFloor-1)];	
		
			else
				cout << "\nThe input is not valid.";
		}

		else
		{
			cout << "\nThe building has no floor.";		
		}

		return room_Area;
	}


	//Sets the specified room's area
	void setRoomArea(int currFloor, int currApartment, int currRoom, int roomArea)
	{
		if (totalFloors != 0)
		{
			if ( (currFloor <= totalFloors && currFloor > 0) && (currApartment <= totalApartments && currApartment > 0) && (currRoom <= totalRooms && currRoom > 0))
			{
				area [ ((currRoom-1) * totalApartments * totalFloors) + ((currApartment-1) * totalFloors) + (currFloor-1)] = roomArea;	
				cout << "\nThe area has been successfully set.";
			}
			else
				cout << "\nThe input is not valid.";
		}

		else
			cout << "\nThe building has no floor.";
	}


	//Outputs the area of rooms of one floor in tabular format
	void outputEntireBuilding()
	{
		if(totalFloors != 0)
		{
			for (int i = 0; i < totalFloors; ++i)
			{
				cout <<"\nRoom Areas of Floor \""<<i+1<<"\" are :\n";

				for (int j = 0; j < totalApartments; ++j)
				{
					cout << "Appartment \""<<j+1<<"\" : ";

					for (int k = 0; k < totalRooms; ++k)
					{
						cout << area [(k * totalApartments * totalFloors) + (j * totalFloors) + i] << '\t';
					}	

					cout << endl;
				}
			}
		}

		else
			cout << "\nThe building has no floor.";
	}


	void printFunctions()
	{
		cout << "\n-------------------------------------------------------";
		cout << "\nBuilding class has the following functionality.\n";
		cout << "\n1) Add Floor";
		cout << "\n2) Remove Top Floor";
		cout << "\n3) Expand Each Floor";
		cout << "\n4) Get Room Area";
		cout << "\n5) Set Room Area";
		cout << "\n6) Output Entire Building";
		cout << "\n-------------------------------------------------------";
		cout << "\n\nChoose any option or enter '-1' to exit : ";
	}

	//Destructor
	~building()
	{
		if (area)
			delete[] area;
	}

};



//---------------------------------------------------------------------------------------------------------







void Driver()
{
	/////Driver/////

	int f,a,r;

    cout << "Enter the dimensions of the building : ";
	cout << "\nFloors : ";
	cin  >> f;
	cout << "Apartments : ";
	cin  >> a;
	cout << "Rooms : ";
	cin  >> r;

	building b1 (f,a,r);

	int userInput = 0;
	int currRoom = 0,currFloor = 0,currApartment = 0;

	int ** new_floor 	 = nullptr;
	int ** new_apartment = nullptr;

	while (userInput != -1)
	{
		b1.printFunctions();
		cin >> userInput;

		//////////////////////////////////Add Floor//////////////////////////////////////
		if(userInput == 1) 
		{
			//Creating the new floor
			
			new_floor = new int* [a];

			for (int i = 0; i < a; ++i)
				new_floor[i] = new int [r];
			
			//Initializng the new floor

			cout << "\nInput areas for the newly created floor : \n\n";

			for (int i = 0; i < r; ++i)
			{
				for (int j = 0; j < a; ++j)
				{
					cout << "Enter the area of the room \""<<i+1<<"\" at apartment \""<<j+1<<"\" of newly created floor : ";
					cin >> new_floor[j][i];
				}
			}

			//Adding the new floor
			b1.addFloor(new_floor);
			f = f + 1;


    		if (new_floor)
   		    {
    			//De allocating the new floor array because we don't need that anymore
				for (int i = 0; i < a; ++i)
				{
					delete [] new_floor[i];
				}

				delete[] new_floor;
				new_floor = nullptr;
    		}
		}

		//////////////////////////////////Remove Top Floor//////////////////////////////////////
		else if (userInput == 2)
    	{
    		if (b1.removeTopFloor())
    			f = f - 1;
    	}

    	//////////////////////////////////Expand Each Floor//////////////////////////////////////
    	else if (userInput == 3)
    	{
			new_apartment = new int* [f];

			for (int i = 0; i < f; ++i)
				new_apartment[i] = new int [r];

			//Initialing the new appartment
			for (int i = 0; i < r; ++i)
			{
				for (int j = 0; j < f; ++j)
				{
					cout << "Enter the area of the room \""<<i+1<<"\" of new apartment at floor \""<< j+1<<"\" : ";
					cin >> new_apartment[j][i];
				}
			}

			if( b1.expandEachFloor(new_apartment) )
				a = a + 1;

			if (new_apartment)
    		{
				for (int i = 0; i < f; ++i)
					delete [] new_apartment[i];

				delete[] new_apartment;	
				new_apartment = nullptr;
    		}
    	}


    	//////////////////////////////////Get Room Area//////////////////////////////////////
    	else if (userInput == 4)
    	{
    		cout << "\nWhich room area do you want to read ? \n";
			cout << "Floor Number : ";
			cin  >> currFloor;
			cout << "Apartment Number : ";
			cin  >> currApartment;
			cout << "Room Number  : ";
			cin  >> currRoom;

			if (b1.getRoomArea(currFloor,currApartment,currRoom) != -1)
				cout << "\n\nThe area of room \""<<currRoom<<"\" of apartment \""<<currApartment<<"\" of floor \""<<currFloor
	    			 << "\" is : \""<<b1.getRoomArea (currFloor,currApartment,currRoom) <<"\"";
	    }		 


	    //////////////////////////////////Set Room Area//////////////////////////////////////
    	else if (userInput == 5)
    	{
			cout << "\n\nWhich room area do you want to set ? \n";
			int  currArea = 0;
			cout << "Room Area : ";
			cin  >> currArea;
			cout << "Floor Number : ";
			cin  >> currFloor;
			cout << "Apartment Number : ";
			cin  >> currApartment;
			cout << "Room Number  : ";
			cin  >> currRoom;

			b1.setRoomArea (currFloor,currApartment,currRoom,currArea);
    	}
	

		//////////////////////////////////Output Entire Building//////////////////////////////////////
		else if (userInput == 6)
			b1.outputEntireBuilding();

		else if( userInput == -1)
   			cout << "\nExiting !!!";
		
		else
    		cout << "---Invalid Entry--- \nPlease choose from the Options below.\n ";
    }   
}




////////////////////Main/////////////////////////
int main()
{
	Driver();
	system("PAUSE");
	return 0;
}