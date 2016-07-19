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
#include <map>

class Metrics {
    // Name that identifies a metric
    std::string _name;
    
    // Current value of the metric. I think we need to specify the unit also
    uint64_t    _current_value;
    uint64_t    _peak_value;
    uint64_t    _min_value;
    uint64_t    _threshold;
    
public:
    Metrics()
    { }
    
    Metrics(std::string name, uint64_t val, uint64_t threshold = 0)
      : _name(name), _current_value(val), _threshold(threshold)
    {
        _min_value  = ~(0x0);
        _peak_value = 0;
    }
    
    std::string getName()             { return _name;              }
    uint64_t    getCurrentValue()     { return _current_value;     }
    uint64_t    getPeakValue()        { return _peak_value;        }
    uint64_t    getMinValue()         { return _min_value;         }
    uint64_t    getThreshold()        { return _threshold;         }
    
    void        update(uint64_t value);
    bool        isGreen();
};

typedef std::map<std::string, Metrics>  MetricsList;
typedef MetricsList::iterator MetricsListIterator;


#endif /* Metrics_hpp */
