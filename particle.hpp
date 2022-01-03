//
//  particle.hpp
//  ogl
//
//  Created by logpoint on 8/21/20.
//  Copyright © 2020 logpoint. All rights reserved.
//

#ifndef particle_hpp
#define particle_hpp
#include <glm/glm.hpp>

#include <stdio.h>

namespace cyclone {
class Particle{
public:
protected:
    double invertmass;
    double damping;
    glm::vec3 position;
    glm::vec3 forceAccum;
    glm::vec3 velocity;
    glm::vec3 acceleration;
public:
    void integrate(double duration);
    void addForce(const glm::vec3 &force);
    void clearAccumulator();

    
};
}

#endif /* particle_hpp */
