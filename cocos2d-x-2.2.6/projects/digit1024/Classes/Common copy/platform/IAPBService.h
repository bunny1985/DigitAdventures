/*
 * IAPBService.h
 *
 *  Created on: 22 gru 2014
 *      Author: Michal
 */

#ifndef IAPBSERVICE_H_
#define IAPBSERVICE_H_

class IAPBService
{
public:
    IAPBService();
    virtual ~IAPBService();
    bool buyProduct(const char* sku );
    bool consumeProsuct(const char* sku);
protected:
    bool isInitiated();
    void initiate();

    //purchase_arguments_t *args;
};

#endif /* IAPBSERVICE_H_ */
