#include<bits/stdc++.h>
#include<fstream>
#include <jni.h>
#include <jni_md.h>
#include "BookYourConcert.h"
using namespace std;

class Ticket;
class Concert;
class Seat;
class Person;
class Customer;
class Admin;
class Venue;

bool isValidTime(int hour, int minute) {
    return hour >= 0 && hour < 24 && minute >= 0 && minute < 60;
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(int day, int month, int year) {
    if (year < 0 || month < 1 || month > 12 || day < 1) {
        return false;
    }

    // Days in each month
    int daysInMonth[] = {31, isLeapYear(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    return day <= daysInMonth[month - 1];
}

class Date{
    private:
        int date;
        int month;
        int year;
    public:
        Date(int date,int month,int year){
            this->date=date;
            this->month=month;
            this->year=year;
        }
        Date()=default;
    //methods for setting date,month,year.
        void setting_date(int date){
            this->date=date;
        }
        void setting_month(int month){
            this->month=month;
        }
        void setting_year(int year){
            this->year=year;
        }

        //methods for getting date,month,year.
        int getting_date(){
            return this->date;
        }
        int getting_month(){
            return this->month;
        }
        int getting_year(){
            return this->year;
        }
        int checking_date(Date date2){
            //checking between two years
            if (this->year > date2.getting_year()) {
                return 1;
            } else if (this->year < date2.getting_year()) {
                return -1;
            } else {
                //checking between two months
                if (this->month > date2.getting_month()) {
                    return 1;
                } else if (this->month < date2.getting_month()) {
                    return -1;
                } else {
                    //checking between two days
                    if (this->date > date2.getting_date()) {
                        return 1;
                    } else if (this->date < date2.getting_date()) {
                        return -1;
                    } else {
                        return 0; // Both dates are equal
                    }
                }
            }
        }
};

class Time{
    private:
        int hour;
        int minute;
    public:
        Time(int hour,int minute){
        this->hour=hour;
        this->minute=minute;
        }
        Time()=default;
    //methods for setting hour,minute.
        void setting_hour(int hour){
            this->hour=hour;
        }
        void setting_minute(int minute){
            this->minute=minute;
        }
        //methods for getting hour,minute.
        int getting_hour(){
            return this->hour;
        }
        int getting_minute(){
            return this->minute;
        }


        int checking_time(Time time2){
            if (this->hour > time2.getting_hour()) {
                return 1;
            } else if (this->hour < time2.getting_hour()) {
                return -1;
            } else {
                if (this->minute > time2.getting_minute()) {
                    return 1;
                } else if (this->minute < time2.getting_minute()) {
                    return -1;
                } else {
                    return 0; // Both times are equal
                }
            }
        }
};
bool comparing_time(Time old_begin, Time old_end, Time new_begin, Time new_end) {
    // no overlap if new concert ends before or exactly when the existing concert begins
    if (new_end.checking_time(old_begin) <= 0) {
        return false;  // no overlap
    }

    // no overlap if new concert begins after or exactly when the existing concert ends
    if (new_begin.checking_time(old_end) >= 0) {
        return false;  // no overlap
    }

    // else, there is a overlap
    return true;
}


class Seat{
private:
    int row_number;
    int column_number;
    bool available;
    
public:
    Seat()=default;
    Seat(int row_number,int column_number,bool available=true){
        this->row_number=row_number;
        this->column_number=column_number;
        this->available=available;
    }
    //methods for setting row_number,coloumn_number,available 
    void setting_row_number(int n){
        this->row_number = n;
    }
    void setting_column_number(int n){
        this->column_number = n;
    }
    void setting_available(bool b){
        this->available = b;
    }
    //methods for getting row_number,coloumn_number,available
    int getting_row_number(){
        return row_number;
    }
    int getting_column_number(){
        return column_number;
    }
    bool getting_available(){
        return this->available;
    }


};
class Concert {
private:
    string genre_name;
    string concert_name;
    Time concert_start_time;
    Time concert_end_time;
    Date concert_date;
    string language;
    string rating;
    string concert_overview;
    vector<vector<Seat*>> seats_track;

public:
    Concert()=default;
    Concert(string concert_name,Date concert_date,Time concert_start_time,Time concert_end_time,string language){
        this->concert_name=concert_name;
        this->concert_date=concert_date;
        this->concert_start_time=concert_start_time;
        this->concert_end_time=concert_end_time;
        this->language=language;
    }
    // methods for setting genre_name,concert_name,concert_start_time,concert_end_time,language,rating,overview
    void setting_language(string language){
        this->language=language;
    }
    void setting_genre_name(string genre_name) {
        this->genre_name = genre_name;
    }

    void setting_concert_name(string concert_name){
        this->concert_name=concert_name;
    }

    void setting_concert_start_time(Time start_time) {
        this->concert_start_time = start_time;
    }

    void setting_concert_end_time(Time end_time) {
        this->concert_end_time = end_time;
    }

    void setting_concert_date(Date date){
        this->concert_date = date;
    }/*
    void set_Language(string lang) {
        this->language = lang;
    }

   */

    void setting_rating(string concert_rating) {
        this->rating = concert_rating;
    }

    void setting_concert_overview(string overview) {
        this->concert_overview = overview;
    }

    void setting_seats_track(int rows,int columns) {
        for(int i=0;i<rows;i++){
            vector<Seat*> row_seats;
            for(int j=0;j<columns;j++){
                Seat *seat1 = new Seat;
                seat1->setting_available(true);
                seat1->setting_row_number(i+1);
                seat1->setting_column_number(j+1);
                row_seats.push_back(seat1);
            }
            this->seats_track.push_back(row_seats);
        }
    }

    // methods for getting genre_name,concert_name,concert_start_time,concert_end_time,language,rating,overview
    string getting_genre_name() {
        return this->genre_name;
    }

    string getting_concert_name(){
        return this->concert_name;
    }

    Time getting_concert_start_time() {
        return this->concert_start_time;
    }

    Time getting_concert_end_time() {
        return this->concert_end_time;
    }

    string getting_language() {
        return this->language;
    }

    string getting_rating() {
        return this->rating;
    }

    string getting_concert_overview() {
        return this->concert_overview;
    }
    Date getting_concert_date(){
        return this->concert_date;
    }

    vector<vector<Seat*>> getting_seats_track() {
        return this->seats_track;
    }
};


class Venue {
protected:
    string venue_name;
    string location;
    string city;
    int capacity;
    string owner_name;
    int rows;
    int columns;
    vector<Concert*> concerts_track;

public:
    Venue()=default;
    Venue(string venue_name,string location){
        this->venue_name=venue_name;
        this->location=location;
    }
    // methods for setting venue_name,location,city,capacity,owner_name,rows,columns
    void setting_venue_name(string venue_name) {
        this->venue_name = venue_name;
    }

    void setting_location(string venue_location) {
        this->location = venue_location;
    }

    void setting_city(string venue_city) {
        this->city = venue_city;
    }

    void setting_capacity(int venue_capacity) {
        this->capacity = venue_capacity;
    }

    void setting_owner_name(string owner) {
        this->owner_name = owner;
    }

    void setting_rows(int row_count) {
        this->rows = row_count;
    }

    void setting_columns(int column_count) {
        this->columns = column_count;
    }

   /* void settting_seats_track(int rows,int columns) {
        for(int i=0;i<columns;i++){
            vector<Seat*> row_seats;


            for(int j=0;j<rows;j++){
                Seat *seat1 = new Seat;
                seat1->setting_available(true);
                seat1->setting_row_number(j+1);
                seat1->setting_column_number(i+1);
                row_seats.push_back(seat1);
            }
            this->seats_track.push_back(row_seats);
        }
    }  */


    void add_concert(Concert *concert1){
        this->concerts_track.push_back(concert1);
    }

    // methods for getting venue_name,location,city,capacity,owner_name,rows,columns
    string getting_venue_name() {
        return this->venue_name;
    }

    string getting_location() {
        return this->location;
    }

    string getting_city() {
        return this->city;
    }

    int getting_capacity() {
        return this->capacity;
    }

    string getting_owner_name() {
        return this->owner_name;
    }

    int getting_rows() {
        return this->rows;
    }

    int getting_columns() {
        return this->columns;
    }

  /*  vector<vector<Seat*>> concert_seats_track() {
        return this->seats_track;
    }
*/
    vector<Concert*> getting_concerts_track() {
        return this->concerts_track;
    }

    void delete_concert(Time ct_time){//this should be there already checked
        int j=0;
        Concert *concert1;
        for(auto i:concerts_track){
            if ((i->getting_concert_start_time()).checking_time(ct_time) == 0){
            concert1 = i;
            break; 
            }
            j++;
        }
        if(j==concerts_track.size()){
            cout << "no such concert in the given venue\n-----------------------------------" << endl;
            return;
        }
        concerts_track.erase(concerts_track.begin()+j);
        delete concert1;
       // cout << "deleted the concert sucessfully" << endl;
    }
};

class Ticket{
    protected:
        Seat seat;
        Venue venue;
        Concert concert;
    public:
        Ticket(Concert concert,Venue venue,Seat seat){
            this->concert=concert;
            this->venue=venue;
            this->seat=seat;
        }
        Ticket()=default;
        void setting_Concert(Concert concert){
            this->concert=concert;
        }
        void setting_Seat(Seat seat){
            this->seat=seat;
        }
        void setting_Venue(Venue venue){
            this->venue=venue;
        }
        Seat getting_Seat(){
            return this->seat;
        }
        Venue getting_Venue(){
            return this->venue;
        }
        Concert getting_Concert(){
            return this->concert;
        }
};

vector<Venue*> Venues;
vector<Customer*> Customers;
vector<string> Concerts;

class Person{
protected:
    string name;
    int age;
    string email;
public:
    Person(){

    }
    Person(string name,int age,string email){
        this->name=name;
        this->age=age;
        this->email=email;
    }

    void setting_name(string name){
        this->name = name;
    }
    void setting_age(int age){
        this->age = age;
    }
    void setting_email(string email){
        this->email = email;
    }
    string getting_name(){
        return this->name;
    }
    int getting_age(){
        return this->age;
    }
    string getting_email(){
        return this->email;
    }
};

class Customer: public Person{
protected:
    string Phone_Number;
    vector<Ticket> Customer_Bookings;
    string encrypted_password;
    unordered_map<char, char> encryptionTable;
    unordered_map<char, char> decryptionTable;
    void initializeTables() {
        string plain = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{}|;:'\",.<>?/`~";
        string cipher = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0987654321<>?,./;'[]{}|`~!@#$%^&*()-_=+";

        for (size_t i = 0; i < plain.length(); ++i) {
            encryptionTable[plain[i]] = cipher[i];
            decryptionTable[cipher[i]] = plain[i];
        }
    }
public:
    Customer(){
        initializeTables();
    }
    Customer(string name,int age,string email,string Phone_Number,string &password):Person(name,age,email){
        this->Phone_Number=Phone_Number;
        initializeTables();
      //  this->encrypted_password = password;
        this->encrypted_password.clear();
        for (char c : password) {
            this->encrypted_password += encryptionTable.count(c) ? encryptionTable[c] : c;
        }
    }

    void setting_password(string password){
        this->encrypted_password = password;
    }

    void bookConcert(Ticket ticket){
      //  int rowNo=ticket.getting_Seat().getting_row_number();
      //  int columnNo=ticket.getting_Seat().getting_column_number();
        string venueName=ticket.getting_Venue().getting_venue_name();
        string venueLocation=ticket.getting_Venue().getting_location();
        string concertName=ticket.getting_Concert().getting_concert_name();
        Date concertDate=ticket.getting_Concert().getting_concert_date();
        int rowNumber=ticket.getting_Seat().getting_row_number();
        int columnNumber=ticket.getting_Seat().getting_column_number();
        int startHour=ticket.getting_Concert().getting_concert_start_time().getting_hour();
        int startMinute=ticket.getting_Concert().getting_concert_start_time().getting_minute();
        for(Venue* &venue:Venues){
                if(venue->getting_venue_name()==venueName and venue->getting_location()==venueLocation){
                  //  cout<<"Name: "<<venue->getting_venue_name()<<endl;

                    for(Concert* &concert:venue->getting_concerts_track()){
                        if(concert->getting_concert_name()==concertName and concert->getting_concert_date().getting_date()==concertDate.getting_date() and concert->getting_concert_date().getting_month()==concertDate.getting_month() and concert->getting_concert_date().getting_year()==concertDate.getting_year() and concert->getting_concert_start_time().getting_hour()==startHour and concert->getting_concert_start_time().getting_minute()==startMinute){
                            if(concert->getting_seats_track()[rowNumber-1][columnNumber-1]->getting_available()){
                                concert->getting_seats_track()[rowNumber-1][columnNumber-1]->setting_available(false);
                                cout<< "The seat is booked successfully\n-----------------------------------" << endl;
                            }
                            else{
                                cout<<"This seat which you are trying to book is not available!\n-----------------------------------" << endl;
                                return;
                            }
                        }
                    }

                }
            }
        this->Customer_Bookings.push_back(ticket);

    }
    string getting_PhoneNumber(){
        return this->Phone_Number;
    }
    string getting_password(){
        return this->encrypted_password;
    }
    vector<Ticket>& getting_Customer_Bookings(){
        return this->Customer_Bookings;
    }
    bool match_password(string &password){
      /*  if(this->password == password){
            return true;
        }
        else{
            return false;
        }*/
        string decryptedPassword;
        for (char c : this->encrypted_password) {
            decryptedPassword += decryptionTable.count(c) ? decryptionTable[c] : c;
        }
        return decryptedPassword == password;
    }
    void cancelBooking(int i){
       this->Customer_Bookings.erase(this->Customer_Bookings.begin()+i);
    }

    
};

class Admin: public Person{
protected:

public:
    void add_venue(string venue_name,string location,string city,int capacity,string owner_name,int rows,int columns){
        if(rows*columns!=capacity){
            cout<<"The capacity does not match with the number of columns and rows\n-----------------------------------"<<endl;
            return;
        }
        Venue *venue1 = new Venue();
       // cout << "venue_name" << endl;
       // cout << location << endl;
       venue1->setting_venue_name(venue_name);
       venue1->setting_location(location);
        venue1->setting_city(city);
        venue1->setting_capacity(capacity);
        venue1->setting_owner_name(owner_name);
        venue1->setting_rows(rows);
        venue1->setting_columns(columns);
        Venues.push_back(venue1);
        cout<< "The venue is added successfully\n-----------------------------------" << endl;
     //   for(auto i:Venues){
       //     cout << i->getting_city() << endl;
       // }
       // cout << Venues[0]->getting_venue_name << endl;
    }   
    void add_concert(string venue_name,string concert_name,int start_timehour,int start_timeminute,int end_timehour, int end_timeminute,int dateday, int datemonth,int dateyear, string rating, string overview,string language) {
        Venue *venue1;
        Date date;
        Time start_time, end_time;

        if(!isValidTime(start_timehour,start_timeminute)){
            cout<<"Invalid time\n-----------------------------------"<<endl;
            return;
        }

        if(!isValidTime(end_timehour,end_timeminute)){
            cout<<"Invalid time\n-----------------------------------"<<endl;
            return;
        }
        
        if(!isValidDate(dateday,datemonth,dateyear)){
            cout<<"Invalid date\n-----------------------------------"<<endl;
            return;
        }


        start_time.setting_hour(start_timehour);
        start_time.setting_minute(start_timeminute);
        // Set end_time using the setter methods
        end_time.setting_hour(end_timehour);
        end_time.setting_minute(end_timeminute);



        if(start_time.checking_time(end_time)>=0){
            cout<<"Invalid start time and end time\n-----------------------------------"<< endl;
            return;
        }

        // Set date using the setter methods
        date.setting_date(dateday);
        date.setting_month(datemonth);
        date.setting_year(dateyear);

        Date presentdate;
        presentdate.setting_date(30);
        presentdate.setting_month(11);
        presentdate.setting_year(2024);

        if(date.checking_date(presentdate)<0){
            cout<<"Invalid date\n-----------------------------------"<<endl;
            return;
        }

        for (auto i : Venues){
            for(Concert* &concert:i->getting_concerts_track()){
                if(concert->getting_concert_name()==concert_name){
                    if(comparing_time(concert->getting_concert_start_time(),concert->getting_concert_end_time(), start_time, end_time)){
                        cout<< "Concert cannot be added!\n-----------------------------------" << endl;
                        return;
                    }
                }
            }
        }
        int changed=0;
        // Find the venue by name
        for (auto i : Venues) {
           // cout<<i->getting_venue_name()<<endl;
            if (venue_name == i->getting_venue_name()) {
                venue1 = i;
                changed = 1;
                break;
            }
        }

        if (changed == 0) {
            cout << "No such venue exists\n-----------------------------------" << endl;
            return;
        }

        // Check for time conflicts with existing shows
        for (auto existing_concert : venue1->getting_concerts_track()) {
            if (!date.checking_date(existing_concert->getting_concert_date())) { // First, check if the dates are the same  //added a not because it returns 0;
                if (comparing_time(existing_concert->getting_concert_start_time(), existing_concert->getting_concert_end_time(), start_time, end_time)) {
                    cout << "Time conflict with another concert!\n-----------------------------------" << endl;
                    return;
                }
            }
        }

        // If no conflict, proceed to add the concert
        Concert *concert1 = new Concert();
        concert1->setting_concert_name(concert_name);
        concert1->setting_concert_start_time(start_time);
        concert1->setting_concert_end_time(end_time);
        concert1->setting_concert_date(date);
        concert1->setting_language(language);
        concert1->setting_rating(rating);
        concert1->setting_seats_track(venue1->getting_rows(),venue1->getting_columns());
        concert1->setting_concert_overview(overview);

    
        auto it = find(Concerts.begin(),Concerts.end(),concert_name);
        if(it == Concerts.end()){
            Concerts.push_back(concert_name);
        }

        venue1->add_concert(concert1);  // Add the concert to the venue
        cout << "Concert added successfully!\n-----------------------------------" << endl;
    }


    void delete_venue(string venue_name){
        Venue *venue1;
        int changed = 0;

        
       /* for (auto i : Venues){
            for(Concert* &concert:i->getting_concerts_track()){
                if(concert->getting_concert_name()==concert_name){
                    if(comparing_time(concert->getting_concert_start_time(),concert->getting_concert_end_time(), start_time, end_time)){
                        cout<< "Concert cannot be added!" << endl;
                    }
                }
            }
        } */

        // Find the venue by name
        int j=0;
        for (auto i : Venues) {
            if (venue_name == i->getting_venue_name()) {
                venue1 = i;
                changed = 1;
                break;
            }
            j++;
        }
        if (changed == 0) {
            cout << "No such venue exists\n-----------------------------------" << endl;
            return;
        }  
        //deleting all the tickets that are having concerts in this venue
        int m;
        for(auto i:Customers){
            m=0;
            for(auto j:i->getting_Customer_Bookings()){
                if(j.getting_Venue().getting_venue_name() == venue1->getting_venue_name()){
                    i->cancelBooking(m);
                }
                m++;
            }
        }
        Venues.erase(Venues.begin()+j);
        delete venue1;
        cout<<"Venue deleted successfully\n-----------------------------------" <<endl;
    }
   /* void delete_concert(string concert_name){
        int j=0;
        for(auto i: Concerts){
            if(i == concert_name){
                break;
            } 
            j++;
        }
        if(j == Concerts.size()){
            cout << "no such concert present" << endl;
            return;
        }
        //deleting all the tickets that are having their concert as the concert we are deleting
        for(auto i:Customers){
            for(auto j:i->getting_Customer_Bookings()){
                if(j.getting_Concert().getting_concert_name() == concert_name){
                    i->cancelBooking(j.getting_Concert());
                }
            }
        }
    
        Concerts.erase(Concerts.begin()+j);

    } */
    void delete_concert(string venue_name,int start_timehour,int start_timeminute){
        Venue *venue1;
        int changed = 0;
        Time start_time;
        start_time.setting_hour(start_timehour);
        start_time.setting_minute(start_timeminute);

        // Find the venue by name
        int j=0;
        for (auto i : Venues) {
            if (venue_name == i->getting_venue_name()) {
                venue1 = i;
                changed = 1;
                break;
            }
            j++;
        }
        if(changed == 0){
            cout << "no such venue\n-----------------------------------" << endl;
            return;
        }
        //delting all the tickets that are corresponding to this concert in the customers ticket booking list
        int m;
        for(auto i:Customers){
            m=0;
            for(auto j:i->getting_Customer_Bookings()){
                if((j.getting_Venue().getting_venue_name() == venue1->getting_venue_name()) && (j.getting_Concert().getting_concert_start_time().checking_time(start_time) == 0)){
                    i->cancelBooking(m);
                }
                m++;
            }
        }
        venue1->delete_concert(start_time);
        cout<<"The concert is deleted successfully\n-----------------------------------" <<endl;
    }
    
};


class Booking_Manager{
protected:
    
public:
    
    void add_NewCustomer(){
        string name;
        cout<<"Username:";
        cin>>name;
        string email;
        cout<<"Email Id:";
        cin>>email;
        int age;
        cout<<"Enter your age:";
        cin>>age;
        string phoneNumber;
        cout<<"Enter phone number:";
        cin>>phoneNumber;
        string password;
        while(1){
            cout << "Enter the password" << endl;
            string pass;
            cin >> pass;
            cout << "confirm the password" << endl;
            string pass1;
            cin >> pass1;
            if(pass == pass1){
                password = pass1;
                break;
            }
            cout<<"/n"<<endl;
            cout<< "confirmation password is not matched please try again" << endl;
        }
        for(auto i:Customers){
            if(i->getting_email() == email){
                cout<<"/n"<<endl;
                cout << "other customer already exists with the same email" << endl;
                return;
            }
        }
        Customer* customer=new Customer(name,age,email,phoneNumber,password);
        Customers.push_back(customer);
        cout<<"\n-----------------------------------"<<endl;
        handleBooking(customer);
    }
    void handleExistingCustomer(){
        string email;
        bool found=false;
        Customer *cust1 = new Customer;
        cout << "Enter email id: ";
        cin >> email; 
        for(auto &it:Customers){
            if(it->getting_email()==email){
                found=true;
                cust1 = it;
            }
        }
        if(!found){
            cout<<"No User Exists with the current details"<<endl;
            return;
        }
        string pass;
        while(1){
            cout << "Enter password: " << endl;
            cin >> pass;
            if(!(cust1->match_password(pass))){
                cout << "Invalid password try again" << endl;
            }
            else{
                break;
            }
        }
        handleBooking(cust1);
    }
    void handleBooking(Customer *customer){
        cout<<"Press 1 to book a concert"<<endl;
        cout<<"Press 2 to check your previous bookings or cancel any of the previous bookings\n-----------------------------------"<<endl;
        int command;
        cin>>command;
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input.\n-----------------------------------"<<endl;
            return;
        }
        if(command==1){
            int i=1;
            for(auto& concert:Concerts){
                cout<<i++<<". "<<concert<<endl;
            }
            cout<<"Select a concert(enter the serial number of the concert you want to book):\n-----------------------------------"<<endl;
            int index;
            cin>>index;
            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input.\n-----------------------------------"<<endl;
                return;
            }
            string concertName=Concerts[index-1];
            set<pair<int,int>> dates;
            for(auto &venue:Venues){
                for(auto &concerts:venue->getting_concerts_track()){
                if(concerts->getting_concert_name()==concertName){
                    dates.insert(make_pair(concerts->getting_concert_date().getting_date(),concerts->getting_concert_date().getting_month()));
                    }
                }
            }
            cout<<"Select a date for the concert"<<endl;
            cout<<"Available Dates:"<<endl;
            for(auto it=dates.begin();it!=dates.end();++it){
                cout<<it->first<<" "<<it->second<<endl;
            }
            int concertIndex;
            vector<Venue*> filteredVenues;
            vector<Concert*> filteredConcerts;
            while(1){
            cout<<"Type the date and month you are looking for(from above list):"<<endl;
            int date,month;
            cin>>date;
            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input.\n-----------------------------------"<<endl;
                return;
            }
            cin>>month;
            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input.\n-----------------------------------"<<endl;
                return;
            }
            cout<<"\n-----------------------------------"<<endl;
            int i=1;
            int ta=0;
            for (auto &venue : Venues) {
                concertIndex = 0;
                for (auto &concerts : venue->getting_concerts_track()) {
                    concertIndex++;
                    if (concerts->getting_concert_name() == concertName && 
                        concerts->getting_concert_date().getting_date() == date && 
                        concerts->getting_concert_date().getting_month() == month) {
                        ta++;
                        cout<<"Serial no :"<<i++<<endl;
                        cout << "-------------------------------------------------" << endl;   
                        cout << "Venue " << ":" << endl;
                        cout << "Name      : " << venue->getting_venue_name() << endl;
                        cout << "Location  : " << venue->getting_location() << endl;
                        cout << "City      : " << venue->getting_city() << endl;
                        cout << "Capacity  : " << venue->getting_capacity() << endl;
                        cout << "-------------------------------------------------" << endl;

                        cout << "Concert Details:" << endl;
                        cout << "Concert Name     : " << concerts->getting_concert_name() << endl;
                        cout << "Start Time     : " 
                            << concerts->getting_concert_start_time().getting_hour() << ":" 
                            << setw(2) << setfill('0') << concerts->getting_concert_start_time().getting_minute() << endl;
                        cout << "End Time       : " 
                            << concerts->getting_concert_end_time().getting_hour() << ":" 
                            << setw(2) << setfill('0') << concerts->getting_concert_end_time().getting_minute() << endl;
                        cout << "-------------------------------------------------" << endl;

                        // Add venue to the filtered list
                        filteredVenues.push_back(venue);
                        filteredConcerts.push_back(concerts);
                    }
                }
            }
            cout<<"Type 1 if you want to continue\nType 2 If you want to see on another date\nType 3 If you want to return\n-----------------------------------"<<endl;
            int type;
            cin>>type;
            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input.\n-----------------------------------"<<endl;
                return;
            }
            if(type==1){
                if(ta==0){
                    cout<<"Invalid\n-----------------------------------"<<endl;
                    return;
                }
                break;
            }
            else if(type==3){
                return;
            }
            else{
                continue;
            }
        }
        cout<<"Type the serial number of the concert you want to book"<<endl;
        int sno;
        cin>>sno;
        if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input.\n-----------------------------------"<<endl;
                return;
            }
        Venue* venue=filteredVenues[sno-1];
        Concert* concert=filteredConcerts[sno-1];
        i = 1;
        cout << "   ";
        for (int j = 1; j <= venue->getting_columns(); j++) {
            cout << setw(3) << j;
        }
        cout << endl;
        cout << "   ";
        for (int j = 1; j <= venue->getting_columns(); j++) {
            cout << "---";
        }
        cout << endl;
        for (auto &row : concert->getting_seats_track()) {
            cout << setw(2) << i++ << " | ";  
            for (auto &elem : row) {
                cout << (elem->getting_available() ? " A " : "NA ");
            }
            cout << endl;
        }
        cout << endl << "Legend:" << endl;
        cout << "A  - Available Seat" << endl;
        cout << "NA - Not Available Seat\n-----------------------------------" << endl;

        cout<<"Please select the row number and column number from the available seats"<<endl;
        int rowNo,columnNo;
        cin>>rowNo;
        if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input.\n-----------------------------------"<<endl;
                return;
            }
        cin>>columnNo;
        if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input.\n-----------------------------------"<<endl;
                return;
            }
        Seat* seat=new Seat();
        seat->setting_row_number(rowNo);
        seat->setting_column_number(columnNo);
        seat->setting_available(false);
        Ticket* ticket=new Ticket();
        ticket->setting_Seat(*seat);
        ticket->setting_Concert(*concert);
        ticket->setting_Venue(*venue);
        customer->bookConcert(*ticket);
        }
    else if(command==2){
        int f=0;
        for(auto &Customer:Customers){
            int i=1;
            if(Customer->getting_name()==customer->getting_name() and Customer->getting_email()==customer->getting_email() and Customer->getting_PhoneNumber()==customer->getting_PhoneNumber()){
                cout<<"Number of bookings: "<<Customer->getting_Customer_Bookings().size()<<endl;
                if(Customer->getting_Customer_Bookings().size()>0){
                    f=1;
                }
                for(auto &ticket: Customer->getting_Customer_Bookings()) {
                    cout << "Booking #" << i++ << endl;
                    cout << "Concert Name: " << ticket.getting_Concert().getting_concert_name() << endl;
                    cout << "Date: " 
                        << ticket.getting_Concert().getting_concert_date().getting_date() << "-" 
                        << ticket.getting_Concert().getting_concert_date().getting_month() << "-" 
                        << ticket.getting_Concert().getting_concert_date().getting_year() << endl;
                    cout << "Start Time: " 
                        << ticket.getting_Concert().getting_concert_start_time().getting_hour() << ":" 
                        << ticket.getting_Concert().getting_concert_start_time().getting_minute() << endl;
                    cout << "End Time: " 
                        << ticket.getting_Concert().getting_concert_end_time().getting_hour() << ":" 
                        << ticket.getting_Concert().getting_concert_end_time().getting_minute() << endl;
                    cout << "Language: " << ticket.getting_Concert().getting_language() << endl;
                    cout << "Venue Name: " << ticket.getting_Venue().getting_venue_name() << endl;
                    cout << "Location: " << ticket.getting_Venue().getting_location() << ", " 
                        << ticket.getting_Venue().getting_city() << endl;
                    cout << "Seat: Row " << ticket.getting_Seat().getting_row_number() 
                        << ", Seat " << ticket.getting_Seat().getting_column_number() << endl;
                    cout << "-----------------------------------------" << endl;
                }

            }
        }
        cout<<"Do you want to cancel any of the above bookings?\nType 1 if you want to cancel\nType 2 to exit\n-----------------------------------"<<endl;
        int cancelBooking;
        cin>>cancelBooking;
        if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input.\n-----------------------------------"<<endl;
                return;
            }
        cout<<"\n-----------------------------------"<<endl;
        if(cancelBooking==1){
            cout<<"Type the serial number of the bookings you want to cancel\n-----------------------------------"<<endl;
            int no;
            cin>>no;
            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "Invalid input.\n-----------------------------------"<<endl;
                return;
            }
            cout<<"\n-----------------------------------"<<endl;
            if(f){
                customer->cancelBooking(no-1);
                handleBooking(customer);
            }
        }
        else{
            return;
        }
    }
    }     
    
};

void saveCustomers(){
        ofstream outFile("Customers.txt",ios::trunc);
        if(!outFile){
            cerr<<"Error Opening file.\n";
            return;
        }
        for(const auto& customer:Customers){
            outFile<< customer->getting_name()<<" "<<customer->getting_age()<<" "<<customer->getting_email()<<" "<<customer->getting_PhoneNumber()<<" "<<customer->getting_password();

            outFile<<" "<<customer->getting_Customer_Bookings().size()<<endl;
            for(auto& ticket:customer->getting_Customer_Bookings()){
                outFile<<ticket.getting_Concert().getting_concert_name()<<endl;
                outFile<<ticket.getting_Concert().getting_concert_date().getting_date()<<" "<<ticket.getting_Concert().getting_concert_date().getting_month()<<" "<<ticket.getting_Concert().getting_concert_date().getting_year()<<endl;
                outFile<<ticket.getting_Concert().getting_concert_start_time().getting_hour()<<" "<<ticket.getting_Concert().getting_concert_start_time().getting_minute()<<endl;
                outFile<<ticket.getting_Concert().getting_concert_end_time().getting_hour()<<" "<<ticket.getting_Concert().getting_concert_end_time().getting_minute()<<endl;
                outFile<<ticket.getting_Concert().getting_language()<<endl;
                outFile<<ticket.getting_Venue().getting_venue_name()<<endl;
                outFile<<ticket.getting_Venue().getting_location()<<endl;
                outFile<<ticket.getting_Seat().getting_row_number()<<endl;
                outFile<<ticket.getting_Seat().getting_column_number()<<endl;
            }
        }
    }
    void loadCustomers(){
        ifstream inFile("Customers.txt");
        if(!inFile){
            return;
        }
        string name,email,phoneNumber,password;
        int age,numBookings;
        Customers.clear();
        while(inFile>>name>>age>>email>>phoneNumber>>password>>numBookings){
            Customer* customer=new Customer(name,age,email,phoneNumber,password);
            customer->setting_password(password);
            for(int i=0;i<numBookings;i++){
                // cout<<"I went in atleast"<<endl;
                string concertName,language,venueName,venueLocation;
                int date,month,year,startHour,startMinute,endHour,endMinute;
                int rowNumber,columnNumber;

                inFile.ignore();
                getline(inFile,concertName);
                inFile>>date>>month>>year;
                // cout<<"date: "<<date<<" "<<"month: "<<month<<" "<<"year: "<<year<<endl;
                inFile>>startHour>>startMinute;
                // cout<<"startHour: "<<startHour<<"startMinute: "<<startMinute<<endl;
                inFile>>endHour>>endMinute;
                // cout<<"endHour: "<<endHour<<"endMinute: "<<endMinute<<endl;
                inFile.ignore();
                getline(inFile,language);
                // cout<<"language: "<<language<<endl;
                getline(inFile,venueName);
                // cout<<"venueName: "<<venueName<<endl;
                getline(inFile,venueLocation);
                inFile>>rowNumber>>columnNumber;
                // cout<<"rowNumber: "<<rowNumber<<"seatNumber: "<<seatNumber<<endl;

                Date concertDate(date,month,year);
                Time startTime(startHour,startMinute);
                Time endTime(endHour,endMinute);
                Concert concert(concertName,concertDate,startTime,endTime,language);
                Venue venue(venueName,venueLocation);
                Seat seat(rowNumber,columnNumber,false);
                for(Venue* &venue:Venues){
                    if(venue->getting_venue_name()==venueName and venue->getting_location()==venueLocation){
                      //  cout<<"Name: "<<venue->getting_venue_name()<<endl;

                        for(Concert* &concert:venue->getting_concerts_track()){
                            if(concert->getting_concert_name()==concertName and concert->getting_concert_date().getting_date()==concertDate.getting_date() and concert->getting_concert_date().getting_month()==concertDate.getting_month() and concert->getting_concert_date().getting_year()==concertDate.getting_year() and concert->getting_concert_start_time().getting_hour()==startHour and concert->getting_concert_start_time().getting_minute()==startMinute){
                                concert->getting_seats_track()[rowNumber-1][columnNumber-1]->setting_available(false);
                            }
                        }

                    }
                }
                Ticket ticket(concert,venue,seat);
                // cout<<"Pushed "<<i<<"th ticket"<<endl;

                customer->getting_Customer_Bookings().push_back(ticket);

                
            }
            // cout<<"I am pushing it here also"<<endl;
            Customers.push_back(customer);
        }

    }
void saveConcerts(){
    ofstream outFile("concerts.txt",ios::trunc);
    if(!outFile){
        cerr<<"Error Opening file for opening concerts\n"<<endl;
        return;
    }
    set<string> existingConcerts;
    ifstream inFile("concerts.txt");
    string concert;
    while(getline(inFile,concert)) {
        if(!concert.empty()){
            existingConcerts.insert(concert);
        }
    }
    inFile.close();
    for (const auto& concert : Concerts) {
        if (existingConcerts.find(concert) == existingConcerts.end()) {
            outFile << concert << endl; // Append concert to the file
        }
    }

    outFile.close();
}

void loadConcerts() {
    ifstream inFile("concerts.txt");
    if(!inFile){
        cerr<<"Error opening file for loading concerts.\n";
        return;
    }
    Concerts.clear();
    string concert;
    while (getline(inFile, concert)) {
        if (!concert.empty()) {
            Concerts.push_back(concert);
        }
    }

    inFile.close();
}
void saveVenues() {
    ofstream outFile("Venues.txt", ios::trunc);
    if (!outFile) {
        cerr << "Error opening file for saving venues.\n";
        return;
    }

    for (const auto& venue : Venues) {
        outFile << venue->getting_venue_name() << endl;
        outFile << venue->getting_location() << endl;
        outFile << venue->getting_city() << endl;
        outFile << venue->getting_capacity() << endl;
        outFile << venue->getting_rows() << endl;
        outFile << venue->getting_columns() << endl;
        outFile << venue->getting_concerts_track().size() << endl; 

        for (const auto& concert : venue->getting_concerts_track()) {
            outFile << concert->getting_concert_name() << endl;
            Date concertDate = concert->getting_concert_date();
            outFile << concertDate.getting_date() << " " << concertDate.getting_month() << " " << concertDate.getting_year() << endl;
            Time startTime = concert->getting_concert_start_time();
            outFile << startTime.getting_hour() << " " << startTime.getting_minute() << endl;
            Time endTime = concert->getting_concert_end_time();
            outFile << endTime.getting_hour() << " " << endTime.getting_minute() << endl;
            outFile << concert->getting_language() << endl;
            outFile << concert->getting_rating() << endl;
            outFile << concert->getting_concert_overview() << endl;
        }
    }

    outFile.close();
}

void loadVenues() {

    ifstream inFile("Venues.txt");
    if (!inFile) {
        cerr << "Error opening file for loading venues.\n";
        return;
    }

    Venues.clear(); 
    string venueName, location, city, concertName, language,rating, overview;
    int capacity, rows, columns, numConcerts, date, month, year, startHour, startMinute, endHour, endMinute;

    while (getline(inFile, venueName)) { 
        getline(inFile, location);
        getline(inFile, city);
        inFile >> capacity >> rows >> columns >> numConcerts;
        inFile.ignore();

        Venue* venue = new Venue(venueName, location);
        venue->setting_city(city);
        venue->setting_capacity(capacity);
        // cout<<"rows set to "<<rows<<endl;
        venue->setting_rows(rows);
        // cout<<"columns set to"<<columns<<endl;
        venue->setting_columns(columns);
        // venue->set_SeatsTrack(rows,columns);
      //  cout<<"I came to concerts "<<endl;

        for (int i = 0; i < numConcerts; ++i) { // Read each concert for the venue
            getline(inFile, concertName);
            inFile >> date >> month >> year >> startHour >> startMinute >> endHour >> endMinute;
            inFile.ignore(); // Ignore newline character after endMinute
            getline(inFile, language);
            getline(inFile, rating);
            getline(inFile, overview);

            Date concertDate(date, month, year);
            Time startTime(startHour, startMinute);
            Time endTime(endHour, endMinute);
            Concert* concert = new Concert(concertName, concertDate, startTime, endTime, language);
            concert->setting_rating(rating);
            concert->setting_concert_overview(overview);
            concert->setting_seats_track(rows,columns);

            venue->add_concert(concert);
        }
      //  cout<<"Venues pushed"<<endl;
        Venues.push_back(venue);
    }

    inFile.close();
}

void Start(){
    loadVenues();
    loadCustomers();
    loadConcerts();
}

void Save(){
    saveCustomers();
    saveVenues();
    saveConcerts();
}



JNIEXPORT void JNICALL Java_BookYourConcert_addVenue(JNIEnv *env, jobject obj,
                                                     jstring name, jstring location, jstring city,
                                                     jint capacity, jstring ownerName, jint rows, jint columns) {
    const char *cName = env->GetStringUTFChars(name, 0);
    const char *cLocation = env->GetStringUTFChars(location, 0);
    const char *cCity = env->GetStringUTFChars(city, 0);
    const char *cOwnerName = env->GetStringUTFChars(ownerName, 0);

    string ccName(cName);
    string ccLocation(cLocation);
    string ccCity(cCity);
    string ccOwnerName(cOwnerName);
  //  cout << "ccName"<< endl;

    Admin admin;
    admin.add_venue(ccName, ccLocation, ccCity, capacity, ccOwnerName, rows, columns);

    env->ReleaseStringUTFChars(name, cName);
    env->ReleaseStringUTFChars(location, cLocation);
    env->ReleaseStringUTFChars(city, cCity);
    env->ReleaseStringUTFChars(ownerName, cOwnerName);
}

// Add Concert
JNIEXPORT void JNICALL Java_BookYourConcert_addConcert(JNIEnv *env, jobject obj,
                                                  jstring venueName, jstring concertName,
                                                  jint startHour, jint startMinute, jint endHour, jint endMinute,jint day,jint month,jint year,jstring language, jstring rating, jstring overview) {
    const char  *cVenueName= env->GetStringUTFChars(venueName, 0);
    const char  *cConcertName = env->GetStringUTFChars(concertName, 0);
    const char  *cLanguage = env->GetStringUTFChars(language, 0);
    const char  *cRating = env->GetStringUTFChars(rating, 0);
    const char  *cOverview = env->GetStringUTFChars(overview, 0);

    string ccVenueName(cVenueName);
    string ccConcertName(cConcertName);
    string ccLanguage(cLanguage);
    string ccRating(cRating);
    string ccOverview(cOverview);


    Admin admin;
    admin.add_concert(ccVenueName,ccConcertName,startHour,startMinute,endHour,endMinute,day,month,year,ccLanguage,ccRating,ccOverview);

    env->ReleaseStringUTFChars(venueName,cVenueName);
    env->ReleaseStringUTFChars(concertName, cConcertName);
    env->ReleaseStringUTFChars(language, cLanguage);
    env->ReleaseStringUTFChars(rating, cRating);
    env->ReleaseStringUTFChars(overview, cOverview);
}

// Handle Existing Customer
JNIEXPORT void JNICALL Java_BookYourConcert_handleExistingCustomer(JNIEnv *env, jobject obj) {
    Booking_Manager manager;
    manager.handleExistingCustomer();
}

// Delete Concert
JNIEXPORT void JNICALL Java_BookYourConcert_deleteConcert(JNIEnv *env, jobject obj,
                                                     jstring venueName, jint startHour, jint startMinute) {
    const char *cVenueName = env->GetStringUTFChars(venueName, 0);
    string ccVenueName(cVenueName);

    Admin admin;
    admin.delete_concert(ccVenueName, startHour, startMinute);

    env->ReleaseStringUTFChars(venueName, cVenueName);
}


// Delete Venue
JNIEXPORT void JNICALL Java_BookYourConcert_deleteVenue(JNIEnv *env, jobject obj, jstring venueName) {
    const char *cVenueName = env->GetStringUTFChars(venueName, 0);
    string ccVenueName(cVenueName);

    Admin admin;
    admin.delete_venue(ccVenueName);

    env->ReleaseStringUTFChars(venueName, cVenueName);
}

// Add New Customer
JNIEXPORT void JNICALL Java_BookYourConcert_addNewCustomer(JNIEnv *env, jobject obj) {
    Booking_Manager manager;
    manager.add_NewCustomer();
}

// Start System
JNIEXPORT void JNICALL Java_BookYourConcert_start(JNIEnv *env, jobject obj) {
    Start();
}

// Save System
JNIEXPORT void JNICALL Java_BookYourConcert_save(JNIEnv *env, jobject obj) {
    Save();
}