#include <iostream>
#include <ctime>
#include <chrono>
#include <raylib.h>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

int cacheMemory = 4000;
int numBlocks = 50;
int gridCols = 6;
const int blockSize = cacheMemory / numBlocks;
const int gridRows = numBlocks / gridCols;

int getRandomTwoDigitNumber() 
{
   
    std::srand(static_cast<unsigned int>(std::time(0)));

   
    int randomTwoDigitNumber = rand() % 90 + 10;

    return randomTwoDigitNumber;
}

void cacheBlocksDraw() 
{
    int data = 0;

    for (int row = 0; row < gridRows; row++) {
        for (int col = 0; col < gridCols; col++) {
            Rectangle rect = { col * (blockSize + 10), row * (blockSize + 10), blockSize, blockSize };
            DrawRectangleRec(rect, MAGENTA);

            DrawText(("data: " + to_string(data)).c_str(), col * (blockSize + 10), row * (blockSize + 10) + 20, 10, BLACK);
            data++;
        }
    }
}

void drawCPU(int mainmemorysize) 
{
    Rectangle rect = { 800, 10, static_cast<float>(mainmemorysize), static_cast<float>(mainmemorysize) };
    DrawRectangleRec(rect, RAYWHITE);
    DrawText("CPU", 850, 400, 80, BLACK);

}

vector<int> timestamp;
vector<int> nummemcalls;

void initializeArrays(int size) 
{
    timestamp.resize(size);
    nummemcalls.resize(size,0);
}

void updateArrays() 
{
    for (int i = 0; i < numBlocks; ++i) 
    {
        timestamp[i]++;
    }
}

void mainmemCall(int i)
{
    if (i >= 0 && i < numBlocks)
    {
        nummemcalls[i]++;
        timestamp[i] = 0;

    }

}

bool  mainmemCalluser(int i)
{
    if (i >= 0 && i < numBlocks)
    {
        nummemcalls[i]++;
        timestamp[i] = 0;

        return true;
    }
    else
    {

        return false;
    }
}

void displayCache() 
{
    

    cout << "Current nummemcalls for each block:\n";
    for (int i = 0; i < nummemcalls.size(); i++) {
        cout << "data" << i << ": " << nummemcalls[i] << " memory calls\n";
    }
    cout << "\n";
}
int main()
{
    const int screenWidth = 1900;
    const int screenHeight = 1000;

    cout << "Welcome to the Cache Simulation App!\n\n";
    cout << "This app simulates a CPU cache and memory interaction.\n";
    cout << "You can manually or automatically make memory calls and observe cache hits/misses.\n";
    cout << "The cache is represented visually on the window.\n";
    cout << "Enjoy exploring the simulation!\n\n";
   
    int usermemCall;
    cout << "Give the data you want to call from cache :" << endl;
    cin >> usermemCall;




    InitWindow(screenWidth, screenHeight, "Dynamic Arrays and Graphics Example");

    initializeArrays(numBlocks);



    // MANUAL MAIN MEMORY CALLS, CAN BE AUTOMATED


    mainmemCall(1); mainmemCall(7); mainmemCall(12); mainmemCall(3); mainmemCall(18);
    mainmemCall(9); mainmemCall(5); mainmemCall(14); mainmemCall(2); mainmemCall(11);
    mainmemCall(6); mainmemCall(17); mainmemCall(8); mainmemCall(4); mainmemCall(15);
    mainmemCall(10); mainmemCall(13); mainmemCall(16); mainmemCall(19); mainmemCall(0);
    mainmemCall(5); mainmemCall(12); mainmemCall(3); mainmemCall(7); mainmemCall(9);
    mainmemCall(18); mainmemCall(11); mainmemCall(6); mainmemCall(2); mainmemCall(15);
    mainmemCall(14); mainmemCall(4); mainmemCall(8); mainmemCall(17); mainmemCall(13);
    mainmemCall(10); mainmemCall(16); mainmemCall(1); mainmemCall(19);
    mainmemCall(0); mainmemCall(1); mainmemCall(2); mainmemCall(3); mainmemCall(4);
    mainmemCall(5); mainmemCall(6); mainmemCall(7); mainmemCall(8); mainmemCall(9);
    mainmemCall(10); mainmemCall(11); mainmemCall(12); mainmemCall(13); mainmemCall(14);
    mainmemCall(28); mainmemCall(32); mainmemCall(37); mainmemCall(25); mainmemCall(39);
    mainmemCall(35); mainmemCall(30); mainmemCall(38); mainmemCall(26); mainmemCall(34);
    mainmemCall(29); mainmemCall(36); mainmemCall(31); mainmemCall(27); mainmemCall(40);
    mainmemCall(33); mainmemCall(39); mainmemCall(25); mainmemCall(28); mainmemCall(30);
    mainmemCall(37); mainmemCall(36); mainmemCall(26); mainmemCall(35); mainmemCall(34);
    mainmemCall(32); mainmemCall(38); mainmemCall(33); mainmemCall(31); mainmemCall(27);
    mainmemCall(29); mainmemCall(40);

    displayCache();

    int frameCounter = 0;
    bool searching = false;

    bool didcachehit = mainmemCalluser(usermemCall);

    while (!WindowShouldClose()) 
    {


        BeginDrawing();



        ClearBackground(BLACK);


        cacheBlocksDraw();
        drawCPU(800);




        // simulate a memory call on a specific block 


        if (didcachehit)
        {
            DrawText(("finding data in cache...\ncache hit " + to_string(usermemCall)).c_str(), 850, 600, 40, BLACK);

        }
        else
        {
            DrawText("finding data in cache...\ncache miss", 850, 600, 40, BLACK);
            DrawText(("usermemCall value: " + to_string(usermemCall)).c_str(), 850, 640, 40, BLACK);
        }




        updateArrays();
        // DrawText(("Time " + to_string(elapsed)).c_str(),900,900, 50, WHITE);



        
        int i = 0;
        for (int row = 0; row < gridRows; row++) {

            for (int col = 0; col < gridCols; col++) {

                DrawText(("Timestamp " + to_string(i) + to_string(timestamp[i])).c_str(), col * (blockSize + 10), row * (blockSize + 10) + 40, 10, BLACK);
                DrawText(("NumMemCalls: " + to_string(nummemcalls[i])).c_str(), col * (blockSize + 10), row * (blockSize + 10) + 50, 10, BLACK);
                i++;
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
