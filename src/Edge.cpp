#include "Edge.h"

//
// Created by 35196 on 26/01/2022.
//
Edge::Edge(string dest, int weight, string lineCode) {
    this->weight=weight;
    this->lineCode=lineCode;
    this->dest=dest;
}

string Edge::getDest() {
    return dest;
}

string Edge::getLineCode() {
    return lineCode;
}

int Edge::getWeight() {
    return weight;
}

void Edge::setDest(string dest) {
    this->dest=dest;
}

void Edge::setLineCode(string lineCode) {
    this->lineCode=lineCode;
}

void Edge::setWeight(int weight) {
    this->weight=weight;
}