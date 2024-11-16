#ifndef BATTERYPACK_H
#define BATTERYPACK_H

#include <stdio.h>
#include <stdlib.h>
#include "Scene3D.h"

class Battery
{
    private:
        string name;
        int capacity;
        float voltage;
        float nominalVoltage;
        float chargeVoltage;
        float dischargeVoltage;
        float chargeCurrent;
        float dischargeCurrent;

    public:
        Battery();

        /**
         * @brief Constructor of Battery
         * 
         * @param capacity - Amount of energy battery can hold (mAh)
         * @param nominalVoltage - Voltage at 0% charge (V)
         * @param chargeVoltage - Voltage while charging (V)
         * @param dischrageVoltage - Voltage while discharging at max speed (V)
         * @param chargeCurrent - Rate at which battery can charge (A)
         * @param chargeTime - How long to charge from 0%-100% (hr)
         * @param dischargeCurrent - Rate at which battery can discharge (A)
        */
        Battery(string name, int capacity, float nominalVoltage, 
                float chargeVoltage, float dischargeVoltage, 
                float chargeCurrent, float dischargeCurrent);

        //getters
        string getName();
        int getCapacity();
        float getVoltage();
        float getNominalVoltage();
        float getChargeVoltage();
        float getDischargeVoltage();
        float getChargeCurrent();
        float getDischargeCurrent();

        //setters
        void setVoltage(float voltage);

        /**
         * @brief Charges the cell to 100%
         * 
        */
       void charge();

       /**
         * @brief Discharges the cell to 0%
         * 
        */
       void discharge();

        /**
         * @brief Prints out all specs of battery cell
         * 
        */
        void print();

        /**
         * @brief Generates a 3D cell in a scene
         * 
        */
        void draw(Scene3D& scene, double x, double y, double z, 
                bool flip);

};

class BatteryPack
{
    private:
        int s;
        int p;
        Battery* cell;
        int capacity;
        float voltage;
        float nominalVoltage;
        float chargeVoltage;
        float dischargeVoltage;
        float chargeCurrent;
        float dischargeCurrent;

    public:
        /**
         * @brief Default constructor of BatteryPack (P42A 10s2p)
         * 
        */
        BatteryPack();

        /**
         * @brief Constructor of Battery 
         * 
         * @param s - The number of p-packs in series
         * @param p - The number of cells in parallel
         * @param cell - The Battery used to build the BatteryPack
        */
        BatteryPack(int s, int p, Battery* cell);

        //getters
        int getS();
        int getP();
        Battery* getCell();

        //setters
        void setS(int s);
        void setP(int p);
        void setCell(Battery* cell);

        /**
         * @brief Set to charge status of BatteryPack
         * 
        */
        void charge();

        /**
         * @brief set to discharge status of BatteryPack
        */
        void discharge();

        //output
        /**
         * @brief Prints out all specs of battery pack
         * 
        */
        void printSpecs();

        /**
         * @brief Prints out current state of battery pack
         * 
        */
        void printState();

       /**
         * @brief Generates a 3D battery in a scene
         * 
        */
        void draw(Scene3D& scene, double x, double y, double z);

        /**
         * @brief Helper method for BatteryPack's draw method
         * Draws a p-pack
         * 
        */
        void drawPPack(Scene3D& scene, BatteryPack* pack, double x, double y, double z, 
                bool flip);



};
#endif