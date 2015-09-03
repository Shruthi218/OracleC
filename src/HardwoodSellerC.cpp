#include <iostream>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <fstream>
#include <vector>
using namespace std;

void readInputFile(string);
void fillMap();
vector<double> deliveryTime();
vector<double>  Price();
void output(vector<double> &, vector<double> &);
struct Buyer {
	string name;
	string address;
	string date;
	vector<string> woodtype;
	vector<int> amount;
};

vector<Buyer> buyers;
map<string, double> mymap;
map<string, double> mymapPrice;

int main() {

	string file = "1.txt";
	readInputFile(file);
	fillMap();
        vector<double> deliveryRes = deliveryTime();
	vector<double> priceRes = Price();
	output(deliveryRes, priceRes);
	return 0;
}

void fillMap() {

 mymap.insert ( std::pair<string,double>("Cherry",2.5) );
 mymap.insert ( std::pair<string,double>("Curly Maple",1.5) );
 mymap.insert ( std::pair<string,double>("Genuine Mahogany",3) );
 mymap.insert ( std::pair<string,double>("Wenge",5) );
 mymap.insert ( std::pair<string,double>("White Oak",2.3) );
 mymap.insert ( std::pair<string,double>("Sawdust",1) );
 
 mymapPrice.insert ( std::pair<string,double>("Cherry",5.95) );
 mymapPrice.insert ( std::pair<string,double>("Curly Maple",6.00) );
 mymapPrice.insert ( std::pair<string,double>("Genuine Mahogany",9.60) );
 mymapPrice.insert ( std::pair<string,double>("Wenge",22.35) );
 mymapPrice.insert ( std::pair<string,double>("White Oak",6.70) );
 mymapPrice.insert ( std::pair<string,double>("Sawdust",1.5) );

}

/*
 *  * Method to read the input file
 *   */
void readInputFile(string inputFilePath) {
	string file = "1.txt";
	string line, line2;
	vector<string> rand;
	int k = 0;
	ifstream myfile(file.c_str()); 
	while(!myfile.eof()) { 
	getline(myfile, line);
		Buyer temp;	
		char *name_ = strtok(strdup(line.c_str()),";");
		if(name_ != NULL) 
			temp.name = name_; 	
		char *address_ = strtok(NULL, ";");
		if(address_ != NULL)
			temp.address = address_;
		char *date_ = strtok(NULL, "\n");
		if(date_ != NULL)
			temp.date = date_;
	size_t prev = 0, pos;
		getline(myfile, line2);
		while ((pos = line2.find_first_of(":;", prev)) != std::string::npos) {
			if(pos > prev) {
				rand.push_back(line2.substr(prev, pos-prev));
				prev = pos+1;
			}
		}
		if (prev < line2.length()) {
			rand.push_back(line2.substr(prev, pos-prev));
		}
	   for(int i = 0; i < rand.size(); i+=2) 
		 temp.woodtype.push_back(rand[i]);	   	
	   for(int i = 1; i < rand.size(); i+=2) { 
		 temp.amount.push_back(atoi(rand[i].c_str()));
	   }
	   
	   buyers.push_back(temp);
	   rand.clear();
			   
	}
	myfile.close();
}	
/*
 *  * Method to compute the deliveryTime
 *   */
double maxTime(vector<double> arr) {
 vector<double>::const_iterator its;
 its = max_element(arr.begin(), arr.end());
 return *its;

}

vector<double>  Price() {
         vector<double> pricePerBuyer(buyers.size() - 1);
	for(int i = 0; i < buyers.size() -1; i++) {
	double totalPrice = 0;
	  for(int j = 0; j < buyers[i].woodtype.size(); j++) {
	    map<string, double>::iterator its;
	    its = mymapPrice.find(buyers[i].woodtype[j]);
	    totalPrice += buyers[i].amount[j] * (its->second);
	  }
	   pricePerBuyer.push_back(totalPrice);
	}  
	return pricePerBuyer;
}

vector<double> deliveryTime() {
	double deliveryETA = 0.0;
	vector<double> itemDeliveryTime;
	vector<double> finalDeliveryTime;
 	for(int i = 0; i < buyers.size() -1; i++) {
	  for(int j = 0; j < buyers[i].woodtype.size(); j++) {
	    if((buyers[i].amount[j] >= 1) && (buyers[i].amount[j] <= 100)) {
	       map<string, double>::iterator it;
	       it = mymap.find(buyers[i].woodtype[j]);
	       double itemDelivery = 1 * (it->second);
	       itemDeliveryTime.push_back(itemDelivery);
	    } else if((buyers[i].amount[j] >= 101) && (buyers[i].amount[j] <= 200)) {
	       map<string, double>::iterator it;
	       it = mymap.find(buyers[i].woodtype[j]);
	       double itemDelivery = 2 * (it->second);
	       itemDeliveryTime.push_back(itemDelivery);
	    } else if((buyers[i].amount[j] >= 201) && (buyers[i].amount[j] <= 300)) {
	       map<string, double>::iterator it;
	       it = mymap.find(buyers[i].woodtype[j]);
	       double itemDelivery = 3 * (it->second);
	       itemDeliveryTime.push_back(itemDelivery);
	    } else if((buyers[i].amount[j] >= 301) && (buyers[i].amount[j] <= 400)) {
	       map<string, double>::iterator it;
	       it = mymap.find(buyers[i].woodtype[j]);
	       double itemDelivery= 4 * (it->second);
	       itemDeliveryTime.push_back(itemDelivery);
	    } else if((buyers[i].amount[j] >= 401) && (buyers[i].amount[j] <= 500)) {
	       map<string, double>::iterator it;
	       it = mymap.find(buyers[i].woodtype[j]);
	       double itemDelivery = 5 * (it->second);
	       itemDeliveryTime.push_back(itemDelivery);
	    } else if((buyers[i].amount[j] >= 501) && (buyers[i].amount[j] <= 1000)) {
	       map<string, double>::iterator it;
	       it = mymap.find(buyers[i].woodtype[j]);
	       double itemDelivery = 5.5 * (it->second);
	       itemDeliveryTime.push_back(itemDelivery);
	    }
	   }
	    double time_ = maxTime(itemDeliveryTime);
	   itemDeliveryTime.clear();
	   finalDeliveryTime.push_back(time_);
	}   
	return finalDeliveryTime;
}

void output(vector<double> &del_, vector<double> &time_) {
	double total_price = 0;
	for(int i = 0; i < buyers.size() -1; i++) {
	    cout << "******************BUYER" << i+1 << "*********************************\n"; 	
	    cout << "Buyer's Name: " << buyers[i].name << "\n";
	    cout << "Delivery address: " << buyers[i].address <<"\n";
	  for(int j = 0; j < buyers[i].woodtype.size(); j++) {
	    cout << "Purchased Woodtypes: " << buyers[i].woodtype[j] <<"\n";
	    cout << "BF: " << buyers[i].amount[j] <<"\n";
	    double price_ = 0;
	    map<string, double>::iterator its;
	    its = mymapPrice.find(buyers[i].woodtype[j]);
	    price_ = buyers[i].amount[j] * (its->second);
	    total_price+= price_;
	    cout << "Price for woodtype and BF: " << price_ <<"\n";
	  }
	    cout << "Estimated delivery time: " << del_[i] <<"\n";
	    cout << "Total purchase price: " << total_price << "\n";
	}  



}
