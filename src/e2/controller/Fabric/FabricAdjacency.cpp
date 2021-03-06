//
//  FabricAdjacency.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/18/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "Element.hpp"
#include "FabricAdjacency.hpp"
#include "ServiceLag.hpp"
#include "Fabric.hpp"

status_t
FabricAdjacency::activate()
{
    status_t status;
 
    // Create LAG bundles on both end points
    addLagBundle(getEndPoint1());
    addLagBundle(getEndPoint2());
    
    // Update the map
    status = Fabric::addMap(this);
    if (status != EOK) {
        goto error;
    }
    
    return EOK;

error:
    return status;
}

void
FabricAdjacency::deactivate()
{
    removeLagBundle(getEndPoint1());
    removeLagBundle(getEndPoint2());
    Fabric::removeMap(this);
}

status_t
FabricAdjacency::addLagBundle (const std::string &element_name)
{
    Element *element = nullptr;
    status_t status;
    
    // Make sure that the two elements are alive
    element = Element::find(element_name);
    if (!element) {
        return ENOENT;
    }
    
    // Create an interface on the element
    std::string lag_name = "AE:" + getEndPoint1() + ":" + getEndPoint2();
    ElementInterface *lag = new ElementInterface(lag_name, element->allocateInterfaceIndex(), true);
    element->addInterface(lag);
    
    // Add the LAG service on these elements
    status = element->addServiceOrder(ServiceOrderLag::create(lag_name));
    if (status != EOK) {
        return status;
    }
    
    // Any customers that are present on this element, need to be provisioned on the LAG
    // element->addCustomerLag(lag_name);
                                      
    return EOK;
}

void
FabricAdjacency::removeLagBundle (const std::string &element_name)
{
    Element *element = nullptr;
    
    // Make sure that the two elements are alive
    element = Element::find(element_name);
    if (!element) {
        return;
    }
    
    // Create an interface on the element
    std::string lag_name = "AE:" + getEndPoint1() + ":" + getEndPoint2();
    element->removeInterface(lag_name);
  
    // Remove the LAG service
    (void) element->removeServiceOrder(ServiceOrderLag::create(lag_name));
}

void
FabricAdjacency::getOperationalState (ElementOpstateList &opstate)
{
    // Connectivity details
    opstate["element/fabric/name"] = _name;
    opstate["element/fabric/link"] = getEndPoint1() + "<->" + getEndPoint2();
}
