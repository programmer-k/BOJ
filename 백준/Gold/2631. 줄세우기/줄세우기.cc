#include <iostream>
using namespace std;

int n;
int kids[200];
int dp[200];

void GetInput()
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> kids[i];
}

void Solve()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
            if (kids[i] > kids[j])
                dp[i] = max(dp[i], dp[j]);
        dp[i]++;
    }

    int maximum = dp[0];
    for (int i = 1; i < n; i++)
        maximum = max(maximum, dp[i]);
    
    cout << n - maximum << '\n';
}

int main(void)
{
    GetInput();
    Solve();
    return 0;
}