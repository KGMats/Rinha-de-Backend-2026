#include"../include/vector.hpp"
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;
using namespace std;

int main(int argc, char *argv[])
{
    json test_dict = json::parse(R"({ "id": "tx-1329056812",
	"transaction": {
	      "amount": 41.12,
	      "installments": 2,
	      "requested_at": "2026-03-11T18:45:53Z"
	    },
	"customer": {
	      "avg_amount": 82.24,
	      "tx_count_24h": 3,
	      "known_merchants": [
		"MERC-003",
		"MERC-016"
	      ]
	    },
	"merchant": {
	      "id": "MERC-016",
	      "mcc": "5411",
	      "avg_amount": 60.25
	    },
	"terminal": {
	      "is_online": false,
	      "card_present": true,
	      "km_from_home": 29.2331036248
	    },
	"last_transaction": null
    })");

    Vector v = request_treatment(test_dict);
    cout<<"v[";
    for(int i = 0; i < 14; i++){
	cout<<v.components[i];
	if(i != 13)cout<<", ";
    }
    cout<<"]"<<endl;
    cout<<endl<<endl;
    v = normalize_vector(v);
    cout<<"v[";
    for(int i = 0; i < 14; i++){
	cout<<v.components[i];
	if(i != 13)cout<<", ";
    }
    cout<<"]"<<endl;
    return 0;
}
