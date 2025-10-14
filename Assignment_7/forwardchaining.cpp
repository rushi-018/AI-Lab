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

// Forward Chaining Function
bool forwardChaining(vector<Rule>& rules, set<string>& facts, string goal) {
    bool addedNewFact = true;

    while (addedNewFact) {
        addedNewFact = false;

        for (auto& rule : rules) {
            bool satisfied = true;

            // Check if all conditions are present in facts
            for (auto& cond : rule.conditions) {
                if (facts.find(cond) == facts.end()) {
                    satisfied = false;
                    break;
                }
            }

            // Add conclusion if conditions satisfied
            if (satisfied && facts.find(rule.conclusion) == facts.end()) {
                cout << "Deriving: " << rule.conclusion << " from rule\n";
                facts.insert(rule.conclusion);
                addedNewFact = true;

                if (rule.conclusion == goal) {
                    cout << "✅ Goal " << goal << " reached!\n";
                    return true;
                }
            }
        }
    }

    return (facts.find(goal) != facts.end());
}

int main() {
    int choice;
    vector<Rule> rules;
    set<string> facts;
    string goal;

    cout << "=== Forward Chaining Inference System ===\n";

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Rule\n";
        cout << "2. Add Fact\n";
        cout << "3. Set Goal\n";
        cout << "4. Run Forward Chaining\n";
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
            cout << "\nRunning Forward Chaining...\n";
            if (!forwardChaining(rules, facts, goal)) {
                cout << "❌ Goal " << goal << " not reached.\n";
            }

        } else if (choice == 0) {
            break;

        } else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
