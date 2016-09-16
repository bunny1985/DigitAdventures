/*
 * SkipLevelService.h
 *
 *  Created on: 11 sty 2015
 *      Author: Michal
 */

#ifndef SKIPLEVELSERVICE_H_
#define SKIPLEVELSERVICE_H_
#include "Common/PaymentService.h"
class SkipLevelService
{
public:
    SkipLevelService();
    virtual ~SkipLevelService();
    int getNumberOfSkips(){
        PaymentService ps;
        return ps.getSkipsQuantity();

    }
    bool skipLevel(){
        PaymentService ps;
        if(getNumberOfSkips()==0){
            if(ps.buySkip()){
                return skipLevel();
            }else{
                return false;
            }
        }else{
            ps.useSkip();
            return true;
        }
    }

};

#endif /* SKIPLEVELSERVICE_H_ */
