#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define Wwidth 1000
#define Wheight 700
#define nobar 50
#define fontsize 55

//this
//typedef
typedef struct Bar{
    int height;
    Color color;
}Bar;

//variables
Bar bar[nobar];
char AlgorithmNames[][10] = {"NONE","BUBBLE", "SELECTION", "INSERTION", "QUICKSORT"};

//functions
void Barsetup(){
    for(int i = 0; i<nobar; i++){
        bar[i].height = GetRandomValue(10,Wheight-50);
        bar[i].color = WHITE;
    }
}

void DrawBars(){
    for(int i = 0; i<nobar; i++){
        DrawRectangle(i*(Wwidth/nobar),
        Wheight - bar[i].height,
        Wwidth/nobar - 2,
        bar[i].height,
        bar[i].color
        );
    }
}
void SigmaGreenBars(){
  for(int i = 0; i<nobar; i++){
      bar[i].color = GREEN;
  }  
}

//the actual algorithms
void BubbleSort(){
    static int i = 0, j = 0;
    if(i<nobar){
        if(j<nobar-i-1){
            bar[j].color = RED;
            bar[j+1].color = RED;
            DrawBars();
            if(bar[j].height>bar[j+1].height){
                int th = bar[j].height;
                bar[j].height = bar[j+1].height;
                bar[j+1].height = th;
            }
            bar[j].color = WHITE;
            bar[j+1].color = WHITE;
            j++;
            DrawBars();
        }else{
            j = 0;
            i++;
        }
    }else{
        SigmaGreenBars();
        DrawBars();
    }
}

void SelectionSort(){
   static int i = 0, j = 0, mindex = 0;
   if(i<nobar-1){
       if(j<nobar){
        bar[mindex].color = BLUE;
        bar[j].color = RED;
        DrawBars();
       
        if(bar[j].height<bar[mindex].height){
           bar[mindex].color = WHITE;
           mindex = j;
        }
        bar[j].color = WHITE;
        j++;
        DrawBars();
       }else{
        int temp = bar[i].height;
        bar[i].height = bar[mindex].height;
        bar[mindex].height = temp;
        bar[mindex].color = WHITE;
        bar[i].color = WHITE;
       
       i++;
       j = i+1;
       mindex = i;
       }
   }else{
       SigmaGreenBars();
       DrawBars();
   }
}

void InsertionSort(){
    static int i = 1, j = 0, k = 0;
    static bool placing = false;
    
    if(i<nobar){
        if(!placing){
            k = bar[i].height;
            j = i-1;
            placing = true;
        }
        if(j>=0 && bar[j].height > k){
            bar[j+1].height = bar[j].height;
            bar[j].color = RED;
            bar[j+1].color = BLUE;
            DrawBars();
            
            bar[j].color = WHITE;   
            bar[j+1].color = WHITE;
            j--;
        }else{
            bar[j+1].height = k;
            i++;
            placing = false;
        }
    }
    else{
        SigmaGreenBars();
        DrawBars();
    }
}

/**void QUICKSORT(){
    static int stack[nobar];
    static int top = -1;
    static bool intialized = false;
    
    if(!initialized){
        stack[++top]
    }
    
}**/

//this
typedef enum {None, Bubble, Selection, Insertion, Quick, Exit} SAlgorithm;
SAlgorithm currentsort = None;

//Main menu (basically)
void BarUpdateAlgorithm(){
    if(IsKeyPressed(KEY_ONE)){
        currentsort = Bubble;
    }else if(IsKeyPressed(KEY_TWO)){
        currentsort = Selection;
    }else if(IsKeyPressed(KEY_THREE)){
        currentsort = Insertion;
    }else if(IsKeyPressed(KEY_FOUR)){
        currentsort = Quick;
    }else if(IsKeyPressed(KEY_ESCAPE)){
        currentsort = Exit;
    }
    if(currentsort != None){
        DrawBars();
    }else{
        DrawText("ALGORITHM VISUALIZER", Wwidth/15, Wheight/6,fontsize,RED);
        DrawText("1. BUBBLE SORT",Wwidth/15,Wheight/5 + 100,fontsize/2,WHITE);
        DrawText("2. SELECTION SORT",Wwidth/15,Wheight/5 + 150,fontsize/2,WHITE);
        DrawText("3. INSERTION SORT",Wwidth/15,Wheight/5 + 200,fontsize/2,WHITE);
        DrawText("4. QUICK SORT",Wwidth/15,Wheight/5 + 250,fontsize/2,WHITE);
        DrawText("ESC TO EXIT",(Wwidth/2)-fontsize*2,Wheight/5 + 400,fontsize/2,DARKGRAY);
    }
}

//main
int main(){
    InitWindow(Wwidth,Wheight,"Algorithm Visualizer");
    SetTargetFPS(60);
    
    SetRandomSeed(time(NULL)); //this (seed random number generator)
    Barsetup();
    while(!WindowShouldClose()){
        BarUpdateAlgorithm();
        if(currentsort == Bubble) {
            BubbleSort();
        }else if(currentsort == Selection){
            SelectionSort();
        }else if(currentsort == Insertion){
            InsertionSort();
        }else if(currentsort == Quick){
            //QuickSort();
        }else if(currentsort == Exit){
            break;
        }
        if(IsKeyPressed(KEY_BACKSPACE)){
            SetRandomSeed(time(NULL)); 
            currentsort = None;
            Barsetup();
            BarUpdateAlgorithm();
        }
        if(currentsort != None){
            DrawText(AlgorithmNames[currentsort],10,10,20,WHITE);
        }
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
  
    }
    CloseWindow();
    return 0;
}   
