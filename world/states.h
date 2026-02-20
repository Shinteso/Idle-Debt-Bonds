//
// Created by Loonj on 2/18/2026.
//
#pragma once
#include "fsm.h"
#include "world.h"

class Standing: public State {
public:
    void on_enter(World&, GameObject&) override;
    Action* input(World&, GameObject&, ActionType) override;
};

class InAir: public State {
public:
    void on_enter(World &, GameObject &) override;
    void update(World &, GameObject &, double dt) override;

    const double cooldown = 1;
    double elapsed = 0;
};