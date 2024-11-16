#include "batterypack.h"

using namespace std;

BatteryPack::BatteryPack() 
{
    s = 10;
    p = 2;
    cell = new Battery(); //default P42A cell

    this->capacity = cell->getCapacity() * p;
    this->dischargeCurrent = cell->getDischargeCurrent() * p;
    this->chargeCurrent = cell->getChargeCurrent() * p;

    this->chargeVoltage = cell->getChargeVoltage() * s;
    this->nominalVoltage = cell->getNominalVoltage() * s;
    this->dischargeVoltage = cell->getDischargeVoltage() * s;
    this->voltage = nominalVoltage;
}

BatteryPack::BatteryPack(int s, int p, Battery* cell) 
{
    this->s = s;
    this->p = p;
    this->cell = cell;
    
    this->capacity = cell->getCapacity() * p;
    this->dischargeCurrent = cell->getDischargeCurrent() * p;
    this->chargeCurrent = cell->getChargeCurrent() * p;

    this->chargeVoltage = cell->getChargeVoltage() * s;
    this->nominalVoltage = cell->getNominalVoltage() * s;
    this->dischargeVoltage = cell->getDischargeVoltage() * s;
    this->voltage = this->nominalVoltage;
}

int BatteryPack::getS()
{
    return s;
}

int BatteryPack::getP()
{
    return p;
}

Battery* BatteryPack::getCell()
{
    return cell;
}

void BatteryPack::charge()
{
    cout << "CHARGED\n";
    this->voltage = chargeVoltage;
}

void BatteryPack::discharge()
{
    cout << "DISCHARGED\n";
    this->voltage = dischargeVoltage;
}

void BatteryPack::printSpecs()
{
    cout << "Battery cell: " << cell->getName() << "\n";
    cout << "Capacity: " << capacity << " (" << capacity*voltage/1000 << " Wh)\n";
    cout << "Nominal Voltage: " << nominalVoltage << " V\n";
    cout << "Charge current: " << chargeCurrent << " A\n";
    cout << "Discharge current: " << dischargeCurrent << " A\n";
}

void BatteryPack::printState()
{
    cout << "Battery cell: " << cell->getName() << "\n";
    cout << "Current Voltage: " << voltage << " V\n";
}

void BatteryPack::draw(Scene3D& scene, double x, double y, double z)
{
    bool flip = false;
    bool inside = (s/2)%2 == 0;
    for (int i = 0; i < s/2; i++)
    {
        //logic for drawing the wire connecting the 2 rows of p-packs
        if (i+1 >= s/2)
        {
            scene.addCylinder((x+1)-(2*p*i)-(i*0.1)-p, y+1.2, z+3.6, 0.1, 1, 150, 0, 0, 1, 1, 90, 0, 0, 1, 1, 1);
        } 
        //draw 2 rows of p-packs to halve the length of the battery
        drawPPack(scene, this, x-(i*2*p)-(0.1*i), 1, -10, flip);
        drawPPack(scene, this, x-(i*2*p)-(0.1*i), 1, -2.8, flip);
        //draw wires
        if (inside)
        {
            if (i == 0)
            {
                scene.addCylinder((x+1)-(i*2*p)-(0.1*i), y+1.2, z+3, 0.1, (p*2)+(0.1*i), 0, 0, 0, 1, 1, 90, 90, 0, 1, 1, 1);
            }
            else
            {
                scene.addCylinder((x+1)-(i*2*p)-(0.1*i), y+1.2, z+3, 0.1, (p*2)+(0.1*i), 150, 0, 0, 1, 1, 90, 90, 0, 1, 1, 1);
            }
            scene.addCylinder((x+1)-(i*2*p)-(0.1*i), y+1.2, z+4.1, 0.1, (p*2)+(0.1*i), 150, 0, 0, 1, 1, 90, 90, 0, 1, 1, 1);
        }
        else
        {
            if (i == 0)
            {
                scene.addCylinder((x+1)-(i*2*p)-(0.1*i), y+1.2, z+7.1, 0.1, 7.2, 0, 0, 0, 1, 1, 90, 150, 0, 1, 1, 1);
                scene.addCylinder((x+1)-(i*2*p)-(0.1*i), y+1.2, z, 0.1, 7.2, 150, 0, 0, 1, 1, 90, 30, 0, 1, 1, 1);
            }
            else
            {
                scene.addCylinder((x+1)-(i*2*p)-(0.1*i), y+1.2, z+10.1, 0.1, (p*2)+(0.1*i), 150, 0, 0, 1, 1, 90, 90, 0, 1, 1, 1);
                scene.addCylinder((x+1)-(i*2*p)-(0.1*i), y+1.2, z-3, 0.1, (p*2)+(0.1*i), 150, 0, 0, 1, 1, 90, 90, 0, 1, 1, 1);
            }
        }
        //logic to draw wires on the correct sides of the p-packs
        flip = !flip;
        inside = !inside;
    }
    //draw insulating separator between 2 rows of p-packs
    scene.addBox(x-((s*p)/2)+1, y+0.1, z+3.6, p*s, 2.2, 0.1, 10, 10, 10, 1, 1);
    //draw XT90 connector
    scene.addBox(x+p+1.8, y+1.2, z+3.6, 2, 0.5, 2, 220, 220, 0, 1, 1);
    scene.addBox(x+p+1.6, y+1.45, z+3, 0.1, 0.08, 0.5, 0, 0, 0, 1, 1);
    scene.addBox(x+p+1.6, y+1.45, z+3, 0.5, 0.08, 0.1, 0, 0, 0, 1, 1);
    scene.addBox(x+p+1.6, y+1.45, z+4.2, 0.1, 0.08, 0.5, 0, 0, 0, 1, 1);
    
}

void BatteryPack::drawPPack(Scene3D& scene, BatteryPack* pack, double x, double y, double z, bool flip)
{
    int p = pack->getP();
    for (int i = 0; i < p; i++)
    {
        pack->getCell()->draw(scene, x-(i*2), y, z, flip);
    }
    //x, y, z are relative to the first cell
    //add tin strips on terminals
    //the long parts
    scene.addBox(x-p+1, y, z-3.5, (p*2)-0.7, 1.3, 0.1, 240, 240, 240, 1, 1);
    scene.addBox(x-p+1, y, z+3.5, (p*2)-0.7, 1.3, 0.1, 240, 240, 240, 1, 1);
    //the part that contacts the wire
    scene.addBox(x-p+1, y+1.05, z-3.05, (p*2)-2.5, 0.1, 1, 240, 240, 240, 1, 1);
    scene.addBox(x-p+1, y+1.05, z+3.05, (p*2)-2.5, 0.1, 1, 240, 240, 240, 1, 1);
    //the part that connects the long part and the part that contacts the wire
    scene.addBox(x-p+1, y+0.7, z+3.5, 1, 0.7, 0.1, 240, 240, 240, 1, 1);
    scene.addBox(x-p+1, y+0.7, z-3.5, 1, 0.7, 0.1, 240, 240, 240, 1, 1);
    
}

Battery::Battery()
{
    name = "P42A";
    capacity = 4200;
    nominalVoltage = 3.6;
    voltage = nominalVoltage;
    chargeVoltage = 4.2;
    dischargeVoltage = 2.5;
    chargeCurrent = 4.2;
    dischargeCurrent = 45;
}


Battery::Battery(string name, int capacity, float nominalVoltage, 
        float chargeVoltage, float dischargeVoltage, 
        float chargeCurrent, float dischargeCurrent)
{
    this->name = name;
    this->capacity = capacity;
    this->nominalVoltage = nominalVoltage;
    this->voltage = nominalVoltage;
    this->chargeVoltage = chargeVoltage;
    this->dischargeVoltage = dischargeVoltage;
    this->chargeCurrent = chargeCurrent;
    this->dischargeCurrent = dischargeCurrent;
}

string Battery::getName()
{
    return this->name;
}

int Battery::getCapacity()
{
    return this->capacity;
}

float Battery::getVoltage()
{
    return this->voltage;
}

float Battery::getNominalVoltage()
{
    return this->nominalVoltage;
}

float Battery::getChargeVoltage()
{
    return this->chargeVoltage;
}

float Battery::getDischargeVoltage()
{
    return this->dischargeVoltage;
}

float Battery::getChargeCurrent()
{
    return this->chargeCurrent;
}

float Battery::getDischargeCurrent()
{
    return this->dischargeCurrent;
}

void Battery::print()
{
    cout << "Name: " << name << "\n";
    cout << "Capacity: " << capacity << " mAh\n";
    cout << "Voltage: " << voltage << " V\n";
    cout << "Charge current: " << chargeCurrent << " A\n";
    cout << "Discharge current: " << dischargeCurrent << " A\n";
}

void Battery::draw(Scene3D& scene, double x, double y, double z, bool flip)
{
    //battery casing
    scene.addCylinder(x, y, z, 1, 7, 150, 150, 150, 1, 1, 90, 0, 0, 1, 1, 1);
    //positive terminal
    scene.addCylinder(x, y, z+3.5, 0.5, 0.01, 200, 200, 200, 1, 1, 90, 0, 0, 1, 1, 1);
    //negative terminal
    scene.addCylinder(x, y, z-3.5, 0.5, 0.01, 200, 200, 200, 1, 1, 90, 0, 0, 1, 1, 1);
    if (flip)
    {
        //positive symbol
        scene.addBox(x, y+0.9, z+3, 0.5, 0.2, 0.1, 0, 0, 0, 1, 1);
        scene.addBox(x, y+0.9, z+3, 0.1, 0.2, 0.5, 0, 0, 0, 1, 1);
        //negative symbol
        scene.addBox(x, y+0.9, z-3, 0.5, 0.2, 0.1, 0, 0, 0, 1, 1);
    }
    else
    {
        //positive symbol
        scene.addBox(x, y+0.9, z-3, 0.5, 0.2, 0.1, 0, 0, 0, 1, 1);
        scene.addBox(x, y+0.9, z-3, 0.1, 0.2, 0.5, 0, 0, 0, 1, 1);
        //negative symbol
        scene.addBox(x, y+0.9, z+3, 0.5, 0.2, 0.1, 0, 0, 0, 1, 1);
    }
    
}