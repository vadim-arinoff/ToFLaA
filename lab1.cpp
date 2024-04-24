#include <iostream>
#include <vector>
#include <map>
#include <set>

/*
Тема "Детерминированный конечный автомат" (20 баллов)
1. Создать объекты программы для представления детерминированного конечного автомата 
(ДКА), его состояний и переходов.
2. Реализовать процедуры добавления/удаления переходов и состояний, добавления и 
удаления начальных и заключительных состояний.
3. Реализовать процедуру перевода ДКА из заданного состояния в другое посредством одного
из допустимых переходов ДКА.
4. Реализовать процедуру/метод работы детерминированного конечного автомата по входной 
цепочке символов алфавита ДКА.
*/
class DFA {
private:
    std::set<int> states; 
    std::set<int> accepting_states; 
    int initial_state; // Исходное состояние
    std::map<std::pair<int, char>, int> transitions; // переходы (состояние, ввод) -> следующее состояние

public:
    // состояние ДКА
    void addState(int state) {
        states.insert(state);
    }

    // исходное состояние
    void setInitialState(int state) {
        initial_state = state;
    }

    // принимающее состояние
    void addAcceptingState(int state) {
        accepting_states.insert(state);
    }

    // переход
    void addTransition(int from, char input, int to) {
        transitions[{from, input}] = to;
    }

    // проверка принимабщего состояния
    bool isAccepting(int state) {
        return accepting_states.count(state) > 0;
    }

    // Симуляция ДКА на основе входной строки
    bool simulate(const std::string& input) {
        int current_state = initial_state;
        for (char c : input) {
            if (transitions.count({current_state, c}) == 0) {
                return false; // Недопустимый переход
            }
            current_state = transitions[{current_state, c}];
        }
        return isAccepting(current_state);
    }
};

int main() {
    DFA dfa;
    dfa.addState(0); // Состояние 0
    dfa.addState(1); // Состояние 1
    dfa.setInitialState(0); // начальное состояние 0
    dfa.addAcceptingState(1); // состояние 1 в качестве принимающего
    dfa.addTransition(0, 'a', 1); // переход от 0 к 1 на входе 'a'
    dfa.addTransition(1, 'b', 0); // от 1 к 0 при 'b'

    std::string input;
    std::cout << "Enter an input string: ";
    std::cin >> input;

    if (dfa.simulate(input)) {
        std::cout << "Accepted" << std::endl;
    } else {
        std::cout << "Rejected" << std::endl;
    }

    return 0;
}
