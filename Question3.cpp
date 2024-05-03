#include <bits/stdc++.h>
using namespace std;
struct JSONObject
{
    map<string, string> keyValuePairs;
    map<string, JSONObject> nestedObj;
};
stack<char> bracketStack;
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
    if (key.front() == '\"')
    {
        key = key.substr(1);
    }
    if (key.back() == '\"')
    {
        key.pop_back();
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
JSONObject &parseInputAndBuildJSON(JSONObject &jsonObj, string line)
{
    if (line != "{")
    {
        getline(cin, line);
    }
    if (line == "{")
    {
        bracketStack.push('{');
        while (getline(cin, line))
        {
            if (line == "}")
            {
                if (bracketStack.empty())
                {
                    cout << "Invalid JSON" << endl;
                    exit(1);
                }
                bracketStack.pop();
                return jsonObj;
            }
            else
            {
                string key, value;
                parseKeyValue(line, key, value);
                if (value == "{")
                {
                    JSONObject nestedObject;
                    if (jsonObj.keyValuePairs.find(key) != jsonObj.keyValuePairs.end())
                    {
                        jsonObj.keyValuePairs.erase(jsonObj.keyValuePairs.find(key));
                    }
                    jsonObj.nestedObj[key] = parseInputAndBuildJSON(nestedObject, value);
                }
                else
                {
                    auto it = jsonObj.nestedObj.find(key);
                    if (it != jsonObj.nestedObj.end())
                    {
                        jsonObj.nestedObj.erase(it);
                    }
                    jsonObj.keyValuePairs[key] = value;
                }
            }
        }
    }
    else
    {
        cout << "Invalid JSON" << endl;
        exit(1);
    }
    return jsonObj;
}
void printJSONObject(const JSONObject &jsonObj, const string &parentKey = "", int space = 0)
{
    if (!parentKey.empty())
    {
        for (int i = 0; i < space; i++)
        {
            cout << "\t";
        }
        cout << '\"' << parentKey << '\"' << ": {" << endl;
    }
    else
    {
        cout << "{" << endl;
    }
    for (const auto &pair : jsonObj.keyValuePairs)
    {
        for (int i = 0; i < space + 1; i++)
        {
            cout << "\t";
        }
        cout << '\"' << pair.first << '\"' << ": " << pair.second << endl;
    }
    for (const auto &pair : jsonObj.nestedObj)
    {
        printJSONObject(pair.second, pair.first, space + 1);
    }
    for (int i = 0; i < space; i++)
    {
        cout << "\t";
    }
    cout << "}" << endl;
}
int main()
{
    JSONObject JSON;
    cout << "ENTER JSON" << endl;
    parseInputAndBuildJSON(JSON, "");
    cout << "ENTER PATH" << endl;
    string path;
    getline(cin, path);
    trim(path);
    vector<std::string> parts;
    if (path.front() == '\"')
    {
        path = path.substr(1);
    }
    if (path.back() == '\"')
    {
        path.pop_back();
    }
    istringstream iss(path);
    string part;
    while (getline(iss, part, '.'))
    {
        parts.push_back(part);
    }
    int n = parts.size();
    JSONObject obj = JSON;
    for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
        {
            auto it = obj.keyValuePairs.find(parts[i]);
            auto itr = obj.nestedObj.find(parts[i]);
            if (it != obj.keyValuePairs.end())
            {
                cout << it->second << endl;
            }
            else if (itr != obj.nestedObj.end())
            {
                printJSONObject(itr->second);
            }
            else
            {
                cout << "Path does not exist." << endl;
            }
            return 0;
        }
        else if (obj.nestedObj.find(parts[i]) != obj.nestedObj.end())
        {
            obj = obj.nestedObj.find(parts[i])->second;
        }
        else
        {
            cout << "Path does not exist." << endl;
            return 0;
        }
    }
    return 0;
}