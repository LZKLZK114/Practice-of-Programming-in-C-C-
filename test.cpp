#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int health[6];
int lastred = 0, lastblue = 0;

class warriors
{
public:
    int health = 0;
    int nums = 0;
};

// class dragon {
// public:
//	int health = 0, nums = 0;
// };
//
// class ninja {
// public:
//	int health = 0, nums = 0;
// };
//
// class iceman {
// public:
//	int health = 0, nums = 0;
// };
//
// class lion {
// public:
//	int health = 0, nums = 0;
// };
//
// class wolf {
// public:
//	int health = 0, nums = 0;
// };

int ranks[5][2]{0};

class base
{
public:
    warriors warrior[5]; // dragon 、ninja、iceman、lion、wolf

    /*dragon dr;
    ninja nj;
    iceman im;
    lion on;
    wolf wf;*/

    int remainhealth = 0;
    string color = " ";
    int tag = 1;
    base(string str)
    {
        color = str;
    }
    void reset()
    {
        for (int i = 0; i < 5; i++)
        {
            warrior[i].nums = 0;
        }
    }

    /*void forzero(base& color) {
        color.dr.nums = 0;
        color.im.nums = 0;
        color.on.nums = 0;
        color.nj.nums = 0;
        color.wf.nums = 0;
        return;
    }*/
};

int times[3] = {0};

void incrementTime()
{
    times[2]++;
    if (times[2] == 10)
    {
        times[2] = 0;
        times[1]++;
    }
    if (times[1] == 10)
    {
        times[1] = 0;
        times[0]++;
    }
}
base red("red");
base blue("blue");

void initialize()
{
    red.tag = 1, blue.tag = 1;
    lastred = 0, lastblue = 0;
    /*red.forzero(red);
    blue.forzero(blue);*/
    red.reset();
    blue.reset();

    for (int i = 0; i < 3; i++)
        times[i] = 0;
    int totalhealth = 0;
    cin >> totalhealth;
    red.remainhealth = totalhealth;
    blue.remainhealth = totalhealth;
    for (int i = 0; i < 5; i++)
    {
        cin >> health[i];
    }
    for (int i = 0; i < 5; i++) // dragon 、ninja、iceman、lion、wolf
    {
        red.warrior[i].health = blue.warrior[i].health = health[i];
    }
    /*red.dr.health = health[0], blue.dr.health = health[0];
    red.nj.health = health[1], blue.nj.health = health[1];
    red.im.health = health[2], blue.im.health = health[2];
    red.on.health = health[3], blue.on.health = health[3];
    red.wf.health = health[4], blue.wf.health = health[4];
    ranks[0][0] = red.im.health, ranks[1][0] = red.on.health, ranks[2][0] = red.wf.health, ranks[3][0] = red.nj.health, ranks[4][0] = red.dr.health;
    ranks[0][1] = blue.on.health, ranks[1][1] = blue.dr.health, ranks[2][1] = blue.nj.health, ranks[3][1] = blue.im.health, ranks[4][1] = blue.wf.health;*/
    ranks[0][0] = red.warrior[2].health, ranks[1][0] = red.warrior[3].health, ranks[2][0] = red.warrior[4].health, ranks[3][0] = red.warrior[1].health, ranks[4][0] = red.warrior[0].health;
    ranks[0][1] = blue.warrior[3].health, ranks[1][1] = blue.warrior[0].health, ranks[2][1] = blue.warrior[1].health, ranks[3][1] = blue.warrior[2].health, ranks[4][1] = blue.warrior[4].health;
}
void start()
{

    bool key = 0, overred = 0, overblue = 0;

    while (!key)
    {

        if (overred == 1 && overblue == 1)
        {
            break;
        }
        // red:
        bool rk = 0, bk = 0;
        int rn = -1, bn = -1;
        for (int i = lastred, cnts = 0; cnts < 5; i++)
        {
            if (rk == 1)
                break;
            if (i > 4)
                i = 0;
            if (red.remainhealth >= ranks[i][0])
            {
                red.remainhealth -= ranks[i][0];
                rn = i;
                lastred = i + 1;
                rk = 1;
            }
            cnts++;
        }
        // blue:
        for (int i = lastblue, cnts = 0; cnts < 5; i++)
        {
            if (bk == 1)
                break;
            if (i > 4)
                i = 0;
            if (blue.remainhealth >= ranks[i][1])
            {
                blue.remainhealth -= ranks[i][1];
                bn = i;
                lastblue = i + 1;
                bk = 1;
            }
            cnts++;
        }
        if (rn == -1 && overred == 0)
        {
            for (int i = 0; i < 3; i++)
                cout << times[i];
            cout << " red headquarter stops making warriors" << endl;
            overred = 1;
        }
        /*if (rn != -1 && overred == 0) {
            for (int i = 0; i < 3; i++) cout << times[i];
            cout << " red ";
            switch (rn) {
            case 0:
                red.im.nums++;
                cout << "iceman " << red.tag << " born with strength " << red.im.health << "," << red.im.nums << " iceman in red headquarter";
                break;
            case 1:
                red.on.nums++;
                cout << "lion " << red.tag << " born with strength " << red.on.health << "," << red.on.nums << " lion in red headquarter";
                break;
            case 2:
                red.wf.nums++;
                cout << "wolf " << red.tag << " born with strength " << red.wf.health << "," << red.wf.nums << " wolf in red headquarter";
                break;
            case 3:
                red.nj.nums++;
                cout << "ninja " << red.tag << " born with strength " << red.nj.health << "," << red.nj.nums << " ninja in red headquarter";
                break;
            case 4:
                red.dr.nums++;
                cout << "dragon " << red.tag << " born with strength " << red.dr.health << "," << red.dr.nums << " dragon in red headquarter";
            }
            red.tag++;
            cout << endl;
        }
        if (bn == -1 && overblue == 0) {
            for (int i = 0; i < 3; i++) cout << times[i];
            cout << " blue headquarter stops making warriors" << endl;
            overblue = 1;
        }
        if (bn != -1 && overblue == 0) {
            for (int i = 0; i < 3; i++) cout << times[i];
            int strg = 0, numss = 0;
            string names = " ";
            switch (bn) {
            case 0:
                blue.on.nums++;
                numss = blue.on.nums;
                names = "lion";
                strg = blue.on.health;
                break;
            case 1:
                blue.dr.nums++;
                numss = blue.dr.nums;
                names = "dragon";
                strg = blue.dr.health;
                break;
            case 2:
                blue.nj.nums++;
                numss = blue.nj.nums;
                names = "ninja";
                strg = blue.nj.health;
                break;
            case 3:
                blue.im.nums++;
                numss = blue.im.nums;
                names = "iceman";
                strg = blue.im.health;
                break;
            case 4:
                blue.wf.nums++;
                numss = blue.wf.nums;
                names = "wolf";
                strg = blue.wf.health;

            }
            cout << " blue " << names << " " << blue.tag << " born with strength " << strg << "," << numss << " " << names << " in blue headquarter";
            cout << endl;
            blue.tag++;
        }*/
        if (rn != -1 && overred == 0)
        {
            for (int i = 0; i < 3; i++)
                cout << times[i];
            cout << " red ";
            switch (rn)
            {
            case 0:
                red.warrior[2].nums++; // iceman
                cout << "iceman " << red.tag << " born with strength " << red.warrior[2].health << "," << red.warrior[2].nums << " iceman in red headquarter";
                break;
            case 1:
                red.warrior[3].nums++; // lion
                cout << "lion " << red.tag << " born with strength " << red.warrior[3].health << "," << red.warrior[3].nums << " lion in red headquarter";
                break;
            case 2:
                red.warrior[4].nums++; // wolf
                cout << "wolf " << red.tag << " born with strength " << red.warrior[4].health << "," << red.warrior[4].nums << " wolf in red headquarter";
                break;
            case 3:
                red.warrior[1].nums++; // ninja
                cout << "ninja " << red.tag << " born with strength " << red.warrior[1].health << "," << red.warrior[1].nums << " ninja in red headquarter";
                break;
            case 4:
                red.warrior[0].nums++; // dragon
                cout << "dragon " << red.tag << " born with strength " << red.warrior[0].health << "," << red.warrior[0].nums << " dragon in red headquarter";
            }
            red.tag++;
            cout << endl;
        }

        if (bn == -1 && overblue == 0)
        {
            for (int i = 0; i < 3; i++)
                cout << times[i];
            cout << " blue headquarter stops making warriors" << endl;
            overblue = 1;
        }

        if (bn != -1 && overblue == 0)
        {
            for (int i = 0; i < 3; i++)
                cout << times[i];
            int strg = 0, numss = 0;
            string names = " ";
            switch (bn)
            {
            case 0:
                blue.warrior[3].nums++; // lion
                numss = blue.warrior[3].nums;
                names = "lion";
                strg = blue.warrior[3].health;
                break;
            case 1:
                blue.warrior[0].nums++; // dragon
                numss = blue.warrior[0].nums;
                names = "dragon";
                strg = blue.warrior[0].health;
                break;
            case 2:
                blue.warrior[1].nums++; // ninja
                numss = blue.warrior[1].nums;
                names = "ninja";
                strg = blue.warrior[1].health;
                break;
            case 3:
                blue.warrior[2].nums++; // iceman
                numss = blue.warrior[2].nums;
                names = "iceman";
                strg = blue.warrior[2].health;
                break;
            case 4:
                blue.warrior[4].nums++; // wolf
                numss = blue.warrior[4].nums;
                names = "wolf";
                strg = blue.warrior[4].health;
            }
            cout << " blue " << names << " " << blue.tag << " born with strength " << strg << "," << numss << " " << names << " in blue headquarter";
            cout << endl;
            blue.tag++;
        }
        incrementTime();
    }
}
int main()
{
    int cases = 0;
    cin >> cases;
    for (int i = 1; i <= cases; i++)
    {
        cout << "Case:" << i << endl;
        initialize();
        start();
    }
}