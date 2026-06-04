#ifndef VECTOR_H
#define VECTOR_H

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

#define VECTOR_DIMENSIONS 14
//#define NVECTORS 3000000
//#define SQRT_NVECTORS 1733
//#define NVECTORS 500000
//#define SQRT_NVECTORS 708
//#define NVECTORS 10000
//#define SQRT_NVECTORS 100

#define NVECTORS 62500
#define SQRT_NVECTORS 250
using namespace std;

struct VectorContent
{
	uint16_t amount;
	uint16_t amount_vs_avg;
	uint16_t minutes_since_last_tx;
	uint16_t km_from_last_tx;
	uint16_t km_from_home;
	uint16_t merchant_avg_amount;
	uint8_t installments;
	uint8_t hour_of_day;
	uint8_t day_of_week;
	uint8_t tx_count_24h;
	uint8_t mcc_risk;
	bool is_online;
	bool card_present;
	bool unknown_merchant;
	//extra
	bool last_transaction;
};

struct Vector
{
    VectorContent components;
    char  label;   // f = fraud, l = legit, n = none
};

struct Content
{
	string contents[VECTOR_DIMENSIONS + 1] = { "amount", "installments", "amount_vs_avg", "hour_of_day", "day_of_week", "km_from_last_tx", "km_from_home", "minutes_since_last_tx", "tx_count_24h", "is_online", "card_present", "unknown_merchant", "last_transaction", "mcc_risk", "merchant_avg_amount" };
};

const unordered_map<string, int> normalization_dict = {
    {"max_amount", 10000},
    {"max_installments", 12},
    {"amount_vs_avg_ratio", 10},
    {"max_minutes", 1440},
    {"max_km", 1000},
    {"max_tx_count_24h", 20},
    {"max_merchant_avg_amount", 10000}
};


float simple_distance(Vector v1, Vector v2);
float euclidian_distance(Vector v1, Vector v2);

bool is_num(uint16_t n);
bool is_char(char c);

void next_val(const char* &p);

uint16_t get_uint16(const char* &p);
uint8_t get_uint8(const char* &p);
uint16_t get_float(const char* &p);

uint16_t parse_datetime_element(const char* &p, char* req_at, int&i);
void parse_iso(const char* &p, char* req_at, int& i, uint16_t& year, uint8_t& month, uint8_t& day, uint8_t& hour, uint8_t& minute, uint8_t& second);
uint16_t get_diff(uint16_t y1,uint8_t mo1,uint8_t d1,uint8_t h1, uint8_t mi1,uint16_t y2,uint8_t mo2,uint8_t d2, uint8_t h2, uint8_t mi2);
uint8_t get_day_of_week(uint16_t year, uint8_t month, uint8_t day);

void get_mcc(const char* &p, char* aux, int& i);
bool get_bool(const char* &p);
uint16_t get_km(const char* &p);

extern const unordered_map<string,int> normalization_dict;
uint8_t mcc_risk(uint16_t mcc_code);

Vector normalize_vector(Vector& v);
Vector parse_request(const char* &p);
vector<Vector> payload_parser(const char* json_dict);
Vector* references_parser(const char* json_dict);

bool vector_is_equals(Vector v1, Vector v2);

void print_vector(Vector v);

#endif /* VECTOR_H */
