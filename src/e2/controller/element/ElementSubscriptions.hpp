//
//  ElementSubscriptions.hpp
//  e2
//
//  Created by NITIN KUMAR on 7/5/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef ElementSubscriptions_hpp
#define ElementSubscriptions_hpp

#include <stdio.h>

extern std::string subscription_paths[];
extern int         subscription_count;

typedef struct SubscriptionInterest_ {
    std::string                      subscription_name;
    ServiceInterest::ServiceCallback callback;
} SubscriptionInterest_t;
extern SubscriptionInterest_t interest_list[];
extern int                    interest_count;

#endif /* ElementSubscriptions_hpp */
