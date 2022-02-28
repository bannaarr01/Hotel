
#ifndef HOTEL_PROMOTION_H
#define HOTEL_PROMOTION_H

#include<string>

//IMPLEMENT THIS, IF ANY...
class Promotion {
public:
    const std::string getPromoName() const;

    void setPromoName(const std::string promoName);

    double getPromoDiscount() const;

    void setPromoDiscount(double promoDiscount);

    const std::string getPromoDescription() const;

    void setPromoDescription(const std::string promoDescription);

private:
    std::string promoName;
    double promoDiscount;
    std::string promoDescription;
};


#endif //HOTEL_PROMOTION_H
