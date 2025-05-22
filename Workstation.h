#ifndef WORKSTATION_H
#define WORKSTATION_H
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

    //Global queues for order processing
    //Each queue is accessible outside this module's translation unit.
    extern std::deque<CustomerOrder> g_pending;//holds the orders to be placed onto the assembly line at the first station.
    extern std::deque<CustomerOrder> g_completed;//holds the orders that have been removed from the last station and have been completely filled.
    extern std::deque<CustomerOrder> g_incomplete;//holds the orders that have been removed from the last station and could not be filled completely.

    class Workstation : public Station {
        std::deque<CustomerOrder> m_orders{};
        Workstation* m_pNextStation{};

    public:
        Workstation(const std::string& data);

        // Prevent copying and moving of stations
        Workstation(const Workstation&) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(Workstation&&) = delete;

        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);//Parameter defaults to nullptr
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);
    };


#endif 