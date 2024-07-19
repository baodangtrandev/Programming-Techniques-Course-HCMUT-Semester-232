#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <climits>
#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;



////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Forward declaration
class MovingObject;
class Position;
class Configuration;
class Map;

class Criminal;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;

class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;
class Character;

class TestStudyInPink;

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C=0, S, W, SW };

class MapElement {
protected:
    ElementType type;
public:
    MapElement(){};
    MapElement(ElementType in_type);
    virtual ~MapElement();
    virtual ElementType getType() const;
};

class Path : public MapElement {
    public:
        Path();
};

class Wall : public MapElement {
    public:
        Wall();
};

class FakeWall : public MapElement {
    private:
        int req_exp;
    public:
        FakeWall(int req_exp);
        int getReqExp() const; 
};

class Map {
private:
    int num_rows, num_cols;
    MapElement** map;

public:
    Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls);

    ~Map();

    // Additional member functions can be defined here

     bool isValid ( const Position & pos , MovingObject * mv_obj ) const ;
};

class Position {
private:
    int r, c;
public:
    static const Position npos;

    Position(int r=0, int c=0);

    Position(const string & str_pos);

    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);

    string str() const;

    bool isEqual(int in_r, int in_c) const;

    // Overload the != operator to compare two Position objects
    bool operator!=(const Position& other) const {
        // Compare the row and column of two Position objects
        return r != other.r || c != other.c;
    }
     friend istream &operator>>(istream &input, Position &pos) {
        char c;
        input >> c >> pos.r >> c >> pos.c >> c;
        return input;
    }

    // Optionally, you might want to overload the << operator for Position as well
    friend ostream &operator<<(ostream &output, const Position &pos) {
        output << "(" << pos.r << "," << pos.c << ")";
        return output;
    }
};

class MovingObject {
protected:
    int index;
    Position pos;
    Map * map;
    string name;

public:
    MovingObject(int index, const Position pos, Map * map, const string & name);
    MovingObject();
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition();
    virtual void move() = 0;
    virtual string str() = 0;
    string getName(){
        return name;
    
    }
};

class Character: public MovingObject {
    protected:
        int hp;
        int exp;
    public:
    Character(int index,const Position& init_pos,Map* map, string name): MovingObject(index,init_pos,map,name) {};
    int getHp();
    int getExp();
    void setHp(int hp);
    void setExp(int exp);
        // virtual void displayInfo() = 0;
        // virtual bool isActive() = 0;
};

class Sherlock : public Character {
private:
    // TODO
    string moving_rule;
    
public:
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    string str() override;
    Position getNextPosition() override;
    void move() override;
    
};

class Watson :public Character {
private:
    // TODO
    string moving_rule;
public:
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    string str() override;
    Position getNextPosition() override;
    void move() override;
    int getExp();
    
    // ...
};

class Criminal : public Character{
private:
    Sherlock *sherlock;
    Watson *watson;

public:
    Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson);
    string str() override;
    Position getNextPosition() override;
    void move() override;
    // ...
};

class ArrayMovingObject {
private:
    // TODO
    MovingObject **arr_mv_objs;
    int count;
    int capacity;

public:
    ArrayMovingObject(int capacity);

    ~ArrayMovingObject() ;
    bool isFull() const;
    bool add(MovingObject * mv_obj);
    MovingObject * get(int index) const;
    int size() const; // return current number of elements in the array
    string str() const;
};

class Configuration {
    friend class StudyPinkProgram;

private:
    int map_num_rows;
    int map_num_cols;
    int max_num_moving_objects;
    int num_walls;
    Position *arr_walls;
    int num_fake_walls;
    Position *arr_fake_walls;
    string sherlock_moving_rule;
    Position sherlock_init_pos;
    int sherlock_init_hp;
    int sherlock_init_exp;
    string watson_moving_rule;
    Position watson_init_pos;
    int watson_init_hp;
    int watson_init_exp;
    Position criminal_init_pos;
    int num_steps;
private:
    void processLine(const string &line) {
  
        int pos = line.find('=');
    string key= line.substr(0, pos);
    string value = line.substr(pos + 1);
    if (key == "MAP_NUM_ROWS") {
             map_num_rows = stoi(value);
        } else if (key == "MAP_NUM_COLS") {
            map_num_cols = stoi(value);
        } else if (key == "MAX_NUM_MOVING_OBJECTS") {
            max_num_moving_objects = stoi(value);
        } else if (key == "ARRAY_WALLS") {
            processPositionArray(value, arr_walls, num_walls);
        } else if (key == "ARRAY_FAKE_WALLS") {
            processPositionArray(value, arr_fake_walls, num_fake_walls);
        } else if (key == "SHERLOCK_MOVING_RULE") {
            sherlock_moving_rule=value;
        } else if (key == "SHERLOCK_INIT_POS") {
            sherlock_init_pos = Position(value);
        } else if (key == "SHERLOCK_INIT_HP") {
            sherlock_init_hp = stoi(value);
        } else if (key == "SHERLOCK_INIT_EXP") {
            sherlock_init_exp = stoi(value);
        } else if (key == "WATSON_MOVING_RULE") {
            watson_moving_rule = value;
        } else if (key == "WATSON_INIT_POS") {
            watson_init_pos = Position(value);
        } else if (key == "WATSON_INIT_HP") {
            watson_init_hp = stoi(value);
        } else if (key == "WATSON_INIT_EXP") {
            watson_init_exp = stoi(value);
        } else if (key == "CRIMINAL_INIT_POS") {
            criminal_init_pos = Position(value);
        } else if (key == "NUM_STEPS") {
            num_steps = stoi(value);
        } else {
            cerr << "Unknown configuration key: " << key << endl;
        }
    
    }

    void processPositionArray(string value, Position *&arr, int &num) {
    // Clearing the existing array, if any
    //cout << 0 << endl;
    if (arr != nullptr) {
        // delete[] arr;
        arr = nullptr;
    }
    //cout << 1 << endl;
    // Counting the number of positions in the string
    num = 0;
    for (char ch : value) {
        if (ch == '(')
            num++;
    }

    //cout << 2 << endl;

    // Allocating memory for the Position array
    arr = new Position[num];

    //cout << 3 << endl;
    // Parsing the string value
    stringstream ss(value);
    char ch;
    int i = 0;
    while (ss >> ch) {
        if (ch == '(') {
            int r, c;
            char comma;
            ss >> r >> comma >> c >> ch; // read until ')'
            arr[i++] = Position(r, c);
        }
    }
    //cout << 4 << endl;
}


//     void processPositionArray(const std::string& value, Position *&arr, int &num) {
//     std::string positions = value.substr(1, value.length() - 2);
//     std::istringstream posStream(positions);
//     num = 0;
//     char c;
//     int row, col;
//     while (posStream >> c >> row >> c >> col >> c) {
//         num++;
//     }

//     arr = new Position[num];
//     posStream.clear();
//     posStream.seekg(0);
//     int count = 0;
//     while (posStream >> c >> row >> c >> col >> c) {
//         arr[count++] = Position(row, col);
//     }
// }
public:
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;


};

// Robot, BaseItem, BaseBag,...
class Robot : public MovingObject {
protected:
    RobotType robot_type;
    BaseItem* item; // Item obtained upon defeating the robot

public:
    Robot(RobotType type, int index, const Position& init_pos, Map* map)
        : MovingObject(index, init_pos, map, "Robot"), robot_type(type), item(nullptr) {}

    int calculateManhattanDistance(Position pos1, Position pos2) {
        int col_diff = abs(pos1.getCol() - pos2.getCol());
        int row_diff = abs(pos1.getRow() - pos2.getRow());
        return col_diff + row_diff;
}

    // Method to add the robot to the ArrayMovingObject
    bool addToMovingObjects(ArrayMovingObject& moving_objects) {
        if (!moving_objects.isFull()) {
            moving_objects.add(this);
            return true;
        }
        return false;
    }

    // Add other methods as needed
};


// Class representing a criminal robot
class RobotC : public Robot {
private:
    Criminal* criminal;

public:
    RobotC(int index, const Position& init_pos, Map* map, Criminal* criminal);
    int getDistanceToSherlock(Sherlock* sherlock);
    int getDistanceToWatson(Watson* watson);
    Position getNextPosition();
    void move();
    string str();
};

// Class representing a Sherlock robot
class RobotS : public Robot {
private:
    Criminal* criminal;
    Sherlock* sherlock;

public:
    RobotS(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock);
    int getDistance();
    Position getNextPosition();
    void move();
    string str();
    // Add other methods as needed
};

// Class representing a Watson robot
class RobotW : public Robot {
private:
    Criminal* criminal;
    Watson* watson;

public:
    RobotW(int index, const Position& init_pos, Map* map, Criminal* criminal, Watson* watson);
    int getDistance();
    Position getNextPosition();
    void move();
    string str();
};

// Class representing a Sherlock and Watson robot
class RobotSW : public Robot {
private:
    Criminal* criminal;
    Sherlock* sherlock;
    Watson* watson;

public:
    RobotSW(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson);
    string str();
    int getDistance();
    Position getNextPosition();
    void move();
    
    // Add other methods as needed
};




class BaseItem {
    // Add necessary members here
    private:
        ItemType type;
    public:
        BaseItem(ItemType type): type(type){};
        virtual bool canUse ( Character * obj , Robot * robot ) = 0;
        virtual void use( Character * obj , Robot * robot ) = 0;
        ItemType getType(){
            return type;
        }
};

class MagicBook : public BaseItem {
    // Add necessary members here
    private:
    public:
        MagicBook(): BaseItem(MAGIC_BOOK){};
        bool canUse ( Character * obj , Robot * robot ) override;
        void use( Character * obj , Robot * robot ) override;
};

class EnergyDrink : public BaseItem {
    // Add necessary members here
    private:
    public:
        EnergyDrink(): BaseItem(ENERGY_DRINK){};
        bool canUse ( Character * obj , Robot * robot ) override;
        void use( Character * obj , Robot * robot ) override;
};

class FirstAid : public BaseItem {
    // Add necessary members here
    private:
    public:
        FirstAid(): BaseItem(FIRST_AID){};
        bool canUse ( Character * obj , Robot * robot ) override;
        void use( Character * obj , Robot * robot ) override;
};

class ExcemptionCard : public BaseItem {
    // Add necessary members here
    private:
       
    public:
        ExcemptionCard(): BaseItem(EXCEMPTION_CARD){};
        bool canUse ( Character * obj , Robot * robot ) override;
        void use( Character * obj , Robot * robot ) override;
};

class PassingCard : public BaseItem {
    // Add necessary members here
    private:
        string challenge;
    public:
        PassingCard(string challenge):challenge(challenge), BaseItem(PASSING_CARD){};
        bool canUse ( Character * obj , Robot * robot ) override;
        void use( Character * obj , Robot * robot ) override;
};


struct ItemNode {
    BaseItem * item;
    ItemNode * next;

    ItemNode(BaseItem * item): item(item), next(nullptr) {};
    ItemNode(BaseItem * item, ItemNode * next): item(item), next(next) {};
};


class BaseBag{
    private:
        Character* obj;
    public:
        BaseBag(Character* obj):obj(obj){};
        virtual bool insert ( BaseItem * item )=0;
        virtual BaseItem * get()=0;
        virtual BaseItem * get( ItemType itemType )=0; 
        virtual string str () const =0;
        Character* getObj();
};

class SherlockBag : public BaseBag {
    private:
        ItemNode * head;
        int const capacity = 13;
        int count;
    public:
        SherlockBag(Sherlock * sherlock);
        bool insert ( BaseItem * item ) override;
        BaseItem * get() override;
        BaseItem * get( ItemType itemType ) override;
        string str () const override;
        BaseItem* useAvailableItem();
};


class WatsonBag : public BaseBag {
    private:
        ItemNode * head;
        int const capacity = 15;
        int count;
    public:
        WatsonBag(Watson * watson);
        bool insert ( BaseItem * item ) override;
        BaseItem * get() override;
        BaseItem * get( ItemType itemType ) override;
        string str () const override;
};

class StudyPinkProgram {
private:
    // Sample attributes
    Configuration * config;
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    Map * map;
    ArrayMovingObject * arr_mv_objs;


public:
    StudyPinkProgram(const string & config_file_path);

    bool isStop() const;

    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(),criminal->getCurrentPosition().getCol())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(),criminal->getCurrentPosition().getCol())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose) {
        // Note: This is a sample code. You can change the implementation as you like.
        // TODO
        for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                arr_mv_objs->get(i)->move();
                if (isStop()) {
                    printStep(istep);
                    break;
                }
                if (verbose) {
                    printStep(istep);
                }
            }
        }
        printResult();
    }

    ~StudyPinkProgram();
};

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
// class Configuration
////////////////////////////////////////////////
Configuration::Configuration(const string& filepath) {
    ifstream file(filepath);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                processLine(line);
            }
            file.close();
        } else {
            cerr << "Unable to open file " << filepath << endl;
        }
}

Configuration::~Configuration() {
    delete[] arr_walls;
    delete[] arr_fake_walls;
}

string Configuration::str() const {
    stringstream ss;
        ss << "Configuration[\n"
           << "MAP_NUM_ROWS=" << map_num_rows << "\n"
           << "MAP_NUM_COLS=" << map_num_cols << "\n"
           << "MAX_NUM_MOVING_OBJECTS=" << max_num_moving_objects << "\n"
           << "NUM_WALLS=" << num_walls << "\n"
           << "ARRAY_WALLS=[";
        for (int i = 0; i < num_walls; ++i) {
            ss << "(" << arr_walls[i].getRow() << "," << arr_walls[i].getCol() << ")";
            if (i < num_walls - 1) {
                ss << ";";
            }
        }
        ss << "]\n"
           << "NUM_FAKE_WALLS=" << num_fake_walls << "\n"
           << "ARRAY_FAKE_WALLS=[";
        for (int i = 0; i < num_fake_walls; ++i) {
            ss << "(" << arr_fake_walls[i].getRow() << "," << arr_fake_walls[i].getCol() << ")";
            if (i < num_fake_walls - 1) {
                ss << ";";
            }
        }
        ss << "]\n"
           << "SHERLOCK_MOVING_RULE=" << sherlock_moving_rule << "\n"
           << "SHERLOCK_INIT_POS=(" << sherlock_init_pos.getRow() << "," << sherlock_init_pos.getCol() << ")\n"
           << "SHERLOCK_INIT_HP=" << sherlock_init_hp << "\n"
           << "SHERLOCK_INIT_EXP=" << sherlock_init_exp << "\n"
           << "WATSON_MOVING_RULE=" << watson_moving_rule << "\n"
           << "WATSON_INIT_POS=(" << watson_init_pos.getRow() << "," << watson_init_pos.getCol() << ")\n"
           << "WATSON_INIT_HP=" << watson_init_hp << "\n"
           << "WATSON_INIT_EXP=" << watson_init_exp << "\n"
           << "CRIMINAL_INIT_POS=(" << criminal_init_pos.getRow() << "," << criminal_init_pos.getCol() << ")\n"
           << "NUM_STEPS=" << num_steps << "\n"
           << "]";
        return ss.str();
}

////////////////////////////////////////////////////////////////////////
// class MapElement
////////////////////////////////////////////////
MapElement::MapElement(ElementType in_type) {
    this->type = in_type;
}

ElementType MapElement::getType() const {
    return this->type;
}

MapElement::~MapElement() {
}

////////////////////////////////////////////////////////////////////////
// class FakeWall
////////////////////////////////////////////////

FakeWall::FakeWall(int req_exp) : MapElement(FAKE_WALL), req_exp(req_exp) {
}

int FakeWall::getReqExp() const {
    return this->req_exp;
}

////////////////////////////////////////////////////////////////////////
// class Path
////////////////////////////////////////////////

Path::Path() : MapElement(PATH) {}

////////////////////////////////////////////////////////////////////////
// class Wall
////////////////////////////////////////////////

Wall::Wall() : MapElement(WALL) {}

////////////////////////////////////////////////////////////////////////
// class Map
////////////////////////////////////////////////

Map::Map(int num_rows, int num_cols, int num_walls, Position* array_walls, int num_fake_walls, Position* array_fake_walls) {
    this->num_rows = num_rows;
    this->num_cols = num_cols;
    map = new MapElement*[num_rows];
    
    for (int i = 0; i < num_rows; ++i) {
        map[i] = new MapElement[num_cols];
        // Initialize each element based on the type
        for (int j = 0; j < num_cols; ++j) {
            Position current_position(i, j);
            bool is_wall = false;
            bool is_fake_wall = false;

            // Check if the current position is in the array of walls
            for (int k = 0; k < num_walls; ++k) {
                if (array_walls[k].isEqual(i, j)) {
                    is_wall = true;
                    break;
                }
            }

            // Check if the current position is in the array of fake walls
            for (int k = 0; k < num_fake_walls; ++k) {
                if (array_fake_walls[k].isEqual(i, j)) {
                    is_fake_wall = true;
                    break;
                }
            }

            // Initialize the element based on its type
            if (is_wall) {
                map[i][j] = Wall();
            } else if (is_fake_wall) {
                // Calculate req_exp for FakeWall
                int req_exp = (i * 257 + j * 139 + 89) % 900 + 1;
                map[i][j] = FakeWall(req_exp);
            } else {
                map[i][j] = Path();
            }
        }
    }
}

Map::~Map() {
    for (int i = 0; i < num_rows; ++i) {
        delete[] map[i];
    }
    delete[] map;
}

// bool Map::isValid(const Position& pos, MovingObject* mv_obj) const {
//     // Get the map element at the given position
//     MapElement map_element = map[pos.getRow()][pos.getCol()];

//     // Check if the map element is a fake wall
//     if (map_element.getType() == FAKE_WALL) {
//         // If the moving object is Watson, check if its EXP is sufficient
//         if (dynamic_cast<Watson*>(mv_obj) != nullptr) {
//             // Retrieve Watson's EXP
//             int watson_exp = dynamic_cast<Watson*>(mv_obj)->getExp();

//             // Retrieve the required EXP for the fake wall at this position
//             int req_exp = dynamic_cast<FakeWall*>(&map_element)->getReqExp();

//             // Check if Watson's EXP is greater than or equal to the required EXP
//             if (watson_exp >= req_exp) {
//                 return true; // Watson can move to this position
//             } else {
//                 return false; // Watson cannot move to this position due to insufficient EXP
//             }
//         }
//     }

//     // For other cases or if the map element is not a fake wall, consider the position valid
//     return true;
//}

bool Map::isValid(const Position& pos, MovingObject* mv_obj) const {
    // Get the map element pointer at the given position
    MapElement* map_element = &map[pos.getRow()][pos.getCol()];
    cout << "Map element type: " << map_element->getType() << endl;
    // Check if the map element is a fake wall
    if (map_element->getType() == FAKE_WALL) {
        // If the moving object is Watson, check if its EXP is sufficient
        if (dynamic_cast<Watson*>(mv_obj) != nullptr) {
            // Retrieve Watson's EXP
            int watson_exp = dynamic_cast<Watson*>(mv_obj)->getExp();

            // Retrieve the required EXP for the fake wall at this position
            int req_exp = dynamic_cast<FakeWall*>(map_element)->getReqExp();

            // Check if Watson's EXP is greater than or equal to the required EXP
            if (watson_exp >= req_exp) {
                return true; // Watson can move to this position
            } else {
                return false; // Watson cannot move to this position due to insufficient EXP
            }
        }
    }

    return true;
}






////////////////////////////////////////////////////////////////////////
// class Position
////////////////////////////////////////////////

const Position Position::npos = Position(-1, -1);

Position::Position(int r, int c) {
    this->r = r;
    this->c = c;
}

Position::Position(const string &str_pos) {
        // Remove parentheses and tokenize string
        string pos = str_pos.substr(1, str_pos.size() - 2); // Remove parentheses
        stringstream ss(pos);
        string token;
        getline(ss, token, ','); // Extract row
        r = stoi(token);
        getline(ss, token, ','); // Extract column
        c = stoi(token);
    }

int Position::getRow() const {
    return this->r;
}

int Position::getCol() const {
    return this->c;
}

void Position::setRow(int r) {
    this->r = r;
}

void Position::setCol(int c) {
    this->c = c;
}

string Position::str() const {  
        stringstream ss;
        ss << "(" << r << "," << c << ")";
        return ss.str();
    }

bool Position::isEqual(int in_r, int in_c) const {
        return (r == in_r) && (c == in_c);
    }

////////////////////////////////////////////////////////////////////////
// class MovingObject
////////////////////////////////////////////////
MovingObject::MovingObject(int index, const Position pos, Map * map, const string & name) {
    this->index = index;
    this->pos = pos;
    this->map = map;
    this->name = name;
}
MovingObject::MovingObject() {
}

void MovingObject::move() {
}

Position MovingObject::getCurrentPosition(){
    return this->pos;
}

MovingObject::~MovingObject() {
}

////////////////////////////////////////////////////////////////////////
// class Character
////////////////////////////////////////////////
int Character::getHp() {
    return this->hp;
}

int Character::getExp() {
    return this->exp;
}

void Character::setHp(int hp) {
    this->hp = hp;
}

void Character::setExp(int exp) {
    this->exp = exp;
}

////////////////////////////////////////////////////////////////////////
// class Sheclock
////////////////////////////////////////////////
Sherlock::Sherlock(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp)
        : Character(index, init_pos, map, "Sherlock"), moving_rule(moving_rule) {
        // Set initial HP and EXP within valid ranges
        hp = (init_hp < 0) ? 0 : (init_hp > 500) ? 500 : init_hp;
        exp = (init_exp < 0) ? 0 : (init_exp > 900) ? 900 : init_exp;
    }

void Sherlock::move() {
    // Get the next position
        Position next_pos = getNextPosition();

        // Check if the next position is valid
        if (next_pos != Position::npos) {
            // Move Sherlock to the next position
            pos = next_pos;
        }
        // Otherwise, Sherlock stands still
}

string Sherlock::str() {
    stringstream ss;
    ss << "Sherlock[index=" << index << ";pos=" << pos.str() << ";moving_rule=" << moving_rule << "]";
    return ss.str();
}

Position Sherlock::getNextPosition() {
     // If moving_rule is empty or the map is not set, return npos
        if (moving_rule.empty() || map == nullptr) {
            return Position::npos;
        }
        cout << moving_rule << endl;
        // Calculate the index of the next character in the moving_rule
        static size_t next_char_index = 0;
        char next_direction = moving_rule[next_char_index];
        cout << next_direction << endl;
        // Update the index for the next call
        next_char_index = (next_char_index + 1) % moving_rule.size();
        cout << next_char_index << endl;
        // Calculate the next position based on the direction
        int next_r = pos.getRow();
        int next_c = pos.getCol();
        cout << next_r << " " << next_c << endl;
        switch (next_direction) {
            case 'L':
                next_c--;
                break;
            case 'R':
                next_c++;
                break;
            case 'U':
                next_r--;
                break;
            case 'D':
                next_r++;
                break;
            default:
                break; // Handle invalid characters, if needed
        }

        // Check if the next position is valid
        Position next_pos(next_r, next_c);

        cout << next_pos.str() << endl;
        if (map->isValid(next_pos, this)) {
            pos.setCol(next_pos.getCol());
            pos.setRow(next_pos.getRow());
            cout << pos.str() << endl;
            return pos;
        } else {
            return Position::npos;
        }
}

////////////////////////////////////////////////////////////////////////
// class Waston
////////////////////////////////////////////////
Watson::Watson(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp)
        : Character(index, init_pos, map, "Watson"), moving_rule(moving_rule) {
        // Set initial HP and EXP within valid ranges
        hp = (init_hp < 0) ? 0 : (init_hp > 500) ? 500 : init_hp;
        exp = (init_exp < 0) ? 0 : (init_exp > 900) ? 900 : init_exp;
    }

void Watson::move() {
    // Get the next position
        Position next_pos = getNextPosition();

        // Check if the next position is valid
        if (next_pos != Position::npos) {
            // Move Sherlock to the next position
            pos = next_pos;
        }
        // Otherwise, Sherlock stands still
}

Position Watson::getNextPosition() {
    // If moving_rule is empty or the map is not set, return npos
        if (moving_rule.empty() || map == nullptr) {
            return Position::npos;
        }

        // Calculate the index of the next character in the moving_rule
        static size_t next_char_index = 0;
        char next_direction = moving_rule[next_char_index];

        // Update the index for the next call
        next_char_index = (next_char_index + 1) % moving_rule.size();

        // Calculate the next position based on the direction
        int next_r = pos.getRow();
        int next_c = pos.getCol();

        switch (next_direction) {
            case 'L':
                next_c--;
                break;
            case 'R':
                next_c++;
                break;
            case 'U':
                next_r--;
                break;
            case 'D':
                next_r++;
                break;
            default:
                break; // Handle invalid characters, if needed
        }

        // Check if the next position is valid
        Position next_pos(next_r, next_c);
        if (map->isValid(next_pos, this)) {
            return next_pos;
        } else {
            return Position::npos;
        }
}

string Watson::str() {
    stringstream ss;
    ss << "Watson[index=" << index << ";pos=" << pos.str() << ";moving_rule=" << moving_rule << "]";
    return ss.str();
}

int Watson::getExp() {
    return this->exp;
}

////////////////////////////////////////////////////////////////////////
// class Criminal
////////////////////////////////////////////////
Criminal::Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson)
    : Character(index, init_pos, map, "Criminal"), sherlock(sherlock), watson(watson) {}

Position Criminal::getNextPosition() {
    int maxDistance = -1;
        Position nextPos = Position::npos;

        // Define the directions in order of priority: Up, Left, Down, Right
        const Position directions[] = {
            Position(-1, 0), // Up
            Position(0, -1), // Left
            Position(1, 0),  // Down
            Position(0, 1)   // Right
        };

        // Iterate through each direction
        for (const auto &dir : directions) {
            Position newPos(pos.getRow() + dir.getRow(), pos.getCol() + dir.getCol());

            // Check if the new position is valid
            if (map->isValid(newPos, this)) {
                // Calculate Manhattan distance to Sherlock and Watson
                int distanceToSherlock = std::abs(newPos.getRow() - sherlock->getCurrentPosition().getRow()) +
                                         std::abs(newPos.getCol() - sherlock->getCurrentPosition().getCol());
                int distanceToWatson = std::abs(newPos.getRow() - watson->getCurrentPosition().getRow()) +
                                       std::abs(newPos.getCol() - watson->getCurrentPosition().getCol());
                int totalDistance = distanceToSherlock + distanceToWatson;

                // Check if the total distance is greater than the current max distance
                if (totalDistance > maxDistance) {
                    maxDistance = totalDistance;
                    nextPos = newPos;
                }
            }
        }

        return nextPos;
}

void Criminal::move() {
    // Get the next position
        Position next_pos = getNextPosition();

        // Check if the next position is valid
        if (next_pos != Position::npos) {
            // Move Sherlock to the next position
            pos = next_pos;
        }
        // Otherwise, Sherlock stands still
}

string Criminal::str(){
    return "Criminal[index=" + std::to_string(index) + ";pos=" + pos.str() + "]";
}

////////////////////////////////////////////////////////////////////////
// class ArrayMovingObject
////////////////////////////////////////////////
ArrayMovingObject::ArrayMovingObject(int size) : count(0), capacity(size) {
        arr_mv_objs = new MovingObject *[capacity];
    }

bool ArrayMovingObject::add(MovingObject * mv_obj) {
    if (!isFull()) {
        arr_mv_objs[count++] = mv_obj;
        return true;
    }
    return false;
}

string ArrayMovingObject::str() const {
     stringstream ss;
    ss << "ArrayMovingObject[count=" << count << ";capacity=" << capacity << ";";
    for (int i = 0; i < count; ++i) {
        ss << arr_mv_objs[i]->str();
        if (i < count - 1) {
            ss << "; ";
        }
    }
    ss << "]";
    return ss.str();
}

 bool ArrayMovingObject::isFull() const {
        return count == capacity;
    }

ArrayMovingObject:: ~ArrayMovingObject() {
        for (int i = 0; i < count; ++i) {
            delete arr_mv_objs[i];
        }
        delete[] arr_mv_objs;
    }
int ArrayMovingObject::size() const {
    return count;
}

MovingObject* ArrayMovingObject::get(int index) const {
    if (index < 0 || index >= count) {
        return nullptr;
    }
    return arr_mv_objs[index];
}

////////////////////////////////////////////////////////////////////////
// class RobotC
////////////////////////////////////////////////
RobotC::RobotC(int index, const Position& init_pos, Map* map, Criminal* criminal)
        : Robot(C, index, init_pos, map), criminal(criminal) {}

int RobotC::getDistanceToSherlock(Sherlock* sherlock){
    // Calculate the Manhattan distance from the robot to Sherlock
    return calculateManhattanDistance(pos, sherlock->getCurrentPosition());
}

int RobotC::getDistanceToWatson(Watson* watson){
    // Calculate the Manhattan distance from the robot to Watson
    return calculateManhattanDistance(pos, watson->getCurrentPosition());
}

Position RobotC::getNextPosition() {
    // Move to the next position with the same position as the criminal
    return criminal->getCurrentPosition();
}

string RobotC::str(){
        stringstream ss;
        ss << "Robot[pos=" << pos << ";type=C;dist=]";
        return ss.str();
    }

void RobotC::move() {
    Position nextPos = getNextPosition();

    // Check if the next position is valid
    if (nextPos != Position::npos) {
        // Move the robot to the next position
        pos = nextPos;
    }
}

////////////////////////////////////////////////////////////////////////
// class RobotS
////////////////////////////////////////////////
RobotS::RobotS(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock)
    : Robot(S, index, init_pos, map), criminal(criminal), sherlock(sherlock) {
        // Additional initialization for RobotS
    }


int RobotS::getDistance() {
    // Calculate the Manhattan distance from the robot to Sherlock
    int distance_to_sherlock = calculateManhattanDistance(pos, sherlock->getCurrentPosition());
    return distance_to_sherlock;
}

Position RobotS::getNextPosition() {
    // Initialize variables to store the closest position and its Manhattan distance
    Position closestPos = Position::npos;
    int closestDistance = numeric_limits<int>::max();

    // Define the possible directions in a clockwise order starting from upward movement
    int directions[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

    // Iterate through adjacent positions in clockwise order
    for (int i = 0; i < 4; ++i) {
        // Calculate the row and column of the next position
        int nextRow = pos.getRow() + directions[i][0];
        int nextCol = pos.getCol() + directions[i][1];
        
        // Create the next position object
        Position nextPos(nextRow, nextCol);
        
        // Check if the next position is valid
        if (!map->isValid(nextPos, this)) continue;
        
        // Calculate Manhattan distance to Sherlock
        int distance = calculateManhattanDistance(nextPos, sherlock->getCurrentPosition());
        
        // Update closest position if this position is closer
        if (distance < closestDistance) {
            closestDistance = distance;
            closestPos = nextPos;
        }
    }

    return closestPos;
}

void RobotS::move() {
    Position nextPos = getNextPosition();

    // Check if the next position is valid
    if (nextPos != Position::npos) {
        // Move the robot to the next position
        pos = nextPos;
    }
}

string RobotS::str(){
        int dist = getDistance();
        stringstream ss;
        ss << "Robot[pos=" << pos << ";type=S;dist=" << dist << "]";
        return ss.str();
    }
////////////////////////////////////////////////////////////////////////
// class RobotW
////////////////////////////////////////////////
RobotW::RobotW(int index, const Position& init_pos, Map* map, Criminal* criminal, Watson* watson)
    : Robot(W, index, init_pos, map), criminal(criminal), watson(watson) {
        // Additional initialization for RobotW
    }

int RobotW::getDistance(){
    // Calculate the Manhattan distance from the robot to Watson
    int distance_to_watson = calculateManhattanDistance(pos, watson->getCurrentPosition());
    return distance_to_watson;
}

Position RobotW::getNextPosition() {
    // Initialize variables to store the closest position and its Manhattan distance
    Position closestPos = Position::npos;
    int closestDistance = numeric_limits<int>::max();

    // Define the possible directions in a clockwise order starting from upward movement
    int directions[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

    // Get Watson's next position
    Position watsonNextPos = watson->getNextPosition();

    // Iterate through adjacent positions in clockwise order
    for (int i = 0; i < 4; ++i) {
        // Calculate the row and column of the next position
        int nextRow = pos.getRow() + directions[i][0];
        int nextCol = pos.getCol() + directions[i][1];
        
        // Create the next position object
        Position nextPos(nextRow, nextCol);
        
        // Check if the next position is valid
        if (!map->isValid(nextPos, this)) continue;
        
        // Calculate Manhattan distance to Watson's next position
        int distance = calculateManhattanDistance(nextPos, watsonNextPos);
        
        // Update closest position if this position is closer
        if (distance < closestDistance) {
            closestDistance = distance;
            closestPos = nextPos;
        }
    }

    return closestPos;
}

void RobotW::move() {
    Position nextPos = getNextPosition();

    // Check if the next position is valid
    if (nextPos != Position::npos) {
        // Move the robot to the next position
        pos = nextPos;
    }
}


string RobotW::str() {
        int dist = getDistance();
        stringstream ss;
        ss << "Robot[pos=" << pos << ";type=W;dist=" << dist << "]";
        return ss.str();
    }

////////////////////////////////////////////////////////////////////////
// class RobotSW
////////////////////////////////////////////////
RobotSW::RobotSW(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson)
    : Robot(SW, index, init_pos, map), criminal(criminal), sherlock(sherlock), watson(watson) {
        // Additional initialization for RobotSW
    }

int RobotSW::getDistance(){
    // Calculate the Manhattan distance from the robot to both Sherlock and Watson and return the sum
    int distance_to_sherlock = calculateManhattanDistance(pos, sherlock->getCurrentPosition());
    int distance_to_watson = calculateManhattanDistance(pos, watson->getCurrentPosition());
    return distance_to_sherlock + distance_to_watson;
}

Position RobotSW::getNextPosition() {
    // Initialize variables to store the closest position and its total Manhattan distance
    Position closestPos = Position::npos;
    int closestDistance = numeric_limits<int>::max();

    // Define the possible directions in a clockwise order starting from upward movement
    int directions[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

    // Get Sherlock's next position
    Position sherlockNextPos = sherlock->getNextPosition();
    // Get Watson's next position
    Position watsonNextPos = watson->getNextPosition();

    // Iterate through adjacent positions in clockwise order
    for (int i = 0; i < 4; ++i) {
        // Calculate the row and column of the next position
        int nextRow = pos.getRow() + (2 * directions[i][0]);
        int nextCol = pos.getCol() + (2 * directions[i][1]);
        
        // Create the next position object
        Position nextPos(nextRow, nextCol);
        
        // Check if the next position is valid
        if (!map->isValid(nextPos, this)) continue;
        
        // Calculate Manhattan distance to both Sherlock's and Watson's next positions
        int distanceToSherlock = calculateManhattanDistance(nextPos, sherlockNextPos);
        int distanceToWatson = calculateManhattanDistance(nextPos, watsonNextPos);
        int totalDistance = distanceToSherlock + distanceToWatson;
        
        // Update closest position if this position has the closest total distance
        if (totalDistance < closestDistance) {
            closestDistance = totalDistance;
            closestPos = nextPos;
        }
    }

    return closestPos;
}

void RobotSW::move() {
    Position nextPos = getNextPosition();

    // Check if the next position is valid
    if (nextPos != Position::npos) {
        // Move the robot to the next position
        pos = nextPos;
    }
}

string RobotSW::str() {
        int dist = getDistance();
        stringstream ss;
        ss << "Robot[pos=" << pos << ";type=SW;dist=" << dist << "]";
        return ss.str();
    }

////////////////////////////////////////////////////////////////////////
// class MagicBook
////////////////////////////////////////////////
bool MagicBook::canUse(Character* obj,Robot* robot){
   if(robot){
        return false;
   }else if(obj->getExp() > 350) return false;
   return true;
}

void MagicBook::use(Character* obj,Robot* robot){
    if(canUse(obj,robot)){
        obj->setExp(obj->getExp()*1.25);
    }
}

////////////////////////////////////////////////////////////////////////
// class EneryDrink
////////////////////////////////////////////////
bool EnergyDrink::canUse(Character* obj,Robot* robot){
    if(robot){
        return false;
    }else if(obj->getHp() > 100) return false;
    return true;
}

void EnergyDrink::use(Character* obj,Robot* robot){
    if(canUse(obj,robot)){
        obj->setHp(obj->getHp()*1.2);
    }
}

////////////////////////////////////////////////////////////////////////
// class FirstAid
////////////////////////////////////////////////

bool FirstAid::canUse(Character* obj,Robot* robot){
    if(robot){
        return false;
    }else if(obj->getHp() > 100 || obj->getExp() > 350) return false;
    return true;
}

void FirstAid::use(Character* obj,Robot* robot){
    if(canUse(obj,robot)){
        obj->setHp(obj->getHp()*1.5);
    }
}

////////////////////////////////////////////////////////////////////////
// class ExemptionCard
////////////////////////////////////////////////

bool ExcemptionCard::canUse(Character* obj,Robot* robot){
    if(!robot){
        return false;
    }else if((obj->getName()!="Sherlock")||(obj->getHp()%2!=1)) return false;
    return true;
}

void ExcemptionCard::use(Character* obj,Robot* robot){
    // if(canUse(obj,robot)){
    //     obj->setHp(obj->getHp()*1.5);
    // }
}

////////////////////////////////////////////////////////////////////////
// class PassingCard
////////////////////////////////////////////////
bool PassingCard::canUse(Character* obj,Robot* robot){
    if(!robot){
        return false;
    }else if((obj->getName()!="Watson")||(obj->getExp()%2!=0)) return false;
    return true;
}
void PassingCard::use(Character* obj,Robot* robot){
    // if(canUse(obj,robot)){
    //     obj->setHp(obj->getHp()*1.5);
    // }
}


////////////////////////////////////////////////////////////////////////
// class BaseBag
////////////////////////////////////////////////

Character* BaseBag::getObj() {
    return obj;
}

BaseItem* SherlockBag::useAvailableItem() {
    ItemNode* current = head;
    ItemNode* prev = nullptr;
    while (current != nullptr) {
        if (current->item->canUse(this->getObj(), nullptr)) {
            // Move this item to the front of the list
            if (prev != nullptr) {
                prev->next = current->next;
                current->next = head;
                head = current;
            }
            return get();
        }
        prev = current;
        current = current->next;
    }
    cerr << "No usable item found in bag." << endl;
    return nullptr;
}

////////////////////////////////////////////////////////////////////////
// class SherlockBag
////////////////////////////////////////////////
SherlockBag::SherlockBag(Sherlock* sherlock) : BaseBag(sherlock), head(nullptr),count(0) {}

bool SherlockBag::insert(BaseItem* item) {
    if (head == nullptr) {
        head = new ItemNode(item);
        return true;
    }

    if (count >= capacity) {
        return false;
    }

    ItemNode* newNode = new ItemNode(item, head);
    head = newNode;
    count++;
    // capacity--;
    return true;
}

BaseItem* SherlockBag::get() {
    if (head == nullptr) {
        cerr << "Bag is empty." << endl;
        return nullptr;
    }

    BaseItem* item = head->item;
    ItemNode* temp = head;
    head = head->next;
    delete temp;
    count--;
    return item;
}

BaseItem* SherlockBag::get(ItemType itemType) {
    ItemNode* current = head;
    while (current != nullptr) {
        if (current->item->getType() == itemType) {
            BaseItem* item = current->item;
            // Remove item from bag
            if (current == head) {
                head = head->next;
            } else {
                ItemNode* prev = head;
                while (prev->next != current) {
                    prev = prev->next;
                }
                prev->next = current->next;
            }
            delete current;
            count--;
            return item;
        }
        current = current->next;
    }
    cerr << "Item type not found in bag." << endl;
    return nullptr;
}

string SherlockBag::str() const {
    stringstream ss;
    ss << "Bag[count=" << count << ";";
    ItemNode *current = head;
    while (current != nullptr) {
        ss << current->item->getType(); // Adding item type to the string
        if (current->next != nullptr) {
            ss << ",";
        }
        current = current->next;
    }
    ss << "]";
    return ss.str();
}


////////////////////////////////////////////////////////////////////////
// class WastonBag
////////////////////////////////////////////////
WatsonBag::WatsonBag(Watson* watson) : BaseBag(watson), head(nullptr),count(0) {}

bool WatsonBag::insert(BaseItem* item) {
    if (head == nullptr) {
        head = new ItemNode(item);
        return true;
    }

    if (count >= capacity) {
        return false;
    }

    ItemNode* newNode = new ItemNode(item, head);
    head = newNode;
    count++;
    // capacity--;
    return true;
}

BaseItem* WatsonBag::get() {
    if (head == nullptr) {
        cerr << "Bag is empty." << endl;
        return nullptr;
    }

    BaseItem* item = head->item;
    ItemNode* temp = head;
    head = head->next;
    delete temp;
    count--;
    return item;
}

BaseItem* WatsonBag::get(ItemType itemType) {
    ItemNode* current = head;
    while (current != nullptr) {
        if (current->item->getType() == itemType) {
            BaseItem* item = current->item;
            // Remove item from bag
            if (current == head) {
                head = head->next;
            } else {
                ItemNode* prev = head;
                while (prev->next != current) {
                    prev = prev->next;
                }
                prev->next = current->next;
            }
            delete current;
            count--;
            return item;
        }
        current = current->next;
    }
    cerr << "Item type not found in bag." << endl;
    return nullptr;
}

string WatsonBag::str() const {
    stringstream ss;
    ss << "Bag[count=" << count << ";";
    ItemNode *current = head;
    while (current != nullptr) {
        ss << current->item->getType(); // Adding item type to the string
        if (current->next != nullptr) {
            ss << ",";
        }
        current = current->next;
    }
    ss << "]";
    return ss.str();
}


////////////////////////////////////////////////////////////////////////
// class StudyPinkProgram
////////////////////////////////////////////////
StudyPinkProgram::StudyPinkProgram(const string &config_file_path) {
    // Read the configuration from the file
    config = new Configuration(config_file_path);

    // Create the map
    map = new Map(config->map_num_rows, config->map_num_cols, config->num_walls, config->arr_walls, config->num_fake_walls, config->arr_fake_walls);

    // Create characters
    sherlock = new Sherlock(0, config->sherlock_moving_rule, config->sherlock_init_pos, map, config->sherlock_init_hp, config->sherlock_init_exp);
    watson = new Watson(1, config->watson_moving_rule, config->watson_init_pos, map, config->watson_init_hp, config->watson_init_exp);
    criminal = new Criminal(2, config->criminal_init_pos, map, sherlock, watson);

    // Create array of moving objects
    arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);

    // Add characters to array of moving objects
    arr_mv_objs->add(sherlock);
    arr_mv_objs->add(watson);
    arr_mv_objs->add(criminal);
}

StudyPinkProgram::~StudyPinkProgram() {
    // Free dynamically allocated memory
    delete config;
    delete map;
    delete arr_mv_objs;
    delete sherlock;
    delete watson;
    delete criminal;
}


bool StudyPinkProgram::isStop() const {
    // Check if any of the stop conditions are met
    if (sherlock->getHp() <= 0 || watson->getHp() <= 0 ||
        sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(), criminal->getCurrentPosition().getCol()) ||
        watson->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(), criminal->getCurrentPosition().getCol())) {
        return true; // Stop condition is met
    }
    return false; // Stop condition is not met
}


#include <cstdlib>
#include <filesystem>

using namespace std;

#ifdef _WIN32
const std::string path_separator = "\\";
#else
const std::string path_separator = "/";
#endif

#ifdef _WIN32
const std::string open_cmd = "start";
#elif __APPLE__
const std::string open_cmd = "open";
#else
const std::string open_cmd = "xdg-open";
#endif

// Sử dụng hàm compareFiles để so sánh 2 file
bool compareFiles(const string &p1, const string &p2)
{
    ifstream f1(p1, ifstream::binary | ifstream::ate);
    ifstream f2(p2, ifstream::binary | ifstream::ate);

    if (f1.fail() || f2.fail())
    {
        return false; // file problem
    }

    if (f1.tellg() != f2.tellg())
    {
        return false; // size mismatch
    }

    // seek back to beginning and use equal to compare contents
    f1.seekg(0, ifstream::beg);
    f2.seekg(0, ifstream::beg);
    return equal(istreambuf_iterator<char>(f1.rdbuf()),
                 istreambuf_iterator<char>(),
                 istreambuf_iterator<char>(f2.rdbuf()));
}

// Sử dụng hàm printFile để in nội dung file ra màn hình
void printFile(const string &p1)
{
    ifstream f1(p1);
    string line;
    while (getline(f1, line))
    {
        std::cout << line << endl;
    }
}

// Hàm clearScreen dùng để xóa màn hình console
void clearScreen()
{
#ifdef _WIN32
    string clear_command = "cls";
#else
    string clear_command = "printf '\\33c\\e[3J'";
#endif
    system(clear_command.c_str());
}

// Ham stringToItemType chuyen string thanh BaseItem
BaseItem *stringtoItem(string input)
{
    if (input == "MAGIC_BOOK")
        return new MagicBook();
    else if (input == "ENERGY_DRINK")
        return new EnergyDrink();
    else if (input == "FIRST_AID")
        return new FirstAid;
    else if (input == "EXCEMPTION_CARD")
        return new ExcemptionCard();
    else
        return new PassingCard("all");
}

// Ham stringToItemType chuyen string thanh ItemType
ItemType stringtoItemType(string input)
{
    if (input == "MAGIC_BOOK")
        return MAGIC_BOOK;
    else if (input == "ENERGY_DRINK")
        return ENERGY_DRINK;
    else if (input == "FIRST_AID")
        return FIRST_AID;
    else if (input == "EXCEMPTION_CARD")
        return EXCEMPTION_CARD;
    else
        return PASSING_CARD;
}

class TestStudyInPink
{
public:
    static void check_01(string input_file, string output_file)
    {
        ifstream infile(input_file); // Mở file

        int num_steps;
        int in_num_rows;
        int in_num_cols;
        int num_walls;
        int num_fake_walls;
        string moving_rules;
        Position init_pos;

        infile >> num_steps;
        infile >> in_num_rows;
        infile >> in_num_cols;
        infile >> num_walls;
        infile >> num_fake_walls;
        infile >> moving_rules;

        Position *arr_walls = new Position[num_walls];
        Position *arr_fake_walls = new Position[num_fake_walls];

        string temp_pos;
        int wall_idx = 0, fake_wall_idx = 0;
        while (infile >> temp_pos)
        {
            if (wall_idx < num_walls)
            {
                arr_walls[wall_idx] = Position(temp_pos);
                wall_idx++;
            }
            else if (fake_wall_idx < num_fake_walls)
            {
                arr_fake_walls[fake_wall_idx] = Position(temp_pos);
                fake_wall_idx++;
            }
            else
            {
                init_pos = Position(temp_pos);
                break;
            }
        }

        Map *map = new Map(in_num_rows, in_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        Sherlock *sherlock = new Sherlock(1, moving_rules, init_pos, map, 100, 100);
        infile.close();

        ArrayMovingObject *arr_moving_obj = new ArrayMovingObject(10);
        arr_moving_obj->add(sherlock);

        ofstream outfile(output_file);
        outfile << sherlock->str() << endl;

        for (int i = 0; i < num_steps; i++)
        {
            outfile << "STEP" << i + 1 << ": * Sherlock makes a move" << endl;
            sherlock->move();
            outfile << arr_moving_obj->str() << endl;
        }
        outfile << "End." << endl;
        outfile.close();
        delete arr_moving_obj;
        delete sherlock;
        delete[] arr_walls;
        delete[] arr_fake_walls;
        delete map;
    }
    static void check_02(string input_file, string output_file)
    {
        ifstream infile(input_file); // Mở file

        int num_steps;
        int in_num_rows;
        int in_num_cols;
        int num_walls;
        int num_fake_walls;
        string moving_rules;
        Position init_pos;

        infile >> num_steps;
        infile >> in_num_rows;
        infile >> in_num_cols;
        infile >> num_walls;
        infile >> num_fake_walls;
        infile >> moving_rules;

        Position *arr_walls = new Position[num_walls];
        Position *arr_fake_walls = new Position[num_fake_walls];

        string temp_pos;
        int wall_idx = 0, fake_wall_idx = 0;
        while (infile >> temp_pos)
        {
            if (wall_idx < num_walls)
            {
                arr_walls[wall_idx] = Position(temp_pos);
                wall_idx++;
            }
            else if (fake_wall_idx < num_fake_walls)
            {
                arr_fake_walls[fake_wall_idx] = Position(temp_pos);
                fake_wall_idx++;
            }
            else
            {
                init_pos = Position(temp_pos);
                break;
            }
        }

        Map *map = new Map(in_num_rows, in_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        Watson *watson = new Watson(0, moving_rules, init_pos, map, 100, 100);
        infile.close();

        ArrayMovingObject *arr_moving_obj = new ArrayMovingObject(10);
        arr_moving_obj->add(watson);

        ofstream outfile(output_file);
        outfile << watson->str() << endl;
        for (int i = 0; i < num_steps; i++)
        {
            outfile << "STEP" << i + 1 << ": * Watson makes a move" << endl;
            watson->move();
            outfile << arr_moving_obj->str() << endl;
        }
        outfile << "End." << endl;
        outfile.close();
        delete arr_moving_obj;
        delete watson;
        delete[] arr_walls;
        delete[] arr_fake_walls;
        delete map;
    }
    static void check_03(string input_file, string output_file)
    {
        ifstream infile(input_file); // Mở file

        int num_steps;
        int in_num_rows;
        int in_num_cols;
        int num_walls;
        int num_fake_walls;
        string moving_rules_sher;
        string moving_rules_wat;
        Position init_pos_sher;
        Position init_pos_watson;
        Position init_pos_criminal;

        infile >> num_steps;
        infile >> in_num_rows;
        infile >> in_num_cols;
        infile >> num_walls;
        infile >> num_fake_walls;
        infile >> moving_rules_sher;
        infile >> moving_rules_wat;

        Position *arr_walls = new Position[num_walls];
        Position *arr_fake_walls = new Position[num_fake_walls];

        string temp_pos;
        int wall_idx = 0, fake_wall_idx = 0;
        int index_object = 0;
        while (infile >> temp_pos)
        {
            if (wall_idx < num_walls)
            {
                arr_walls[wall_idx] = Position(temp_pos);
                wall_idx++;
            }
            else if (fake_wall_idx < num_fake_walls)
            {
                arr_fake_walls[fake_wall_idx] = Position(temp_pos);
                fake_wall_idx++;
            }
            else
            {
                if (index_object == 0)
                {
                    init_pos_sher = Position(temp_pos);
                }
                else if (index_object == 1)
                {
                    init_pos_watson = Position(temp_pos);
                }
                else
                {
                    init_pos_criminal = Position(temp_pos);
                    break;
                }
                index_object++;
            }
        }

        Map *map = new Map(in_num_rows, in_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        Watson *watson = new Watson(2, moving_rules_sher, init_pos_watson, map, 100, 100);
        Sherlock *sherlock = new Sherlock(1, moving_rules_wat, init_pos_sher, map, 100, 100);
        Criminal *criminal = new Criminal(0, init_pos_criminal, map, sherlock, watson);
        infile.close();

        ArrayMovingObject *arr_moving_obj = new ArrayMovingObject(10);
        arr_moving_obj->add(sherlock);
        arr_moving_obj->add(watson);
        arr_moving_obj->add(criminal);

        ofstream outfile(output_file);
        outfile << sherlock->str() << endl;
        outfile << watson->str() << endl;
        outfile << criminal->str() << endl;
        for (int i = 0; i < num_steps; i++)
        {
            outfile << "STEP" << i + 1 << ": * Sherlock, Watson, Criminal makes a move" << endl;
            sherlock->move();
            watson->move();
            criminal->move();
            outfile << arr_moving_obj->str() << endl;
        }
        outfile << "End." << endl;
        outfile.close();

        delete sherlock;
        delete watson;
        delete criminal;
        delete arr_moving_obj;
        delete[] arr_walls;
        delete[] arr_fake_walls;
        delete map;
    }
    static void check_04(string input_file, string output_file)
    {
        Configuration *config = new Configuration(input_file);
        ofstream outfile(output_file);
        outfile << config->str() << endl;
        outfile << "End." << endl;
        outfile.close();
        delete config;
    }
    static void check_05(string input_file, string output_file)
    {
        ifstream infile(input_file); // Mở file

        int num_steps;
        int in_num_rows;
        int in_num_cols;
        int num_walls;
        int num_fake_walls;
        string moving_rules_sher;
        string moving_rules_wat;
        Position init_pos_sher;
        Position init_pos_watson;
        Position init_pos_criminal;

        infile >> num_steps;
        infile >> in_num_rows;
        infile >> in_num_cols;
        infile >> num_walls;
        infile >> num_fake_walls;
        infile >> moving_rules_sher;
        infile >> moving_rules_wat;

        Position *arr_walls = new Position[num_walls];
        Position *arr_fake_walls = new Position[num_fake_walls];

        string temp_pos;
        int wall_idx = 0, fake_wall_idx = 0;
        int index_object = 0;
        while (infile >> temp_pos)
        {
            if (wall_idx < num_walls)
            {
                arr_walls[wall_idx] = Position(temp_pos);
                wall_idx++;
            }
            else if (fake_wall_idx < num_fake_walls)
            {
                arr_fake_walls[fake_wall_idx] = Position(temp_pos);
                fake_wall_idx++;
            }
            else
            {
                if (index_object == 0)
                {
                    init_pos_sher = Position(temp_pos);
                }
                else if (index_object == 1)
                {
                    init_pos_watson = Position(temp_pos);
                }
                else
                {
                    init_pos_criminal = Position(temp_pos);
                    break;
                }
                index_object++;
            }
        }

        Map *map = new Map(in_num_rows, in_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        Watson *watson = new Watson(2, moving_rules_sher, init_pos_watson, map, 100, 100);
        Sherlock *sherlock = new Sherlock(1, moving_rules_wat, init_pos_sher, map, 100, 100);
        Criminal *criminal = new Criminal(0, init_pos_criminal, map, sherlock, watson);
        infile.close();
        RobotC *robotC = nullptr;

        ArrayMovingObject *arr_moving_obj = new ArrayMovingObject(10);
        arr_moving_obj->add(sherlock);
        arr_moving_obj->add(watson);
        arr_moving_obj->add(criminal);

        ofstream outfile(output_file);
        outfile << sherlock->str() << endl;
        outfile << watson->str() << endl;
        outfile << criminal->str() << endl;
        for (int i = 0; i < num_steps; i++)
        {
            Position temp_pos = criminal->getCurrentPosition();
            outfile << "STEP" << i + 1 << ": * Moving objects make a move" << endl;

            criminal->move();
            sherlock->move();
            watson->move();
            if (robotC != nullptr)
                robotC->move();

            outfile << arr_moving_obj->str() << endl;
            if (i == 3)
            {
                outfile << "* Create new RobotC" << endl;
                robotC = new RobotC(3, temp_pos, map, criminal);
                outfile << robotC->str() << endl;
                arr_moving_obj->add(robotC);
            }
        }
        outfile << "End." << endl;
        outfile.close();

        delete sherlock;
        delete watson;
        delete criminal;

        if (robotC != nullptr)
            delete robotC;

        delete arr_moving_obj;
        delete[] arr_walls;
        delete[] arr_fake_walls;
        delete map;
    }
    static void check_06(string input_file, string output_file)
    {
        ifstream infile(input_file); // Mở file

        int num_steps;
        int in_num_rows;
        int in_num_cols;
        int num_walls;
        int num_fake_walls;
        string moving_rules_sher;
        string moving_rules_wat;
        Position init_pos_sher;
        Position init_pos_watson;
        Position init_pos_criminal;

        infile >> num_steps;
        infile >> in_num_rows;
        infile >> in_num_cols;
        infile >> num_walls;
        infile >> num_fake_walls;
        infile >> moving_rules_sher;
        infile >> moving_rules_wat;

        Position *arr_walls = new Position[num_walls];
        Position *arr_fake_walls = new Position[num_fake_walls];

        string temp_pos;
        int wall_idx = 0, fake_wall_idx = 0;
        int index_object = 0;
        while (infile >> temp_pos)
        {
            if (wall_idx < num_walls)
            {
                arr_walls[wall_idx] = Position(temp_pos);
                wall_idx++;
            }
            else if (fake_wall_idx < num_fake_walls)
            {
                arr_fake_walls[fake_wall_idx] = Position(temp_pos);
                fake_wall_idx++;
            }
            else
            {
                if (index_object == 0)
                {
                    init_pos_sher = Position(temp_pos);
                }
                else if (index_object == 1)
                {
                    init_pos_watson = Position(temp_pos);
                }
                else
                {
                    init_pos_criminal = Position(temp_pos);
                    break;
                }
                index_object++;
            }
        }

        Map *map = new Map(in_num_rows, in_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        Watson *watson = new Watson(2, moving_rules_sher, init_pos_watson, map, 100, 100);
        Sherlock *sherlock = new Sherlock(1, moving_rules_wat, init_pos_sher, map, 100, 100);
        Criminal *criminal = new Criminal(0, init_pos_criminal, map, sherlock, watson);
        infile.close();
        RobotS *robotS = nullptr;

        ArrayMovingObject *arr_moving_obj = new ArrayMovingObject(10);
        arr_moving_obj->add(sherlock);
        arr_moving_obj->add(watson);
        arr_moving_obj->add(criminal);

        ofstream outfile(output_file);
        outfile << sherlock->str() << endl;
        outfile << watson->str() << endl;
        outfile << criminal->str() << endl;
        for (int i = 0; i < num_steps; i++)
        {
            Position temp_pos = criminal->getCurrentPosition();
            outfile << "STEP" << i + 1 << ": * Moving objects make a move" << endl;

            criminal->move();
            sherlock->move();
            watson->move();
            if (robotS != nullptr)
                robotS->move();

            outfile << arr_moving_obj->str() << endl;
            if (i == 6)
            {
                outfile << "* Create new RobotS" << endl;
                robotS = new RobotS(4, temp_pos, map, criminal, sherlock);
                outfile << robotS->str() << endl;
                arr_moving_obj->add(robotS);
            }
        }
        outfile << "End." << endl;
        outfile.close();

        delete sherlock;
        delete watson;
        delete criminal;

        if (robotS != nullptr)
            delete robotS;

        delete arr_moving_obj;
        delete[] arr_walls;
        delete[] arr_fake_walls;
        delete map;
    }
    static void check_07(string input_file, string output_file)
    {
        ifstream infile(input_file); // Mở file

        int num_steps;
        int in_num_rows;
        int in_num_cols;
        int num_walls;
        int num_fake_walls;
        string moving_rules_sher;
        string moving_rules_wat;
        Position init_pos_sher;
        Position init_pos_watson;
        Position init_pos_criminal;

        infile >> num_steps;
        infile >> in_num_rows;
        infile >> in_num_cols;
        infile >> num_walls;
        infile >> num_fake_walls;
        infile >> moving_rules_sher;
        infile >> moving_rules_wat;

        Position *arr_walls = new Position[num_walls];
        Position *arr_fake_walls = new Position[num_fake_walls];

        string temp_pos;
        int wall_idx = 0, fake_wall_idx = 0;
        int index_object = 0;
        while (infile >> temp_pos)
        {
            if (wall_idx < num_walls)
            {
                arr_walls[wall_idx] = Position(temp_pos);
                wall_idx++;
            }
            else if (fake_wall_idx < num_fake_walls)
            {
                arr_fake_walls[fake_wall_idx] = Position(temp_pos);
                fake_wall_idx++;
            }
            else
            {
                if (index_object == 0)
                {
                    init_pos_sher = Position(temp_pos);
                }
                else if (index_object == 1)
                {
                    init_pos_watson = Position(temp_pos);
                }
                else
                {
                    init_pos_criminal = Position(temp_pos);
                    break;
                }
                index_object++;
            }
        }

        Map *map = new Map(in_num_rows, in_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        Watson *watson = new Watson(2, moving_rules_sher, init_pos_watson, map, 100, 100);
        Sherlock *sherlock = new Sherlock(1, moving_rules_wat, init_pos_sher, map, 100, 100);
        Criminal *criminal = new Criminal(0, init_pos_criminal, map, sherlock, watson);
        infile.close();
        RobotW *robotW = nullptr;

        ArrayMovingObject *arr_moving_obj = new ArrayMovingObject(10);
        arr_moving_obj->add(sherlock);
        arr_moving_obj->add(watson);
        arr_moving_obj->add(criminal);

        ofstream outfile(output_file);
        outfile << sherlock->str() << endl;
        outfile << watson->str() << endl;
        outfile << criminal->str() << endl;
        for (int i = 0; i < num_steps; i++)
        {
            Position temp_pos = criminal->getCurrentPosition();
            outfile << "STEP" << i + 1 << ": * Moving objects make a move" << endl;

            criminal->move();
            sherlock->move();
            watson->move();
            if (robotW != nullptr)
                robotW->move();

            outfile << arr_moving_obj->str() << endl;
            if (i == 9)
            {
                outfile << "* Create new RobotW" << endl;
                robotW = new RobotW(5, temp_pos, map, criminal, watson);
                outfile << robotW->str() << endl;
                arr_moving_obj->add(robotW);
            }
        }
        outfile << "End." << endl;
        outfile.close();

        delete sherlock;
        delete watson;
        delete criminal;

        if (robotW != nullptr)
            delete robotW;

        delete arr_moving_obj;
        delete[] arr_walls;
        delete[] arr_fake_walls;
        delete map;
    }
    static void check_08(string input_file, string output_file)
    {
        ifstream infile(input_file); // Mở file

        int num_steps;
        int in_num_rows;
        int in_num_cols;
        int num_walls;
        int num_fake_walls;
        string moving_rules_sher;
        string moving_rules_wat;
        Position init_pos_sher;
        Position init_pos_watson;
        Position init_pos_criminal;

        infile >> num_steps;
        infile >> in_num_rows;
        infile >> in_num_cols;
        infile >> num_walls;
        infile >> num_fake_walls;
        infile >> moving_rules_sher;
        infile >> moving_rules_wat;

        Position *arr_walls = new Position[num_walls];
        Position *arr_fake_walls = new Position[num_fake_walls];

        string temp_pos;
        int wall_idx = 0, fake_wall_idx = 0;
        int index_object = 0;
        while (infile >> temp_pos)
        {
            if (wall_idx < num_walls)
            {
                arr_walls[wall_idx] = Position(temp_pos);
                wall_idx++;
            }
            else if (fake_wall_idx < num_fake_walls)
            {
                arr_fake_walls[fake_wall_idx] = Position(temp_pos);
                fake_wall_idx++;
            }
            else
            {
                if (index_object == 0)
                {
                    init_pos_sher = Position(temp_pos);
                }
                else if (index_object == 1)
                {
                    init_pos_watson = Position(temp_pos);
                }
                else
                {
                    init_pos_criminal = Position(temp_pos);
                    break;
                }
                index_object++;
            }
        }

        Map *map = new Map(in_num_rows, in_num_cols, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        Watson *watson = new Watson(2, moving_rules_sher, init_pos_watson, map, 100, 100);
        Sherlock *sherlock = new Sherlock(1, moving_rules_wat, init_pos_sher, map, 100, 100);
        Criminal *criminal = new Criminal(0, init_pos_criminal, map, sherlock, watson);
        infile.close();
        RobotSW *robotSW = nullptr;

        ArrayMovingObject *arr_moving_obj = new ArrayMovingObject(10);
        arr_moving_obj->add(sherlock);
        arr_moving_obj->add(watson);
        arr_moving_obj->add(criminal);

        ofstream outfile(output_file);
        outfile << sherlock->str() << endl;
        outfile << watson->str() << endl;
        outfile << criminal->str() << endl;
        for (int i = 0; i < num_steps; i++)
        {
            Position temp_pos = criminal->getCurrentPosition();
            outfile << "STEP" << i + 1 << ": * Moving objects make a move" << endl;

            criminal->move();
            sherlock->move();
            watson->move();
            if (robotSW != nullptr)
                robotSW->move();

            outfile << arr_moving_obj->str() << endl;
            if (i == 12)
            {
                outfile << "* Create new RobotWS" << endl;
                robotSW = new RobotSW(6, temp_pos, map, criminal, sherlock, watson);
                outfile << robotSW->str() << endl;
                arr_moving_obj->add(robotSW);
            }
        }
        outfile << "End." << endl;
        outfile.close();

        delete sherlock;
        delete watson;
        delete criminal;

        if (robotSW != nullptr)
            delete robotSW;

        delete arr_moving_obj;
        delete[] arr_walls;
        delete[] arr_fake_walls;
        delete map;
    }
    static void check_09(string input_file, string output_file)
    {
        int num_walls = 3;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
        int num_fake_walls = 1;
        Position arr_fake_walls[] = {Position(2, 0)};
        Map *map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        ifstream infile(input_file); // Mở file
        ofstream outfile(output_file);

        int hp_sher;
        int hp_wat;
        int exp_sher;
        int exp_wat;
        vector<BaseItem *> items;

        infile >> hp_sher;
        infile >> hp_wat;
        infile >> exp_sher;
        infile >> exp_wat;

        Sherlock *sherlock = new Sherlock(0, "RL", Position(1, 3), map, hp_sher, exp_sher);
        outfile << sherlock->str() << " HP: " << hp_sher << " EXP: " << exp_sher << endl;
        Watson *watson = new Watson(1, "UD", Position(2, 1), map, hp_wat, exp_wat);
        outfile << watson->str() << " HP: " << hp_wat << " EXP: " << exp_wat << endl;

        BaseBag *sher_bag = new SherlockBag(sherlock);
        outfile << sher_bag->str() << endl;
        BaseBag *wat_bag = new WatsonBag(watson);
        outfile << wat_bag->str() << endl;
        int numline = 3;
        string line;

        while (getline(infile, line))
        {
            numline++;
            istringstream iss(line);
            string command;
            iss >> command;

            if (command == "INSERT")
            {
                string input;
                iss >> input;
                outfile << "LINE " << numline << ": * Insert " << input << " into bag" << endl;
                BaseItem *tempitem = stringtoItem(input);
                items.push_back(tempitem);
                sher_bag->insert(tempitem);
                wat_bag->insert(tempitem);
                outfile << "SherlockBag: " << sher_bag->str() << endl;
                outfile << "WatsonBag " << wat_bag->str() << endl;
            }
            else if (command == "GET")
            {
                string input;
                iss >> input;
                outfile << "LINE " << numline << ": * Get " << input << " from bag" << endl;
                if (input.empty())
                {
                    sher_bag->get();
                    wat_bag->get();
                }
                else
                {
                    sher_bag->get(stringtoItemType(input));
                    wat_bag->get(stringtoItemType(input));
                }
                outfile << "SherlockBag: " << sher_bag->str() << endl;
                outfile << "WatsonBag " << wat_bag->str() << endl;
            }
        }
        infile.close();
        outfile << "End." << endl;
        outfile.close();

        delete sherlock;
        delete watson;
        delete sher_bag;
        delete wat_bag;
        delete map;
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i] != nullptr)
                delete items[i];
        }
    }
    static void check_10(string input_file, string output_file)
    {
        StudyPinkProgram *program = new StudyPinkProgram(input_file);
        // Lưu lại buffer std::cout cũ
        streambuf *oldcoutStreamBuf = std::cout.rdbuf();

        // Mở file output và liên kết nó với std::cout
        ofstream ofs(output_file);
        std::cout.rdbuf(ofs.rdbuf());
        // Chạy hàm, output sẽ được ghi vào file
        program->run(true);
        std::cout << "End." << endl;
        // Khôi phục lại std::cout về buffer cũ
        std::cout.rdbuf(oldcoutStreamBuf);
    }
};

void printResult(string input_folder)
{

    std::cout << "Enter start input (0 - 499): ";
    int start_input = 0;
    // std::cin >> start_input;
    std::cout << "Enter end input (0 - 499): ";
    int end_input = 499;
    // std::cin >> end_input;

    std::string command = "mkdir -p testcase" + path_separator + input_folder + path_separator + "output";
    system(command.c_str());

    for (int i = start_input; i <= end_input; ++i)
    {
        clearScreen();
        std::cout << "Checking " << input_folder << " - Testcase: " << i << endl;
        string input_file = "testcase/" + input_folder + "/input/input" + to_string(i) + ".txt";
        string output_file = "testcase/" + input_folder + "/output/output" + to_string(i) + ".txt";
        string expect_file = "testcase/" + input_folder + "/expect/output" + to_string(i) + ".txt";

        if (input_folder == "Sherlock_move")
        {
            TestStudyInPink::check_01(input_file, output_file);
        }
        else if (input_folder == "Watson_move")
        {
            TestStudyInPink::check_02(input_file, output_file);
        }
        else if (input_folder == "Criminal_move")
        {
            TestStudyInPink::check_03(input_file, output_file);
        }
        else if (input_folder == "Configuration")
        {
            TestStudyInPink::check_04(input_file, output_file);
        }
        else if (input_folder == "RobotC_move")
        {
            TestStudyInPink::check_05(input_file, output_file);
        }
        else if (input_folder == "RobotS_move")
        {
            TestStudyInPink::check_06(input_file, output_file);
        }
        else if (input_folder == "RobotW_move")
        {
            TestStudyInPink::check_07(input_file, output_file);
        }
        else if (input_folder == "RobotSW_move")
        {
            TestStudyInPink::check_08(input_file, output_file);
        }
        else if (input_folder == "BaseBag")
        {
            TestStudyInPink::check_09(input_file, output_file);
        }
        else if (input_folder == "StudyPinkProgram")
        {
            TestStudyInPink::check_10(input_file, output_file);
        }

        if (!compareFiles(output_file, expect_file))
        {
            clearScreen();
            std::cout << "Test case " << i << " failed" << endl;
            std::cout << "Input file: " << input_file << endl;
            std::cout << "-------------------------------" << endl;
            std::cout << "Your output: " << output_file << endl;
            std::cout << "-------------------------------" << endl;
            std::cout << "Expected output: " << expect_file << endl;
            std::cout << "-------------------------------" << endl;
            std::cout << "Structure of input file: " << endl;
            printFile("testcase/" + input_folder + "/readme.txt");
            break;
        }
        if (i == 499)
        {
            clearScreen();
            std::cout << "All test cases passed" << endl;
            std::string command = "rmdir /S /Q testcase" + path_separator + input_folder + path_separator + "output";
            system(command.c_str());
        }
    }
}

// Hàm main dùng để chạy chương trình
int main()
{
    while (true)
    {
        clearScreen();
        int choice;
        // std::cout << "1. Check Sherlock's movement" << endl;
        // std::cout << "2. Check Waison's movement" << endl;
        // std::cout << "3. Check Sherlock, Watson, Criminal's movement. Not create robot" << endl;
        // //std::cout << "Hello World" << endl;
        // std::cout << "4. Check Configuration" << endl;
        // std::cout << "5. Check RobotC's movement" << endl;
        // std::cout << "6. Check RobotS's movement" << endl;
        // std::cout << "7. Check RobotW's movement" << endl;
        // std::cout << "8. Check RobotSW's movement" << endl;
        // std::cout << "9. Check BaseBag" << endl;
        // std::cout << "10. Check StudyPinkProgram" << endl;
        // std::cout << "11. FULL SAMPLE CODE" << endl;
        // std::cout << "========================================" << endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        clearScreen();

        switch (choice)
        {
        case 1:
        {
            printResult("Sherlock_move");
            break;
        }
        case 2:
        {
            printResult("Watson_move");
            break;
        }
        case 3:
        {
            printResult("Criminal_move");
            break;
        }
        case 4:
        {
            printResult("Configuration");
            break;
        }
        case 5:
        {
            printResult("RobotC_move");
            break;
        }
        case 6:
        {
            printResult("RobotS_move");
            break;
        }
        case 7:
        {
            printResult("RobotW_move");
            break;
        }
        case 8:
        {
            printResult("RobotSW_move");
            break;
        }
        case 9:
        {
            printResult("BaseBag");
            break;
        }
        case 10:
        {
            printResult("StudyPinkProgram");
            break;
        }
        case 11:
        {
            clearScreen();
            std::cout << "Inbox to get full sample code" << endl;
            std::string url = "https://m.me/quocanhcse";
            std::string cmd = open_cmd + " " + url;
            system(cmd.c_str());
            break;
        }
        }
        std::cout << "========================================" << endl;
        std::cout << "Press 0 to exit, 1 to continue: ";
        std::cin >> choice;
        if (choice == 0)
        {
            break;
        }
    }
    return 0;
}
