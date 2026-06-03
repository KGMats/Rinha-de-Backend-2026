//#include "network.hpp"
#include "vector.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	Vector v, vv;

	v.components.amount = 33334;
	v.components.installments = 1;
	v.components.amount_vs_avg = 2944;
	v.components.hour_of_day = 15;
	v.components.day_of_week = 4;
	v.components.minutes_since_last_tx = 65535;
	v.components.km_from_last_tx = 58;
	v.components.km_from_home = 3869;
	v.components.tx_count_24h = 4;
	v.components.is_online = 0;
	v.components.card_present = 1;
	v.components.unknown_merchant = 0;
	v.components.mcc_risk = 3;
	v.components.merchant_avg_amount = 48414;
	v.label = 'n';
	v.components.last_transaction = 1;

	vv.components.amount = 55726;
	vv.components.installments = 10;
	vv.components.amount_vs_avg = 546;
	vv.components.hour_of_day = 0;
	vv.components.day_of_week = 1;
	vv.components.km_from_last_tx = 54;
	vv.components.km_from_home = 9645;
	vv.components.minutes_since_last_tx = 65535;
	vv.components.tx_count_24h = 15;
	vv.components.is_online = 1;
	vv.components.card_present = 0;
	vv.components.unknown_merchant = 1;
	vv.components.mcc_risk = 85;
	vv.components.merchant_avg_amount = 2677;
	vv.label = 'n';
	vv.components.last_transaction = 1;

	v = normalize_vector(v);
	vv = normalize_vector(vv);

	cout << endl;
	cout << "amount: " << v.components.amount << endl;
	cout << "installments: " << (int)v.components.installments << endl;
	cout << "amount_vs_avg: " << v.components.amount_vs_avg << endl;
	cout << "hour_of_day: " << (int)v.components.hour_of_day << endl;
	cout << "day_of_week: " << (int)v.components.day_of_week << endl;
	cout << "minutes_since_last_tx: " << v.components.minutes_since_last_tx << endl;
	cout << "km_from_last_tx: " << v.components.km_from_last_tx << endl;
	cout << "km_from_home: " << v.components.km_from_home << endl;
	cout << "tx_count_24h: " << (int)v.components.tx_count_24h << endl;
	cout << "is_online: " << v.components.is_online << endl;
	cout << "card_present: " << v.components.card_present << endl;
	cout << "unknown_merchant: " << v.components.unknown_merchant << endl;
	cout << "mcc_risk: " << (int)v.components.mcc_risk << endl;
	cout << "merchant_avg_amount: " << v.components.merchant_avg_amount << endl;
	cout << "label: " << v.label << endl;
	cout << "last_transaction: " << v.components.last_transaction << endl;
	cout << endl;

	cout << endl;
	cout << "amount: " << vv.components.amount << endl;
	cout << "installments: " << (int)vv.components.installments << endl;
	cout << "amount_vs_avg: " << vv.components.amount_vs_avg << endl;
	cout << "hour_of_day: " << (int)vv.components.hour_of_day << endl;
	cout << "day_of_week: " << (int)vv.components.day_of_week << endl;
	cout << "minutes_since_last_tx: " << vv.components.minutes_since_last_tx << endl;
	cout << "km_from_last_tx: " << vv.components.km_from_last_tx << endl;
	cout << "km_from_home: " << vv.components.km_from_home << endl;
	cout << "tx_count_24h: " << (int)vv.components.tx_count_24h << endl;
	cout << "is_online: " << vv.components.is_online << endl;
	cout << "card_present: " << vv.components.card_present << endl;
	cout << "unknown_merchant: " << vv.components.unknown_merchant << endl;
	cout << "mcc_risk: " << (int)vv.components.mcc_risk << endl;
	cout << "merchant_avg_amount: " << vv.components.merchant_avg_amount << endl;
	cout << "label: " << vv.label << endl;
	cout << "last_transaction: " << vv.components.last_transaction << endl;
	cout << endl;

	cout << simple_distance(v,vv) << endl;
	cout << euclidian_distance(v,vv) << endl;

	cout << endl;
	
	char st[] = "2026-03-10T00:24:01Z";
	uint16_t yy; uint8_t moo,dd,hh,mm,ss;
	const char* pp = st; int ii = 0;
	parse_iso(pp,st,ii,yy,moo,dd,hh,mm,ss);
	cout << "year: " << yy << endl;
	cout << "month: " << (int)moo << endl;
	cout << "day: " << (int)dd << endl;
	cout << "hour: " << (int)hh << endl;
	cout << "minute: " << (int)mm << endl;
	cout << "second: " << (int)ss << endl;
	cout << "day of week: " << (int)get_day_of_week(yy,moo,dd) << endl;
	cout << endl;

	cout << endl;

	char str[] = "2026-03-10T00:31:01Z";
	uint16_t y; uint8_t mo,d,h,m,s;
	const char* p = str; int i = 0;
	parse_iso(p,str,i,y,mo,d,h,m,s);
	cout << "year: " << y << endl;
	cout << "month: " << (int)mo << endl;
	cout << "day: " << (int)d << endl;
	cout << "hour: " << (int)h << endl;
	cout << "minute: " << (int)m << endl;
	cout << "second: " << (int)s << endl;
	cout << "day of week: " << (int)get_day_of_week(y,mo,d) << endl;
	cout << endl;

	cout << "diff in minutes: " << (int)get_diff(yy,moo,dd,hh,mm,y,mo,d,h,m) << endl;

	char str1[] = "2026-03-13T15:31:01Z";
	uint16_t y1; uint8_t mo1,d1,h1,m1,s1;
	const char* p1 = str1; int i1 = 0;
	parse_iso(p1,str1,i1,y1,mo1,d1,h1,m1,s1);
	cout << "year: " << y1 << endl;
	cout << "month: " << (int)mo1 << endl;
	cout << "day: " << (int)d1 << endl;
	cout << "hour: " << (int)h1 << endl;
	cout << "minute: " << (int)m1 << endl;
	cout << "second: " << (int)s1 << endl;
	cout << endl;
	cout << "day of week: " << (int)get_day_of_week(y1,mo1,d1) << endl;
		      
	char str2[] = "2026-03-13T14:50:01Z";
	uint16_t y2; uint8_t mo2,d2,h2,m2,s2;
	const char* p2 = str2; int i2 = 0;
	parse_iso(p2,str2,i2,y2,mo2,d2,h2,m2,s2);
	cout << "year: " << y2 << endl;
	cout << "month: " << (int)mo2 << endl;
	cout << "day: " << (int)d2 << endl;
	cout << "hour: " << (int)h2 << endl;
	cout << "minute: " << (int)m2 << endl;
	cout << "second: " << (int)s2 << endl;
	cout << "day of week: " << (int)get_day_of_week(y2,mo2,d2) << endl;
	cout << endl;

	cout << "diff in minutes: " << get_diff(y2,mo2,d2,h2,m2,y1,mo1,d1,h1,m1) << endl;

	return 0;
}

