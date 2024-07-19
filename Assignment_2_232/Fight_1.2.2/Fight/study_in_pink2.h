#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

//static ofstream OUTPUT;

class MovingObject;
class Position;
class Configuration;
class Map;



// class Criminal;
// class RobotS;
// class RobotW;
// class RobotSW;
// class RobotC;

class ArrayMovingObject;
class StudyPinkProgram;

class BaseItem;
class BaseBag;
class SherlockBag;
class WatsonBag;
class Character;

// class MagicBook;
// class EnergyDrink;
// class FirstAid;
// class ExcemptionCard;
// class PassingCard;

class Robot;
class RobotS;
class RobotW;
class RobotSW;
class RobotC;
class BaseBag;
class BaseItem;
class MagicBook;
class ExcemptionCard;
class EnergyDrink;
class PassingCard;
class FirstAid;
class Watson;
class MapElement;

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
    virtual int getReqExp() const=0;
};

class Path : public MapElement {
    public:
        Path();
        int getReqExp() const{
            return 0;
        }
};

class Wall : public MapElement {
    public:
        Wall();
        int getReqExp() const{
            return 0;
        }
};

class FakeWall : public MapElement {
    private:
        int req_exp;
    public:
        FakeWall(int req_exp);
        int getReqExp() const override{
            return req_exp;
        }
};

class Map {
private:
    int num_rows, num_cols;
    MapElement*** map;

public:
    Map(int num_rows, int num_cols, int num_walls, Position *array_walls, int num_fake_walls, Position *array_fake_walls);
    MapElement*** getMap(){
        return map;
    }
    ~Map();
    int getNumRows() const {
        return num_rows;
    }
    int getNumCols() const {
        return num_cols;
    }

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
    virtual int getExp()=0;
    virtual int getHp()=0;
    int getindex(){
        return index;
    }
    string getName(){
        return name;
    }
    virtual bool meet(MovingObject * obj){
        cout << "MovingObject meet" << endl;
        return false;
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
    SherlockBag * sherlockBag;
    int next_char_index;
public:
    Sherlock(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    string str() override;
    Position getNextPosition() override;
    void move() override;
    SherlockBag* getBag(){
        return sherlockBag;
    }
    bool meet(RobotS *robotS);
    bool meet(RobotW *robotW);
    bool meet(RobotSW *robotSW);
    bool meet(RobotC *robotC);
    bool meet(Watson *watson);
    
};
 
class Watson :public Character {
private:
    // TODO
    string moving_rule;
    WatsonBag * watsonBag;
    int next_char_index;
public:
    
    Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp);
    string str() override;
    Position getNextPosition() override;
    void move() override;
    int getExp();
    bool meet(RobotS *robotS);
    bool meet(RobotW *robotW);
    bool meet(RobotSW *robotSW);
    bool meet(RobotC *robotC);
    bool meet(Sherlock *sherlock);
    WatsonBag* getBag(){
        return watsonBag;
    }
    
    // ...
};

class Criminal : public Character{
private:
    Sherlock *sherlock;
    Watson *watson;
    Position prev_pos;
    int count;
public:
    Criminal(int index, const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson);
    string str() override;
    Position getNextPosition() override;
    void move() override;
    Position getPrevPosition(){
        return prev_pos;
    }
    int getCount(){
        return count;
    }
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
    bool checkMeet(int index);
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
    Configuration(const string  filepath);
    ~Configuration();
    string str() const;


};





// Robot, BaseItem, BaseBag,...
class Robot : public MovingObject {
protected:
    RobotType robot_type;
    BaseItem* item; // Item obtained upon defeating the robot
    //static inline int first_created = 0;
public:
    
    Robot(RobotType type, int index, const Position& init_pos, Map* map,string name);

    int calculateManhattanDistance(Position pos1, Position pos2) {
        int col_diff = abs(pos1.getCol() - pos2.getCol());
        int row_diff = abs(pos1.getRow() - pos2.getRow());
        return col_diff + row_diff;
}
    // bool getFirstCreated(){
    //     return first_created;
    // }
    // Method to add the robot to the ArrayMovingObject
    bool addToMovingObjects(ArrayMovingObject& moving_objects) {
        if (!moving_objects.isFull()) {
            moving_objects.add(this);
            return true;
        }
        return false;
    }

    int getHp(){
        return 0;
    }
    int getExp(){
        return 0;
    }

    RobotType getRobotType(){
        return robot_type;
    }

    BaseItem* getItem(){
        return item;
    }

    // Add other methods as needed
    static Robot *create(int index, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson);
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
        ItemNode * getHead(){
            return head;
        }
        bool insert ( BaseItem * item ) override;
        BaseItem * get() override;
        BaseItem * get( ItemType itemType ) override;
        string str () const override;
        BaseItem* useAvailableItem();
        ItemNode* deleteItem(ItemType itemType){
            ItemNode * current = head;
            ItemNode * prev = nullptr;
            int countdelete = 0;
            ItemNode * gift = nullptr;
            while(current != nullptr){
                if(current->item->getType() == itemType){
                    if(prev == nullptr){
                        head = current->next;
                        current->next = nullptr;
                    }else{
                        prev->next = current->next;
                        current->next = nullptr;
                    }
                    if(gift == nullptr){
                        gift = current;
                    }else{
                        ItemNode * temp = gift;
                        while (temp->next != nullptr)
                        {
                            temp = temp->next;
                        }
                        temp->next = current;

                    }   
                    //delete current;
                    //countdelete++;
                    count--;
                }
                prev = current;
                current = current->next;
            }
            return gift;
        }
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
        int deleteItem(ItemType itemType){
            ItemNode * current = head;
            ItemNode * prev = nullptr;
            int countdelete = 0;
            while(current != nullptr){
                if(current->item->getType() == itemType){
                    if(prev == nullptr){
                        head = current->next;
                    }else{
                        prev->next = current->next;
                        current = prev;
                    }
                    //delete current;
                    countdelete++;
                    count--;
                }
                prev = current;
                current = current->next;
            }
            return countdelete;
        }
        ItemNode* getHead(){
            return head;
        }
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
    void printMap(ofstream &OUTPUT) const;

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
        bool stop = arr_mv_objs->checkMeet(0) || sherlock->getHp() == 0 || watson->getHp() == 0;
        for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                if (stop)
                break;


                MovingObject *robot = nullptr;
                if (arr_mv_objs->get(i)->getName() == "Criminal")
                {
                    robot = Robot::create(arr_mv_objs->size(), map, criminal, sherlock, watson);
                }
                arr_mv_objs->get(i)->move();
                if(arr_mv_objs->get(i)->getName() == "Criminal"){
                for (int i = 0; i < arr_mv_objs->size(); i++)
                {
                    if(arr_mv_objs->get(i)->getName()=="RobotC"){
                        arr_mv_objs->get(i)->move();
                    }
                }
                
            }
                if(robot != nullptr){
                    if (criminal->getCount() % 3 == 0 && criminal->getCount() > 0)
                    {
                        arr_mv_objs->add(robot);
                    }
                    else
                    {
                        delete robot;
                    }
                }
                stop = arr_mv_objs->checkMeet(i);
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

    void run(ofstream &OUTPUT){
        if (!OUTPUT.is_open())
    {
        return;
    }
    bool stop = arr_mv_objs->checkMeet(0) || sherlock->getHp() == 0 || watson->getHp() == 0;
    OUTPUT << config->str() << endl;
    for (int istep = 0; istep < config->num_steps && !stop; ++istep)
    {
        for (int i = 0; i < arr_mv_objs->size() && !stop; ++i)
        {

            if (stop)
                break;
            OUTPUT << endl
                   << "*********************************************************" << endl;
            OUTPUT << "ROUND : " << istep << " - TURN : " << i << endl;

            MovingObject *robot = nullptr;
            if (arr_mv_objs->get(i)->getName() == "Criminal")
            {
                robot = Robot::create(arr_mv_objs->size(), map, criminal, sherlock, watson);
            }
            //OUTPUT << arr_mv_objs->get(i)->getName() <<" to ";
            arr_mv_objs->get(i)->move();
            if(arr_mv_objs->get(i)->getName() == "Criminal"){
                for (int i = 0; i < arr_mv_objs->size(); i++)
                {
                    if(arr_mv_objs->get(i)->getName()=="RobotC"){
                        arr_mv_objs->get(i)->move();
                    }
                }
                
            }
            //OUTPUT <<arr_mv_objs->get(i)->getCurrentPosition().str() << endl;
            if (robot != nullptr)
            {
                if (criminal->getCount() % 3 == 0 && criminal->getCount() > 0)
                {
                    //OUTPUT << "Robot added to the moving objects list" << endl;
                    //OUTPUT <<"Robot Position: " <<robot->getCurrentPosition().str() << endl;
                    //OUTPUT << "Robot type: " << robot->getName() << endl;
                    arr_mv_objs->add(robot);
                }
                else
                {
                    delete robot;
                }
            }
            printMap(OUTPUT);
            stop = arr_mv_objs->checkMeet(i);
            OUTPUT << "---------------" << endl
                   << "LOG : " << endl
                   << arr_mv_objs->str() << endl
                   << "Sherlock HP_" << sherlock->getHp() << " EXP_" << sherlock->getExp() << endl
                   << "Watson HP_" << watson->getHp() << " EXP_" << watson->getExp() << endl
                   << "SherlockBag : " << sherlock->getBag()->str() << endl
                   << "WatsonBag : " << watson->getBag()->str() << endl;
        }
    }
    OUTPUT << "---------------" << endl
           << "RESULT : ";
    if (watson->getHp() == 0)
        OUTPUT << "Watson can not continue the journey";
    else if (sherlock->getHp() == 0)
        OUTPUT << "Sherlock can not continue the journey";
    else if (stop)
        OUTPUT << "The Criminal was caught";
    else
        OUTPUT << "The Criminal escaped";
    }
    ~StudyPinkProgram();
};

#endif /* _H_STUDY_IN_PINK_2_H_ */