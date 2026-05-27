#ifndef VECTOR_H
#define VECTOR_H

#include <nlohmann/json.hpp>
#include <cstdint>
#include <string>
#include <map>

#define VECTOR_DIMENSIONS 14

#define NVECTORS 3000000
#define SQRT_NVECTORS 1733

using namespace std;
using json = nlohmann::json;

struct Vector
{
    float components[VECTOR_DIMENSIONS];
    char  label;   // f=fraud,v=valid,n=none(requests???)
};

const unordered_map<string, float> mcc_risk = {
    {"5411", 0.15},
    {"5812", 0.30},
    {"5912", 0.20},
    {"5944", 0.45},
    {"7801", 0.80},
    {"7802", 0.75},
    {"7995", 0.85},
    {"4511", 0.35},
    {"5311", 0.25},
    {"5999", 0.50}
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

uint16_t simple_distance(Vector v1, Vector v2);
uint16_t euclidian_distance(Vector v1, Vector v2);

Vector request_treatment(const json& request);
Vector normalize_vector(Vector& v);

#endif /* VECTOR_H */
