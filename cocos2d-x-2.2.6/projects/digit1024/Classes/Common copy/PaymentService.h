/*
 * PaymentService.h
 *
 *  Created on: 22 gru 2014
 *      Author: Michal
 */

#ifndef PAYMENTSERVICE_H_
#define PAYMENTSERVICE_H_

class PaymentService
{
public:
    PaymentService();
    virtual ~PaymentService();
    int getSkipsQuantity();
    bool buySkip();
    void useSkip();
    void consumeSkip();

    bool hasBadge();
    bool buyBadge();

    bool hasExtraLevels();
    bool BuyExtraLevels();

private:
    static const char* SKU_skip ;
    static const char* SKU_levels;
    static const char* SKU_badger;

};

#endif /* PAYMENTSERVICE_H_ */
