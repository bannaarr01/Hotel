#include "Promotion.h"

const std::string Promotion::getPromoName() const {
    return promoName;
}

void Promotion::setPromoName(const std::string promoName) {
    Promotion::promoName = promoName;
}

double Promotion::getPromoDiscount() const {
    return promoDiscount;
}

void Promotion::setPromoDiscount(double promoDiscount) {
    Promotion::promoDiscount = promoDiscount;
}

const std::string Promotion::getPromoDescription() const {
    return promoDescription;
}

void Promotion::setPromoDescription(const std::string promoDescription) {
    Promotion::promoDescription = promoDescription;
}