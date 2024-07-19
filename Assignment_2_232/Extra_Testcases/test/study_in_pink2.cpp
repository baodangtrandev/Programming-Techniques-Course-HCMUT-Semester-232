#include "study_in_pink2.h"



Configuration::Configuration(const string filepath) {
    //cout << "Configuration: filepath "<< filepath  << endl;
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
    //delete[] arr_walls;
    //delete[] arr_fake_walls;
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

// int FakeWall::getReqExp() const{
//     return this->req_exp;
// }

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
    map = new MapElement**[num_rows];
    
    for (int i = 0; i < num_rows; ++i) {
        map[i] = new MapElement*[num_cols];
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
                map[i][j] = new Wall();
            } else if (is_fake_wall) {
                // Calculate req_exp for FakeWall
                int req_exp = (i * 257 + j * 139 + 89) % 900 + 1;
                map[i][j] = new FakeWall(req_exp);
            } else {
                map[i][j] = new Path();
            }
        }
    }
}

Map::~Map() {
    for (int i = 0; i < num_rows; ++i) {
        //delete[] map[i];
    }
    //delete[] map;
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
    if(pos.getCol()< 0||pos.getRow() < 0||pos.getCol()>=num_cols||pos.getRow()>=num_rows){
        return false;
    }
    MapElement* map_element = map[pos.getRow()][pos.getCol()];
    //cout << "Map element type: " << map_element->getType() << endl;
    // Check if the map element is a fake wall
    if (map_element->getType() == FAKE_WALL) {
        // If the moving object is Watson, check if its EXP is sufficient
        //cout << pos.str() << "is FAKE WALL" << endl;
        if (mv_obj->getName()=="Watson") {
            // Retrieve Watson's EXP
            int watson_exp = mv_obj->getExp();
            //cout << "watson exp: " << watson_exp << endl;

            // Retrieve the required EXP for the fake wall at this position
            int req_exp = map_element->getReqExp();

            //cout << "req exp: " << req_exp << endl;

            // Check if Watson's EXP is greater than or equal to the required EXP
            if (watson_exp > req_exp) {
                //cout << "true" << endl;
                return true; // Watson can move to this position
            } else {
                //cout << "false" << endl;
                return false; // Watson cannot move to this position due to insufficient EXP
            }
        }
    }
    if(map_element->getType() == WALL){
        return false;
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
        next_char_index = 0;
        sherlockBag = new SherlockBag(this);
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
        //cout << "Moving Rule: "<< moving_rule << endl;
        
        // Calculate the index of the next character in the moving_rule
        // static int next_char_index = 0;
        char next_direction = moving_rule[next_char_index];
        //cout <<"next direction: " <<next_direction << endl;
        // moving_rule = moving_rule.substr(1,moving_rule.length()-1) + next_direction;
        // Update the index for the next call
        next_char_index = (next_char_index + 1) % moving_rule.size();
        //cout <<"next char index: " <<next_char_index << endl;
        // Calculate the next position based on the direction
        int next_r = pos.getRow();
        int next_c = pos.getCol();
        //cout << next_r << " " << next_c << endl;
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

        //cout << next_pos.str() << endl;
        if (map->isValid(next_pos, this)) {
            // pos.setCol(next_pos.getCol());
            // pos.setRow(next_pos.getRow());
            //cout << pos.str() << endl;
           
            return next_pos;
        } else {
    //          if (next_char_index == moving_rule.size() - 1) {
    //     next_char_index = 0;
    // } else {
    //     // Otherwise, increment next_char_index
    //     next_char_index++;
    // }
        // next_char_index = 0;
            return Position::npos;
        }
}

////////////////////////////////////////////////////////////////////////
// class Waston
////////////////////////////////////////////////
Watson::Watson(int index, const string& moving_rule, const Position& init_pos, Map* map, int init_hp, int init_exp)
        : Character(index, init_pos, map, "Watson"), moving_rule(moving_rule){
        // Set initial HP and EXP within valid ranges
        hp = (init_hp < 0) ? 0 : (init_hp > 500) ? 500 : init_hp;
        exp = (init_exp < 0) ? 0 : (init_exp > 900) ? 900 : init_exp;
        next_char_index = 0;
        watsonBag = new WatsonBag(this);
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
        if (moving_rule.empty() || map == nullptr) {
            return Position::npos;
        }
        //cout << "next char index: " << next_char_index << endl;
        char next_direction = moving_rule[next_char_index];
        //cout <<"next direction: " <<next_direction << endl;
        next_char_index = (next_char_index + 1) % moving_rule.size();
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
        Position next_pos(next_r, next_c);

        //cout << next_pos.str() << endl;
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
    : Character(index, init_pos, map, "Criminal"), sherlock(sherlock), watson(watson), prev_pos(Position::npos), count(0) {}

Position Criminal::getNextPosition() {
    // int maxDistance = std::abs(pos.getRow() - sherlock->getCurrentPosition().getRow()) +
    //                                         std::abs(pos.getCol() - sherlock->getCurrentPosition().getCol())
    //                                         + std::abs(pos.getRow() - watson->getCurrentPosition().getRow()) 
    //                                         + std::abs(pos.getCol() - watson->getCurrentPosition().getCol());
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
                // cout <<"Sherlock Pos: "<< sherlock->getCurrentPosition().str() << endl;
                // cout <<"Watson Pos: "<< watson->getCurrentPosition().str() << endl;
                // cout << "Pos: " << newPos.str() << endl;
                // cout << "Total distance: " << totalDistance << endl;
                
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
            prev_pos = pos;
            pos = next_pos;
            count++;
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
    // Kiểm tra xem mảng đã đầy chưa
    // if (isFull()) {
    //     // Nếu đã đầy, không thêm được nữa
    //     return false;
    // }

    // // Tìm vị trí thích hợp để chèn phần tử vào mảng theo thứ tự index
    // int insertIndex = 0;
    // while (insertIndex < count && arr_mv_objs[insertIndex]->getindex() < mv_obj->getindex()) {
    //     insertIndex++;
    // }

    // // Dịch chuyển các phần tử từ vị trí chèn đến cuối mảng sang phải một vị trí để tạo chỗ trống
    // for (int i = count; i > insertIndex; i--) {
    //     arr_mv_objs[i] = arr_mv_objs[i - 1];
    // }

    // // Chèn phần tử mới vào vị trí thích hợp
    // arr_mv_objs[insertIndex] = mv_obj;

    // // Tăng số lượng phần tử trong mảng
    // count++;

    // return true;
     // Kiểm tra xem mảng đã đầy chưa
    if (isFull()) {
        // Nếu đã đầy, không thêm được nữa
        return false;
    }

    // Thêm phần tử mới vào cuối mảng
    arr_mv_objs[count] = mv_obj;

    // Tăng số lượng phần tử trong mảng
    count++;

    return true;
}


string ArrayMovingObject::str() const {
     stringstream ss;
    ss << "ArrayMovingObject[count=" << count << ";capacity=" << capacity;
    if(count > 0) ss << ";";
    for (int i = 0; i < count; ++i) {
        ss <<arr_mv_objs[i]->str();
        if (i < count - 1) {
            ss << ";";
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
            //delete arr_mv_objs[i];
        }
        //delete[] arr_mv_objs;
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

// BaseItem* createItem(Position pos){
    
// }
int tinh_tong_chu_so(int n) {
    // Kiểm tra nếu số n chỉ có một chữ số
    if (n < 10) {
        return n;
    }
    
    int total = 0;
    // Tiếp tục tính tổng các chữ số
    while (n > 0) {
        total += n % 10;  // Lấy chữ số cuối cùng của n và cộng vào tổng
        n /= 10;          // Loại bỏ chữ số cuối cùng của n
    }
    // Gọi đệ quy với tổng mới tính được
    return tinh_tong_chu_so(total);
}

 Robot::Robot(RobotType type, int index, const Position& init_pos, Map* map,string name)
        : MovingObject(index, init_pos, map, name), robot_type(type){
           int p = pos.getRow()*pos.getCol();
            int s = tinh_tong_chu_so(p);
            if(s>=0&&s<=1){
                item =  new MagicBook();
            }
            else if(s>=2&&s<=3){
                item =  new EnergyDrink();
            }
            else if(s>=4&&s<=5){
                item =  new FirstAid();
            }
            else if(s>=6&&s<=7){
                item =  new ExcemptionCard();
            }
            else if(s>=8&&s<=9){
                int t = (pos.getRow()*11 + pos.getCol())%4;
                if(t == 0){
                    item =  new PassingCard("RobotS");
                }
                else if(t == 1){
                    item =  new PassingCard("RobotC");
                }
                else if(t == 2){
                    item =  new PassingCard("RobotSW");
                }
                else if(t == 3){
                    item =  new PassingCard("all");
                }
            }
        }

Robot* Robot::create(int index, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson) {\
    int sherlock_distance = abs(criminal->getCurrentPosition().getRow() - sherlock->getCurrentPosition().getRow()) +
                                         std::abs(criminal->getCurrentPosition().getCol() - sherlock->getCurrentPosition().getCol());
    int watson_distance = abs(criminal->getCurrentPosition().getRow() - watson->getCurrentPosition().getRow()) +
                                         std::abs(criminal->getCurrentPosition().getCol() - watson->getCurrentPosition().getCol());
    if(criminal->getCount() <= 2){
        // first_created++;
        //cout << "Create Robot C" << endl;
        return new RobotC(index, criminal->getCurrentPosition(), map, criminal);
    }
    else if(sherlock_distance < watson_distance){
        //cout << "Create Robot S" << endl;
        return new RobotS(index, criminal->getCurrentPosition(), map, criminal, sherlock);
    }
    else if(sherlock_distance > watson_distance){
        //cout << "Create Robot W" << endl;
        return new RobotW(index, criminal->getCurrentPosition(), map, criminal, watson);
    }
    else{
        //cout << "Create Robot SW" << endl;
        return new RobotSW(index, criminal->getCurrentPosition(), map, criminal, sherlock, watson);
    }
}
////////////////////////////////////////////////////////////////////////
// class RobotC
////////////////////////////////////////////////
RobotC::RobotC(int index, const Position& init_pos, Map* map, Criminal* criminal)
        : Robot(C, index, init_pos, map,"RobotC"), criminal(criminal) {}

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
    criminal->getPrevPosition().str();
    return criminal->getPrevPosition();
}

string RobotC::str(){
        stringstream ss;
        ss << "Robot[pos=" << pos << ";type=C;dist=]";
        return ss.str();
    }

void RobotC::move() {
    // Position nextPos = getNextPosition();
    // cout << "CurrentPos: " << pos.str() << endl;
    // cout << "NextPos: " <<nextPos.str() << endl;
    // // Check if the next position is valid
    // if (nextPos != Position::npos) {
    //     // Move the robot to the next position
    //     cout << "RobotC Move to the next position" << endl;
    //     pos = nextPos;
    // }
    
        pos = criminal->getPrevPosition();
}

////////////////////////////////////////////////////////////////////////
// class RobotS
////////////////////////////////////////////////
RobotS::RobotS(int index, const Position& init_pos, Map* map, Criminal* criminal, Sherlock* sherlock)
    : Robot(S, index, init_pos, map,"RobotS"), criminal(criminal), sherlock(sherlock) {
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
    int closestDistance = 999999;

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
        //cout << "step " << i << endl;
        
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
    : Robot(W, index, init_pos, map,"RobotW"), criminal(criminal), watson(watson) {
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
    int closestDistance = 999999;

    // Define the possible directions in a clockwise order starting from upward movement
    int directions[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

    // Get Watson's next position
   // Position watsonNextPos = watson->getNextPosition();

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
        int distance = calculateManhattanDistance(nextPos, watson->getCurrentPosition());
        
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
    : Robot(SW, index, init_pos, map,"RobotSW"), criminal(criminal), sherlock(sherlock), watson(watson) {
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
    int closestDistance = 999999;

    // Define the possible directions in a clockwise order starting from upward movement
    int directions[8][2] = { {-2, 0}, {-1, 1}, {0, 2},{1, 1}, {2, 0},{1, -1}, {0, -2}, {-1, -1}};

    // Get Sherlock's next position
    Position sherlockNextPos = sherlock->getCurrentPosition();
    // Get Watson's next position
    Position watsonNextPos = watson->getCurrentPosition();

    // Iterate through adjacent positions in clockwise order
    for (int i = 0; i < 8; ++i) {
        // Calculate the row and column of the next position
        int nextRow = pos.getRow() + ( directions[i][0]);
        int nextCol = pos.getCol() + (directions[i][1]);
        
        // Create the next position object
        Position nextPos(nextRow, nextCol);
        
        // Check if the next position is valid
        if (!map->isValid(nextPos, this)) continue;
        
        // Calculate Manhattan distance to both Sherlock's and Watson's next positions
        int distanceToSherlock = calculateManhattanDistance(nextPos, sherlock->getCurrentPosition());
        int distanceToWatson = calculateManhattanDistance(nextPos, watson->getCurrentPosition());
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
        obj->setExp(ceil(obj->getExp()*1.25));
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
        obj->setHp(ceil(obj->getHp()*1.2));
    }
}

////////////////////////////////////////////////////////////////////////
// class FirstAid
////////////////////////////////////////////////

bool FirstAid::canUse(Character* obj,Robot* robot){
    if(robot){
        return false;
    }else if(obj->getHp() > 100 && obj->getExp() > 350) return false;
    return true;
}

void FirstAid::use(Character* obj,Robot* robot){
    if(canUse(obj,robot)){
        obj->setHp(ceil(obj->getHp()*1.5));
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
    if(this->challenge == "RobotS"&&robot->getRobotType() != S){
        obj->setExp(obj->getExp() - 50);
    }else if(this->challenge == "RobotC"&&robot->getRobotType() != C){
        obj->setExp(obj->getExp() - 50);
    }else if(this->challenge == "RobotW"&&robot->getRobotType() != W){
        obj->setExp(obj->getExp() - 50);
    }else if(this->challenge == "RobotSW"&&robot->getRobotType() != SW){
        obj->setExp(obj->getExp() - 50);
    }else if(this->challenge == "all"){
        return;
    }
    
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
        count++;
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
     ItemNode* current = head;
    while (current != nullptr) {
            if (current->item->canUse(this->getObj(), nullptr)){
                BaseItem* item = current->item;
                // Remove item from bag
                if (current == head) {
                    head = head->next;
                }else if(head->next == current){
                    head->next = current->next;
                    // delete current;
                    // count--;
                    // return item;
                }
                 else {
                        ItemNode* prev = head;
                    while (prev->next != current) {
                        prev = prev->next;
                    }
                    ItemNode* temp = head->next;
                    prev->next = head;
                    head->next = current->next;
                    head = temp;
                }
                delete current;
                count--;
                return item;
            }
            current = current->next;
        }
        //cerr << "Item type not found in bag." << endl;
        return nullptr;
}

BaseItem* SherlockBag::get(ItemType itemType) {
        ItemNode* current = head;
        while (current != nullptr) {
            if (current->item->getType() == itemType) {
                BaseItem* item = current->item;
                // Remove item from bag
                if (current == head) {
                    head = head->next;
                }else if(head->next == current){
                    head->next = current->next;
                    // delete current;
                    // count--;
                    // return item;
                }
                 else {
                        ItemNode* prev = head;
                    while (prev->next != current) {
                        prev = prev->next;
                    }
                    ItemNode* temp = head->next;
                    prev->next = head;
                    head->next = current->next;
                    head = temp;
                }
                delete current;
                count--;
                return item;
            }
            current = current->next;
        }
        //cerr << "Item type not found in bag." << endl;
        return nullptr;
}

string SherlockBag::str() const {
    stringstream ss;
    ss << "Bag[count=" << count <<";";
    // if(head!=nullptr){
    //     ss << ";";
    // }
    ItemNode *current = head;
    while (current != nullptr) {
        // ss << current->item->getType(); // Adding item type to the string
        if(current->item->getType() == ENERGY_DRINK){
            ss << "EnergyDrink";
        }else if(current->item->getType() == FIRST_AID){
            ss << "FirstAid";
        }else if(current->item->getType() == MAGIC_BOOK){
            ss << "MagicBook";
        }else if (current->item->getType() == EXCEMPTION_CARD){
            ss << "ExcemptionCard";
        }else if (current->item->getType() == PASSING_CARD){
            ss << "PassingCard";
        }
        
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
        count++;
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
     ItemNode* current = head;
    while (current != nullptr) {
            if (current->item->canUse(this->getObj(), nullptr)){
                BaseItem* item = current->item;
                // Remove item from bag
                if (current == head) {
                    head = head->next;
                }else if(head->next == current){
                    head->next = current->next;
                    // delete current;
                    // count--;
                    // return item;
                }
                 else {
                        ItemNode* prev = head;
                    while (prev->next != current) {
                        prev = prev->next;
                    }
                    ItemNode* temp = head->next;
                    prev->next = head;
                    head->next = current->next;
                    head = temp;
                }
                delete current;
                count--;
                return item;
            }
            current = current->next;
        }
        //
        //cerr << "Item type not found in bag." << endl;
        return nullptr;
}
BaseItem* WatsonBag::get(ItemType itemType) {
    ItemNode* current = head;
    while (current != nullptr) {
        if (current->item->getType() == itemType) {
            BaseItem* item = current->item;
            // Remove item from bag
             if (current == head) {
                    head = head->next;
                }else if(head->next == current){
                    head->next = current->next;
                    // delete current;
                    // count--;
                    // return item;
                }
                 else {
                        ItemNode* prev = head;
                    while (prev->next != current) {
                        prev = prev->next;
                    }
                    ItemNode* temp = head->next;
                    prev->next = head;
                    head->next = current->next;
                    head = temp;
                }
            delete current;
            count--;
            return item;
        }
        current = current->next;
    }
    //cerr << "Item type not found in bag." << endl;
    return nullptr;
}

string WatsonBag::str() const {
    stringstream ss;
    ss << "Bag[count=" << count <<";";
    // if(head!=nullptr){
    //     ss << ";";
    // }
    ItemNode *current = head;
    while (current != nullptr) {
        // ss << current->item->getType(); // Adding item type to the string
        if(current->item->getType() == ENERGY_DRINK){
            ss << "EnergyDrink";
        }else if(current->item->getType() == FIRST_AID){
            ss << "FirstAid";
        }else if(current->item->getType() == MAGIC_BOOK){
            ss << "MagicBook";
        }else if (current->item->getType() == EXCEMPTION_CARD){
            ss << "ExcemptionCard";
        }else if (current->item->getType() == PASSING_CARD){
            ss << "PassingCard";
        }
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

StudyPinkProgram::~StudyPinkProgram() {
    // Free dynamically allocated memory
    //delete config;
    //delete map;
    //delete arr_mv_objs;
    //delete sherlock;
    //delete watson;
    //delete criminal;
}


bool StudyPinkProgram::isStop() const {
    // Check if any of the stop conditions are met
    if (sherlock->getHp() == 1 || watson->getHp() == 1 ||
        sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(), criminal->getCurrentPosition().getCol()) ||
        watson->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(), criminal->getCurrentPosition().getCol())) {
        return true; // Stop condition is met
    }
    return false; // Stop condition is not met
}


bool ArrayMovingObject::checkMeet(int index)
{
   //cout << "Vo ham checkMeet" << endl;
        for(int i = 0; i < count; i++){
            if(i != index){
                if(arr_mv_objs[i]->getCurrentPosition().isEqual(arr_mv_objs[index]->getCurrentPosition().getRow(),arr_mv_objs[index]->getCurrentPosition().getCol())){
                    //cout << "Gap nhau roi ne" << endl;
                    if((arr_mv_objs[index]->getName()=="Sherlock"&&arr_mv_objs[i]->getName()=="Criminal")
                    ||(arr_mv_objs[index]->getName()=="Criminal"&&arr_mv_objs[i]->getName()=="Sherlock")){
                        return true;
                    }
                    if((arr_mv_objs[index]->getName()=="Watson"&&arr_mv_objs[i]->getName()=="Criminal")
                    ||(arr_mv_objs[index]->getName()=="Criminal"&&arr_mv_objs[i]->getName()=="Watson")){
                        return true;
                    }
                    if(arr_mv_objs[index]->getName()=="Sherlock"&&arr_mv_objs[i]->getName()=="RobotS"){
                        //cout << "Sherlock Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[index])->meet(dynamic_cast<RobotS*>(arr_mv_objs[i]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="RobotS"&&arr_mv_objs[i]->getName()=="Sherlock"){
                        //cout << "RobotS Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[i])->meet(dynamic_cast<RobotS*>(arr_mv_objs[index]));
                        //return false;
                    }
                    else if(arr_mv_objs[index]->getName()=="Sherlock"&&arr_mv_objs[i]->getName()=="RobotW"){
                        //cout << "Sherlock Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[index])->meet(dynamic_cast<RobotW*>(arr_mv_objs[i]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="RobotW"&&arr_mv_objs[i]->getName()=="Sherlock"){
                        //cout << "RobotW Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[i])->meet(dynamic_cast<RobotW*>(arr_mv_objs[index]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="Sherlock"&&arr_mv_objs[i]->getName()=="RobotSW"){
                        //cout << "Sherlock Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[index])->meet(dynamic_cast<RobotSW*>(arr_mv_objs[i]));
                        //return false;   
                    }
                    else if(arr_mv_objs[index]->getName()=="RobotSW"&&arr_mv_objs[i]->getName()=="Sherlock"){
                        //cout << "RobotSW Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[i])->meet(dynamic_cast<RobotSW*>(arr_mv_objs[index]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="RobotC"&&arr_mv_objs[i]->getName()=="Sherlock"){
                        //cout << "RobotC Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[i])->meet(dynamic_cast<RobotC*>(arr_mv_objs[index]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="Sherlock"&&arr_mv_objs[i]->getName()=="RobotC"){
                        //cout << "Sherlock Meet: " << arr_mv_objs[i]->getName() << endl;
                        return dynamic_cast<Sherlock*>(arr_mv_objs[index])->meet(dynamic_cast<RobotC*>(arr_mv_objs[i]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="Watson"&&arr_mv_objs[i]->getName()=="RobotS"){
                        //cout << "Watson Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[index])->meet(dynamic_cast<RobotS*>(arr_mv_objs[i]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="RobotS"&&arr_mv_objs[i]->getName()=="Watson"){
                        //cout << "RobotS Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[i])->meet(dynamic_cast<RobotS*>(arr_mv_objs[index]));
                        //return false;
                    }
                    else if(arr_mv_objs[index]->getName()=="Watson"&&arr_mv_objs[i]->getName()=="RobotW"){
                        //cout << "Watson Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[index])->meet(dynamic_cast<RobotW*>(arr_mv_objs[i]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="RobotW"&&arr_mv_objs[i]->getName()=="Watson"){
                        //cout << "RobotW Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[i])->meet(dynamic_cast<RobotW*>(arr_mv_objs[index]));
                        //return false;
                    }
                    else if(arr_mv_objs[index]->getName()=="Watson"&&arr_mv_objs[i]->getName()=="RobotSW"){
                        //cout << "Watson Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[index])->meet(dynamic_cast<RobotSW*>(arr_mv_objs[i]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="RobotSW"&&arr_mv_objs[i]->getName()=="Watson"){
                        //cout << "RobotSW Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[i])->meet(dynamic_cast<RobotSW*>(arr_mv_objs[index]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="Watson"&&arr_mv_objs[i]->getName()=="RobotC"){
                        //cout << "Watson Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[index])->meet(dynamic_cast<RobotC*>(arr_mv_objs[i]));
                        //return false;
                    } else if(arr_mv_objs[index]->getName()=="RobotC"&&arr_mv_objs[i]->getName()=="Watson"){
                        //cout << "RobotC Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[i])->meet(dynamic_cast<RobotC*>(arr_mv_objs[index]));
                        //return false;
                    }
                    else if(arr_mv_objs[index]->getName()=="Sherlock"&&arr_mv_objs[i]->getName()=="Watson"){
                        //cout << "Sherlock Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[index])->meet(dynamic_cast<Watson*>(arr_mv_objs[i]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="Watson"&&arr_mv_objs[i]->getName()=="Sherlock"){
                        //cout << "Watson Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[index])->meet(dynamic_cast<Sherlock*>(arr_mv_objs[i]));
                        //return false;
                    }
                    
                }
            }
        }
        return false;
}
// *CLASS: Sherlock
// ! Lưu ý: ExcemptionCard được dùng để BỎ QUA nếu THỬ THÁCH THẤT BẠI -> xem như không thực hiện thử thách -> không gọi get lần 2
// ! Thực hiện get từ bag sau khi insert item
bool Sherlock::meet(RobotS* robotS)
{
    // TODO: Xử lý khi gặp robot S
    //cout << "Sherlock Meet RobotS" << endl;
    // bool pass = false;
    //ItemNode* headbag = this->getBag()->getHead();
    BaseItem* item = this->getBag()->get(EXCEMPTION_CARD);
    if(item == nullptr || this->getHp()%2 == 0){
        if(this->getExp()>400){
        this->getBag()->insert(robotS->getItem());
        }else{
        this->setExp(ceil(this->getExp()*0.9));
        }
    }
    ItemNode* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getType());
            headbag->item->use(this,nullptr);
            break;
        }
        headbag = headbag->next;
    }

    return true;
}
bool Sherlock::meet(RobotW* robotW)
{
    // TODO: Xử lý khi gặp robot W
    //cout << "Sherlock Meet RobotW" << endl;
    this->getBag()->insert(robotW->getItem());

    ItemNode* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getType());
            headbag->item->use(this,nullptr);
            break;
        }
        headbag = headbag->next;
    }
    return true;
}
bool Sherlock::meet(RobotSW *robotSW)
{
    // TODO: Xử lý khi gặp robot SW
    //cout << "Sherlock Meet RobotSW" << endl;
    BaseItem* item = this->getBag()->get(EXCEMPTION_CARD);
    
    if(item == nullptr || this->getHp()%2 == 0){
        if(this->getExp()>300&&this->getHp()>335){
        this->getBag()->insert(robotSW->getItem());
    }else{
        this->setHp(ceil(this->getHp()*0.85));
        this->setExp(ceil(this->getExp()*0.85));
    }
    }
    ItemNode* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getType());
            headbag->item->use(this,nullptr);
            break;
        }
        headbag = headbag->next;
    }
    return true;
}
bool Sherlock::meet(RobotC *robotC)
{
    // TODO: Xử lý khi gặp robot C
    //cout << "Sherlock Meet RobotC" << endl;
    BaseItem* item = this->getBag()->get(EXCEMPTION_CARD);
    if(item == nullptr || this->getHp()%2 == 0){
        if(this->getExp()>500){
        return true;
    }else{
        this->getBag()->insert(robotC->getItem());
    }
    }
    ItemNode* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getType());
            headbag->item->use(this,nullptr);
            break;
        }
        headbag = headbag->next;
    }
    return false;

    


}

bool Sherlock::meet(Watson *watson)
{
    //cout << "Sherlock Meet Watson" << endl;
    ItemNode* gift = this->getBag()->deleteItem(PASSING_CARD);
    // cout << watson->getCurrentPosition() << endl;
    // cout << watson->getBag()->str() << endl;
    // if(gift!=nullptr){
    //     cout << gift->item->getType() << endl;
    // }
    ItemNode* temp = gift;
    while(temp!=nullptr){
        watson->getBag()->insert(temp->item);
        temp = temp->next;
    }
    int countWatson = watson->getBag()->deleteItem(EXCEMPTION_CARD);
    for(int i = 0; i < countWatson; i++){
        this->getBag()->insert(new ExcemptionCard());
    }
    // for(int i = 0; i < count_sherlock; i++){
    //     watson->getBag()->insert();
    // }
    return true;
}
// *CLASS: Watson
// ! Lưu ý: PassingCard được dùng khi GẶP ROBOT để bỏ qua thử thách nếu đúng loại thẻ
// ! Thực hiện get từ bag sau khi insert item
bool Watson::meet(RobotS *robotS)
{
    // TODO: Xử lý trao đổi khi gặp robot S
    //cout << "Watson Meet RobotS" << endl;
    //this->getBag()->insert(robotS->getItem());

    ItemNode* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getType());
            headbag->item->use(this,nullptr);
            break;
        }
        headbag = headbag->next;
    }
    return true;
}
bool Watson::meet(RobotW *robotW)
{
    // TODO: Xử lý trao đổi khi gặp robot W
    //cout << "Watson Meet RobotW" << endl;

    BaseItem* item = nullptr;
    if(this->getHp()%2==0){
        item = this->getBag()->get(PASSING_CARD);
        if(item!=nullptr){
        item->use(this,robotW);
        }
    }
    if(item == nullptr){
        if(this->getHp()>350){
        this->getBag()->insert(robotW->getItem());
    }else{
        this->setHp(ceil(this->getHp()*0.95));
    }
    }
    ItemNode* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getType());
            headbag->item->use(this,nullptr);
            break;
        }
        headbag = headbag->next;
    }
    return false;
}
bool Watson::meet(RobotSW *robotSW)
{
    // TODO: Xử lý trao đổi khi gặp robot SW
    //cout << "Watson Meet RobotSW" << endl;
    

    BaseItem* item = nullptr;
    if(this->getHp()%2==0){
        item = this->getBag()->get(PASSING_CARD);
        if(item!=nullptr){
        item->use(this,robotSW);
        }
    }
    if(item == nullptr){
       if(this->getHp()>165&&this->getExp()>600){
        this->getBag()->insert(robotSW->getItem());
    }else{
        this->setHp(ceil(this->getHp()*0.85));
        this->setExp(ceil(this->getExp()*0.85));
    }
    }
    ItemNode* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getType());
            headbag->item->use(this,nullptr);
            break;
        }
        headbag = headbag->next;
    }
    return false;
}
bool Watson::meet(RobotC *robotC)
{
    // TODO: Xử lý trao đổi khi gặp robot C
    //cout << "Watson Meet RobotC" << endl;
    //this->getBag()->insert(robotC->getItem());
    BaseItem* item = nullptr;
    if(this->getHp()%2==0){
        item = this->getBag()->get(PASSING_CARD);
        if(item!=nullptr){
        item->use(this,robotC);
        }
    }
    // if(item == nullptr){
     
    // }
    this->getBag()->insert(robotC->getItem());
    
    ItemNode* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getType());
            headbag->item->use(this,nullptr);
            break;
        }
        headbag = headbag->next;
    }
    return false;
}
bool Watson::meet(Sherlock *sherlock)
{
    // TODO: Xử lý trao đổi khi gặp Sherlock
    //cout << "Watson Meet Sherlock" << endl;
    //cout << "Sherlock Meet Watson" << endl;
    ItemNode* gift = sherlock->getBag()->deleteItem(PASSING_CARD);
    ItemNode* temp = gift;
    while(temp!=nullptr){
        this->getBag()->insert(temp->item);
        temp = temp->next;
    }
    int countWatson = this->getBag()->deleteItem(EXCEMPTION_CARD);
    for(int i = 0; i < countWatson; i++){
        sherlock->getBag()->insert(new ExcemptionCard());
    }
    // for(int i = 0; i < count_sherlock; i++){
    //     watson->getBag()->insert();
    // }
    return true;
}


void StudyPinkProgram::printMap(ofstream &OUTPUT) const{
    if (!OUTPUT.is_open())
        return;
    for (int i = 0; i < map->getNumCols(); ++i) {
        if(i<10){
            OUTPUT << "      "<< i <<"|";
        }else{
            OUTPUT << "     "<< i <<"|";
        }
    }
    OUTPUT << endl;
    bool is_meet = false;
    for (int i = 0; i < map->getNumRows(); ++i) {
            for (int j = 0; j < map->getNumCols(); ++j) {
                // if(sherlock->getCurrentPosition().isEqual(i,j)){
                //     OUTPUT << "      " << "S" << "|";
                //     continue;
                // }else if(watson->getCurrentPosition().isEqual(i,j)){
                //     OUTPUT << "      " << "W" << "|";
                //     continue;
                // }else if(criminal->getCurrentPosition().isEqual(i,j)){
                //     OUTPUT << "      " << "C" << "|";
                //     continue;
                // }
                
                
                bool okie = false;
                for(int k = 0; k< arr_mv_objs->size(); k++){
                    if(arr_mv_objs->get(k)->getCurrentPosition().isEqual(i,j)){
                        // OUTPUT << "      " << arr_mv_objs->get(i)->getName() << "|";
                        if (sherlock->getCurrentPosition().isEqual(watson->getCurrentPosition().getRow(),watson->getCurrentPosition().getCol())&&!is_meet&&arr_mv_objs->get(k)->getName()!= "Criminal"){
                            OUTPUT << "     " << "SW" << "|";
                            okie = true;
                            is_meet = true;
                            break;
                        }
                        else if(sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(),criminal->getCurrentPosition().getCol())&&!is_meet){
                            OUTPUT << "     " << "CS" << "|";
                            okie = true;
                            is_meet = true;
                            break;
                        }else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow(),criminal->getCurrentPosition().getCol())&&!is_meet){
                            OUTPUT << "     " << "CW" << "|";
                            okie = true;
                            is_meet = true;
                            break;
                        }
                        okie = true;
                        if(arr_mv_objs->get(k)->getName()=="Sherlock"){
                            OUTPUT << "      " << "S" << "|";
                        }else if(arr_mv_objs->get(k)->getName()=="Watson"){
                            OUTPUT << "      " << "W" << "|";
                        }else if(arr_mv_objs->get(k)->getName()=="Criminal"){
                            OUTPUT << "      " << "C" << "|";
                        }
                        break;
                    }
                }
                if(okie){
                    continue;
                }
               if(map->getMap()[i][j]->getType() == WALL){
                   OUTPUT << "  " << "IIIII|";
                }else if(map->getMap()[i][j]->getType() == FAKE_WALL){
                    OUTPUT << "  " << "-----" << "|";
                }else{
                    OUTPUT << "       " << "|";
                }
            }
            OUTPUT << endl;
        }
}