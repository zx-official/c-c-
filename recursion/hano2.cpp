#include <iostream>
#include <stack>

using namespace std;

class Move {
public:
    Move(int n, char src, char tgt, char aux) : num(n), source(src), target(tgt), auxiliary(aux) {}

    int num;
    char source, target, auxiliary;
};

void hanoi(int n) {
    stack<Move> moves;
    moves.push(Move(n, 'A', 'C', 'B'));

    while (!moves.empty()) {
        Move currentMove = moves.top();
        moves.pop();

        int num = currentMove.num;
        char source = currentMove.source;
        char target = currentMove.target;
        char auxiliary = currentMove.auxiliary;

        if (num == 1) {
            // 直接移动一个圆盘
            cout << "Move disk 1 from " << source << " to " << target << endl;
        } else {
            // 拆分任务并按逆序压入栈
            moves.push(Move(num - 1, auxiliary, target, source));
            moves.push(Move(1, source, target, auxiliary));
            moves.push(Move(num - 1, source, auxiliary, target));
        }
    }
}

int main() {
    int numDisks = 3;
    hanoi(numDisks);
    return 0;
}
