#include "vector.hpp"
#include <ostream>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

/*
 * @brief compares if two vector have all the fields values in commom
 */
bool vector_is_equals(Vector v1, Vector v2)
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
    float delta;

    delta = (float)(v1.components.amount - v2.components.amount)/100000;
    distance += delta * delta;
    delta = (float)(v1.components.installments - v2.components.installments)/100;
    distance += delta * delta;
    delta = (float)(v1.components.amount_vs_avg - v2.components.amount_vs_avg)/100000;
    distance += delta * delta;
    delta = (float)(v1.components.hour_of_day - v2.components.hour_of_day)/100;
    distance += delta * delta;
    delta = (float)(v1.components.day_of_week - v2.components.day_of_week)/100;
    distance += delta * delta;
    delta = (float)(v1.components.minutes_since_last_tx - v2.components.minutes_since_last_tx)/100000;
    distance += delta * delta;
    delta = (float)(v1.components.km_from_last_tx - v2.components.km_from_last_tx)/100000;
    distance += delta * delta;
    delta = (float)(v1.components.km_from_home - v2.components.km_from_home)/100000;
    distance += delta * delta;
    delta = (float)(v1.components.tx_count_24h - v2.components.tx_count_24h)/100;
    distance += delta * delta;
    delta = (float)(v1.components.is_online - v2.components.is_online);
    distance += delta * delta;
    delta = (float)(v1.components.card_present - v2.components.card_present);
    distance += delta * delta;
    delta = (float)(v1.components.unknown_merchant - v2.components.unknown_merchant);
    distance += delta * delta;
    delta = (float)(v1.components.merchant_avg_amount - v2.components.merchant_avg_amount)/100000;
    distance += delta * delta;
    delta = (float)(v1.components.mcc_risk - v2.components.mcc_risk)/100;
    distance += delta * delta;

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

    if(*p == 'n'){ p += 4;
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

        while(*p && *p != '}')
        {
            ++p;
        }
        if(*p)
        {
            ++p;
        }

    }
    while(*p && *p != '}')
    {
        ++p;
    }

    if(*p)
    {
        ++p;
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
        //v = normalize_vector(v);
        data.push_back(v);
        next_char = *p;
    }
    return data;
}

/*
 * @brief parse a already normalized vector and get its values for test
 */
Vector* references_parser(const char* json_dict) {
    Vector* data = (Vector*) malloc(sizeof(Vector) * NVECTORS);
    const char* p = json_dict;
    size_t vector_idx = 0;

    if (*p != '[')
    {
        return data;
    }

    // Pointers to each field in declaration order, matching the JSON array layout.
    // All stored as uint16_t* — narrow fields (uint8_t) are widened on write via the helper below.
    // Index:  0       1              2             3            4             5                      6                 7             8              9           10             11                 12          13
    //       amount installments amount_vs_avg hour_of_day day_of_week minutes_since_last_tx km_from_last_tx km_from_home tx_count_24h is_online card_present unknown_merchant mcc_risk merchant_avg_amount

    char next_char = ',';
    while (next_char == ',') {
        Vector v = {};

        next_val(p);
        if (*p != '[') return data;

        bool last_transaction = true;
        uint16_t fields[14] = {};

        for (int index = 0; index < 14; index++) {
            // Advance to next number (or '-' sentinel for null fields)
            while (*p != ']') {
                if (*p == '-' || is_num(*p)) break;
                ++p;
            }

            // Indices 5 and 6 are km/minutes which are -1 when there's no last tx
            bool is_nullable = (index == 5 || index == 6);
            if (is_nullable && *p == '-') {
                last_transaction = false;
                ++p; // skip '-'
            }

            // Indices that need 2-digit truncation (were encoded as e.g. 0.8333 -> 83)
            bool needs_trunc = (index == 1 || index == 3 || index == 4 || index == 8);
            if (needs_trunc) {
                uint16_t aux = get_float(p);
                uint16_t tmp = aux; int size = 0;
                while (tmp > 0) { tmp /= 10; size++; }
                if (size > 2) {
                    string digits = to_string(aux);
                    uint8_t value = (digits[0] - '0') * 10 + (digits[1] - '0');
                    fields[index] = value;
                } else {
                    fields[index] = aux;
                }
            } else {
                fields[index] = get_float(p);
            }
        }

        v.components.amount                = fields[0];
        v.components.installments          = (uint8_t)fields[1];
        v.components.amount_vs_avg         = fields[2];
        v.components.hour_of_day           = (uint8_t)fields[3];
        v.components.day_of_week           = (uint8_t)fields[4];
        v.components.minutes_since_last_tx = fields[5];
        v.components.km_from_last_tx       = fields[6];
        v.components.km_from_home          = fields[7];
        v.components.tx_count_24h          = (uint8_t)fields[8];
        v.components.is_online             = (bool)fields[9];
        v.components.card_present          = (bool)fields[10];
        v.components.unknown_merchant      = (bool)fields[11];
        v.components.mcc_risk              = (uint8_t)fields[12];
        v.components.merchant_avg_amount   = fields[13];
        v.components.last_transaction      = last_transaction;

        next_val(p);
        ++p; // skip opening '"' of label value
        v.label = *p;

        while (*p != '}') ++p;
        ++p;

        data[vector_idx++] = v;
        next_char = *p;
    }
    return data;
}

void print_vector(Vector v)
{
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
    cout << "mcc_risk: " << (int) v.components.mcc_risk << endl;
    cout << "merchant_avg_amount: " << v.components.merchant_avg_amount << endl;
    cout << "label: " << v.label << endl;
    cout << endl;
}
