#include <bits/stdc++.h>
using namespace std;
string generateRandomString(int length)
{
    static const char alpha[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string randomString;
    randomString.reserve(length);
    for (int i = 0; i < length; ++i)
    {
        randomString += alpha[rand() % (sizeof(alpha) - 1)];
    }
    return randomString;
}
int generateRandomNumber(int min, int max)
{
    return min + rand() % (max - min + 1);
}
void trim(string &str)
{
    size_t start = str.find_first_not_of(" \t");
    if (start != string::npos)
    {
        str = str.substr(start);
    }
    size_t end = str.find_last_not_of(" \t");
    if (end != string::npos)
    {
        str = str.substr(0, end + 1);
    }
}
void parseKeyValue(string &line, string &key, string &value)
{
    size_t colonPos = line.find(':');
    key = line.substr(0, colonPos);
    value = line.substr(colonPos + 1);
    trim(key);
    if (key.size() == 0)
    {
        cout << "Key should be there." << endl;
        exit(0);
    }
    trim(value);
    if (value.back() == ',')
    {
        value.pop_back();
    }
    if (value.size() == 0)
    {
        cout << key << " should have value." << endl;
        exit(0);
    }
}
int main()
{
    srand(time(0));
    string line;
    vector<pair<string, string>> properties;
    getline(cin, line);
    trim(line);
    if (line == "[")
    {
        string key, type;
        while (getline(cin, line))
        {
            trim(line);
            if (line == "{")
                continue;
            if (line == "}" or line == "},")
            {
                properties.push_back(make_pair(key, type));
                continue;
            }
            if (line == "]")
                break;
            string first, second;
            parseKeyValue(line, first, second);
            if (first == "\"key\"")
                key = second;
            if (first == "\"type\"")
                type = second;
        }
    }
    else
    {
        cout << "Wrong Starting." << endl;
        exit(0);
    }
    int n;
    cout << "n: ";
    cin >> n;
    cout << '[' << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << '{' << endl;
        for (size_t j = 0; j < properties.size(); ++j)
        {
            cout << "\t" << properties[j].first << ":";
            if (properties[j].second == "\"string\"")
            {
                cout << '"' << generateRandomString(7) << '"';
            }
            else if (properties[j].second == "\"number\"")
            {
                cout << generateRandomNumber(20, 50);
            }
            else if (properties[j].second == "\"boolean\"")
            {
                if (rand() % 2 == 0)
                    cout << "false";
                else
                    cout << "true";
            }
            if (j < properties.size() - 1)
            {
                cout << ',';
            }
            cout << endl;
        }
        cout << '}';
        if (i < n - 1)
        {
            cout << ',';
        }
        cout << endl;
    }
    cout << ']' << endl;
    return 0;
}