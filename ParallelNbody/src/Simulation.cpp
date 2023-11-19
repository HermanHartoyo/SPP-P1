/*
 * Simulation.cpp
 *
 *  Created on: Dec 15, 2014
 *  Updated on: Aug 23, 2022
 *      Author: ahueck
 */

#include "Simulation.h"
#include "Logger.h"
#include "Vec2.h"

namespace practical::nbody {

    Simulation::Simulation(SimulationData data) : m_sim_data(std::move(data)) {
    }

    void Simulation::run() {
        for (unsigned int step = 0; step < m_sim_data.num_steps; ++step) {
            nextTimestep();
        }
    }

    void Simulation::nextTimestep() {
        // TODO implement N-body calculation according to the exercise sheet.

        handleCollisions();
        for (int i = 0; i < m_sim_data.bodies.size(); ++i) {
            m_sim_data.bodies[i].resetAcceleration();
            for (int j = 0; j < m_sim_data.bodies.size(); ++j) {
                if (i != j) {
                    m_sim_data.bodies[i].applyForces(m_sim_data.bodies[j]);
                }
            }
            m_sim_data.bodies[i].update(m_sim_data.dt);
        }

/*
#pragma omp task
{
    handleCollisions();
    }


#pragma omp task shared (m_sim_data)
        {
#pragma omp parallel for shared(m_sim_data)
            for (int a = 0; a < m_sim_data.bodies.size(); ++a) {
                m_sim_data.bodies[a].resetAcceleration();
            }
        }


#pragma omp task shared (m_sim_data)
        {
#pragma omp parallel for collapse(2) shared(m_sim_data)
            for (int i = 0; i < m_sim_data.bodies.size(); ++i) {
                for (int j = 0; j < m_sim_data.bodies.size(); ++j) {
                    if (i != j) {
                        m_sim_data.bodies[i].applyForces(m_sim_data.bodies[j]);
                    }
                }
            }
        }
#pragma omp task shared (m_sim_data)
        {
#pragma omp parallel for shared(m_sim_data)
            for (int b = 0; b < m_sim_data.bodies.size(); ++b) {
                m_sim_data.bodies[b].update(m_sim_data.dt);
            }
        }

#pragma omp taskwait
 */
    }
void Simulation::handleCollisions() {
    // TODO handle collision per timestep (before updating forces)

    for (int i = 0; i < m_sim_data.bodies.size(); ++i) {
        for (int j = 0; j < m_sim_data.bodies.size(); ++j) {

            if(i!=j && m_sim_data.bodies[i].distanceTo(m_sim_data.bodies[j]) <= m_sim_data.distance && m_sim_data.bodies[i].mass() != 0 && m_sim_data.bodies[j].mass() != 0){
                Body k = Body(m_sim_data.bodies[i].position(), (((m_sim_data.bodies[i].velocity() * m_sim_data.bodies[i].mass()) + (m_sim_data.bodies[j].velocity() * m_sim_data.bodies[j].mass())) / (m_sim_data.bodies[i].mass()+m_sim_data.bodies[j].mass()) ) , m_sim_data.bodies[i].mass() + m_sim_data.bodies[j].mass());
                m_sim_data.bodies.push_back(k);

                m_sim_data.bodies[i] = Body(m_sim_data.bodies[i].position(), m_sim_data.bodies[i].velocity(), m_sim_data.bodies[i].mass() + m_sim_data.bodies[j].mass());
                m_sim_data.bodies[j] = Body(m_sim_data.bodies[j].position(), m_sim_data.bodies[j].velocity(), 0);
            }
        }
    }
/*
#pragma omp parallel for collapse(2)
    for (int i = 0; i < m_sim_data.bodies.size(); ++i) {
        for (int j = 0; j < m_sim_data.bodies.size(); ++j) {
            if (i != j && m_sim_data.bodies[i].distanceTo(m_sim_data.bodies[j]) <= m_sim_data.distance &&
                m_sim_data.bodies[i].mass() != 0 && m_sim_data.bodies[j].mass() != 0) {
                Body k = Body(m_sim_data.bodies[i].position(),
                              (((m_sim_data.bodies[i].velocity() * m_sim_data.bodies[i].mass()) +
                                (m_sim_data.bodies[j].velocity() * m_sim_data.bodies[j].mass())) /
                               (m_sim_data.bodies[i].mass() + m_sim_data.bodies[j].mass())),
                              m_sim_data.bodies[i].mass() + m_sim_data.bodies[j].mass());
                m_sim_data.bodies.push_back(k);

                m_sim_data.bodies[i] = Body(m_sim_data.bodies[i].position(), m_sim_data.bodies[i].velocity(),
                                            m_sim_data.bodies[i].mass() + m_sim_data.bodies[j].mass());
                m_sim_data.bodies[j] = Body(m_sim_data.bodies[j].position(), m_sim_data.bodies[j].velocity(), 0);
            }
        }
    }
    */
}

const SimulationData &Simulation::simulationState() const {
    return m_sim_data;
}

Simulation::~Simulation() = default;

}  // namespace practical::nbody
