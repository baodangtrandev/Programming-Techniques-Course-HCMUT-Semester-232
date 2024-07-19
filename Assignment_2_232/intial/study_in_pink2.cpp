#include "study_in_pink2.h"

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

    // Handle other cases if needed
    // For example, return true or false based on the requirements of your program
    // If none of the conditions are met, you might want to return false
    return false;
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

bool ExemptionCard::canUse(Character* obj,Robot* robot){
    if(!robot){
        return false;
    }else if((obj->getName()!="Sherlock")||(obj->getHp()%2!=1)) return false;
    return true;
}

void ExemptionCard::use(Character* obj,Robot* robot){
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




////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////