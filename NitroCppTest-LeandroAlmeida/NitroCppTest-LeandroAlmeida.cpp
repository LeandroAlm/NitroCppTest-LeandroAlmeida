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
void CalculateItersection(const vector<unique_ptr<CustomRectangle>>& _rects)
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

    auto Interssection = make_unique<CustomRectangle>(Position2D(x1, y1), Position2D(x2, y2));

    // In case of no intersection
    if (!Interssection->Verify())
        return;

    printf("Between rectangle x and x at (%.2f, %.2f), w=%.2f, h=%.2f.", Interssection->GetLeftTopCorner().x, Interssection->GetLeftTopCorner().y, 
        Interssection->GetRightBottomCorner().x - Interssection->GetLeftTopCorner().x, Interssection->GetRightBottomCorner().y - Interssection->GetLeftTopCorner().y);
}

bool fileExists(const std::string& filePath) {
    ifstream file(filePath);
    return file.is_open();
}

void PrintTitle()
{
    ColoredPrintf::CPrint("######################################\n", ColoredPrintf::Cyan);
    ColoredPrintf::CPrint("#", ColoredPrintf::Cyan);
    cout << " Rectangle Intersections Calculator ";
    ColoredPrintf::CPrint("#\n", ColoredPrintf::Cyan);
    ColoredPrintf::CPrint("######################################\n", ColoredPrintf::Cyan);
}

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
            ColoredPrintf::CPrint("\n>  ", ColoredPrintf::Yellow);
            system("pause");
            system("cls");
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

int main()
{

    vector<unique_ptr<CustomRectangle>> AllRects;

    string FileName = PrintMenu();

    // Open the JSON file
    ifstream file(FileName);

    JSON json;
    file >> json;

    for (const auto& RectSpecs : json["rects"]) {

        AllRects.push_back(make_unique<CustomRectangle>(Position2D(RectSpecs["x"], RectSpecs["y"]), Position2D((double)RectSpecs["x"] + RectSpecs["w"], (double)RectSpecs["y"] + RectSpecs["h"])));
    }

    file.close();
    json.clear();

    // TODO Create a loop system to detect intersections
    //CalculateItersection(AllRects);

    // just to keep cmd open
    getchar();

    return 0;
}
