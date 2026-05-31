#include"../include/vector.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    char test;
    ifstream file("../docs/example-payloads.json");

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    const char* json_dict = content.c_str();

    vector<Vector> data = payload_parser(json_dict);

    for(Vector& v : data){
	    cout << "amount: " << v.components.amount << endl;
	    cout << "installments: " << (int)v.components.installments << endl;
	    cout << "amount_vs_avg: " << v.components.amount_vs_avg << endl;
	    cout << "hour_of_day: " << (int)v.components.hour_of_day << endl;
	    cout << "day_of_week: " << (int)v.components.day_of_week << endl;
	    cout << "km_from_last_tx: " << v.components.km_from_last_tx << endl;
	    cout << "km_from_home: " << v.components.km_from_home << endl;
	    cout << "minutes_since_last_tx: " << v.components.minutes_since_last_tx << endl;
	    cout << "tx_count_24h: " << (int)v.components.tx_count_24h << endl;
	    cout << "is_online: " << v.components.is_online << endl;
	    cout << "card_present: " << v.components.card_present << endl;
	    cout << "unknown_merchant: " << v.components.unknown_merchant << endl;
	    cout << "last_transaction: " << v.components.last_transaction << endl;
	    cout << "mcc_risk: " << v.components.mcc_risk << endl;
	    cout << "merchant_avg_amount: " << v.components.merchant_avg_amount << endl;
	    cout << "label: " << v.label << endl;
	    cout << endl;
    }

    return 0;
}
