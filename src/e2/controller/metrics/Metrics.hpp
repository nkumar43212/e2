//
//  Metrics.hpp
//  e2
//
//  Created by NITIN KUMAR on 6/16/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef Metrics_hpp
#define Metrics_hpp

#include <stdio.h>
#include <string>
#include <vector>

class Metrics {
    std::string _name;
    uint64_t    _value;
    uint64_t    _threshold;
    
public:
    Metrics (std::string name, uint64_t val, uint64_t threshold = 0) : _name(name), _value(val), _threshold(threshold)
    {
    }
    
    std::string getName()      { return _name;      }
    uint64_t    getValue()     { return _value;     }
    uint64_t    getThreshold() { return _threshold; }
};

typedef std::vector<Metrics>  MetricsList;
typedef MetricsList::iterator MetricsListIterator;


#endif /* Metrics_hpp */
