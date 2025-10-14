#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

// Rule structure
struct Rule {
    vector<string> conditions;
    string conclusion;
};

// Recursive Backward Chaining
bool backwardChaining(string goal, vector<Rule>& rules, set<string>& facts, set<string>& visited) {
    // If goal is already a fact
    if (facts.find(goal) != facts.end()) {
        return true;
    }

    // Avoid loops
    if (visited.find(goal) != visited.end()) return false;
    visited.insert(goal);

    // Check rules that conclude the goal
    for (auto& rule : rules) {
        if (rule.conclusion == goal) {
            bool allTrue = true;
            for (auto& cond : rule.conditions) {
                if (!backwardChaining(cond, rules, facts, visited)) {
                    allTrue = false;
                    break;
                }
            }
            if (allTrue) {
                cout << "Derived " << goal << " from rule.\n";
                facts.insert(goal); // Mark as derived fact
                return true;
            }
        }
    }

    return false;
}

int main() {
    int choice;
    vector<Rule> rules;
    set<string> facts;
    string goal;

    cout << "=== Backward Chaining Inference System ===\n";

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Rule\n";
        cout << "2. Add Fact\n";
        cout << "3. Set Goal\n";
        cout << "4. Run Backward Chaining\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int n;
            Rule r;
            cout << "Enter number of conditions for this rule: ";
            cin >> n;

            cout << "Enter conditions: ";
            for (int i = 0; i < n; i++) {
                string cond;
                cin >> cond;
                r.conditions.push_back(cond);
            }

            cout << "Enter conclusion: ";
            cin >> r.conclusion;

            rules.push_back(r);
            cout << "Rule added.\n";

        } else if (choice == 2) {
            string fact;
            cout << "Enter fact: ";
            cin >> fact;
            facts.insert(fact);
            cout << "Fact added.\n";

        } else if (choice == 3) {
            cout << "Enter goal: ";
            cin >> goal;

        } else if (choice == 4) {
            if (goal.empty()) {
                cout << "⚠️ Please set a goal first.\n";
                continue;
            }
            set<string> visited;
            cout << "\nRunning Backward Chaining...\n";
            if (backwardChaining(goal, rules, facts, visited)) {
                cout << "✅ Goal " << goal << " can be proved.\n";
            } else {
                cout << "❌ Goal " << goal << " cannot be proved.\n";
            }

        } else if (choice == 0) {
            break;

        } else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
