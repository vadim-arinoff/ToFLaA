#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

/*
"Недетерминированный конечный автомат"
1. Создать объекты программы для представления недетерминированного конечного автомата
(НКА), его состояний и переходов.
2. Реализовать процедуры добавления/удаления переходов и состояний, добавления и 
удаления начальных и заключительных состояний.
3. Реализовать процедуру перевода НКА из заданного состояния в другое посредством 
одного из допустимых переходов НКА.
4. Реализовать процедуру/метод работы детерминированного конечного автомата по входной 
цепочке символов алфавита НКА. (Решить задачу об окончаниях -ое, -ая, -ие)
*/

class NFA {
private:
    std::set<int> states;
    std::set<int> accepting_states; 
    int initial_state;
    std::map<std::pair<int, char>, std::set<int>> transitions;

public:
    void addState(int state) {
        states.insert(state);
    }

    void setInitialState(int state) {
        initial_state = state;
    }

    void addAcceptingState(int state) {
        accepting_states.insert(state);
    }

    void addTransition(int from, char input, int to) {
        transitions[{from, input}].insert(to);
    }

    bool isAccepting(int state) {
        return accepting_states.count(state) > 0;
    }

    bool simulate(const std::string& input) {
        std::set<int> current_states = {initial_state};
        for (char c : input) {
            std::set<int> next_states;
            for (int state : current_states) {
                if (transitions.count({state, c}) > 0) {
                    next_states.insert(transitions[{state, c}].begin(), transitions[{state, c}].end());
                }
            }
            current_states = next_states;
        }
        for (int state : current_states) {
            if (isAccepting(state)) {
                return true;
            }
        }
        return false;
    }

    // проверка строки на суфикс
    bool endsWith(const std::string& str, const std::string& suffix) {
        if (str.length() < suffix.length()) {
            return false;
        }
        return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
    }

    // есть ли "ое", "ая", "ие"
    bool isAdjectiveEnding(const std::string& str) {
        return endsWith(str, "ое") || endsWith(str, "ая") || endsWith(str, "ие");
    }
};

int main() {
    NFA nfa;
    nfa.addState(0); 
    nfa.addState(1); 
    nfa.setInitialState(0); 
    nfa.addAcceptingState(1); 
    nfa.addTransition(0, 'a', 1); 
    nfa.addTransition(1, 'b', 0); 

    std::string input;
    std::cout << "Enter an input string: ";
    std::cin >> input;

    if (nfa.simulate(input)) {
        std::cout << "Accepted" << std::endl;
        if (nfa.isAdjectiveEnding(input)) {
            std::cout << "The string represents an adjective ending." << std::endl;
        } else {
            std::cout << "The string does not represent an adjective ending." << std::endl;
        }
    } else {
        std::cout << "Rejected" << std::endl;
    }

    return 0;
}
