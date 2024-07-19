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

// #include "main.h"
#include "main.h"
//#include <std::string>
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
    class Sherlock;
    class Watson;

    class ArrayMovingObject;
    class StudyPinkProgram;

    class BaseItem;
    class BaseBag;
    class SherlockBag;
    class WatsonBag;

    class TestStudyInPink;

enum ItemType { MAGIC_BOOK, ENERGY_DRINK, FIRST_AID, EXCEMPTION_CARD, PASSING_CARD };
enum ElementType { PATH, WALL, FAKE_WALL };
enum RobotType { C=0, S, W, SW };

class MapElement {
protected:
    ElementType type;
public:
    MapElement(ElementType in_type);
    virtual ~MapElement(){}
    virtual ElementType getType() const;
};

class Path : public MapElement {
    public:
        Path();
        ~Path(){}
};

class Wall : public MapElement {
    public:
        Wall();
        ~Wall(){}
};

class FakeWall : public MapElement {
    private:
        int req_exp;
    public:
        FakeWall(int in_req_exp);
        ~FakeWall(){}
        int getReqExp() {
            return this -> req_exp;
        }  
};

class Map {
private:
    int num_rows, num_cols;
    MapElement*** map;

public:
    Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls);
    ~Map();
    bool isValid ( const Position & pos , MovingObject * mv_obj ) const ;
};

class Position {
private:
    int r, c;
public:
    static const Position npos;

    Position(int r=0, int c=0);

    Position(const std::string & str_pos);

    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);

    std::string str() const;

    bool isEqual(int in_r, int in_c) const;
    bool isEqual(Position x) ;
};

class MovingObject {
protected:
    int index;
    Position pos;
    Map * map;
    std::string name;
    int step;
public:
    MovingObject() = default;
    MovingObject(int index, Position pos, Map * map, const std::string & name);
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const;
    virtual void move() = 0;
    virtual std::string str() const = 0;
    std::string getName(){
        return name;
    }
    void setStep(int st){
        this->step = st;
    }
};
class Character : public MovingObject   {
public:
    int HP;
    int EXP;
    Character(int index,const Position &pos, Map * map, const std::string & name, int HP, int EXP):MovingObject(index, pos, map, name)  {
        this->HP = HP;
        this->EXP = EXP;
    }    
    int getHP() {
        return HP;
    }
    int getEXP()  {
        return EXP;
    }
    void setHP(int hp) {
        HP = hp;
    }
    void setEXP(int exp) {
        EXP = exp;
    }
};
class Sherlock : public Character {
private:
    // TODO
    // int HP;
    // int EXP;
    std::string moving_rule;
    int nummov;
    SherlockBag * bag;
public:
    Sherlock(int index, const std::string & moving_rule,const Position & init_pos, Map * map, int init_hp, int init_exp);
    char getMVR(){
        return moving_rule[(nummov++)%moving_rule.size()];
    }
    Position getNextPosition();
    // int getHP() {
    //     return HP;
    // }
    // int getEXP()  {
    //     return EXP;
    // }
    void move();
    std::string str() const override;
    SherlockBag * getBag(){
        return bag;
    }
    bool meet(RobotS *robotS);
    bool meet(RobotW *robotW);
    bool meet(RobotSW *robotSW);
    bool meet(RobotC *robotC);
    bool meet(Watson *watson);
    // ...
};

class Watson : public Character {
private:
    // TODO
    // int HP;
    // int EXP;
    std::string moving_rule;
    int nummov = 0;
    WatsonBag * bag;
public:
    Watson(int index, const std::string & moving_rule,const Position & init_pos, Map * map, int init_hp, int init_exp);
    char getMVR(){
        return moving_rule[(nummov++)%moving_rule.size()];
    }
    Position getNextPosition();
    void move();
    std::string str() const override;
    // int getHP() {
    //     return HP;
    // }
    // int getEXP()  {
    //     return EXP;
    // }
    WatsonBag * getBag(){
        return bag;
    }

    bool meet(RobotS *robotS);
    bool meet(RobotW *robotW);
    bool meet(RobotSW *robotSW);
    bool meet(RobotC *robotC);
    bool meet(Sherlock *sherlock);
    // ...
};

class Criminal : public Character {
private:
    // TODO
    Sherlock * sherlock;
    Watson * watson;
    int stepcount;
    Position preposition;
public:
    Criminal(int index,const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson);
    Position getNextPosition();
    void move();
    std::string str() const override;
    int getstepcount()   {
        return stepcount;
    }
    Position getpreposition()   {
        return preposition;
    }
    // ...
};

class ArrayMovingObject {
private:
    MovingObject** arr_mv_objs;
    int count;
    int capacity;
    /*冰激凌*/
public:
    ArrayMovingObject(int capacity);
    ~ArrayMovingObject() ;
    bool isFull() const;
    bool add(MovingObject * mv_obj);
    MovingObject * get(int index) const;
    int size() const; // return current number of elements in the array
    std::string str() const;
    bool checkMeet(int index);
};

class Configuration
{
    friend class StudyPinkProgram;
    private:
        int map_num_rows, map_num_cols;
        int max_num_moving_objects;
        int num_walls = 0;
        Position* arr_walls;
        int num_fake_walls = 0;
        Position* arr_fake_walls;
        std::string sherlock_moving_rule;
        Position sherlock_init_pos;
        int sherlock_init_hp;
        int sherlock_init_exp;
        std::string watson_moving_rule;
        Position watson_init_pos;
        int watson_init_hp;
        int watson_init_exp;
        Position criminal_init_pos;
        int num_steps; 
    public:
        Configuration(const std::string & filepath);
        ~Configuration();
        std::string str() const;
};

// Robot, BaseItem, BaseBag,...
class Robot : public MovingObject   {

    protected:
        RobotType robot_type;
        BaseItem * item;
    public:
        Robot(int index, const Position &init_pos, Map * map, RobotType robot_type,string name);
        virtual Position getNextPosition() = 0;
        void move();
        virtual std::string str() const{return "";}
        RobotType getType();
        static Robot *create(int index, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson);
        RobotType getRobotType(){
            return robot_type;
        }
        BaseItem* getItem(){
            return this->item;
        }
    
};
class RobotC : public Robot {
    public:
        RobotC(int index, const Position & init_pos,Map * map,Criminal * criminal);
        Position getNextPosition();
        int getDistance(Sherlock * sherlock);
        int getDistance(Watson * watson);
        std::string str() const;
    private:
        Criminal * criminal;
};
class RobotS : public Robot {
    public:
        RobotS(int index, const Position & init_pos,Map * map,Criminal * criminal,Sherlock * sherlock);
        Position getNextPosition();
        int getDistance();
        std::string str() const;
        void move();
    private:
        Criminal * criminal;
        Sherlock * sherlock;
};
class RobotW : public Robot {
    public:
        RobotW( int index,const Position & init_pos,Map * map,Criminal * criminal,Watson * watson);
        Position getNextPosition();
        int getDistance();
        std::string str() const;
        void move();
    private:
        Criminal * criminal;
        Watson * watson;
};
class RobotSW : public Robot {
    public:
        RobotSW( int index,const Position & init_pos,Map * map,Criminal * criminal,Sherlock * sherlock,Watson * watson);
        Position getNextPosition();
        int getDistance();
        std::string str() const;
        void move();
    private:
        Criminal * criminal;
        Sherlock * sherlock;
        Watson * watson;
};
/// class BaseItem
class BaseItem  {
    private:
    ItemType itemtype;
    public:
    virtual bool canUse ( Character * obj , Robot * robot ) = 0;
    virtual void use( Character * obj , Robot * robot ) = 0;
    BaseItem(ItemType itemtype){
        this->itemtype = itemtype;
    }
    ItemType getItem(){
        return itemtype;
    }

    bool insert ( BaseItem * item ); // return true if insert
    BaseItem * get ();
    BaseItem * get( ItemType itemType ); 
    string str () const ;
};
class MagicBook : public BaseItem   {
    public:
    MagicBook(): BaseItem(MAGIC_BOOK){};
    bool canUse (Character * obj, Robot * robot);
    void use (Character * obj, Robot * robot);
};
class EnergyDrink : public BaseItem   {
    public:
    EnergyDrink(): BaseItem(ENERGY_DRINK){};
    bool canUse (Character * obj, Robot * robot) ;
    void use (Character * obj, Robot * robot) ;
};
class FirstAid : public BaseItem   {
    public:
    FirstAid(): BaseItem(FIRST_AID){};
    bool canUse (Character * obj, Robot * robot) ;
    void use (Character * obj, Robot * robot) ;
};
class ExcemptionCard : public BaseItem   {
    public:
    ExcemptionCard(): BaseItem(EXCEMPTION_CARD){};
    bool canUse (Character * obj, Robot * robot) ;
    void use (Character * obj, Robot * robot){
        
    }
};
class PassingCard : public BaseItem   {
    private:
    std::string challenge;
    public:
    PassingCard(std::string challenge): BaseItem(PASSING_CARD),challenge(challenge){};
    bool canUse (Character * obj, Robot * robot) ;
    void use (Character * obj, Robot * robot) ;
};
/// ItemNode
struct NodeItem
{
    BaseItem* item;
    NodeItem* next;
    NodeItem(BaseItem* item){
        this->item = item;
        this->next = nullptr;
    }
};
class BaseBag{
    private:
        NodeItem* head;
        int count;
        int capacity;
    public:
        BaseBag(int capacity);
        Character* character;
        virtual bool insert (BaseItem* item);
        virtual BaseItem* get()
        {
            BaseItem* item = nullptr;
            return item;
        }
        virtual BaseItem* get(ItemType itemType);
        virtual std::string str();
        int getcount()  {
            return count;
        }
        NodeItem* getHead() {
            return head;
        }
        int deleteItem(ItemType itemType){
            NodeItem * current = head;
            NodeItem * prev = nullptr;
            int countdelete = 0;
            while(current != nullptr){
                if(current->item->getItem() == itemType){
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

        NodeItem* deleteItemSherlock(ItemType itemType){
            NodeItem * current = head;
            NodeItem * prev = nullptr;
            int countdelete = 0;
            NodeItem * gift = nullptr;
            while(current != nullptr){
                if(current->item->getItem() == itemType){
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
                        NodeItem * temp = gift;
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

// class SherlockBag
class SherlockBag:public BaseBag{
    private:    
    public:
    SherlockBag(Sherlock* sherlock):BaseBag(13){}
    //BaseItem* get();
    //bool insert (BaseItem* item);
    //BaseItem* get(ItemType itemType);
    //std::string str();
};


class WatsonBag : public BaseBag    {
    private:
    public:
    WatsonBag(Watson* watson):BaseBag(15){}
    //BaseItem* get();
    //bool insert (BaseItem* item);
   // BaseItem* get(ItemType itemType);
    //std::string str();
    
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
    StudyPinkProgram(const std::string & config_file_path){
    config = new Configuration(config_file_path);


    //std::cout << config->str() << endl;


    map = new Map(config->map_num_rows, config->map_num_cols, config->num_walls, config->arr_walls, config->num_fake_walls, config->arr_fake_walls);

    // Create characters
    // cout << "sherlock HP: " << config->sherlock_init_hp << endl;
    // cout << "sherlock EXP: " << config->sherlock_init_exp << endl;
    // cout << "watson HP: " << config->watson_init_hp << endl;
    // cout << "watson EXP: " << config->watson_init_exp << endl; 
    sherlock = new Sherlock(1, config->sherlock_moving_rule, config->sherlock_init_pos, map, config->sherlock_init_hp, config->sherlock_init_exp);
    watson = new Watson(2, config->watson_moving_rule, config->watson_init_pos, map, config->watson_init_hp, config->watson_init_exp);
    criminal = new Criminal(0, config->criminal_init_pos, map, sherlock, watson);

    // Create array of moving objects
    arr_mv_objs = new ArrayMovingObject(config->max_num_moving_objects);

    // Add characters to array of moving objects
    arr_mv_objs->add(criminal);
    arr_mv_objs->add(sherlock);
    arr_mv_objs->add(watson);
    }

    

    bool isStop() const{
        if (sherlock->getHP() == 1 || watson->getHP() == 1 ||
        sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(), criminal->getCurrentPosition().getCol()) ||
        watson->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(), criminal->getCurrentPosition().getCol())) {
        return true; 
    }
    return false; 
    }

    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
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
        bool stop = arr_mv_objs->checkMeet(0) || sherlock->getHP() == 1 || watson->getHP() == 1;
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
                //     if(arr_mv_objs->get(i)->getName() == "Criminal"){
                //     for (int i = 0; i < arr_mv_objs->size(); i++)
                //     {
                //         if(arr_mv_objs->get(i)->getName()=="RobotC"){
                //             arr_mv_objs->get(i)->move();
                //         }
                //     }
                    
                // }
                if(robot != nullptr){
                    if (criminal->getstepcount() % 3 == 0 && criminal->getstepcount() > 0)
                    {
                        if(!arr_mv_objs->checkMeet(0)){
                        arr_mv_objs->add(robot);
                        }
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


    void run(bool verbose ,ofstream &OUTPUT){
        if (!OUTPUT.is_open())
    {
        return;
    }
    bool stop = arr_mv_objs->checkMeet(0) || sherlock->getHP() == 1 || watson->getHP() == 1;
    //OUTPUT << config->str() << endl;
    for (int istep = 0; istep < config->num_steps && !stop; ++istep)
    {
        for (int i = 0; i < arr_mv_objs->size() && !stop; ++i)
        {

            if (stop)
                break;
            OUTPUT << endl
                   << "*************AFTER MOVE*************" << endl;
            OUTPUT << "ROUND : " << istep << " - TURN : " << i << endl;

            MovingObject *robot = nullptr;
            if (arr_mv_objs->get(i)->getName() == "Criminal")
            {
                robot = Robot::create(arr_mv_objs->size(), map, criminal, sherlock, watson);
                //OUTPUT << "Robot created"<< endl;
            }
            //OUTPUT << arr_mv_objs->get(i)->getName() <<" to ";
            arr_mv_objs->get(i)->move();

            // if(arr_mv_objs->get(i)->getName() == "Criminal"){
            //     for (int i = 0; i < arr_mv_objs->size(); i++)
            //     {
            //         if(arr_mv_objs->get(i)->getName()=="RobotC"){
            //             arr_mv_objs->get(i)->move();
            //         }
            //     }
                
            // }
            //OUTPUT <<arr_mv_objs->get(i)->getCurrentPosition().str() << endl;
            if (robot != nullptr)
            {
                //OUTPUT << "Numstep: " << criminal->getstepcount() << endl;
                if (criminal->getstepcount() % 3 == 0 && criminal->getstepcount() > 0)
                {
                    //OUTPUT << "Robot added to the moving objects list" << endl;
                    //OUTPUT <<"Robot Position: " <<robot->getCurrentPosition().str() << endl;
                    //OUTPUT << "Robot type: " << robot->getName() << endl;
                    
                    if(!arr_mv_objs->checkMeet(0)){
                        
                        arr_mv_objs->add(robot);
                    }
                    
                }
                else
                {
                    delete robot;
                }
            }
            //printMap(OUTPUT);
            stop = arr_mv_objs->checkMeet(i);
            //  << "---------------" << endl
            //        << "LOG : " << endl
            OUTPUT    << arr_mv_objs->str() << endl
                   << "Sherlock HP_" << sherlock->getHP() << " EXP_" << sherlock->getEXP() << endl
                   << "Watson HP_" << watson->getHP() << " EXP_" << watson->getEXP() << endl
                   << "SherlockBag : " << sherlock->getBag()->str() << endl
                   << "WatsonBag : " << watson->getBag()->str() << endl;
        }
    }
    }
    
    ~StudyPinkProgram(){
        // delete config;
        // delete sherlock;
        // delete watson;
        // delete criminal;
        // delete map;
        // delete arr_mv_objs;
    
    }
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
