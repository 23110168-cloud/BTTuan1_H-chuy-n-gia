#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> a;

void sinhnhiphan(string current, int n)
{
    if (current.length() == n)
    {
        a.push_back(current);
        return;
    }
    sinhnhiphan(current + "0", n);
    if (current.empty() || current.back() == '0')
    {
        sinhnhiphan(current + "1", n);
    }
}

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    int n;
    if (!(infile >> n) || n <= 0)
    {
        cerr << "Erol!\n";
        return 1;
    }

    infile.close();
    sinhnhiphan("", n);
    for (const string &s : a)
    {
        outfile << s << "\n";
    }
    outfile.close();

    return 0;
}
