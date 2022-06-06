#pragma once

#include <QString>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Parcer {
public:
    Parcer();
    bool initDatabase(QString path);
    int getOtherMontlyCosts(const std::string& city, int age);
    int getHomeFoodCost(const std::string& city, int age);
    int getCinemaCost(const std::string& city, const std::string& cinema);
    int getCoffeeCost(const std::string& city, const std::string& coffee);
    int getWeekandCost(const std::string& city, const std::string& cinema, const std::string& coffee, int age);
    int getInstituteDinnerCost(const std::string& city, const std::string& institute);
    int getTransportCost(const std::string& city, const std::string& homeAddress, const std::string& institute);
    int getWorkdayCost(const std::string& city, const std::string& homeAddress, const std::string& institute, int age);
    int getCosts(const std::string& city, const std::string& homeAddress, const std::string& institute, const std::string& cinema, const std::string& coffee, int age);
    bool isCity(const string& city);
    bool is_Caffy(const string& city, const string& caffy);
    bool is_Cinema(const string& city, const string& cinema);
    bool isAddress(const string& city, const string& address);
    bool is_Inst(const string& city, const string& instit);
    void setData(const vector<vector<string>>& newData);
    bool is_Age(int age);

    std::vector < vector < std::string > >  caffy;
    std::vector < vector < std::string > >  costs;
    std::vector < vector < std::string > >  inst;
    std::vector < vector < std::string > >  transport;
};
