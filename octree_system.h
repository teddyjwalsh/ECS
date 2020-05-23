#ifndef OCTREE_SYSTEM_H_
#define OCTREE_SYSTEM_H_

#include <memory>
#include <iostream>
#include <unordered_set>

#include "component_manager.h"
#include "type_id.h"
#include "physics_component.h"
#include "time_component.h"
#include "system.h"

struct Node
{
    Node * parent = nullptr;
    Node * children[8] = {nullptr, nullptr, nullptr, nullptr, 
        nullptr, nullptr, nullptr, nullptr};
    glm::vec3 loc;
    float size;
    std::unordered_set<EntityId> entities;
};

class CompOctree : public Component
{
public:
    Node * node = nullptr;
private:
    void set_type() override { _type = type_id<CompOctree>; }
};

std::unordered_set<EntityId> range_search(glm::vec3 loc, float range)
{
    return std::unordered_set<EntityId>();
}

class CompOctreeRoot : public Component
{
public:
    CompOctreeRoot()
    {
        node.size = 1000;
        node.loc = glm::vec3(0);
    }

    Node node;
private:
    void set_type() override { _type = type_id<CompOctreeRoot>; }
};

class SysOctree: public System
{
public:
    SysOctree()
    {
        _type = type_id<CompOctree>;
    }

    void update(double dt) override
    {
        std::vector<CompOctreeRoot>& root_vec = 
            get_array<CompOctreeRoot>(); 
        std::vector<CompOctree>& oct_vec = 
            get_array<CompOctree>(); 
        for (auto it = oct_vec.begin(); it != oct_vec.end(); ++it)
        {
            CompPosition * pos_c = (*it).sibling<CompPosition>();
            Node * set_node = octree_lookup(&root_vec[0].node, 1.0, pos_c->pos, true);  
        }
    }

    Node * octree_lookup(Node * node, float size, glm::vec3 coord, bool allocate=true)
    {
        Node * current_node = node;
        while (current_node->size > size)
        {
            glm::vec3 node_center = current_node->loc + glm::vec3(current_node->size);
            int x_index = int(coord.x > node_center.x);
            int y_index = int(coord.y > node_center.y);
            int z_index = int(coord.z > node_center.z);
            int child_index = x_index + y_index*2 + z_index*4;
            
            if (current_node->children[child_index] == nullptr)
            {
                if (allocate)
                {
                    current_node->children[child_index] = new Node;
                    current_node->children[child_index]->size = 
                        current_node->children[child_index]->size/2.0;
                    current_node->children[child_index]->parent = 
                        current_node;
                    current_node->children[child_index]->loc = 
                        node_center*glm::vec3(x_index, y_index, z_index);
                }
                else
                {
                    return current_node;
                }
            }
            current_node = current_node->children[child_index];
        }
        return current_node;
    }

};

#endif  // OCTREE_SYSTEM_H_ 
