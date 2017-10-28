/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Thiago Soares Marques
 *
 * Created on 21 de Outubro de 2017, 15:06
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <bits/stdc++.h>
#include <unistd.h>
#include <csignal>
#include <ctime>
#include <cmath>
#include <list>
#include <syscall.h>
#include <errno.h>
#include <linux/random.h>

using namespace std;

bool debug = false;
using namespace std;

int randInt(int begin, int end) {
    unsigned char buff[1];
    int n = syscall(SYS_getrandom, buff, 1, GRND_NONBLOCK);
    if(n == -1)
    {
      cout << "Reading random bytes failed: errno " << errno << endl;
    }
    return buff[0] % (end - begin + 1) + begin;
}

double randDouble(double begin, double end) {
    int b = (int) (begin * 100.0);
    int e = (int) (end * 100.0);
    int r1 = randInt(b, e);
    double r2 = r1 * 1.0;
    r2 = r2 / 100.0;
    return r2;
}

int main(int argc, char* argv[]) {
    map<string, char*> parameters;

    parameters["param_name"];
    parameters["debug_mode"] = (char*) "off";
    parameters["size"];
    parameters["car_capacity"];
    parameters["prefix_name"];
    parameters["file_extension"];
    parameters["number_instances"];
    parameters["distance_range"];
    parameters["time_range"];
    parameters["passenger_range"];
    parameters["bonus_range"];
    parameters["delay_range"];
    parameters["fair_mode"];
    parameters["percentage_fair_mode"];
    parameters["percentage_veretx_bonus"];
    parameters["graph_type"];
    
    if (argc < 3) {
        cout << "To few arguments." << endl;
        return EXIT_SUCCESS;
    }

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]).compare("-p") == 0) {
            parameters["param_name"] = argv[i + 1];
            i++;
        } else if (string(argv[i]).compare("-v") == 0) {
            parameters["degub_mode"] = (char*) "on";
            debug = true;
        }
    }

    ifstream parameters_file(parameters["param_name"]);

    if (!parameters_file.is_open()) {
        cout << "Unable to open parameters file" << endl;
        return EXIT_SUCCESS;
    }
    
    string readed = "";
	parameters_file >> readed;
    while(!parameters_file.eof()) {
        if(string("SIZE").compare(readed) == 0) {
            parameters_file >> readed;
            parameters_file >> readed;
            parameters["size"] =  (char*) readed.data();
            cout << "size = " << parameters["size"] << endl;
        } else if(string("CAR_CAPACITY").compare(readed) == 0) {
            parameters_file >> readed;
            parameters_file >> readed;
            parameters["car_capacity"] =  (char*) readed.data();
            cout << "car_capacity = " << parameters["car_capacity"] << endl;
        } else if(string("PREFIX_NAME").compare(readed) == 0) {
            parameters_file >> readed;
            parameters_file >> readed;
            parameters["prefix_name"] =  (char*) readed.data();
            cout << "prefix_name = " << parameters["prefix_name"] << endl;
        } else if(string("FILE_EXTENSION").compare(readed) == 0) {
            parameters_file >> readed;
            parameters_file >> readed;
            parameters["file_extension"] =  (char*) readed.data();
            cout << "file_extension = " << parameters["file_extension"] << endl;
        } else if(string("NUMBER_INSTANCES").compare(readed) == 0) {
            parameters_file >> readed;
            parameters_file >> readed;
            parameters["number_instances"] =  (char*) readed.data();
            cout << "number_instances = " << parameters["number_instances"] << endl;
        } else if(string("DISTANCE_RANGE").compare(readed) == 0) {
            parameters_file >> readed;
            parameters_file >> readed;
            string temp = readed;
            parameters_file >> readed;
            temp = temp + " " + readed;
            parameters["distance_range"] =  (char*) (temp).data();
            cout << "distance_range = " << parameters["distance_range"] << endl;
        } else if(string("TIME_RANGE").compare(readed) == 0) {
            parameters_file >> readed;
            parameters_file >> readed;
            string temp = readed;
            parameters_file >> readed;
            temp = temp + " " + readed;
            parameters["time_range"] =  (char*) (temp).data();
            cout << "time_range = " << parameters["time_range"] << endl;
        } else if(string("PASSENGER_RANGE").compare(readed) == 0) {
            parameters_file >> readed;
            parameters_file >> readed;
            string temp = readed;
            parameters_file >> readed;
            temp = temp + " " + readed;
            parameters["passenger_range"] =  (char*) (temp).data();
            cout << "passenger_range = " << parameters["passenger_range"] << endl;
        } else if(string("BONUS_RANGE").compare(readed) == 0) {
            parameters_file >> readed;
            parameters_file >> readed;
            string temp = readed;
            parameters_file >> readed;
            temp = temp + " " + readed;
            parameters["bonus_range"] =  (char*) (temp).data();
            cout << "bonus_range = " << parameters["bonus_range"] << endl;
        } else if(string("DELAY_RANGE").compare(readed) == 0) {
            parameters_file >> readed;
            parameters_file >> readed;
            string temp = readed;
            parameters_file >> readed;
            temp = temp + " " + readed;
            parameters["delay_range"] =  (char*) (temp).data();
            cout << "delay_range = " << parameters["delay_range"] << endl;
        } else if(string("FAIR_MODE").compare(readed) == 0) {
            parameters_file >> readed;
            parameters_file >> readed;
            parameters["fair_mode"] =  (char*) readed.data();
            cout << "fair_mode = " << parameters["fair_mode"] << endl;
        } else if(string("PERCENTAGE_FAIR_MODE").compare(readed) == 0) {
            parameters_file >> readed;
            parameters_file >> readed;
            string temp = readed;
            parameters_file >> readed;
            temp = temp + " " + readed;
            parameters["percentage_fair_mode"] =  (char*) (temp).data();
            cout << "percentage_fair_mode = " << parameters["percentage_fair_mode"] << endl;
        } else if(string("PERCENTAGE_VERETX_BONUS").compare(readed) == 0) {
            parameters_file >> readed;
            parameters_file >> readed;
            string temp = readed;
            parameters_file >> readed;
            temp = temp + " " + readed;
            parameters["percentage_veretx_bonus"] =  (char*) (temp).data();
            cout << "percentage_veretx_bonus = " << parameters["percentage_veretx_bonus"] << endl;
        } else if(string("GRAPH_TYPE").compare(readed) == 0) {
            parameters_file >> readed;
            parameters_file >> readed;
            parameters["graph_type"] =  (char*) readed.data();
            cout << "graph_type = " << parameters["graph_type"] << endl;
        } else {
            cout << "Parameter " << readed << " not recognized." << endl;
        }
        parameters_file >> readed;
    }
    
    return EXIT_SUCCESS;
}

