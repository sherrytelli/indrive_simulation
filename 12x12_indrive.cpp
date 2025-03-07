//22k-4308
//22k-4422
//22k-4248

#include <iostream>
#include <bits/stdc++.h>
#include <windows.h>
#include <direct.h>
#include <iomanip>

using namespace std;
//some data shifted above for accessing iun customer class:
const int n = 12; // Number of locations
string Locations[n] = {"FAST", "Gulshan", "Defence", "Saddar", "Nazimabad", "Bahria Town", 
                       "Scheme 33", "PECHS", "Malir", "Korangi", "Gadap", "Lyari"}; // to store all locations

unordered_map<string, float> _map; // Map for our rides


class Ride;
class Driver;

class Customer {

    private:
    string fullname;
    int age;
    string phonenumber;
    list<Ride*> history; //using list as a stack
	vector<Driver*> ride_offer;
    
    /*the three function below will take pickup and dropoff from the book function. negotion will be
    done in the below fucntions. driver selection will also be done in the below fucntions. at the end of
    the fucntion the ride details will be appended at the end of the function to the file.*/
    void book_bike(string pickup, string dropoff,int cost);

    void book_car(string pickup, string dropoff,int cost);

    void book_rickshaw(string pickup, string dropoff,int cost);

    void only_5_in_queue();

    //calculating fares for bike car and rickshaw, a and b are indexes for distance matrix
	int calculate_cost(int choice,int a,int b){
		
		int fare;
		int base_fare=100;
		float distance=_map[Locations[a-1]+"*"+Locations[b-1]];
		switch(choice){
			case 1:
				fare=base_fare-50+(distance*15);	//25 rs per km and -50 for base fare of bike 
				return fare;
			break;
			case 2:
				fare=base_fare+(distance*50);	//50 rs per km and base fare of car
				return fare;
			break;
			case 3:
				fare=base_fare-30+(distance*35);	//35 rs per km and -30 base fare of rickshaw
				return fare;
			break; 
			default:
				
			break;	
		}
		return -1;
	}

    int validate_src_dest(string &option) {

        int converted;

        converted = atoi(option.c_str());

        while(converted < 1 || converted > 12) {

            cout << "\nWrong input. \n\nEnter again: ";
            cin >> option;
            converted = atoi(option.c_str());

        }

        return converted;

    }
    
    int validate_ride_type(string &option) {

        int converted;

        converted = atoi(option.c_str());

        while(converted < 1 || converted > 3) {

            cout << "\nWrong input. \n\nEnter again: ";
            cin >> option;
            converted = atoi(option.c_str());

        }

        return converted;

    }
    
    int validate_customer_amount(string option) {

        int converted;
        bool validated = false;
        bool again;

        while(validated == false) {

            again = false;

            for(int i = 0; i < option.length(); i++) {

                if((option[i] >= 'A' && option[i] <= 'Z') || (option[i] >= 'a' && option[i] <= 'z')) {
                    
                    cout << "\nWrong input. \n\nEnter again: ";
                    cin >> option;
                    again = true;
                    break;

                }

            }

            if(again == false) {

                validated = true;

            }

        }
        
        converted = atoi(option.c_str());
        return converted;

    }
    
    int validate_customer_driver_options(string option, int drivers_available) {

        int converted;
        bool validated = false;
        bool again;

        while(validated == false) {

            again = false;

            for(int i = 0; i < option.length(); i++) {

                if((option[i] >= 'A' && option[i] <= 'Z') || (option[i] >= 'a' && option[i] <= 'z')) {
                    
                    cout << "\nWrong input. \nEnter again: ";
                    cin >> option;
                    again = true;
                    break;

                }

            }

            converted = atoi(option.c_str());
            if(converted < -1 || converted > (drivers_available+1)) {

                cout << "\nWrong input. \nEnter again: ";
                cin >> option;
                again = true;

            }

            if(again == false) {

                validated = true;

            }

        }
        
        return converted;

    }

    public:

    /*when user will check his history, the fucntion will load the ride history from the file
    into the stack and then display the stack on the screen. this is done to save auxillary space
    because if the history is always loaded in the stack then memory will be wasted.*/
    void show_ride_history();

    /*in this function the customer will book ride. customer will choose pickip and dropoff. then
    estimated time and cost for bike, rickshaw and car will be given to customer. customer will
    choose his prefered ride type and then that ride type function will be called in which all the
    negotiaiton and finalization off the rides will be done.*/
    void book() {
		string dropoff,pickup;
        string input;
		int a,b, choice, min_bike, min_rickshaw, min_car;
		//taking pickup data
        system("cls");
		cout<< "Choose your pick-up location : "<<endl<<endl<<endl;
		for(int i=0;i<n;i++){
			cout<<i+1<<". "<<Locations[i]<<endl<<endl;
		}
		cout<<endl<<"\n\nEnter choice : ";
		cin >> input;
        a = validate_src_dest(input);
		pickup=Locations[a-1];
//		taking dropoff data
        system("cls");
        cout<< "Choose your drop-off location : "<<endl<<endl<<endl;
		for(int i=0;i<n;i++){
			cout<<i+1<<". "<<Locations[i]<<endl<<endl;
		}
		cout<<endl<<"\n\nEnter choice : ";
        cin >> input;
        b = validate_src_dest(input);
		dropoff=Locations[b-1];
		
        system("cls");
		//displaying fares for all categories
		min_bike = calculate_cost(1,a,b);
		min_car = calculate_cost(2,a,b);
		min_rickshaw = calculate_cost(3,a,b);
        cout << "\nEstimated fare for " << pickup << " - " << dropoff << endl << endl<<endl; 
		cout<<"1. Bike Fare : "<<min_bike << endl<<endl;
        cout<<"2. Rickshaw Fare : "<<min_rickshaw << endl<<endl;
		cout<<"3. Car Fare : "<<min_car << endl << endl<<endl;
		
		//select category
		cout<<"\nEnter the type of ride you want to take : ";
		cin>>input;
        choice = validate_ride_type(input);
        
		switch(choice){
			case 1:
				book_bike(pickup,dropoff, min_bike);
			break;
			case 2:
				book_rickshaw(pickup,dropoff, min_rickshaw);
			break;
			case 3:
				book_car(pickup,dropoff, min_car);
			break;	
			default:
				
			break;	
		}
    }
		
    void create_data_file(ofstream &filestream, string name, string number, int age) {

        this->fullname = name;
        this->age = age;
        this->phonenumber = number;

        filestream << this->age;

    }

    void restore_details(ifstream &filestream, string name, string number);

    void save_data();

    friend ostream& operator <<(ostream &out, const Ride *obj);
};

class Ride {

    private:
    string pickup;
    string dropoff;
    string driver_name;
    string ride_type;
    int cost;

    public:
    Ride(string pick, string drop, string drvr_name, string type, int cost) {

        this->pickup = pick;
        this->dropoff = drop;
        this->driver_name = drvr_name;
        this->ride_type = type;
        this->cost = cost;

    }  

    Ride(){

        this->pickup = "";
        this->dropoff = "";
        this->driver_name = "";
        this->ride_type = "";
        this->cost = 0;
    };

    //overlading << to display history stack directly using cout;
    friend ostream& operator <<(ostream &out, const Ride *obj);
    friend void Customer::restore_details(ifstream &filestream, string name, string number);
    friend void Customer::show_ride_history();
    friend void Customer::save_data();
};

class Driver {

    public:
    string fullname;
    float rating;
    string location;
    int return_offer;
    
    virtual int negotiation(int customer_amount, int avg_cost) = 0;
	
};

class Bike: public Driver {

    public:
    	//construter
    Bike(string name,float r, string l){
    	fullname=name;
    	rating=r;
    	location=l;
    	return_offer=0;
	}	
    //bike driver can only add between 20-40 rupees
    int negotiation(int customer_amount, int avg_cost) {

        int offer;

        if(customer_amount >= (avg_cost + 30)) {
					
			return_offer = customer_amount;
            return customer_amount;

        }

        offer = avg_cost + (20 + (rand() % 21));
		
		return_offer = offer;
        return offer;

    }

};

class Car: public Driver {

    public:
    		//construter
    Car(string name,float r, string l){
    	fullname=name;
    	rating=r;
    	location=l;
    	return_offer=0;
	}
    //car driver can only add between 80-150 rupees
    int negotiation(int customer_amount, int avg_cost) {

        int offer;

        if(customer_amount >= (avg_cost + 115)) {
			
			return_offer =customer_amount;
            return customer_amount;

        }

        offer = avg_cost + (80 + (rand() % 71));
		
		return_offer = offer;
        return offer;

    }

};

class Rickshaw: public Driver {

    public:
    	//construter
    Rickshaw(string name,float r, string l){
    	fullname=name;
    	rating=r;
    	location=l;
    	return_offer=0;
	}
	//richshaw driver can only add between 40-80 rupees
    int negotiation(int customer_amount, int avg_cost) {

        int offer;

        if(customer_amount >= (avg_cost + 65)) {
			
			return_offer = customer_amount;
            return customer_amount;

        }

        offer = avg_cost + (40 + (rand() % 41));
		
		return_offer = offer;
        return offer;

    }
};

void Customer::restore_details(ifstream &filestream, string name, string number) {

    stringstream buffer;
    string stemp;

    this->fullname = name; 
    getline(filestream, stemp);
    buffer << stemp;
    buffer >> age;
    this->phonenumber = number;

    while(!filestream.eof()) {

        Ride *temp = new Ride();

        getline(filestream, temp->pickup);
        getline(filestream, temp->dropoff);
        getline(filestream, temp->driver_name);
        getline(filestream, temp->ride_type);
        getline(filestream, stemp);
        buffer.clear();
        buffer << stemp;
        buffer >> temp->cost;

        history.push_back(temp);

    }

}

void Customer::show_ride_history() {
    
    if(history.empty()) {

        return;
    }

    list<Ride*>::iterator end = history.end();
    end--;

    list<Ride*>::iterator start = history.begin();
    start--;

    Ride *temp;
    for(end; end != start; end--) {

        temp = *end;

        cout << temp;

    }

}

//drivers avaliable at the specific location vector
vector<Bike*> bike_drivers;
vector<Car*> car_drivers;
vector<Rickshaw*> rickshaw_drivers;

/*the code for the central lists and mashmaps will be put here after the classes. */

/*used to get the shortest distances from everynode to everynode. Also used to store all the hashes
and their locations in the hashtable.*/
void floyd_warshall() {
	//distance matrix decalaration to use that in book ride function
	const float INF = 1000000007;
	
	float Distance_Matrix[n][n] =  {{0, 20.8, 26.9, 26.8, 28.6, 31.6, 40.9, 25.3, 10.7, 15.6, 43.5, 31.7},                                                                  
                                    {20.8, 0, 16, 13, 13, INF, 9.0, 10.6, 17.1, 14.8, 12.9 ,12.3},
                                    {26.9, 16, 0, 4, INF, INF, 27.8, 6.0, 24.4 ,10.6, 27.1, 7.2},
                                    {26.8, 13, 4, 0, 6.3, INF, 25.2, 8.4, 23.6, 13.2, 23.1, 4.6},
                                    {28.6, 13, INF, 6.3, 0, 38, 19.1, 12.5, 23.0, 16.7, 20.2, 7.3},
                                    {31.6, INF, INF, INF, 38, 0, 31.2, 43.3, 26.1, 44.1, 34.1, 45.7},
                                    {40.9, 9.0, 27.8, 25.2, 19.1, 31.2, 0, 19.8, 17.1, 24.0, 8.7, 20.3},
                                    {25.3, 10.6, 6.0, 8.4, 12.5, 43.3, 23.4, 0, 20.6, 10.3, 24.6, 7.3},
                                    {10.7, 17.1, 24.4, 23.6, 23.0, 26.1, 17.5, 18.1, 0, 14.7, 22.7, 27.2},
                                    {15.6, 14.8, 10.6, 13.2, 16.7, 44.1, 27.9, 8.4, 14.0, 0, 29.1, 15.7},
                                    {43.5, 12.9, 27.1, 23.1, 20.2, 23.8, 7.6, 24.9, 27.5, 29.1, 0, 22.2},
                                    {31.7, 12.3, 7.2, 4.6, 7.3, 45.7, 20.3, 7.3, 27.2, 15.7, 22.2, 0}};
	

    for (int k = 0; k < n; k++) { // index of node considered for shortest path.

        for (int i = 0; i < n; i++) {   // iterate over matrix

            for (int j = 0; j < n; j++) {
               
                if(Distance_Matrix[i][j] > (Distance_Matrix[i][k] + Distance_Matrix[k][j]) && Distance_Matrix[i][k] != INF && Distance_Matrix[k][j] != INF) {

                   
                    Distance_Matrix[i][j] = Distance_Matrix[i][k] + Distance_Matrix[k][j];

                }

            }
        }
    }

    for (int i = 0; i < n; i++) {

        string Source_Location = Locations[i]; // hold the Source of the trip

        for (int j = 0; j < n; j++) {

            if(i == j)   // Dont want to map on the same location.
                continue;

            string Destination_Location = Locations[j];

            float distance = Distance_Matrix[i][j];

            string hash_make = Source_Location + "*" + Destination_Location;
            _map[hash_make] = distance; // create graph by adding edges
        }  
    }

}

void Customer :: book_bike (string pickup, string dropoff,int cost) {
		
		int choice;
		Driver* temp;
        int size = bike_drivers.size();
		//1.drivers check in the location and display and select
		for(int i=0;i<size;i++){
			temp=bike_drivers[i];
			if(temp->location==pickup){
				ride_offer.push_back(temp);
			}
		}

		int customer_amount;
        string input;
        cout << endl << endl << "Booking bike!" << endl;
		cout<<"\nEnter your desire amount : ";
		cin>>input;
        customer_amount = validate_customer_amount(input);
		while(customer_amount<cost-30){
            cout<<"\nInvalid amount! \n\nEnter your amount again : ";
			cin>>input;
            customer_amount = validate_customer_amount(input);
		}
		int random;
        
        if(ride_offer.empty()) {

            system("cls");
            cout << "No drivers available near you at the moment. \nPlease try agian later :(";
            system("pause");

        }else {
            do{
                system("cls");
                cout << "Your offer: " << customer_amount << endl;
                cout << "--------------------------" << endl << endl;
                cout << "Drivers available: " << endl << endl;
                random=-1+(rand()%ride_offer.size());
                for(int i=0;i<=random;i++){
                    temp=ride_offer[i];
                    
                    cout<<i+1<<". Driver Name : "<<temp->fullname<<endl;
                    cout<<"   Driver Rating : "<< setprecision(2) << temp->rating<<endl;
                    cout<<"   Offer : "<<temp->negotiation(customer_amount,cost) <<endl << endl;
                    
                }
                cout << "--------------------------" << endl;
                cout<<"\n 0. Re-Offer"<<endl;
                cout<<"-1. Add 5 Rupees."<<endl;
                cout<<"\nEnter choice : "<<endl;
                cin>>input;
                choice = validate_customer_driver_options(input, random);

                if(choice == -1) {

                    customer_amount = customer_amount + 5;

                }
            }while(choice<=0);
            
            system("cls");
            temp=ride_offer[choice-1];

            cout << "Driver " + temp->fullname + " is comming" << endl;
            Sleep(2000);
            
            cout << endl << "Driver has arrived!!!" << endl; 
            Sleep(2000);
            cout << endl << "You have reached your destination!" << endl;
            Sleep(2000);

            //2.ride pointer object and push it in history

            Ride* r=new Ride(pickup, dropoff,temp->fullname,"Bike",temp->return_offer);
            history.push_back(r);
            
            temp->location=dropoff;
            
            //signature for writing final ride details in file.
            // ofstream outfile("data\\"+fullname+phonenumber+".txt", ios::app);
            // //3.input ride object details
            // outfile << endl <<pickup; //pickup //
            // outfile << endl <<dropoff;
            // outfile << endl <<temp->fullname;
            // outfile << endl <<"Bike";
            // outfile << endl <<temp->return_offer;
            // outfile.close();
        }

        ride_offer.clear();
        only_5_in_queue();
    }

void Customer ::  book_car(string pickup, string dropoff,int cost) {

    int choice;
    Driver* temp;
    int size = car_drivers.size();
    //1.drivers check in the location and display and select
    for(int i=0;i<size;i++){
        temp=car_drivers[i];
        if(temp->location==pickup){
            ride_offer.push_back(temp);
        }
    }
    int customer_amount;
    string input;
    cout << endl << endl << "Booking car!" << endl;
    cout<<"\nEnter your desire amount : ";
    cin>>input;
    customer_amount = validate_customer_amount(input);
    while(customer_amount<cost-30){
        cout<<"\nInvalid amount! \nEnter your amount again : ";
        cin>>input;
        customer_amount = validate_customer_amount(input);
    }
    int random;

    if(ride_offer.empty()) {

        system("cls");
        cout << "No drivers available near you at the moment. \nPlease try agian later";
        system("pause");

    }else {
        do{
            system("cls");
            cout << "Your offer: " << customer_amount << endl;
            cout << "--------------------------" << endl << endl;
            cout << "Drivers available: " << endl << endl;
            random=-1+(rand()%ride_offer.size());
            for(int i=0;i<=random;i++){
                temp=ride_offer[i];
                
                cout<<i+1<<". Driver Name : "<<temp->fullname<<endl;
                cout<<"   Driver Rating : "<< setprecision(2) << temp->rating<<endl;
                cout<<"   Offer : "<<temp->negotiation(customer_amount,cost) <<endl;
                
            }
            cout << "--------------------------" << endl;
            cout<<"\n 0. Re-Offer"<<endl;
            cout<<"-1. Add 5 Rupees."<<endl;
            cout<<"\nEnter choice : "<<endl;
            cin>>input;
            choice = validate_customer_driver_options(input, random);

            if(choice == -1) {

                customer_amount = customer_amount + 5;

            }
        }while(choice<=0);
        
        system("cls");
        temp=ride_offer[choice-1];

        cout << "Driver " + temp->fullname + " is comming" << endl;
        Sleep(2000);
        
        cout << endl << "Driver has arrived!!!" << endl; 
        Sleep(2000);
        cout << endl << "You have reached your destination!" << endl;
        Sleep(2000);

        //2.ride pointer object and push it in history

        Ride* r=new Ride(pickup, dropoff,temp->fullname,"Car",temp->return_offer);
        history.push_back(r);
        
        temp->location=dropoff;
        
        //signature for writing final ride details in file.
        // ofstream outfile("data\\"+fullname+phonenumber+".txt", ios::app);
        // //3.input ride object details
        // outfile << endl <<pickup; //pickup //
        // outfile << endl <<dropoff;
        // outfile << endl <<temp->fullname;
        // outfile << endl <<"Car";
        // outfile << endl <<temp->return_offer;
        // outfile.close();
    }

    ride_offer.clear();
    only_5_in_queue();
}

void Customer ::  book_rickshaw(string pickup, string dropoff,int cost) {
    
    int choice;
    Driver* temp;
    int size = rickshaw_drivers.size();
    //1.drivers check in the location and display and select
    for(int i=0;i<size;i++){
        temp=rickshaw_drivers[i];
        if(temp->location==pickup){
            ride_offer.push_back(temp);
        }
    }
    int customer_amount;
    string input;
    cout << endl << endl << "booking rickshaw!" << endl;
    cout<<"\nEnter your desire amount : ";
    cin>>input;
    customer_amount = validate_customer_amount(input);
    while(customer_amount<cost-30){
        cout<<"\nInvalid amount! \nEnter your amount again : ";
        cin>>input;
        customer_amount = validate_customer_amount(input);
    }
    int random;

    if(ride_offer.empty()) {

        system("cls");
        cout << "No drivers available near you at the moment. \n\nPlease try agian later";
        system("pause");

    }else {
        do{
            system("cls");
            cout << "Your offer: " << customer_amount << endl;
            cout << "--------------------------" << endl << endl;
            cout << "Drivers available: " << endl << endl;
            random=-1+(rand()%ride_offer.size());
            for(int i=0;i<=random;i++){
                temp=ride_offer[i];
                
                cout<<i+1<<". Driver Name : "<<temp->fullname<<endl;
                cout<<"   Driver Rating : "<< setprecision(2) << temp->rating<<endl;
                cout<<"   Offer : "<<temp->negotiation(customer_amount,cost) <<endl;
                
            }
            cout << "--------------------------" << endl;
            cout<<"\n 0. Re-Offer"<<endl;
            cout<<"-1. Add 5 Rupees."<<endl;
            cout<<"\nEnter choice : "<<endl;
            cin>>input;
            choice = validate_customer_driver_options(input, random);

            if(choice == -1) {

                customer_amount = customer_amount + 5;

            }
        }while(choice<=0);
        
        system("cls");
        temp=ride_offer[choice-1];

        cout << "Driver " + temp->fullname + " is comming" << endl;
        Sleep(2000);
        
        cout << endl << "Driver has arrived!!!" << endl; 
        Sleep(2000);
        cout << endl << "You have reached your destination!" << endl;
        Sleep(2000);

        //2.ride pointer object and push it in history

        Ride* r=new Ride(pickup, dropoff,temp->fullname,"Rickshaw",temp->return_offer);
        history.push_back(r);
        
        temp->location=dropoff;
        
        //signature for writing final ride details in file.
        // ofstream outfile("data\\"+fullname+phonenumber+".txt", ios::app);
        // //3.input ride object details
        // outfile << endl <<pickup; //pickup //
        // outfile << endl <<dropoff;
        // outfile << endl <<temp->fullname;
        // outfile << endl <<"Rickshaw";
        // outfile << endl <<temp->return_offer;
        // outfile.close();
    }

    ride_offer.clear();
    only_5_in_queue();
}

void Customer::only_5_in_queue() {

    Ride *temp;

    if(history.size() == 6) {

        temp = history.front();
        history.pop_front();

        delete temp;

    }

}

void Customer::save_data() {

    ofstream outfile("data\\"+fullname+phonenumber+".txt", ios::in);
    list<Ride*>::iterator it = history.begin();
    Ride *temp;

    outfile << age;

    for(int i = 0; i < history.size(); i++) {

        temp = *it;

        outfile << endl << temp->pickup; //pickup //
        outfile << endl << temp->dropoff;
        outfile << endl << temp->driver_name;
        outfile << endl << temp->ride_type;
        outfile << endl << temp->cost;

        it++;
    }
    
    outfile.close();

}

int option_input_validation(string &input) {

    stringstream convert;
    int validated;

    while(input < "1" || input > "3") {

        cout << endl << "Invalid option entered. \n\nEnter again : ";
        cin >> input;

    }

    convert << input;
    convert >> validated;

    return validated;

}

//overlaoded << for the class Ride.
ostream& operator <<(ostream &out, const Ride *obj) {

    out << "Pickup: " << obj->pickup << endl;
    out << "Dropoff: " << obj->dropoff << endl;
    out << "Driver name: " << obj->driver_name << endl;
    out << "Ride type: " << obj->ride_type << endl;
    out << "Cost: " << obj->cost << endl << endl;

    return out;

}

bool validate_phone_number(string number) {

    if(number.length() != 11) {

        return false;

    }

    for(int i = 0; i < number.length(); i++) {

        if(number[i] < '0' || number[i] > '9') {

            return false;

        }

    }

    return true;
}

float generate_rating(float min, float max) {

    int r = rand();

    float f = (float) r / RAND_MAX;

    float result = min + f * (max - min);
    
    return result;
}

void initialize_vectors() {
    
    string names[25] = {"Zafar Riaz", "Shahid Qureshi", "Ali Rana", "Zulfiqar Malik", "Nasir Akhtar", 
                        "Imran Chaudhry", "Abdul Aziz", "Sajjad Ahmed", "Javed Hussain", "Naveed Ali", 
                        "Ahmad Siddiqui", "Syed Shah", "Rashid Rehman", "Hamza Butt", "Muhammad Iqbal", 
                        "Ali Awan", "Zafar Abbasi", "Asif Sheikh", "Amir Mirza", "Irfan Khan", "Tariq Riaz",
                        "Khalid Hussain", "Abdul Malik", "Ali Qureshi", "Zulfiqar Rana"};

    //size for bike vector 20-80;
    int size = 20 + (rand() % 61);

    for(int i = 0; i < size; i++) {

        bike_drivers.push_back(new Bike(names[rand()%25], generate_rating(3.0, 5.0), Locations[rand()%12]));

    }

    //size for car vector 20-80;
    size = 20 + (rand() % 61);
    for(int i = 0; i < size; i++) {

        car_drivers.push_back(new Car(names[rand()%25], generate_rating(3.0, 5.0), Locations[rand()%12]));

    }

    //size for bike vector 20-80;
    size = 20 + (rand() % 61);
    for(int i = 0; i < size; i++) {

        rickshaw_drivers.push_back(new Rickshaw(names[rand()%25], generate_rating(3.0, 5.0), Locations[rand()%12]));

    }

}

//initialzier fucntion for the whole program
void PROGRAM_INI() {

    //floyd warshall algorithm substitute of djisktra and initialization of hashmap
    floyd_warshall(); 
    initialize_vectors();
    _mkdir("data");

}

//this function will return true if login is sucessful.
bool login(Customer &user) {

    string name, phone_No;
    char go_back;

    cout << "\nEnter name: ";
    fflush(stdin);
    getline(cin, name);
    cout << "\n\nEnter phone number: ";
    fflush(stdin);
    getline(cin, phone_No);

    while(validate_phone_number(phone_No) == false) {

        cout << "\n\nInvalid phone number entered. \nWould you like to go back to the previous menu? [Y/N]: ";
        cin >> go_back;

        if(go_back == 'Y' || go_back == 'y') {

            return false;

        }

        cout << "\n\nEnter phone number again: ";

        cin >> phone_No;

    }

    ifstream infile("data\\"+name+phone_No+".txt", ios::in);

    if(!infile.is_open()) {

        system("cls");
        cout << "User Not Found! \n\nPlease sign up first." << endl << endl;
        system("pause");

        infile.close();

        return false;
    }

    user.restore_details(infile, name, phone_No);

    infile.close();

    return true;

}

bool signup(Customer &user) {

    string name, phone_No;
    int age;
    char go_back;

    cout << "Enter name: ";
    fflush(stdin);
    getline(cin, name);
    cout << "Enter phone number: ";
    fflush(stdin);
    getline(cin, phone_No);
    while(validate_phone_number(phone_No) == false) {

        cout << "Invalid phone number entered. would you like to go back to the previous menu? [Y/N]: ";
        cin >> go_back;

        if(go_back == 'Y' || go_back == 'y') {

            return false;

        }

        cout << "Enter phone number again: ";

        cin >> phone_No;

    }
    cout << "Enter age: ";
    cin >> age;

    ofstream outfile("data\\"+name+phone_No+".txt", ios::app);

    if(!outfile.is_open()) {

        system("cls");
        cout << "Some error occured. \n\nPlease try again!" << endl << endl;
        system("pause");

        outfile.close();

        return false;
    }

    user.create_data_file(outfile, name, phone_No, age);

    outfile.close();

    return true;

}

int main() {

    std::setprecision(2);
    srand(GetTickCount64());
    PROGRAM_INI();

    //the general flow of the program where all the functions will be called.
    string start_menu_option, menu_option;
    int start_menu_converted, menu_converted;
    Customer current_user;

    do{

        system("cls");
        cout << "-----IN-DRIVE-----" << endl << endl<<endl;
        cout << "1. Login" << endl<<endl;
        cout << "2. Signup" << endl<<endl;
        cout << "3. Exit" << endl << endl<<endl;
        cout << "Enter option: ";
        cin >> start_menu_option;

        //validate the login option and convert into int for switch.
        start_menu_converted = option_input_validation(start_menu_option);

        switch(start_menu_converted) {

            //login case
            case 1: system("cls");

                    //login function
                    if(login(current_user) == false) {

                        continue;

                    }

                    //rest of the program will work from this point onwards.
                    do{
                        system("cls");

                        cout << "-----MAIN MENU-----" << endl << endl<<endl;
                        cout << "1. Book a ride" << endl<<endl;
                        cout << "2. View ride history" << endl<<endl;
                        cout << "3. Logout and exit" << endl << endl<<endl;
                        cout << "Enter option: ";
                        cin >> menu_option;

                        menu_converted = option_input_validation(menu_option);

                        switch(menu_converted) {

                            case 1: system("cls");
                                    current_user.book();
                                    system("pause");
                                    break;

                            case 2: system("cls");
                                    current_user.show_ride_history();
                                    system("pause");
                                    break;

                        }


                    }while(menu_option != "3");

                    goto program_finish;
                    break;

            //signup case
            case 2: system("cls");
                    
                    //signup function
                    if(signup(current_user) == false) {

                        continue;

                    }

                    //after signup rest of the program will work here.
                    do{
                        system("cls");

                        cout << "-----MAIN MENU-----" << endl << endl<<endl;
                        cout << "1. Book a ride" << endl<<endl;
                        cout << "2. View ride history" << endl<<endl;
                        cout << "3. Logout and exit" << endl << endl<<endl;
                        cout << "Enter option: ";
                        cin >> menu_option;

                        menu_converted = option_input_validation(menu_option);

                        switch(menu_converted) {

                            case 1: system("cls");
                                    current_user.book();
                                    system("pause");
                                    break;

                            case 2: system("cls");
                                    current_user.show_ride_history();
                                    system("pause");
                                    break;

                        }


                    }while(menu_option != "3");

                    goto program_finish;
                    break;

            case 3: program_finish:
                    system("cls");
                    cout << "THANKS FOR CHOOSING IN-DRIVE" << endl;
                    current_user.save_data();
                    start_menu_option = "3";
                    break;

        } 

    }while(start_menu_option != "3");

    return 0;
}