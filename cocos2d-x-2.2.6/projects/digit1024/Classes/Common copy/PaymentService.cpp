/*
 * PaymentService.cpp
 *
 *  Created on: 22 gru 2014
 *      Author: Michal
 */

#include <Common/PaymentService.h>
#include "Common/platform/IAPBService.h";
#include "cocos2d.h"

USING_NS_CC;
#ifdef BBIAP
const char* PaymentService::SKU_skip = "59948646";
const char* PaymentService::SKU_levels = "extra_levels";
const char* PaymentService::SKU_badger = "59948645";
#define PAYMENTENABLED
#endif

#ifdef ANDROIDIAP
#include "Common/platform/IAPBService.h";
const char* PaymentService::SKU_skip = "skip_level";
const char* PaymentService::SKU_levels = "extra_levels";
const char* PaymentService::SKU_badger = "fair_play_badge";
#define PAYMENTENABLED
#endif

#define SETTINGSNUMBEROFSKIPS  "nofskips"
#define SETTINGShasBadge "SETTINGShasBadge"


PaymentService::PaymentService()
{
    // TODO Auto-generated constructor stub

}

PaymentService::~PaymentService()
{
    // TODO Auto-generated destructor stub
}

int PaymentService::getSkipsQuantity()
{
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(SETTINGSNUMBEROFSKIPS,0);
}

bool PaymentService::buySkip()
{
#if PAYMENTENABLED
IAPBService service;
bool result  = service.buyProduct(PaymentService::SKU_skip);
if(result){
    int current = CCUserDefault::sharedUserDefault()->getIntegerForKey(SETTINGSNUMBEROFSKIPS,0);
    CCUserDefault::sharedUserDefault()->setIntegerForKey(SETTINGSNUMBEROFSKIPS,(current + 3));
    service.consumeProsuct(PaymentService::SKU_skip);
}
return result;
#else
	return false;
#endif
}
void PaymentService::useSkip(){
        int current = CCUserDefault::sharedUserDefault()->getIntegerForKey(SETTINGSNUMBEROFSKIPS,0);
        CCUserDefault::sharedUserDefault()->setIntegerForKey(SETTINGSNUMBEROFSKIPS,current -1);
}


void PaymentService::consumeSkip()
{
#if PAYMENTENABLED
    IAPBService service;
    bool result  = service.consumeProsuct(PaymentService::SKU_skip);
#endif
}

bool PaymentService::hasBadge()
{
    return CCUserDefault::sharedUserDefault()->getBoolForKey(SETTINGShasBadge,false);
}

bool PaymentService::buyBadge()
{
#if PAYMENTENABLED
	IAPBService service;
    bool result  = service.buyProduct(PaymentService::SKU_badger);
    if(result){
        CCUserDefault::sharedUserDefault()->setBoolForKey(SETTINGShasBadge,true);
    }
    return result;
#else
	return false;
#endif
}

bool PaymentService::hasExtraLevels()
{
	return false;
}

bool PaymentService::BuyExtraLevels()
{
	return false;
}
