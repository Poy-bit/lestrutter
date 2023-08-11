#pragma once

#include "mathtypes.h"
#include <iostream>
#include <vector>

struct Collider;

struct aabb {
    vec2 min_point;
    vec2 max_point;
    Collider* collider;

    aabb(vec2 min_point, vec2 max_point, Collider* collider=nullptr) : min_point(min_point), max_point(max_point), collider(collider) {}

    aabb* combine(aabb o_aabb) {
        return new aabb(
            vec2(std::min(min_point.x, o_aabb.min_point.x), std::min(min_point.y, o_aabb.min_point.y)),
            vec2(std::max(max_point.x, o_aabb.max_point.x), std::max(max_point.y, o_aabb.max_point.y)));
    }

    bool collides(aabb o_aabb) {
        return
            (max_point.x > o_aabb.min_point.x || o_aabb.max_point.x > min_point.x) &&
            (max_point.y > o_aabb.min_point.y || o_aabb.max_point.y > min_point.y);
    }

    float area() {
        return pow((max_point.x - min_point.x) + (max_point.y - min_point.y), 2);
    }
};

struct node {
    node* parent;
    node* child_1;
    node* child_2;
    aabb* box;
    aabb* data;

    bool isLeaf() { return child_1 == nullptr; }

    void setLeaf(aabb* data, float margin) {
        this->data = data;
        child_1 = nullptr;
        child_2 = nullptr;
        update(margin);
    }

    void setBranch(node* n1, node* n2) {
        child_1 = n1;
        child_2 = n2;
        box = n1->data->combine(*n2->data);
    }

    void update(float margin) {
        box = new aabb(data->min_point - margin, data->max_point + margin);
    }
};

struct aabbtree {
    node* root;
    float margin;

    aabbtree() {
        root = nullptr;
        margin = 0.2;
    }

    void add(aabb* box) {
        node* new_node = new node();
        new_node->setLeaf(box, margin);
        if (root) {
            addNode(new_node, &root);
        }
        else {
            root = new_node;
        }
    }

    void addNode(node* new_node, node** parent_p) {
        node* parent = *parent_p;
        if (parent->isLeaf()) {
            node* new_parent = new node();
            new_parent->setBranch(parent, new_node);
            *parent_p = new_parent;
        }
        else {
            panic(__LINE__);
        }
    }

    std::vector<std::pair<aabb, aabb>> computeColliderPairs() {
        std::vector<std::pair<aabb, aabb>> pairs;
        computePair(root->child_1, root->child_2, &pairs);
        return pairs;
    }

    void computePair(node* n1, node* n2, std::vector<std::pair<aabb, aabb>>* pairs) {
        if (n1->isLeaf()) {
            if (n2->isLeaf()) {
                if (n1->data->collides(*n2->data)) {
                    pairs->push_back(std::pair<aabb, aabb>(*n1->data, *n2->data));
                }
            }
            else {
                panic(__LINE__);
            }
        }
        else {
            panic(__LINE__);
        }
    }

    void panic(int line) {
        std::cout << "PANIC on line " << line << std::endl;
    }
};