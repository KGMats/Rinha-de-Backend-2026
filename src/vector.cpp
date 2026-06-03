#include "../include/vector.hpp"
#include <string>
#include <vector>
#include <cmath>

using namespace std;

/*
 * @brief compares if two vector have all the fields values in commom
 */
inline bool vector_is_equals(Vector v1, Vector v2)
{
	if (v1.components.amount != v2.components.amount)
	{
		return false;
	}
	if (v1.components.installments != v2.components.installments)
	{
		return false;
	}
	if (v1.components.amount_vs_avg != v2.components.amount_vs_avg)
	{
		return false;
	}
	if (v1.components.hour_of_day != v2.components.hour_of_day)
	{
		return false;
	}
	if (v1.components.day_of_week != v2.components.day_of_week)
	{
		return false;
	}
	if (v1.components.km_from_last_tx != v2.components.km_from_last_tx)
	{
		return false;
	}
	if (v1.components.km_from_home != v2.components.km_from_home)
	{
		return false;
	}
	if (v1.components.tx_count_24h != v2.components.tx_count_24h)
	{
		return false;
	}
	if (v1.components.is_online != v2.components.is_online)
	{
		return false;
	}
	if (v1.components.card_present != v2.components.card_present)
	{
		return false;
	}
	if (v1.components.unknown_merchant != v2.components.unknown_merchant)
	{
		return false;
	}
	if (v1.components.mcc_risk != v2.components.mcc_risk)
	{
		return false;
	}
	if (v1.components.merchant_avg_amount != v2.components.merchant_avg_amount)
	{
		return false;
	}
	return true;
}

/*
 *@brief return the vector field associated to its numeric index 
 */
uint16_t get_components(Vector& v, int index){
	switch (index){
		case 0: return v.components.amount;
		case 1: return v.components.installments;
		case 2: return v.components.amount_vs_avg;
		case 3: return v.components.hour_of_day;
		case 4: return v.components.day_of_week;
		case 5: return v.components.minutes_since_last_tx;
		case 6: return v.components.km_from_last_tx;
		case 7: return v.components.km_from_home;
		case 8: return v.components.tx_count_24h;
		case 9: return v.components.is_online;
		case 10: return v.components.card_present;
		case 11: return v.components.unknown_merchant;
		case 12: return v.components.mcc_risk;
		case 13: return v.components.merchant_avg_amount;
		default: return v.components.last_transaction;
	}
}

/*
 * @brief calculates the Manhattam Distance between two Vectors
 */
float simple_distance(Vector v1, Vector v2)
{
    	float distance = 0;
	distance += abs((float)v1.components.amount/10000.0f - (float)v2.components.amount/10000.0f);
	distance += abs((float)v1.components.installments/100.0f - (float)v2.components.installments/100.0f);
	distance += abs((float)v1.components.amount_vs_avg/10000.0f - (float)v2.components.amount_vs_avg/10000.0f);
	distance += abs((float)v1.components.hour_of_day/100.0f - (float)v2.components.hour_of_day/100.0f);
	distance += abs((float)v1.components.day_of_week/100.0f - (float)v2.components.day_of_week/100.0f);
	distance += abs((float)v1.components.minutes_since_last_tx/10000.0f - (float)v2.components.minutes_since_last_tx/10000.0f); 
	distance += abs((float)v1.components.km_from_last_tx/10000.0f - (float)v2.components.km_from_last_tx/10000.0f);
	distance += abs((float)v1.components.km_from_home/10000.0f - (float)v2.components.km_from_home/10000.0f);
	distance += abs((float)v1.components.tx_count_24h/100.0f - (float)v2.components.tx_count_24h/100.0f);
	distance += abs((float)v1.components.is_online - (float)v2.components.is_online);
	distance += abs((float)v1.components.card_present - (float)v2.components.card_present);
	distance += abs((float)v1.components.unknown_merchant - (float)v2.components.unknown_merchant);
	distance += abs((float)v1.components.merchant_avg_amount/10000.0f - (float)v2.components.merchant_avg_amount/10000.0f);
	distance += abs((float)v1.components.mcc_risk/100.0f - v2.components.mcc_risk/100.0f);
	return distance;
}

/*
 * @brief calculates the euclician distance between two Vectors
 */
float euclidian_distance(Vector v1, Vector v2)
{
	float distance = 0;
	distance += pow((float)v1.components.amount/10000.0f - (float)v2.components.amount/10000.0f, 2);
	distance += pow((float)v1.components.installments/100.0f - (float)v2.components.installments/100.0f, 2);
	distance += pow((float)v1.components.amount_vs_avg/10000.0f - (float)v2.components.amount_vs_avg/10000.0f, 2);
	distance += pow((float)v1.components.hour_of_day/100.0f - (float)v2.components.hour_of_day/100.0f, 2);
	distance += pow((float)v1.components.day_of_week/100.0f - (float)v2.components.day_of_week/100.0f, 2);
	distance += pow((float)v1.components.minutes_since_last_tx/10000.0f - (float)v2.components.minutes_since_last_tx/10000.0f, 2); 
	distance += pow((float)v1.components.km_from_last_tx/10000.0f - (float)v2.components.km_from_last_tx/10000.0f, 2);
	distance += pow((float)v1.components.km_from_home/10000.0f - (float)v2.components.km_from_home/10000.0f, 2);
	distance += pow((float)v1.components.tx_count_24h/100.0f - (float)v2.components.tx_count_24h/100.0f, 2);
	distance += pow((float)v1.components.is_online - (float)v2.components.is_online, 2);
	distance += pow((float)v1.components.card_present - (float)v2.components.card_present, 2);
	distance += pow((float)v1.components.unknown_merchant - (float)v2.components.unknown_merchant, 2);
	distance += pow((float)v1.components.merchant_avg_amount/10000.0f - (float)v2.components.merchant_avg_amount/10000.0f, 2);
	distance += pow((float)v1.components.mcc_risk/100.0f - v2.components.mcc_risk/100.0f, 2);
	return distance;
}

/*
 * @brief switch with mcc cases and their return type
 */
uint8_t mcc_risk(uint16_t mcc_code){
	switch(mcc_code){
		case 5411 :return 15;
		case 5812 :return 3;
		case 5912 :return 2;
		case 5944 :return 45;
		case 7801 :return 8;
		case 7802 :return 75;
		case 7995 :return 85;
		case 4511 :return 35;
		case 5311 :return 25;
		case 5999 :return 5; //comment?
		default: return 5;	
	}
} 

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
 * @brief iterates to the next position of a value in request
 */
void next_val(const char* &p){
    while(*p && *p != ':'){
        if(*p == '"'){ ++p; while(*p && *p != '"'){ if(*p=='\\')++p; ++p; } ++p; }
        else ++p;
    }
    if(*p) ++p;
    while(*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')++p;
}

/*
 * @brief skips the pointer to the position rightmost of a brace
 */
void skip_to_brace(const char* &p){
    while(*p){
        if(*p == '"'){
            ++p;
            while(*p && *p != '"'){
                if(*p == '\\')++p;
                ++p;
            }
        }
        if(*p == '{')return;
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
uint16_t parse_datetime_element(const char* &p, char* req_at, int&i){
	uint16_t aux = 0;
	while(is_num(*p)){
		aux = aux*10 + (uint16_t)(*p - '0');
		req_at[i] = *p;
		i+=1;
		++p;
	}req_at[i] = *p; i+=1; ++p;
	return aux;
}

/*
 * @brief parses and divides the iso string into varibles 
 */
void parse_iso(const char* &p, char* req_at, int& i, uint16_t& year, uint8_t& month, uint8_t& day, uint8_t& hour, uint8_t& minute, uint8_t& second){
	year = parse_datetime_element(p,req_at,i);
	month = parse_datetime_element(p,req_at,i);
	day = parse_datetime_element(p,req_at,i);
	hour = parse_datetime_element(p,req_at,i);
	minute = parse_datetime_element(p,req_at,i);
	second = parse_datetime_element(p,req_at,i);
	
	req_at[i] = '\0'; // REQUIRED for strptime to work correctly later
}

/*
 * @brief Based on the parsed iso string, returns the respective day of week of the given date with the ctime library
 *
 * thanks to SrPatoS
 */
uint8_t get_day_of_week(uint16_t year, uint8_t month, uint8_t day){
	    if (month < 3) {
		month += 12;
		year--;
	    }
	    uint8_t century = year % 100;
	    uint8_t decade = year / 100;
	    uint8_t h = (day + (13 * (month + 1)) / 5 + century + century / 4 + decade / 4 + 5 * decade) % 7;
	    return ((((h + 6) % 7)+6) % 7);
}

/*
 * @breif returns the total num of days based on current datetime
 *
 * thanks to SrPatoS
 */
static long days_from_civil(int year, unsigned month, unsigned day){
    year -= month <= 2;
    const int era = (year >= 0 ? year : year - 399) / 400;
    const unsigned yoe = (unsigned)(year - era * 400);
    const unsigned doy = (153 * (month + (month > 2 ? -3 : 9)) + 2) / 5 + day - 1;
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097L + (long)doe - 719468L;
}

/*
 * @brief returns the diference in time in double of two iso strings
 *
 * thanks to SrPatoS
 */
uint16_t get_diff(uint16_t y1,uint8_t mo1,uint8_t d1,uint8_t h1, uint8_t mi1,uint16_t y2,uint8_t mo2,uint8_t d2, uint8_t h2, uint8_t mi2){
    long days1 = days_from_civil(y1, mo1, d1);
    long days2 = days_from_civil(y2, mo2, d2);
    long total1 = days1 * 1440L + h1 * 60L + mi1;
    long total2 = days2 * 1440L + h2 * 60L + mi2;
    long diff = total2 - total1;
    return diff < 0 ? 0.0 : (uint16_t)diff;
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

	v.components.amount = get_uint16(p);

	next_val(p);

	v.components.installments = get_uint8(p);

	next_val(p);
	++p;

	char req_at[21]; int i = 0;uint16_t year;
	uint8_t month,day,hour,minute,second;
	parse_iso(p,req_at,i,year,month,day,hour,minute,second);
	
	v.components.hour_of_day = hour;

	v.components.day_of_week = get_day_of_week(year,month,day); 
	
	++p;
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

	v.components.merchant_avg_amount = get_uint16(p);

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

		next_val(p);
		if (*p) ++p; // Prevent stepping out of bounds if next_val hits \0
		
		char last_req[21]; int h =0; uint16_t yearlt;
		uint8_t monthlt,daylt,hourlt,minutelt,secondlt;
		parse_iso(p,last_req,h,yearlt,monthlt,daylt,hourlt,minutelt,secondlt);

		next_val(p);	
		v.components.km_from_last_tx = get_km(p);

		while(*p && *p != '}') ++p; if(*p) ++p;
	}
	while(*p && *p != '}') ++p; if(*p) ++p;
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
		//v = normalize_vector(v);
		data.push_back(v);
		next_char = *p;
	}
	return data;
}

/*
 *@brief switch to classify the vector field the numeric index refers to
 */
void populate_v_index(Vector& v, uint16_t value, int index){
	switch (index){
		case 0: v.components.amount = value;
		case 1: v.components.installments = value;
		case 2: v.components.amount_vs_avg = value;
		case 3: v.components.hour_of_day = value;
		case 4: v.components.day_of_week = value;
		case 5: v.components.minutes_since_last_tx = value;
		case 6: v.components.km_from_last_tx = value;
		case 7: v.components.km_from_home = value;
		case 8: v.components.tx_count_24h = value;
		case 9: v.components.is_online = value;
		case 10: v.components.card_present = value;
		case 11: v.components.unknown_merchant = value;
		case 12: v.components.mcc_risk = value;
		case 13: v.components.merchant_avg_amount = value; 
		case 14: v.components.last_transaction = value;
	}
}

/*
 * @brief parse a already normalized vector and get its values for test
 */
vector<Vector> references_parser(const char* json_dict){

	vector<Vector> data;
	const char* p = json_dict;

	if(*p != '[')return data;		

	char next_char = ',';

	while(next_char == ','){
		Vector v;
		
		next_val(p);
		if(*p != '[') return data;

		int index = 0; bool last_transaction = true;
		while(index != 14){
			while(*p != ']'){ 
				if(*p == '-')break;
				if(is_num(*p))break; 
				++p;
		       	}
			if(index == 5 || index == 6){
				if(*p == '-') last_transaction = false;
				++p;
			}
			if(index == 1 || index == 3 || index == 4 || index == 8){
				uint16_t aux = get_float(p);
				uint16_t tmp = aux; int size = 0;
				while(tmp > 0){ tmp /= 10; size += 1; }	
				if(size > 2){
					uint8_t value = 0;
					string digits = to_string(aux);
					for(int d=0; d<2; d++){ value = value*10 + (uint8_t)(digits[d] - '0'); }
					populate_v_index(v,value,index);
				}
				else populate_v_index(v,aux,index);
			}
			else populate_v_index(v,get_float(p),index);
			index += 1;
		}populate_v_index(v,last_transaction,index);

		next_val(p);
		++p;

		v.label = *p;

		while(*p != '}')++p;
		++p;

		data.push_back(v);
		next_char = *p;
	}
	return data;
}
