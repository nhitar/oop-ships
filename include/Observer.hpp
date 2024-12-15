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
    public:
        OutputObserver(Output& output) : output(output) {};

        void abilityUsed() override {
            std::cout << "Ability used." << std::endl;
        }

        void turnEnded() override {
            std::cout << "Turn ended." << std::endl;
        }

        void playerWin() override {
            std::cout << "Player wins!" << std::endl;
        }

        void botWin() override {
            std::cout << "Bot wins!" << std::endl;
        }
};