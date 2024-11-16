#include "batterypack.h"
#include <iostream>

using namespace std;

void drawScene(BatteryPack* pack) 
{
    Scene3D scene;
    // LIGHTS
    scene.addPointLight(-200, 200, 0, 200, 200, 200, 1.0);
    scene.addPointLight(200, 200, 0, 200, 200, 200, 1.0);
    scene.addPointLight(0, 0, -200, 200, 200, 200, 1.0);
    scene.addPointLight(0, 0, 200, 200, 200, 200, 1.0);
    
    // CAMERA
    scene.addCamera(0, 2, 0, 0);
    scene.addCamera(0, 2, -40, 180);

    // ACTION
    // Add a large gray sbox for the ground
    scene.addBox(0, -25.2, 0, 1000, 50, 1000, 255, 200, 200, 1, 0);

    //Add a p pack
    pack->draw(scene, 0, 1, -10);

    scene.saveScene("battery.html", "Your Battery Pack");
}


int main(int argc, char** argv) {

    if(argc < 3) { // Check to make sure all arguements needed are made

        cout << "Usage: ./driver <# batteries in series (even, greater than 0)> <# batteries in parallel (greater than 0)>\n";

    } else {

        int s = atoi(argv[1]); // Converts line 1 to int for # in series
        int p = atoi(argv[2]); // Converts line 2 to int for # in parallel

        if(s <= 0 || p <= 0 || s%2 != 0){ // Check if arguments are within parameters of battery

            cout << "# of batteries in series and parallel must be greater than 0\n";
            cout << "# of batteries in series must also be an even number\n";

        } else {
            Battery* cell = new Battery(); // Creates default P42A battery
            cell->print(); // print out battery specs
            cout << "\n";

            BatteryPack* pack = new BatteryPack(s, p, cell); // Creates battery pack given command arguements for series and parallel
            pack->printSpecs(); // print out pack specs
            cout << "\n";

            pack->charge(); // changes batterypack to charge state
            pack->printState(); // print out new voltage of batterypack
            cout << "\n";

            pack->discharge(); // changes batterypack to discharge state
            pack->printState(); // print out new voltage of batterypack

            drawScene(pack); // 3D model the batterypack using 3DScene
        }
    }
    return 0;
}