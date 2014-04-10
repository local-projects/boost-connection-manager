//
//  BoostConnectionManager.h
//  CinderSignalTests
//
//  Created by Lucas Vickers on 4/10/14.
//
//

#pragma once

#include <iostream>
#include <boost/signals2/connection.hpp>
#include <vector>


class BoostConnectionManager
{
    
protected:
    std::vector<boost::signals2::connection> mConnections;
    
public:
    BoostConnectionManager();
    
    // disconnects all connections
    ~BoostConnectionManager();
    
    // removes previous connections and adds this one
    BoostConnectionManager& operator=(const boost::signals2::connection& connection);
    // adds this connection, does not remove previous connections
    BoostConnectionManager& operator+=(const boost::signals2::connection& connection);
    
    // tests if we have connected/managed signals
    bool connected();
    
    // disconnects all
    void disconnect();
    
};