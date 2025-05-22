#include "LineManager.h"
#include "Utilities.h"

#include <iostream>
#include <fstream>
#include <algorithm>

namespace seneca {
    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations) {
        try {
            std::ifstream input(file);
            if (!input) {
                throw std::string("Unable to open file ") + file;
            }

            Utilities util;
            std::string record;

            while (std::getline(input, record)) {
                size_t pos = 0;
                bool more = true;

                std::string current_name = util.extractToken(record, pos, more);

                auto current = std::find_if(stations.begin(), stations.end(),
                                            [&](Workstation* ws) { return ws->getItemName() == current_name; });

                if (current != stations.end()) {
                    m_activeLine.push_back(*current);

                    if (more) {
                        std::string next_name = util.extractToken(record, pos, more);
                        auto next = std::find_if(stations.begin(), stations.end(),
                                                 [&](Workstation* ws) { return ws->getItemName() == next_name; });

                        if (next != stations.end()) {
                            (*current)->setNextStation(*next);
                        }
                    }
                }
            }

            m_cntCustomerOrder = g_pending.size();

        } catch (const std::string& msg) {
            throw msg;
        }
    }

    void LineManager::reorderStations() {

        std::vector<Workstation *> ordered;
        std::vector<bool> added(m_activeLine.size(), false);


        for (auto *first_candidate: m_activeLine) {
            bool is_first = true;
            for (auto *station: m_activeLine) {
                if (station->getNextStation() == first_candidate) {
                    is_first = false;
                    break;
                }
            }
            if (is_first) {
                m_firstStation = first_candidate;
                break;
            }
        }
        Workstation *current = m_firstStation;
        while (current != nullptr) {
            ordered.push_back(current);
            current = current->getNextStation();
        }
        m_activeLine = ordered;
    }

    bool LineManager::run(std::ostream& os) {
        static size_t iteration = 0;
        iteration++;

        os << "Line Manager Iteration: " << iteration << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto* station : m_activeLine) {
            station->fill(os);
        }

        for (auto* station : m_activeLine) {
            station->attemptToMoveOrder();
        }

        return g_pending.empty() &&
               (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
    }
    void LineManager::display(std::ostream &os) const {
        for (auto *station: m_activeLine) {
            station->display(os);
        }
    }
}