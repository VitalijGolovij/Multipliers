// information security lab 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include<list>
#include<set>
#include<fstream>
#include<string>
using namespace std;

int C(int n, int k)
{
    if (k == 0 || k == n)
        return 1;
    return C(n - 1, k - 1) * n / k;
}

int fact(int n)
{
    if (n == 0)
        return 1;
    return n * fact(n - 1);
}

int NumbCombInSet(list<int> l)
{
    list<int>::iterator it = l.begin();

    set<int> listItems(l.begin(), l.end());
    set<int>::iterator Itset = listItems.begin();
    
    list<int> countItems;

    for (; Itset != listItems.end(); Itset++)
    {
        int count = 0;
        for (; it!=l.end();it++)
        {
            if (*Itset == *it) count++;
        }
        countItems.push_back(count);
        it = l.begin();
    }

    countItems.sort();
    it = countItems.begin();
    int n = l.size();
    int num = 1;

    for (; it != countItems.end(); it++)
    {
        num *= C(n, *it);
        n -= *it;
    }

    return num;
}

bool IsPrimeNumber(int n)
{
    for (int i = 2; i < n; i++)
        if (n % i == 0) return false;
    return true;
}

int NextPrimeNumber(int primeNum)
{
    primeNum++;
    while (!IsPrimeNumber(primeNum)) primeNum++;
    return primeNum;
}

int MultItems(list<int> l)
{
    list<int>::iterator it = l.begin();
    int mult = 1;
    for (; it != l.end(); it++) mult *= *it;
    return mult;
}

list<int> NextSetList(list<int> l)
{
    list<int>::iterator it = l.begin();
    l.sort();
    int* temp = new int[l.size()];
    for (int i = 0; i < l.size(); i++) {
        temp[i] = *it;
        it++;
    }

    it = l.begin();
    if (l.size() > 1) {
        for (int i = 0; i < l.size() - 1; i++)
        {
            it++;
            if (temp[i] == temp[i + 1])
            {
                l.erase(it);
                l.push_back(NextPrimeNumber(temp[i]));
                return l;
            }
        }
        it = l.begin();
        l.pop_back();
        for (; it != l.end(); it++)*it = 2;
        return l;
    }
    else
    {
        l.pop_back();
        return l;
    }
}

int Min(list<int> l)
{
    list<int>::iterator it = l.begin();
    int min = *it;
    for (; it != l.end(); it++)
        if (*it < min)min = *it;
    return min;
}

int Solution(int n)
{
    list<int> base;
    list<int> solutions;

    for (int i = 0; i < n; i++) 
        base.push_back(2);

    if (n > 1)
    {
        while (base.size() > 0)
        {
            base = NextSetList(base);
            if (NumbCombInSet(base) == n) solutions.push_back(MultItems(base));
        }
        return Min(solutions);
    }
    else return 2;
}

int main()
{
    string line;
    fstream in("input.txt");
    ofstream out("output.txt");
    while (getline(in, line))
    {
        int n = stoi(line);
        out << n << " " << Solution(n)<<endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
