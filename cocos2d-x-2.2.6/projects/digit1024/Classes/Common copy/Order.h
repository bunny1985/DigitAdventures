/*
 * Order.h
 *
 *  Created on: 17-07-2013
 *      Author: michal
 */

#ifndef ORDER_H_
#define ORDER_H_

class Order
{
public:

	virtual ~Order() =0;
	virtual void execute() =0;
};

#endif /* ORDER_H_ */
