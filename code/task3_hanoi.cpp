// ──────────────────────────────────────────────────────────────────────────
//  COMPLETE SOLUTION: Dynamic Programming + Frame-Stewart Move Generator
//  Computes the minimum moves table, prints the DP table, answers the
//  '33 moves' question, then generates and prints the full move sequence.
// ──────────────────────────────────────────────────────────────────────────
#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <iomanip>  // for setw()
using namespace std;
typedef long long ll;

// ── Global move log ────────────────────────────────────────────────────────
int       moveCount = 0;
vector<string> moveLog;

void logMove(int disk, char from, char to) {
    ++moveCount;
    string moveStr;
    if (moveCount < 10)
        moveStr = "  Move " + to_string(moveCount) + ":  ";
    else
        moveStr = "  Move " + to_string(moveCount) + ": ";

    string diskStr = "Disk " + to_string(disk);
    if (disk < 10) diskStr += " ";

    moveLog.push_back(moveStr + diskStr + "  " + from + " -> " + to);
}

// ── Three-peg Hanoi (used as Step-2 subroutine) ────────────────────────────
void hanoi3(int n, int base, char from, char to, char aux) {
    if (n == 0) return;
    hanoi3(n - 1, base, from, aux, to);
    logMove(base + n - 1, from, to);
    hanoi3(n - 1, base, aux, to, from);
}

// ── Frame-Stewart four-peg D&C ─────────────────────────────────────────────
void hanoi4(int n, int base, char from, char to,
    char aux1, char aux2,
    const vector<int>& kopt) {
    if (n == 0) return;
    if (n == 1) { logMove(base, from, to); return; }

    int k = kopt[n];
    hanoi4(k, base, from, aux1, aux2, to, kopt);  // Step 1
    hanoi3(n - k, base + k, from, to, aux2);              // Step 2
    hanoi4(k, base, aux1, to, from, aux2, kopt); // Step 3
}

// ── DP: build Frame-Stewart table for 1..N ────────────────────────────────
void buildDP(int N, vector<ll>& dp, vector<int>& kopt) {
    dp.assign(N + 1, LLONG_MAX);
    kopt.assign(N + 1, 0);
    dp[0] = 0; dp[1] = 1; kopt[1] = 1;

    for (int i = 2; i <= N; i++) {
        for (int k = 1; k < i; k++) {
            ll h3 = (1LL << (i - k)) - 1;   // T(i-k, 3)
            ll cost = 2LL * dp[k] + h3;
            if (cost < dp[i]) {
                dp[i] = cost;
                kopt[i] = k;
            }
        }
    }
}
// ── Print a separator line ─────────────────────────────────────────────────
void printSeparator(int nWidth, int t4Width, int kWidth, int t3Width) {
    cout << "+";
    for (int i = 0; i < nWidth + 2; i++) cout << "-";
    cout << "+";
    for (int i = 0; i < t4Width + 2; i++) cout << "-";
    cout << "+";
    for (int i = 0; i < kWidth + 2; i++) cout << "-";
    cout << "+";
    for (int i = 0; i < t3Width + 2; i++) cout << "-";
    cout << "+" << endl;
}
// ── Main ──────────────────────────────────────────────────────────────────
int main() {
    const int N = 8;
    vector<ll>  dp;
    vector<int> kopt;
    buildDP(N, dp, kopt);

    // ── Print DP table ────────────────────────────────────────────────────
       // ── Calculate column widths ──
    int nWidth = to_string(N).length();
    int t4Width = to_string(dp[N]).length();
    int kWidth = to_string(kopt[N]).length();
    int t3Width = to_string((1LL << N) - 1).length();

    // ── Minimum widths for headers ──
    if (nWidth < 1) nWidth = 1;
    if (t4Width < 6) t4Width = 6;   // "T(n,4)"
    if (kWidth < 4) kWidth = 4;     // "kopt"
    if (t3Width < 6) t3Width = 6;   // "T(n,3)"

    // ── Print DP table with proper formatting ──
    printSeparator(nWidth, t4Width, kWidth, t3Width);
    cout << "| " << left << setw(nWidth) << "n"
        << " | " << setw(t4Width) << "T(n,4)"
        << " | " << setw(kWidth) << "kopt"
        << " | " << setw(t3Width) << "T(n,3)" << " |" << endl;
    printSeparator(nWidth, t4Width, kWidth, t3Width);

    for (int i = 1; i <= N; i++) {
        cout << "| " << left << setw(nWidth) << i
            << " | " << setw(t4Width) << dp[i]
            << " | " << setw(kWidth) << kopt[i]
            << " | " << setw(t3Width) << ((1LL << i) - 1) << " |" << endl;
    }
    printSeparator(nWidth, t4Width, kWidth, t3Width);

    // ── Answer the 33-move question ───────────────────────────────────────
    cout << "\nOPT(8,4) = " << dp[N] << endl;
    cout << "Can DP solve in 33 moves? "
        << (dp[N] == 33 ? "YES - confirmed!" : "NO") << endl;

    // ── Generate the full move sequence ──────────────────────────────────
    hanoi4(N, 1, 'A', 'D', 'B', 'C', kopt);
    cout << "\nTotal moves generated: " << moveCount << endl;
    for (auto& m : moveLog) cout << m << endl;

    return 0;
}
