#include "../include/vector.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <map>

using namespace std;

//uint16_t simple_distance(Vector v1, Vector v2)
//{
//    uint16_t distance = 0;
//    for (int i = 0; i < VECTOR_DIMENSIONS; i++)
//    {
//        distance += std::abs(v1.components[i] - v2.components[i]);
//    }
//    return distance;
//}
//
//uint16_t euclidian_distance(Vector v1, Vector v2)
//{
//    uint16_t distance = 0;
//    for (int i = 0; i < VECTOR_DIMENSIONS; i++)
//    {
//        distance += pow(v1.components[i] - v2.components[i], 2);
//    }
//    return distance;
//}

/*
 * @brief switch with mcc cases and their return type
 */
const uint16_t mcc_risk(uint16_t mcc_code){
	switch(mcc_code){
		case 5411 :return 1500;
		case 5812 :return 3000;
		case 5912 :return 2000;
		case 5944 :return 4500;
		case 7801 :return 8000;
		case 7802 :return 7500;
		case 7995 :return 8500;
		case 4511 :return 3500;
		case 5311 :return 2500;
		case 5999 :return 5000; //comment?
		default: return 5000;	
	} } /*
 * @brief Filters the raw data from a single request json dict input
 * and returns a treated non normalized vector
 */
//Vector request_treatment(const char* request){
//	Vector v;
//
//
//	auto t = request["transaction"];
//	auto c = request["customer"];
//	auto m = request["merchant"];
//	auto terminal = request["terminal"];
//	auto l = request["last_transaction"];
//	
//	v.components[0] = t["amount"]; //float
//	v.components[1] = t["installments"]; //short 
//	v.components[2] = ((float)t["amount"]/(float)c["avg_amount"]); //float
//
//	short hour_of_day = 0; short aux = 10; 
//	string t_cur_str = (string)t["requested_at"];
//	const char* t_cur = t_cur_str.c_str();
//	for(int i = 11; i <= 12; i++){
//		if(t_cur[i]=='1')hour_of_day+=1*aux;
//		else if(t_cur[i]=='2')hour_of_day+=2*aux;
//		else if(t_cur[i]=='3')hour_of_day+=3*aux;
//		else if(t_cur[i]=='4')hour_of_day+=4*aux;
//		else if(t_cur[i]=='5')hour_of_day+=5*aux;
//		else if(t_cur[i]=='6')hour_of_day+=6*aux;
//		else if(t_cur[i]=='7')hour_of_day+=7*aux;
//		else if(t_cur[i]=='8')hour_of_day+=8*aux;
//		else if(t_cur[i]=='9')hour_of_day+=9*aux;
//		aux = 1;
//	}v.components[3] = hour_of_day; //short
//
//	struct tm parsed = {};
//	strptime(t_cur,"%Y-%m-%dT%H:%M:%SZ",&parsed);
//	time_t t1 = timegm(&parsed);
//	struct tm* utc_time = gmtime(&t1);
//	short day = utc_time->tm_wday; // 0 sunday 6 saturday
//	if(day==0)day=6;
//	else day -= 1;
//	v.components[4] = day; // short 
//
//	if(l.is_null()){
//	       	v.components[5] = - 1; //short
//		v.components[6] = -1; //short
//	}
//	else{
//		struct tm parsed1 = {};
//		string t2_str = (string)l["timestamp"];
//		const char* timestamp2 = t2_str.c_str();
//		strptime(timestamp2,"%Y-%m-%dT%H:%M:%SZ",&parsed1);
//		time_t t2 = timegm(&parsed1); // negative time check?
//		v.components[5] = (difftime(t1,t2)/60.0); //double
//		v.components[6] = l["km_from_current"]; //double
//	}	
//
//	v.components[7] = terminal["km_from_home"]; //double
//	v.components[8] = c["tx_count_24h"]; //short
//	
//	if(terminal["is_online"])v.components[9] = 1; //short
//        else v.components[9] = 0;	//short
//
//	if(terminal["card_present"])v.components[10] = 1;
//	else v.components[10] = 0;
//
//	bool unknown = true;
//	for(auto& id : c["known_merchants"])
//	{
//		if(id==m["id"]){unknown = false; break; }
//	}
//	if(unknown)v.components[11] = 1; //short
//	else v.components[11] = 0; //short
//
//	string identifier = (string)m["mcc"];
//	if(mcc_risk.count(identifier))v.components[12] = mcc_risk.at(identifier);//float
//	else v.components[12] = 0.5; //float
//
//	v.components[13] = m["avg_amount"]; //double
//
//	v.label = 'n'; // none = unknown
//
//	return v;
//}

/*
 * @brief receives a populated vector v and return this vector normalized
 */

Vector normalize_vector(Vector& v)
{	
	static const int max_amount = normalization_dict.at("max_amount");
	static const int max_installments = normalization_dict.at("max_installments");
	static const int amount_vs_avg_ratio = normalization_dict.at("amount_vs_avg_ratio");
	static const int max_minutes = normalization_dict.at("max_minutes");
	static const int max_km = normalization_dict.at("max_km");
	static const int max_tx_count_24h = normalization_dict.at("max_tx_count_24h");
	static const int max_merchant_avg_amount = normalization_dict.at("max_merchant_avg_amount");

	if((v.components.amount) >= max_amount*100)v.components.amount = 1.0;
	else if(v.components.amount <= 0)v.components.amount = 0.0;
	else v.components.amount  = 10000.0f*((float)v.components.amount /  ((float)max_amount * 100.0f)); 	

	if(v.components.installments >= max_installments)v.components.installments = 1.0;
	else if(v.components.installments <= 0)v.components.installments = 0.0;
	else v.components.installments = 100.0f*((float)v.components.installments / (float)max_installments);

	if(v.components.amount_vs_avg >= amount_vs_avg_ratio*100)v.components.amount_vs_avg = 1.0;
	else if(v.components.amount_vs_avg <= 0)v.components.amount_vs_avg = 0.0;
	else v.components.amount_vs_avg = 10000.0f*((float)v.components.amount_vs_avg / ((float)amount_vs_avg_ratio * 100.0f));

	if(v.components.hour_of_day >= 23)v.components.hour_of_day = 1.0;
	else if(v.components.hour_of_day <= 0)v.components.hour_of_day  = 0.0;
	else v.components.hour_of_day = 100.0f*((float)v.components.hour_of_day / (float)23);

	if(v.components.day_of_week >= 6)v.components.day_of_week = 1.0;
	else if(v.components.day_of_week <= 0)v.components.day_of_week = 0.0;
	else v.components.day_of_week = 100.0f*((float)v.components.day_of_week / (float)6);

	if(v.components.last_transaction == false){
		v.components.minutes_since_last_tx = 0;
		v.components.km_from_last_tx = 0;
	}else{
		v.components.minutes_since_last_tx = 100.0f*((float)v.components.minutes_since_last_tx / (float)max_minutes);
		v.components.km_from_last_tx =	1000.0f*((float)v.components.km_from_last_tx / (float)max_km);	
	}

	v.components.km_from_home = 1000.0f*((float)v.components.km_from_home /(float)max_km);

	if(v.components.tx_count_24h >= max_tx_count_24h)v.components.tx_count_24h = 1.0;
	else if(v.components.tx_count_24h <= 0)v.components.tx_count_24h = 0.0;
	else v.components.tx_count_24h = 100.0f*((float)v.components.tx_count_24h / (float)max_tx_count_24h);

	if(v.components.merchant_avg_amount >= max_merchant_avg_amount*100)v.components.merchant_avg_amount = 1.0;
	else if(v.components.merchant_avg_amount <= 0)v.components.merchant_avg_amount = 0.0;
	else v.components.merchant_avg_amount = 10000.0f*((float)v.components.merchant_avg_amount / ((float)max_merchant_avg_amount*100.0f));

	return v;
}

/*
 * @brief returns true if digit and false if not digit
 */
bool is_num(uint16_t n){ return (n >= '0' && n <= '9'); }

/*
 * @brief return true if cahr and false if not char (upper)
 */
bool is_char(char c){ return (c >= 'A' && c <= 'Z'); }

/*
 * @brief iterates to the next position of a value of request
 */
void next_val(const char* &p){
    while(*p && *p != ':'){
        if(*p == '"'){ ++p; while(*p && *p != '"'){ if(*p=='\\')++p; ++p; } ++p; }
        else ++p;
    }
    if(*p) ++p;
    while(*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')++p;
}

void skip_to_brace(const char* &p){
    while(*p){
        if(*p == '"'){
            ++p;
            while(*p && *p != '"'){
                if(*p == '\\')++p;
                ++p;
            }
        }
        if(*p == '{'){return;}
        ++p;
    }
}

/*
 * @brief returns a uint16 parsed 
 */
uint16_t get_uint16(const char* &p){
	uint16_t aux = 0;
	while(is_num(*p)){
		aux = aux*10 + (*p - '0');
		++p;
	}return aux;
}

/*
 * @brief returns a uint8_t parsed
 */
uint8_t get_uint8(const char* &p){
	uint8_t aux = 0;
	while(is_num(*p)){
		aux = aux*10 + (*p - '0');
		++p;
	}return aux;
}

/*
 * @brief returns a formatted parsed float as uint16_t
 */
uint16_t get_float(const char* &p){
	uint16_t aux = 0;
	while(is_num(*p) || *p == '.'){
		if(*p == '.') { ++p;continue; }
		aux = aux*10 + (*p - '0');
		++p;
	}return aux;
}

/*
 * @brief parses and returns the curr datetime element as uint8
 */
uint8_t parse_datetime_element(const char* &p, char* req_at, int&i){
	uint8_t aux = 0;
	while(is_num(*p)){
		aux = aux*10 + (uint8_t)(*p - '0');
		req_at[i] = *p;
		i+=1;
		++p;
	}req_at[i] = *p; i+=1; ++p;
	return aux;
}
/*
 * @brief parses and divides the iso string into varibles 
 */

void parse_iso(const char* &p, char* req_at, int& i, uint8_t& hour, uint8_t& minute, uint8_t& second){
	while(*p && *p != 'T' && i < 20) { req_at[i] = *p; i+=1; ++p; }
	
	if (!*p || *p != 'T') {
		req_at[i] = '\0';
		return;
	}
	
	req_at[i] = *p; i+=1; ++p;
	hour = parse_datetime_element(p,req_at,i);
	minute = parse_datetime_element(p,req_at,i);
	second = parse_datetime_element(p,req_at,i);
	
	req_at[i] = '\0'; // REQUIRED for strptime to work correctly later
}

/*
 * @brief Based on the parsed iso string, returns the respective day of week of the given date with the ctime library
 */
uint8_t get_day_of_week(char* req_at){
	const char* t_cur = req_at;
	struct tm parsed = {};
	strptime(t_cur,"%Y-%m-%dT%H:%M:%SZ",&parsed);
	time_t t1 = timegm(&parsed);
	struct tm* utc_time = gmtime(&t1);// limitation 1900+
	uint8_t day = utc_time->tm_wday; // 0 sunday 6 saturday
	if(day==0)day=6;
	else day -= 1;
	return day;
}

/*
 * @brief returns the diference in time in double of two iso strings
 */
double get_diff(char* req_at, char* last_req){
	struct tm date1 = {};
	struct tm date2 = {};
	strptime(req_at,"%Y-%m-%dT%H:%M:%SZ",&date1);	
	strptime(last_req,"%Y-%m-%dT%H:%M:%SZ",&date2);	
	time_t t1 = timegm(&date1);
	time_t t2 = timegm(&date2);
	double diff = difftime(t2,t1); //second to minute /60
	return diff;
}

/*
 * @brief Gets a mcc-like string
 */
void get_mcc(const char* &p, char* aux, int& i){
	while(is_char(*p) || is_num(*p) || *p == '-'){
		aux[i] = *p;
		++p;
		i+=1;
	}aux[i] = '\0';	
}

/*
 * @brief Created a dict with known_merchants for O(1) lookup
 */
unordered_map<string,bool> known_merchants(const char* &p){
	unordered_map<string,bool> km;
	if(*p != '[')return km; // wrong format
	while(*p != '"')++p;
	++p;
	for(;;){
		char aux[9];int i=0;	
		get_mcc(p,aux,i);	
		km.insert({string(aux),true});
		++p;
		if(*p == ','){ while(*p != '"')++p; ++p; }
		else break;
	}return km;
}

/*
 * @brief parses and returns the respective bool from json
 */
bool get_bool(const char* &p){
	if(*p == 'f')return false;
	else return true; // in case missinput!?
}

/*
 * @brief gets a 12 digit integers from the km fields
 */
uint16_t get_km(const char* &p){
	uint16_t aux = 0;
	int digits = 0;
	while(is_num(*p) || *p == '.'){
		if(*p == '.') { ++p;continue; }
		if(digits == 4)break;
		aux = aux*10 + (*p - '0');
		digits += 1;
		++p;
	}return aux;
}

/*
 * @brief parses a singular request and returns a populated vector with its values 
 */
Vector parse_request(const char* &p){
	Vector v;

    skip_to_brace(p);
	++p;

    skip_to_brace(p);
	++p;

	next_val(p);

	v.components.amount = get_float(p);
	next_val(p);

	v.components.installments = get_uint8(p);

	next_val(p);
	++p;

	char req_at[21]; int i = 0;
	uint8_t hour,minute,second;
	parse_iso(p,req_at,i,hour,minute,second);
	
	v.components.hour_of_day = hour;

	v.components.day_of_week = get_day_of_week(req_at); 

    skip_to_brace(p);
	++p;
	next_val(p);

	uint16_t avg_amount = get_float(p);
	v.components.amount_vs_avg = (uint16_t)(100.0f*((float)v.components.amount / (float)avg_amount));

	next_val(p);

	v.components.tx_count_24h = get_uint8(p);

	next_val(p);	

	unordered_map<string,bool> km = known_merchants(p);

    skip_to_brace(p);
	++p;
	next_val(p);

	char id[9];int j=0;
	++p; get_mcc(p,id,j);
    ++p;

	if(km.count(string(id))) v.components.unknown_merchant = false;
	else v.components.unknown_merchant = true;

	next_val(p);
    ++p;

	uint16_t mcc_risk_input = get_uint16(p);
    ++p;

	v.components.mcc_risk = mcc_risk(mcc_risk_input);

	next_val(p);

	v.components.merchant_avg_amount = get_float(p);

    skip_to_brace(p);
	++p;

	next_val(p);

	if(get_bool(p))v.components.is_online = true;
	else v.components.is_online = false;		

	next_val(p);

	if(get_bool(p))v.components.card_present = true;
	else v.components.card_present = false;		

	next_val(p);

	v.components.km_from_home = get_km(p);

    next_val(p);

	if(*p == 'n'){
		v.components.last_transaction = false;
		v.components.minutes_since_last_tx = v.components.km_from_last_tx = -1;
	} else {
		v.components.last_transaction = true;
		skip_to_brace(p);

		next_val(p);
		if (*p) ++p; // Prevent stepping out of bounds if next_val hits \0
		
		char last_req[21]; int h =0;
		uint8_t hourlt,minutelt,secondlt;
		parse_iso(p,last_req,h,hourlt,minutelt,secondlt);

		next_val(p);	
		v.components.km_from_last_tx = get_km(p);

		while(*p && *p != '}') ++p; if(*p) ++p;
		while(*p && *p != '}') ++p; if(*p) ++p;
	}
	v.label = 'n';
	return v;
}

/*
 * @brief parses a payload data until the end
 */
vector<Vector> payload_parser(const char* json_dict){
	vector<Vector> data;
	const char* p = json_dict;
	char next_char = ',';

	while(next_char == ','){
		Vector v = parse_request(p);
		v = normalize_vector(v);
		data.push_back(v);
		next_char = *p;
	}
	return data;
}
