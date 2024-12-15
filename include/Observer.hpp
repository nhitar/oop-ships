#pragma once

class Observer {
    public:
        virtual void abilityUsed() = 0;
        virtual void turnEnded() = 0;
        virtual void playerWin() = 0;
        virtual void botWin() = 0;
        virtual ~Observer() {};
};

template <class Output>
class OutputObserver : public Observer {
    private:
        Output& output;
        GameState& gameState;
    public:
        OutputObserver(Output& output, GameState& gameState) : output(output), gameState(gameState) {};

        void abilityUsed() override {
            output.printString("Ability used.");
            output.printFields(gameState.getBot().getField(), gameState.getPlayer().getField());
            output.printAbilityNames(gameState.getPlayer().getAbilityManager());
        }

        void turnEnded() override {
            output.printString("Turn ended.");
            output.printFields(gameState.getBot().getField(), gameState.getPlayer().getField());
        }

        void playerWin() override {
            output.printString("Player wins.");
        }

        void botWin() override {
            output.printString("Bot wins.");
        }
};