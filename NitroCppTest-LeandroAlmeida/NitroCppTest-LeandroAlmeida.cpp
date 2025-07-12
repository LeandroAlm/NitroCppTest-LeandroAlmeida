// Leandro Almeida Assessment

#include <iostream>
#include <vector>
#include <fstream>
#include "json.hpp"
#include "Helper.h"
#include "CustomRectangle.h"

using namespace std;
using JSON = nlohmann::json;

/// <summary>
/// Calculate intersections between rectangles
/// </summary>
/// <param name="_rects">All rectacngles to verify intersection</param>
bool CalculateItersection(const vector<shared_ptr<CustomRectangle>>& _rects, vector<int> callbackStack)
{
    auto x1 = _rects[0]->GetLeftTopCorner().x;
    auto x2 = _rects[0]->GetRightBottomCorner().x;
    auto y1 = _rects[0]->GetLeftTopCorner().y;
    auto y2 = _rects[0]->GetRightBottomCorner().y;

    for (int i = 1; i < _rects.size(); i++)
    {
        if (_rects[i]->GetLeftTopCorner().x > x1)
            x1 = _rects[i]->GetLeftTopCorner().x;

        if (_rects[i]->GetRightBottomCorner().x < x2)
            x2 = _rects[i]->GetRightBottomCorner().x;

        if (_rects[i]->GetLeftTopCorner().y > y1)
            y1 = _rects[i]->GetLeftTopCorner().y;

        if (_rects[i]->GetRightBottomCorner().y < y2)
            y2 = _rects[i]->GetRightBottomCorner().y;
    }

    auto Intersection = make_shared<CustomRectangle>(Position2D(x1, y1), Position2D(x2, y2));

    // In case of no intersection
    if (!Intersection->Verify())
        return false;

    // Print Intersection
    cout << "Between rectangle ";
    ColoredPrintf::CPrint((callbackStack[0] + 1), ColoredPrintf::Cyan);
    for (int i = 1; i < callbackStack.size(); i++)
    {
        cout << " and ";
        ColoredPrintf::CPrint((callbackStack[i] + 1), ColoredPrintf::Cyan);
    }

    cout << " at (";
    ColoredPrintf::CPrint(Intersection->GetLeftTopCorner().x, ColoredPrintf::Green);
    cout << ", ";
    ColoredPrintf::CPrint(Intersection->GetLeftTopCorner().y, ColoredPrintf::Green);
    cout << "), w=";
    ColoredPrintf::CPrint((Intersection->GetRightBottomCorner().x - Intersection->GetLeftTopCorner().x), ColoredPrintf::Yellow);
    cout << ", h=";
    ColoredPrintf::CPrint((Intersection->GetRightBottomCorner().y - Intersection->GetLeftTopCorner().y), ColoredPrintf::Yellow);
    cout << ";\n";

    return true;
}

/// <summary>
/// Verify if file exists
/// </summary>
/// <param name="filePath"></param>
/// <returns></returns>
bool fileExists(const std::string& filePath) {
    ifstream file(filePath);
    return file.is_open();
}

/// <summary>
/// Print the title message
/// </summary>
void PrintTitle()
{
    ColoredPrintf::CPrint("######################################\n", ColoredPrintf::Cyan);
    ColoredPrintf::CPrint("#", ColoredPrintf::Cyan);
    cout << " Rectangle Intersections Calculator ";
    ColoredPrintf::CPrint("#\n", ColoredPrintf::Cyan);
    ColoredPrintf::CPrint("######################################\n", ColoredPrintf::Cyan);
}

/// <summary>
/// Keep console open and print message to press Enter
/// </summary>
void KeepConsoleWaiting()
{
    ColoredPrintf::CPrint("\n>  ", ColoredPrintf::Yellow);
    system("pause");
    system("cls");
}

/// <summary>
/// Menu handler, lock in menu till type a valid command or json file
/// </summary>
/// <returns></returns>
string PrintMenu()
{
    string filePath, input;
    bool isInMenu = true;
    bool isDisplayErrorOn = false;

    while (isInMenu)
    {
        PrintTitle();
        ColoredPrintf::CPrint("#", ColoredPrintf::Cyan);
        cout << "         Special Commands           ";
        ColoredPrintf::CPrint("#\n", ColoredPrintf::Cyan);
        ColoredPrintf::CPrint("#", ColoredPrintf::Cyan);
        cout << " 1. help                            ";
        ColoredPrintf::CPrint("#\n", ColoredPrintf::Cyan);
        ColoredPrintf::CPrint("#", ColoredPrintf::Cyan);
        cout << " 2. test                            ";
        ColoredPrintf::CPrint("#\n", ColoredPrintf::Cyan);
        ColoredPrintf::CPrint("#", ColoredPrintf::Cyan);
        cout << " 3. exit                            ";
        ColoredPrintf::CPrint("#\n", ColoredPrintf::Cyan);
        ColoredPrintf::CPrint("######################################\n", ColoredPrintf::Cyan);

        if (isDisplayErrorOn)
            ColoredPrintf::CPrint("\nFile not foud or invalid type!\n", ColoredPrintf::Red);

        ColoredPrintf::CPrint("\n> ", ColoredPrintf::Yellow);
        cout << "Type a command or the file name (the file must be added to Data folder)";

        ColoredPrintf::CPrint("\n> ", ColoredPrintf::Yellow);

        getline(cin, input);

        if (input == "help")
        {
            system("cls");

            PrintTitle();
            ColoredPrintf::CPrint("\n> ", ColoredPrintf::Yellow);
            cout << " The application reads a json file with a specific format.";
            ColoredPrintf::CPrint("\n> ", ColoredPrintf::Yellow);
            cout << " The JSON file must be in Data/ folder.";
            ColoredPrintf::CPrint("\n> ", ColoredPrintf::Yellow);
            cout << " Type 'test' to quick test the default file Rectangles_Example.json.";
            ColoredPrintf::CPrint("\n> ", ColoredPrintf::Yellow);
            cout << " Type 'exit' to close the application.";
            KeepConsoleWaiting();
        }
        else if (input == "test")
        {
            system("cls");

            filePath = "Data/Rectangles_Example.json";

            if (!fileExists(filePath))
            {
                system("cls");
                isDisplayErrorOn = true;
            }
            else
            {
                system("cls");
                isInMenu = false;
            }
        }
        else if (input == "exit")
        {
            exit(0);
        }
        else
        {
            filePath = "Data/" + input;

            if (!fileExists(filePath))
            {
                system("cls");
                isDisplayErrorOn = true;
            }
            else
            {
                system("cls");
                isInMenu = false;
            }
        }
        }

    return filePath;
}

/// <summary>
/// Callback to interpolate all combinations
/// </summary>
/// <param name="allRects">All recatgles loaded from JSON</param>
/// <param name="callbackStack">Current ids in stack</param>
/// <param name="id">Current id</param>
void CallbackIntersectionDetection(const vector<shared_ptr<CustomRectangle>>& allRects, vector<int> callbackStack, const int id)
{
    for (int i = id; i <= allRects.size() - 1; i++)
    {
        vector<shared_ptr<CustomRectangle>> rects;
        callbackStack.push_back(i);

        for (int j = 0; j < callbackStack.size(); j++)
        {
            rects.push_back(allRects[callbackStack[j]]);
        }

        if (callbackStack.size() <  2 || CalculateItersection(rects, callbackStack))
            CallbackIntersectionDetection(allRects, callbackStack, i + 1);
        callbackStack.pop_back();
    }
}

/// <summary>
/// Load a json files and extract rectangles from it
/// </summary>
/// <param name="fileName">json file name e.g. Rectangles_Example.json</param>
/// <returns>Rectangles found in json file</returns>
vector<shared_ptr<CustomRectangle>> LoadAllRectanglesFromJson(string fileName)
{
    vector<shared_ptr<CustomRectangle>> AllRects;

    // Open the JSON file
    ifstream file(fileName);

    JSON json;
    file >> json;

    ColoredPrintf::CPrint("######################################\n", ColoredPrintf::Cyan);
    ColoredPrintf::CPrint("#", ColoredPrintf::Cyan);
    cout << "          Rectangles found          ";
    ColoredPrintf::CPrint("#\n", ColoredPrintf::Cyan);
    ColoredPrintf::CPrint("######################################\n\n", ColoredPrintf::Cyan);

    int count = 1;
    for (const auto& RectSpecs : json["rects"]) {
        cout << "Rectangle ";
        ColoredPrintf::CPrint(count, ColoredPrintf::Cyan);

        if (!RectSpecs.contains("x") || !RectSpecs.contains("y") || !RectSpecs.contains("w") || !RectSpecs.contains("h"))
        {
            ColoredPrintf::CPrint(" with wrong data, it's expected x, y, w and h\n", ColoredPrintf::Red);
            AllRects.clear();
            break;
        }

        cout << " created at ";
        AllRects.push_back(make_shared<CustomRectangle>(Position2D(RectSpecs["x"], RectSpecs["y"]),
            Position2D((double)RectSpecs["x"] + RectSpecs["w"], (double)RectSpecs["y"] + RectSpecs["h"]), true));

        count++;
    }

    file.close();
    json.clear();

    return AllRects;
}

int main()
{
    while (true)
    {
        string FileName = PrintMenu();
        vector<shared_ptr<CustomRectangle>> AllRects = LoadAllRectanglesFromJson(FileName);

        if (AllRects.size() > 1)
        {
            // calculate intersections
            ColoredPrintf::CPrint("\n######################################\n", ColoredPrintf::Cyan);
            ColoredPrintf::CPrint("#", ColoredPrintf::Cyan);
            cout << "       Intersections found         ";
            ColoredPrintf::CPrint("#\n", ColoredPrintf::Cyan);
            ColoredPrintf::CPrint("######################################\n\n", ColoredPrintf::Cyan);

            vector<int> callbackStack;
            CallbackIntersectionDetection(AllRects, callbackStack, 0);

            // just to keep cmd open
            KeepConsoleWaiting();
        }
        else
        {
            // display error json format
            ColoredPrintf::CPrint("\n> ", ColoredPrintf::Yellow);
            ColoredPrintf::CPrint("JSON with bad format or less than 2 rectangles found.\n", ColoredPrintf::Red);

            // just to keep cmd open
            KeepConsoleWaiting();
        }
    }

    return 0;
}
