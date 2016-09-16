/*
 * IAPBService.cpp
 *
 *  Created on: 22 gru 2014
 *      Author: Michal
 */

#include "IAPBService.h"
#ifdef BBIAP
#include <bps/bps.h>
#include <bps/paymentservice.h>
#include <bps/navigator.h>
#include <cocos2d.h>
#include <bps/bps.h>
#include <bps/paymentservice.h>
#include <bps/navigator.h>
#include <screen/screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <screen/screen.h>
#endif
#ifdef ANDROIDIAP
#include "cocos2d.h"


 USING_NS_CC;
#endif
IAPBService::IAPBService()
{
    // TODO Auto-generated constructor stub

}

IAPBService::~IAPBService()
{
    // TODO Auto-generated destructor stub
}
#ifdef ANDROIDIAP
bool IAPBService::buyProduct(const char* sku){
    CCApplication::sharedApplication()->BuyItem(sku);
}
bool IAPBService::consumeProsuct(const char* sku)
{

}

bool IAPBService::isInitiated()
{
}

void IAPBService::initiate(){

}
#endif

#ifdef BBIAP
bool IAPBService::buyProduct(const char* sku)
{
    //  aymentservice_purchase_arguments_set_group_id(args, get_window_group_id());
    bps_initialize();
    int exit_application = 0;
    navigator_request_events(0);
    paymentservice_request_events(0);
    paymentservice_set_connection_mode(false);

    unsigned request_id = 0;
    if (paymentservice_purchase_request(sku, NULL, NULL,
    NULL, "Digit Adventures", NULL, cocos2d::CCEGLView::sharedOpenGLView()->getWindowGroupId(),
            &request_id) != BPS_SUCCESS) {
        fprintf(stderr, "Error: purchase request failed.\n");
    }

    while (!exit_application) {
        /*
         * Using a negative timeout (-1) in the call to bps_get_event(...)
         * ensures that we don't busy wait by blocking until an event is
         * available.
         */
        bps_event_t *event = NULL;
        bps_get_event(&event, -1);
        if (event) {
            /*
             * If it is a Payment Service event, determine the response code
             * and handle the event accordingly.
             */
            if (bps_event_get_domain(event) == paymentservice_get_domain()) {
                if (SUCCESS_RESPONSE == paymentservice_event_get_response_code(event)) {
                    if (PURCHASE_RESPONSE == bps_event_get_code(event)) {
                        return true;

                    } else
                        return true;
                } else {
                    return false;
                }
            }
            /*
             * If it is a NAVIGATOR_EXIT event then set the exit_application
             * flag so the application will stop processing events, clean up
             * and exit.
             *
             * If it is a NAVIGATOR_SWIPE_DOWN event, initiate the purchase of
             * the sample digital good.
             */

        }
    }
    bps_shutdown();

    /*paymentservice_purchase_arguments_create(&params);
     paymentservice_purchase_arguments_set_digital_good_sku(&params,  sku);
     paymentservice_purchase_arguments_set_group_id(params, cocos2d::CCEGLView::sharedOpenGLView()->getWindowGroupId());
     paymentservice_set_connection_mode(true);
     int result = paymentservice_purchase_request_with_arguments(&params);*/

}

bool IAPBService::consumeProsuct(const char* sku)
{

}

bool IAPBService::isInitiated()
{
}

void IAPBService::initiate()
{
    bps_initialize();

    // Request all events
    paymentservice_request_events(0);

}

#endif
