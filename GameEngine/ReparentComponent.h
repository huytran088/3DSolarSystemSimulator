#pragma once
#include "Component.h"
class ReparentComponent :
    public Component
{
public:
    /**
     * @fn	ReparentComponent(GameObject* newParent, float radius, int updateOrder = 100);
     *
     * @brief	Constructor 
     *
     * @param   newParent   The new parent of the owning GameObject.
     * 
     * @param   radius  The range for the owning GameObject to be reparented.
     * 
     * @param	updateOrder	(Optional) The update order.
     * 
     */
    ReparentComponent(GameObject* newParent, float radius, int updateOrder = 100);

    /**
    * 
    * @brief    Repeatedly checks to see if it is “in range” of a specified GameObject, 
    *           in this case the GameObject associated with the spaceship. If the ship
    *           is within range, reparent the owning GameObject to the spaceship GameObject.
    */
    virtual void update(const float& deltaTime) override;

protected:
    /* @brief The new parent of the owning GameObject */
    GameObject* newParent;
    /* @brief The range for the owning GameObject to be reparented.*/
    float radius;

    /**
     * @fn   void reparent();
     * 
     * @brief     A helper method for the update() function.  When the spaceship GameObject 
     *            is within range:
     *                Removes all the move components that are attached to the owning GameObject
     *                Reparents the owning GameObject to the spaceShip GameObject.
     *
     *
     */
    void reparent();
};

