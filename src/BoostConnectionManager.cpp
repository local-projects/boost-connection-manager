//
//  BoostConnectionManager.cpp
//  CinderSignalTests
//
//  Created by Lucas Vickers on 4/10/14.
//
//

#include "BoostConnectionManager.h"

#include <boost/assign/std/vector.hpp>

using namespace std;
using namespace boost::assign;

BoostConnectionManager& BoostConnectionManager::operator=(const boost::signals2::connection& connection)
{
    disconnect();
    mConnections += connection;
    return *this;
}

BoostConnectionManager& BoostConnectionManager::operator+=(const boost::signals2::connection& connection)
{
    mConnections += connection;
    return *this;
}

BoostConnectionManager::BoostConnectionManager()
{
    
}

BoostConnectionManager::~BoostConnectionManager()
{
    disconnect();
}

bool BoostConnectionManager::connected()
{
    return ! mConnections.empty();
}

void BoostConnectionManager::disconnect()
{
    for(auto& conn : mConnections) {
        conn.disconnect();
    }
    mConnections.clear();
}
