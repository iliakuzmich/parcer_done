#include "parcer.h"

using namespace std;

//typedef unsigned int uint;

Parcer::Parcer(){}

// Оценка расходов студента, руб./ месяц на основе "статистических данных"
bool Parcer::initDatabase(QString path) {
    // Инициализация базы данных

    ifstream DatabaseHandler;

    string word;
    string line;

    vector <string> A;

    // ------------------------------------------------ //

    DatabaseHandler.open(path.toStdString() + ("/Caffe-and-cinema.csv"));

    if (DatabaseHandler.is_open()){
        while(getline(DatabaseHandler, line)){
            stringstream lineStream(line);
            while(getline(lineStream,word,',')){

                    A.push_back(string(word));
            }
            caffy.push_back(move(A));
        }
    }
    else{
        return (0);
    }
//    for (auto str : caffy){
//        for (auto w : str){
//            cout << w << " ";
//        }
//        cout << "\n";
//    }
    A.clear();
    DatabaseHandler.close();
    // -------------------------------------------------//

    DatabaseHandler.open(path.toStdString() + "/Costs.csv");
    if (DatabaseHandler.is_open()){
        while(getline(DatabaseHandler, line)){
            stringstream lineStream(line);
            while(getline(lineStream,word,',')){
                    A.push_back(string(word));
            }
            costs.push_back(move(A));
        }

    }
    else{
        return (0);
    }
//    for (auto str : costs){
//        for (auto w : str){
//            cout << w << " ";
//        }
//        cout << "\n";
//    }
    A.clear();
    DatabaseHandler.close();

    DatabaseHandler.open(path.toStdString() + "/Institute.csv");
    if (DatabaseHandler.is_open()){
        while(getline(DatabaseHandler, line)){
            stringstream lineStream(line);
            while(getline(lineStream,word,',')){
                    A.push_back(string(word));
            }
            inst.push_back(move(A));
        }

    }
    else{
        return (0);
    }
//    for (auto str : inst){
//        for (auto w : str){
//            cout << w << " ";
//        }
//        cout << "\n";
//    }
    A.clear();
    DatabaseHandler.close();

    DatabaseHandler.open(path.toStdString() + "/Transport.csv");
    if (DatabaseHandler.is_open()){
        while(getline(DatabaseHandler, line)){
            stringstream lineStream(line);
            while(getline(lineStream,word,',')){
                    A.push_back(string(word));
            }
            transport.push_back(move(A));
        }

    }
    else{
        return (0);
    }
//    for (auto str : transport){
//        for (auto w : str){
//            cout << w << " ";
//        }
//        cout << "\n";
//    }
    A.clear();
    DatabaseHandler.close();
    return 1;
}

int Parcer::getOtherMontlyCosts(const std::string& city, int age) {
    /* Получаем из базы данных средние по региону затраты в данном месяце
     для людей данного возраста
    (по остальным статьям кроме еды, транспорта и развлечений) */
    for (size_t i = 1; i < costs.size(); i++){
        if ((stoi(costs[i][1]) == age) && (costs[i][0] == city)){
            return (stoi(costs[i][3]));
        }
    }
    return 0;
}

int Parcer::getHomeFoodCost(const std::string& city, int age) {
    // Получаем из базы данных средние по региону затраты на еду
    for (size_t i = 1; i < costs.size(); i++){
        if ((stoi(costs[i][1]) == age) && (costs[i][0] == city)){
            return (stoi(costs[i][3]));
        }
    }
    return 0;
}

int Parcer::getCinemaCost(const std::string& city, const std::string& cinema) {
    // Получаем из базы данных стоимость билета на вечерний сеанс в данном кинотетре
    for (size_t i = 1; i < caffy.size(); i++){
        if ((caffy[i][0] == city) && (costs[i][4] == cinema)){
            return (stoi(caffy[i][5]));
        }
    }
    return 0;
}

int Parcer::getCoffeeCost(const std::string& city, const std::string& coffee) {
    // Получаем из базы данных средний чек в данном баре
    for (size_t i = 1; i < caffy.size(); i++){
        if ((caffy[i][0] == city) && (costs[i][2] == coffee)){
            return (stoi(caffy[i][3]));
        }
    }
    return 0;
}

int Parcer::getWeekandCost(const std::string& city, const std::string& cinema,
                    const std::string& coffee, int age) {
    /* По выходным дням расходы складываются из стоимости:
     - похода в кино (пешком)
     - похода  в кафе (пешком)
     - завтрака и обеда дома */

    return static_cast<uint>(0.66 * 0.03 * getHomeFoodCost(city, age) +
        getCinemaCost(city, cinema) + getCoffeeCost(city, coffee) + 0.5);
}

int Parcer::getInstituteDinnerCost(const std::string& city, const std::string& institute) {
    // Получаем из базы данных среднюю стоимость обеда в столовой данного института
    for (size_t i = 0; i < inst.size(); i++){
        if (inst[i][0] == city && inst[i][1] == institute){
            return(stoi(inst[i][2]));
        }
    }
    return 0;
}

int Parcer::getTransportCost(const std::string& city, const std::string& homeAddress,
                      const std::string& institute) {
    // Получаем из базы данных стоимость кратчайшей дороги до инстиутта
    for (size_t i = 0; i < transport.size(); i++){
        if (transport[i][0] == city && transport[i][1] == homeAddress && transport[i][2] == institute){
            return(stoi(transport[i][3]));
        }
    }
    return 0;
}

int Parcer::getWorkdayCost(const std::string& city, const std::string& homeAddress,
                    const std::string& institute, int age) {
   /* По рабочим дням расходы складываются из стоимости:
    - дороги до института и обратно
    - обеда в институтской столовой
    - завтрака и обеда дома */

    return static_cast<uint>(2 * getTransportCost(city, homeAddress, institute) +
        getInstituteDinnerCost(city, institute) + 0.66 * 0.03 * getHomeFoodCost(city, age) + 0.5);
}

int Parcer::getCosts(const std::string& city, const std::string& homeAddress,
              const std::string& institute, const std::string& cinema,
              const std::string& coffee, int age) {

    return 22 * getWorkdayCost(city, homeAddress, institute, age) +
           9 * getWeekandCost(city, cinema, coffee, age) +
           getOtherMontlyCosts(city, age);
}

bool Parcer::isCity(const string& city) {
    int k = 0;
    for (size_t i = 0; i < caffy.size(); i += 1){
        if (caffy[i][0] == city){
            k++;
        }
    }
    for (size_t i = 0; i < costs.size(); i += 1){
        if (costs[i][0] == city){
            k++;
        }
    }
    for (size_t i = 0; i < inst.size(); i += 1){
        if (inst[i][0] == city){
            k++;
        }
    }
    for (size_t i = 0; i < transport.size(); i += 1){
        if (transport[i][0] == city){
            k++;
        }
    }
    if (k >= 1){
        return 1;
    }
    return 0;
}


bool Parcer::is_Caffy(const string& city, const string& caf){
    for (size_t i = 0; i < caffy.size(); i += 1){
            if (caffy[i][0] == city &&  caffy[i][2] == caf){
                return (1);
            }
        }
        return (0);
}
bool Parcer::is_Cinema(const string& city, const string& cinema){
    for (size_t i = 0; i < caffy.size(); i += 1){
            if (caffy[i][0] == city &&  caffy[i][4] == cinema){
                return (1);
            }
        }
        return (0);
}

bool Parcer::isAddress(const string& city, const string& address) {
    for (size_t i = 0; i < transport.size(); i += 1){
        if (transport[i][0] == city &&  transport[i][1] == address){
            return (1);
        }
    }
    return (0);

}

bool Parcer::is_Inst(const string& city, const string& instit){
    for (size_t i = 0; i < inst.size(); i += 1){
            if (inst[i][0] == city &&  inst[i][2] == instit){
                return (1);
            }
        }
        return (0);
}

bool Parcer::is_Age(int age){
    for (size_t i = 0; i < costs.size(); i += 1){
            if (stoi(costs[i][1]) == age){
                return (1);
            }
        }
        return (0);
}


