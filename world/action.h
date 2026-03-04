//
// Created by Loonj on 2/13/2026.
//
#pragma once

enum class ActionType {
    None,
    Jump,
    MoveLeft,
    MoveRight,
    StageTransition,
    Attacking,
};

class World;
class GameObject;

class Action {
public:
    virtual ~Action() = default;
    virtual void perform(World& world, GameObject& obj) = 0;
};

class Jump : public Action {
    void perform(World&, GameObject& obj) override;
};

class MoveRight : public Action {
    void perform(World&, GameObject& obj) override;
};

class MoveLeft : public Action {
    void perform(World&, GameObject& obj) override;
};

class StageTrans : public Action {
    void perform(World&, GameObject& obj) override;
};

class Attack : public Action {
    void perform(World&, GameObject& obj) override;
};