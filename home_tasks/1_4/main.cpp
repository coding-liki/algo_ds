#include <iostream>
#include <map>
#include <string>
using namespace std;

struct state {
    size_t countMultilineParenthesisComments = 0;
    size_t countSingleLineComments = 0;
    size_t countMultilineBraceComments = 0;
    size_t countLiteralStrings = 0;
};

enum DFA_STAGE {
    IN_SIMPLE_CODE,
    PARTLY_IN_SINGLE_LINE_COMMENT,
    IN_SINGLE_LINE_COMMENT,
    PARTLY_IN_MULTILINE_PARENTHESIS_COMMENT,
    IN_MULTILINE_PARENTHESIS_COMMENT,
    PARTLY_OUT_MULTILINE_PARENTHESIS_COMMENT,
    IN_MULTILINE_BRACE_COMMENT,
    IN_LITERAL_STRING
};

bool DFA(string const &s, state *dfaState) {
    auto stage = IN_SIMPLE_CODE;
    map<DFA_STAGE, DFA_STAGE (*)(state *)> defaultActionMap = {
        {IN_SIMPLE_CODE, [](state *) { return IN_SIMPLE_CODE; }},
        {IN_SINGLE_LINE_COMMENT, [](state *) { return IN_SINGLE_LINE_COMMENT; }},
        {IN_MULTILINE_PARENTHESIS_COMMENT, [](state *) { return IN_MULTILINE_PARENTHESIS_COMMENT; }},
        {IN_MULTILINE_BRACE_COMMENT, [](state *) { return IN_MULTILINE_BRACE_COMMENT; }},
        {IN_LITERAL_STRING, [](state *_) { return IN_LITERAL_STRING; }},
        {PARTLY_IN_SINGLE_LINE_COMMENT, [](state *) { return IN_SIMPLE_CODE; }},
        {PARTLY_IN_MULTILINE_PARENTHESIS_COMMENT, [](state *) { return IN_SIMPLE_CODE; }},
        {PARTLY_OUT_MULTILINE_PARENTHESIS_COMMENT, [](state *) { return IN_MULTILINE_PARENTHESIS_COMMENT; }},
    };

    map<DFA_STAGE, map<char, DFA_STAGE (*)(state *)> > dfaMap = {
        {
            IN_SIMPLE_CODE, {
                {'/', [](state *) { return PARTLY_IN_SINGLE_LINE_COMMENT; }},
                {'{', [](state *) { return IN_MULTILINE_BRACE_COMMENT; }},
                {'(', [](state *) { return PARTLY_IN_MULTILINE_PARENTHESIS_COMMENT; }},
                {static_cast<char>(39), [](state *) { return IN_LITERAL_STRING; }},
            }
        },
        {
            PARTLY_IN_SINGLE_LINE_COMMENT, {
                {'/', [](state *) { return IN_SINGLE_LINE_COMMENT; }},
                {'{', [](state *) { return IN_MULTILINE_BRACE_COMMENT; }},
                {static_cast<char>(39), [](state *) { return IN_LITERAL_STRING; }},
                {'(', [](state *) { return PARTLY_IN_MULTILINE_PARENTHESIS_COMMENT; }},
            }
        },
        {
            IN_SINGLE_LINE_COMMENT, {
                {
                    '\n', [](state *state) -> DFA_STAGE {
                        state->countSingleLineComments++;
                        return IN_SIMPLE_CODE;
                    }
                },
                {
                    '\0', [](state *state) {
                        state->countSingleLineComments++;
                        return IN_SIMPLE_CODE;
                    }
                },
            }
        },
        {
            PARTLY_IN_MULTILINE_PARENTHESIS_COMMENT, {
                {'*', [](state *) { return IN_MULTILINE_PARENTHESIS_COMMENT; }},
                {static_cast<char>(39), [](state *state) { return IN_LITERAL_STRING; }},
                {'/', [](state *) { return PARTLY_IN_SINGLE_LINE_COMMENT; }},
                {'{', [](state *) { return IN_MULTILINE_BRACE_COMMENT; }},
            }
        },
        {
            IN_MULTILINE_PARENTHESIS_COMMENT, {
                {'*', [](state *) { return PARTLY_OUT_MULTILINE_PARENTHESIS_COMMENT; }}
            }
        },
        {
            PARTLY_OUT_MULTILINE_PARENTHESIS_COMMENT, {
                {
                    ')', [](state *state) {
                        state->countMultilineParenthesisComments++;
                        return IN_SIMPLE_CODE;
                    }
                }
            }
        },
        {
            IN_MULTILINE_BRACE_COMMENT, {
                {
                    '}', [](state *state) {
                        state->countMultilineBraceComments++;
                        return IN_SIMPLE_CODE;
                    }
                }
            }
        },
        {
            IN_LITERAL_STRING, {
                {
                    static_cast<char>(39), [](state *state) {
                        state->countLiteralStrings++;
                        return IN_SIMPLE_CODE;
                    }
                }
            }
        }
    };

    int number = 0;
    for (auto c: s) {
        if (dfaMap.contains(stage) && dfaMap[stage].contains(c)) {
            stage = dfaMap[stage][c](dfaState);
        } else if (defaultActionMap.contains(stage)) {
            stage = defaultActionMap[stage](dfaState);
        }
        number++;
    }


    return stage == IN_SIMPLE_CODE;
}

int main() {
    string input;
    state state;
    string buffer;
    while (cin >> buffer) {
        input.append(buffer);

        if (char c; cin.get(c)) {
            input.push_back(c);
        }
    }
    DFA(input, &state);

    cout
            << state.countMultilineParenthesisComments << " "
            << state.countMultilineBraceComments << " "
            << state.countSingleLineComments << " "
            << state.countLiteralStrings;
    return 0;
}
