#include <nlohmann/json.hpp>
#include "../include/vector.hpp"
#include <string>
#include <cmath>
#include <ctime>
#include <map>

using namespace std;
using json = nlohmann::json;

uint16_t simple_distance(Vector v1, Vector v2)
{
    uint16_t distance = 0;
    for (int i = 0; i < VECTOR_DIMENSIONS; i++)
    {
        distance += std::abs(v1.components[i] - v2.components[i]);
    }
    return distance;
}

uint16_t euclidian_distance(Vector v1, Vector v2)
{
    uint16_t distance = 0;
    for (int i = 0; i < VECTOR_DIMENSIONS; i++)
    {
        distance += pow(v1.components[i] - v2.components[i], 2);
    }
    return distance;
}

/*
 * @brief Filters the raw data from a single request json dict input
 * and returns a treated non normalized vector
 */
Vector request_treatment(const json& request){
	Vector v;

	auto t = request["transaction"];
	auto c = request["customer"];
	auto m = request["merchant"];
	auto terminal = request["terminal"];
	auto l = request["last_transaction"];
	
	v.components[0] = t["amount"]; //float
	v.components[1] = t["installments"]; //short 
	v.components[2] = ((float)t["amount"]/(float)c["avg_amount"]); //float

	short hour_of_day = 0; short aux = 10; 
	string t_cur_str = (string)t["requested_at"];
	const char* t_cur = t_cur_str.c_str();
	for(int i = 11; i <= 12; i++){
		if(t_cur[i]=='1')hour_of_day+=1*aux;
		else if(t_cur[i]=='2')hour_of_day+=2*aux;
		else if(t_cur[i]=='3')hour_of_day+=3*aux;
		else if(t_cur[i]=='4')hour_of_day+=4*aux;
		else if(t_cur[i]=='5')hour_of_day+=5*aux;
		else if(t_cur[i]=='6')hour_of_day+=6*aux;
		else if(t_cur[i]=='7')hour_of_day+=7*aux;
		else if(t_cur[i]=='8')hour_of_day+=8*aux;
		else if(t_cur[i]=='9')hour_of_day+=9*aux;
		aux = 1;
	}v.components[3] = hour_of_day; //short

	struct tm parsed = {};
	strptime(t_cur,"%Y-%m-%dT%H:%M:%SZ",&parsed);
	time_t t1 = timegm(&parsed);
	struct tm* utc_time = gmtime(&t1);
	short day = utc_time->tm_wday; // 0 sunday 6 saturday
	if(day==0)day=6;
	else day -= 1;
	v.components[4] = day; // short 

	if(l.is_null()){
	       	v.components[5] = - 1; //short
		v.components[6] = -1; //short
	}
	else{
		struct tm parsed1 = {};
		string t2_str = (string)l["timestamp"];
		const char* timestamp2 = t2_str.c_str();
		strptime(timestamp2,"%Y-%m-%dT%H:%M:%SZ",&parsed1);
		time_t t2 = timegm(&parsed1); // negative time check?
		v.components[5] = (difftime(t1,t2)/60.0); //double
		v.components[6] = l["km_from_current"]; //double
	}	

	v.components[7] = terminal["km_from_home"]; //double
	v.components[8] = c["tx_count_24h"]; //short
	
	if(terminal["is_online"])v.components[9] = 1; //short
        else v.components[9] = 0;	//short

	if(terminal["card_present"])v.components[10] = 1;
	else v.components[10] = 0;

	bool unknown = true;
	for(auto& id : c["known_merchants"])
	{
		if(id==m["id"]){unknown = false; break; }
	}
	if(unknown)v.components[11] = 1; //short
	else v.components[11] = 0; //short

	string identifier = (string)m["mcc"];
	if(mcc_risk.count(identifier))v.components[12] = mcc_risk.at(identifier);//float
	else v.components[12] = 0.5; //float

	v.components[13] = m["avg_amount"]; //double

	v.label = 'n'; // none = unknown

	return v;
}

// need to specify that float values until the 4th digit, round???
Vector normalize_vector(Vector& v)
{	
	int max_amount = normalization_dict.at("max_amount");
	int max_installments = normalization_dict.at("max_installments");
	int amount_vs_avg_ratio = normalization_dict.at("amount_vs_avg_ratio");
	int max_minutes = normalization_dict.at("max_minutes");
	int max_km = normalization_dict.at("max_km");
	int max_tx_count_24h = normalization_dict.at("max_tx_count_24h");
	int max_merchant_avg_amount = normalization_dict.at("max_merchant_avg_amount");

	if(v.components[0] >= max_amount)v.components[0] = 1.0;
	else if(v.components[0] <= 0)v.components[0] = 0.0;
	else v.components[0] /= max_amount;	

	if(v.components[1] >= max_installments)v.components[1] = 1.0;
	else if(v.components[1] <= 0)v.components[1] = 0.0;
	else v.components[1] /= max_installments;

	if(v.components[2] >= amount_vs_avg_ratio)v.components[2] = 1.0;
	else if(v.components[2] <= 0)v.components[2] = 0.0;
	else v.components[2] /= amount_vs_avg_ratio;

	if(v.components[3] >= 23)v.components[3] = 1.0;
	else if(v.components[3] <= 0)v.components[3] = 0.0;
	else v.components[3] /= 23;

	if(v.components[4] >= 6)v.components[4] = 1.0;
	else if(v.components[4] <= 0)v.components[4] = 0.0;
	else v.components[4] /= 6;

	if(v.components[5] != -1.0)v.components[5] /= max_minutes;

	if(v.components[6] != -1.0)v.components[6] /= max_km;

	v.components[7] /= max_km;

	if(v.components[8] >= max_tx_count_24h)v.components[8] = 1.0;
	else if(v.components[8] <= 0)v.components[8] = 0.0;
	else v.components[8] /= max_tx_count_24h;

	if(v.components[13] >= max_merchant_avg_amount)v.components[13] = 1.0;
	else if(v.components[13] <= 0)v.components[13] = 0.0;
	else v.components[13] /= max_merchant_avg_amount;

	// do something with the label!??!?!
	
	for(int i = 0; i < VECTOR_DIMENSIONS; i++){
		if(v.components[i] == 0.0 ||
		   v.components[i] == -1  ||
		   v.components[i] == 1) continue;
		else v.components[i] = round(v.components[i] * 10000.0f) / 10000.0f;
	}	

	return v;
}
