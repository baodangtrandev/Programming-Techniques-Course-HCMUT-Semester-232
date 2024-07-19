/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 02.02.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

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
        stringstream ss(line);
        string key;
        ss >> key;
        if (key == "MAP_NUM_ROWS=") {
            ss >> map_num_rows;
        } else if (key == "MAP_NUM_COLS=") {
            ss >> map_num_cols;
        } else if (key == "MAX_NUM_MOVING_OBJECTS=") {
            ss >> max_num_moving_objects;
        } else if (key == "ARRAY_WALLS=") {
            processPositionArray(ss, arr_walls, num_walls);
        } else if (key == "ARRAY_FAKE_WALLS=") {
            processPositionArray(ss, arr_fake_walls, num_fake_walls);
        } else if (key == "SHERLOCK_MOVING_RULE=") {
            ss >> sherlock_moving_rule;
        } else if (key == "SHERLOCK_INIT_POS=") {
            ss >> sherlock_init_pos;
        } else if (key == "SHERLOCK_INIT_HP=") {
            ss >> sherlock_init_hp;
        } else if (key == "SHERLOCK_INIT_EXP=") {
            ss >> sherlock_init_exp;
        } else if (key == "WATSON_MOVING_RULE=") {
            ss >> watson_moving_rule;
        } else if (key == "WATSON_INIT_POS=") {
            ss >> watson_init_pos;
        } else if (key == "WATSON_INIT_HP=") {
            ss >> watson_init_hp;
        } else if (key == "WATSON_INIT_EXP=") {
            ss >> watson_init_exp;
        } else if (key == "CRIMINAL_INIT_POS=") {
            ss >> criminal_init_pos;
        } else if (key == "NUM_STEPS=") {
            ss >> num_steps;
        } else {
            cerr << "Unknown configuration key: " << key << endl;
        }
    }

    void processPositionArray(stringstream &ss, Position *&arr, int &num) {
        string positions;
        ss >> positions;
        positions = positions.substr(1, positions.size() - 2);
        stringstream posStream(positions);
        num = 0;
        int count = 0;
        while (posStream) {
            int row, col;
            char c;
            posStream >> c >> row >> c >> col >> c;
            if (posStream) {
                num++;
            }
        }
        arr = new Position[num];
        posStream.clear();
        posStream.seekg(0);
        while (posStream) {
            int row, col;
            char c;
            posStream >> c >> row >> c >> col >> c;
            if (posStream) {
                arr[count++] = Position(row, col);
            }
        }
    }
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

class ExemptionCard : public BaseItem {
    // Add necessary members here
    private:
    public:
        ExemptionCard(): BaseItem(EXCEMPTION_CARD){};
        bool canUse ( Character * obj , Robot * robot ) override;
        void use( Character * obj , Robot * robot ) override;
};

class PassingCard : public BaseItem {
    // Add necessary members here
    private:
        string challenge;
    public:
        PassingCard(): BaseItem(PASSING_CARD){};
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

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
