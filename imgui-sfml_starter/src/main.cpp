#include "Sandbox.h"

int main() {
 
    Sandbox sandbox;

    while (sandbox.IsRunning()) 
    {           
        sandbox.Update();    
    }


    
}