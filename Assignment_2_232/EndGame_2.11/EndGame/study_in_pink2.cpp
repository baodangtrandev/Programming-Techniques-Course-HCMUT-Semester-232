#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
void limitcheck (int & variable, int max) {
    if (variable < 0)
    {
        variable = 0;
    }
    if (variable > max)
    {
        variable = max;
    }
}
void variableadjust (int & variable, double adjustment, int max)    {
    if (abs (adjustment - int(adjustment)) > 1e-9)  {
        adjustment = ceil (adjustment);
    }
    variable += adjustment;
    limitcheck (variable, max);
}
void magicbookuse (int exp) {
    variableadjust (exp, exp * 0.25, 600);
}
void energydrinkuse (int hp)    {
    variableadjust (hp, hp * 0.2, 666);
}
void firstaiduse (int hp)   {
    variableadjust (hp, hp * 0.5, 666);
}
bool excemptioncardhold (std::string charactername){
    if (charactername == "Sherlock") {
        return true;
    }
    else{
        return false;
    }
}
bool passingcardcompatible (std::string cardtype, std::string challenge)  {
    if (cardtype != challenge && cardtype != "all")  {
        return false;
    }
    else{
        return true;
    }
}
bool passingcardhold (std::string charactername)   {
    if (charactername == "Watson")  {
        return true;
    }
    return false;
}
void passingcarduse (int exp, std::string charactername, std::string cardtype, string challenge)   {
    if (passingcardhold(charactername) == true)    {
        if (passingcardcompatible(cardtype,challenge) == false) {
            variableadjust (exp, -50, 600);
        }
    }
}
int chudao (int a) {
    if (a < 10) {
        return a;
    }
    
    int total = 0;
    // Tiếp tục tính tổng các chữ số
    while (a > 0) {
        total += a % 10;  // Lấy chữ số cuối cùng của n và cộng vào tổng
        a /= 10;          // Loại bỏ chữ số cuối cùng của n
    }
    // Gọi đệ quy với tổng mới tính được
    return chudao(total);
}
int discal (int x1, int x2, int y1, int y2)  {
    return abs(x2 - x1) + abs(y2 - y1);
}
MapElement::MapElement(ElementType in_type)
: type(in_type)
{}
ElementType MapElement::getType() const{
    return type;
}
Path::Path()
: MapElement(PATH)
{}
Wall::Wall()
: MapElement(WALL)
{}
FakeWall::FakeWall(int in_req_exp)
: MapElement(FAKE_WALL), req_exp(in_req_exp)
{}

Map::Map(int num_rows, int num_cols, int num_walls, Position * array_walls, int num_fake_walls, Position * array_fake_walls)
: num_cols(num_cols), num_rows(num_rows)
{
    map = new MapElement**[num_rows];
    for (int i = 0; i < num_rows; i++)
    {
        map [i] = new MapElement*[num_cols]; 
    }
    for (int messi = 0; messi < num_rows; messi++)
    {
        for (int bk8 = 0; bk8 < num_cols; bk8++)
        {
            map [messi][bk8] = new Path();
        }
        
    }
    for (int i = 0; i < num_walls; i++)
    {
        int row = array_walls[i].getRow();
        int col = array_walls[i].getCol();
        delete map[row][col];
        map[row][col] = new Wall();
    }
    for (int i = 0; i < num_fake_walls; i++)
    {
        int row = array_fake_walls[i].getRow();
        int col = array_fake_walls[i].getCol();
        int re = (row * 257 + col * 139 + 89)%900 +1;
        delete map[row][col];
        map[row][col] = new FakeWall(re);
    }
}
Map::~Map(){
    for (int i = 0; i < num_rows; i++)
    {
        delete[] map[i];
    }
    delete[] map;
}
Position::Position(int r, int c)
:r(r),c(c)
{}
Position::Position(const string & str_pos)
{
    string x,y;
    int a;
    for (int i = 1; i < str_pos.size() - 1; i++)
    {
        if (str_pos[i] != ',')
        {
            x += str_pos[i];
        }
        else
        {
            a = i+1;
            break;
        }     
    }
    for (int i = a; i < str_pos.size() - 1; i++)
    {
        y += str_pos[i];
    }
    r = stoi(x);
    c = stoi(y);
}
int Position::getRow() const    {
    return r;
}
int Position::getCol() const    {
    return c;
}
void Position::setRow(int row)    {
    r=row;
}
void Position::setCol(int col)    {
    c=col;
}
string Position::str() const    {
    return "(" + to_string(r) + "," + to_string(c) +")";
}
bool Position::isEqual(int in_r, int in_c)  const   {
    if (this->getCol() == in_c && this->getRow() == in_r)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Position::isEqual(Position x)    {
    if (getCol() == x.getCol() && getRow() == x.getRow())
    {
        return true;
    }
    else
    {
        return false;
    }
}
MovingObject::MovingObject(int index, const Position pos, Map * map, const string & name="")
:index(index), pos(pos), map(map), name(name)
{}
MovingObject::~MovingObject()   {}
Position MovingObject::getCurrentPosition() const {
    return pos;
}
const Position Position::npos=Position(-1,-1);
bool Map::isValid (const Position & pos , MovingObject * mv_obj) const    {
    if (pos.getRow() < 0 || pos.getRow() >= num_rows || pos.getCol() < 0 || pos.getCol() >= num_cols)
    {
        return false;
    }
    else if (map [pos.getRow()][pos.getCol()]->getType() == WALL)
    {
        return false;
    }
    else if (map [pos.getRow()][pos.getCol()]->getType() == PATH)
    {
        return true;
    }
    else if (map [pos.getRow()][pos.getCol()]->getType() == FAKE_WALL)
    {

        if (mv_obj->getName() == "Watson")
        {
            if (dynamic_cast<Watson*>(mv_obj)->getEXP() >  dynamic_cast<FakeWall*>(map [pos.getRow()][pos.getCol()])->getReqExp())  {
                return true;
            }
            else{
                return false;
            }
        }
        else
        {
            return true;
        }
        
    }
    return true;
    //để tạm     
}
Sherlock::Sherlock(int index, const string & moving_rule,const Position & init_pos, Map * map, int init_hp, int init_exp)  
:Character(index, init_pos,map,"Sherlock",init_hp,init_exp), moving_rule(moving_rule)
{
    nummov = 0;
    bag = new SherlockBag(this);
}
Position Sherlock::getNextPosition()    {
    Position nextpos = pos;
    char m = getMVR();
    switch (m)
    {
    case 'L':
        nextpos.setCol(pos.getCol() - 1);
        break;
    case 'R':
        nextpos.setCol(pos.getCol() + 1);
        break;
    case 'U':
        nextpos.setRow(pos.getRow() - 1);
        break;
    case 'D':
        nextpos.setRow(pos.getRow() + 1);
        break;
    }
    if (map->isValid(nextpos, this))
    {
        return nextpos;
    }
    else
    {
        return Position::npos;
    }    
}
void Sherlock::move()   {
    Position nextpos = getNextPosition();
    if (!nextpos.isEqual( Position::npos))
    {
        pos = nextpos;
    }
}
string Sherlock::str() const  {
    return "Sherlock[index="+to_string(index)+";pos="+pos.str()+";moving_rule="+moving_rule+"]";
}
Watson::Watson(int index, const string & moving_rule, const Position & init_pos, Map * map, int init_hp, int init_exp)  
:Character(index, init_pos,map,"Watson",init_hp,init_exp), moving_rule(moving_rule)
{
    nummov = 0;
    bag = new WatsonBag(this);
}
Position Watson::getNextPosition()    {
    Position nextpos = pos;
    char m = getMVR();
    switch (m)
    {
    case 'L':
        nextpos.setCol(pos.getCol() - 1);
        break;
    case 'R':
        nextpos.setCol(pos.getCol() + 1);
        break;
    case 'U':
        nextpos.setRow(pos.getRow() - 1);
        break;
    case 'D':
        nextpos.setRow(pos.getRow() + 1);
        break;
    }
    if (map->isValid(nextpos, this))
    {
        return nextpos;
    }
    else
    {
        return Position::npos;
    }    
}
void Watson::move()   {
    Position nextpos = getNextPosition();
    if (!nextpos.isEqual( Position::npos))
    {
        pos = nextpos;
    }
}
string Watson::str() const {
    return "Watson[index="+to_string(index)+";pos="+pos.str()+";moving_rule="+moving_rule+"]";
}
Criminal::Criminal(int index,const Position & init_pos, Map * map, Sherlock * sherlock, Watson * watson)
:Character(index,init_pos,map, "Criminal",0,0), sherlock(sherlock), watson(watson),stepcount(0){}
string Criminal::str() const {
    return "Criminal[index="+to_string(index)+";pos="+pos.str()+"]";
}
Position Criminal::getNextPosition()  {
    Position next = pos;
    Position sherlock_pos = sherlock->getCurrentPosition();
    Position watson_pos = watson->getCurrentPosition();
    int xs = sherlock_pos.getRow();
    int ys = sherlock_pos.getCol();
    int xw = watson_pos.getRow();
    int yw = watson_pos.getCol();
    int cmove [4][2] = {{-1,0},{0,-1},{1,0},{0,1}};
    int max = 0,i = 0, j = 0;
    int sdis, wdis;
    while (i < 4)
    {
        next.setRow(pos.getRow() + cmove[i][0]);
        next.setCol(pos.getCol() + cmove[i][1]);
        if (map->isValid(next, this))
        {
            if ((discal(next.getRow(),xs,next.getCol(),ys) + discal(next.getRow(),xw,next.getCol(),yw)) > max)  {
                max = discal(next.getRow(),xs,next.getCol(),ys) + discal(next.getRow(),xw,next.getCol(),yw);
                j = i;
            }
            next.setRow(pos.getRow() - cmove[i][0]);
            next.setCol(pos.getCol() - cmove[i][1]);
        }
        i++;
    }
    next.setRow(pos.getRow() + cmove[j][0]);
    next.setCol(pos.getCol() + cmove[j][1]);
    preposition = pos;
    if (map->isValid(next, this))
    {
        stepcount++;
        return next;
    }
    else
    {
        return Position::npos;
    }   
}
void Criminal::move()   {
    Position next = getNextPosition();
    if (!next.isEqual( Position::npos))
    {
        pos = next;
        // stepcount++;
    }
}
/*冰激凌*/
ArrayMovingObject::ArrayMovingObject(int capacity)
:capacity(capacity) {
    this->count = 0;
    arr_mv_objs = new MovingObject*[capacity];
}
ArrayMovingObject::~ArrayMovingObject() {}
bool ArrayMovingObject::isFull() const
{
    if (count == capacity)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool ArrayMovingObject::add(MovingObject * mv_obj)  
{
    if (count < capacity)
    {
        arr_mv_objs[count] = mv_obj;
        count++;
        return true;
    }
    else
    {
        return false;
    }  
}
MovingObject* ArrayMovingObject::get(int index) const  {
    return arr_mv_objs[index];
}
int ArrayMovingObject::size() const {
    return count;
}
string ArrayMovingObject::str() const   {
    string s = "ArrayMovingObject[count="+to_string(count)+";capacity="+to_string(capacity)+";";
    for (int i = 0; i < count ; i++) {
        s += ";";
        s += arr_mv_objs[i]->str();
        // if(i < count - 1){
        //     s += "\n";
        // }
    }
    return s+"]";
}

Configuration::Configuration(const string & filepath){
    // cout << "Da vao Constructor class Config" << endl;
    ifstream file(filepath);
    if(!file.is_open()){
        // cout << "Khong mo duoc file config" << endl;
    }
    string l;
    int k = 1;
    while (getline(file, l)){
        // cout << "read " << k << endl;
        k++;
        if (l.find("MAP_NUM_ROWS") != string::npos){
            map_num_rows = stoi(l.substr(l.find("=") + 1));
        }
        else if (l.find("MAP_NUM_COLS") != string::npos){
            map_num_cols = stoi(l.substr(l.find("=") + 1));
        }
        else if (l.find("MAX_NUM_MOVING_OBJECTS") != string::npos){
            // cout << "max num moving obj" << endl;
            max_num_moving_objects = stoi(l.substr(l.find("=") + 1));
        }
        else if (l.find("ARRAY_WALLS") != string::npos){
            string temp = l.substr(13, l.size() - 14);
            //// cout << temp << endl;
            int pos = 0;
            int o = 1;
            for (int i = 0; i < temp.size(); ++i){
                if (temp[i] == ';'){
                    o++;
                }
            }
            arr_walls = new Position[o];
            while (temp.find("(", pos) != string::npos)
            {
                int row = stoi( temp.substr(temp.find("(", pos) + 1, temp.find(",", pos) - temp.find("(", pos) - 1));
                int col = stoi( temp.substr(temp.find(",", pos) + 1, temp.find(")", pos) - temp.find(",", pos) - 1));
                arr_walls[num_walls].setRow(row);
                arr_walls[num_walls].setCol(col);
                num_walls++;
                pos = temp.find(")", pos+1);
            }
        }
        else if (l.find("ARRAY_FAKE_WALLS") != string::npos){
            string temp = l.substr(18, l.size() - 19);
            //cout <<"temp:" <<temp<<  ":" << endl;
            if(temp!=""){
                int pos = 0;
            int o = 1;
            for (int i = 0; i < temp.size(); ++i){
                if (temp[i] == ';'){
                    o++;
                }
            }
            arr_fake_walls = new Position[o];
            while (temp.find("(", pos) != string::npos)
            {
                int r = stoi( temp.substr(temp.find("(", pos) + 1, temp.find(",", pos) - temp.find("(", pos) - 1));
                int c = stoi( temp.substr(temp.find(",", pos) + 1, temp.find(")", pos) - temp.find(",", pos) - 1));
                arr_fake_walls[num_fake_walls].setRow(r);
                arr_fake_walls[num_fake_walls].setCol(c);
                num_fake_walls++;
                pos = temp.find(")", pos+1);
            }
            }else{
                num_fake_walls = 0;
                arr_fake_walls = new Position[0];
            }
        }
        else if (l.find("SHERLOCK_MOVING_RULE") != string::npos){
            sherlock_moving_rule = l.substr(l.find("=") + 1);
        }
        else if (l.find("SHERLOCK_INIT_POS") != string::npos){
            int r = stoi( l.substr(l.find("(") + 1, l.find(",") - l.find("(") - 1));
            int c = stoi( l.substr(l.find(",") + 1, l.find(")") - l.find(",") - 1));
            sherlock_init_pos.setRow(r);
            sherlock_init_pos.setCol(c);
        }
        else if (l.find("SHERLOCK_INIT_HP") != string::npos){
            sherlock_init_hp = stoi(l.substr(l.find("=") + 1));
        }
        else if (l.find("SHERLOCK_INIT_EXP") != string::npos){
            sherlock_init_exp = stoi(l.substr(l.find("=") + 1));
        }
        else if (l.find("WATSON_MOVING_RULE") != string::npos){
            watson_moving_rule = l.substr(l.find("=") + 1);
        }
        else if (l.find("WATSON_INIT_POS") != string::npos){
            int r = stoi( l.substr(l.find("(") + 1, l.find(",") - l.find("(") - 1));
            int c = stoi( l.substr(l.find(",") + 1, l.find(")") - l.find(",") - 1));
            watson_init_pos.setRow(r);
            watson_init_pos.setCol(c);
        }
        else if (l.find("WATSON_INIT_HP") != string::npos){
            watson_init_hp = stoi(l.substr(l.find("=") + 1));
        }
        else if (l.find("WATSON_INIT_EXP") != string::npos){
            // // cout << "watson init exp" << endl;
            watson_init_exp = stoi(l.substr(l.find("=") + 1));
        }
        else if (l.find("CRIMINAL_INIT_POS") != string::npos){
            int r = stoi( l.substr(l.find("(") + 1, l.find(",") - l.find("(") - 1));
            int c = stoi( l.substr(l.find(",") + 1, l.find(")") - l.find(",") - 1));
            criminal_init_pos.setRow(r);
            criminal_init_pos.setCol(c);
        }
        else if (l.find("NUM_STEPS") != string::npos){
            num_steps = stoi(l.substr(l.find("=") + 1));
        }
        
    }
    // // cout << "finish" <<endl;
}
Configuration::~Configuration()
{
    // delete[] arr_walls;
    // delete[] arr_fake_walls;
}
string Configuration::str() const
{
    // // cout <<"Start start" << endl;
    string configstr = "Configuration[\n";
    configstr += "MAP_NUM_ROWS=" + to_string(map_num_rows) + "\n";
    configstr += "MAP_NUM_COLS=" + to_string(map_num_cols) + "\n";
    configstr += "MAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) + "\n";
    configstr += "NUM_WALLS=" + to_string(num_walls) + "\n";
    configstr += "ARRAY_WALLS=[";
    // cout << "start str()" << endl;
    for (int i = 0; i < num_walls; i++){
        configstr += arr_walls[i].str() + ";";
    };

    // cout << "config str 1"<< endl;
    //configstr += arr_walls[num_walls - 1].str();
    configstr += "]\n";
    // cout << "1.25" << endl;
    // cout << to_string(num_fake_walls) << endl;
    configstr += "NUM_FAKE_WALLS=" + to_string(num_fake_walls) + "\n";
    configstr += "ARRAY_FAKE_WALLS=[";
    // cout << "config str 1.5"<< endl;
    for (int i = 0; i < num_fake_walls; i++){
        configstr += arr_fake_walls[i].str() + ";";
    }
    // cout << "config str 2"<< endl;
    //configstr += arr_fake_walls[num_fake_walls - 1].str();
    configstr += "]\n";
    configstr += "SHERLOCK_MOVING_RULE=" + sherlock_moving_rule + "\n";
    configstr += "SHERLOCK_INIT_POS=(" + to_string(sherlock_init_pos.getRow()) + "," + to_string(sherlock_init_pos.getCol()) + ")\n";
    configstr += "SHERLOCK_INIT_HP=" + to_string(sherlock_init_hp) + "\n";
    configstr += "SHERLOCK_INIT_EXP=" + to_string(sherlock_init_exp) + "\n";
    configstr += "WATSON_MOVING_RULE=" + watson_moving_rule + "\n";
    configstr += "WATSON_INIT_POS=(" + to_string(watson_init_pos.getRow()) + "," + to_string(watson_init_pos.getCol()) + ")\n";
    configstr += "WATSON_INIT_HP=" + to_string(watson_init_hp) + "\n";
    configstr += "WATSON_INIT_EXP=" + to_string(watson_init_exp) + "\n";
    configstr += "CRIMINAL_INIT_POS=(" + to_string(criminal_init_pos.getRow()) + "," + to_string(criminal_init_pos.getCol()) + ")\n";
    configstr += "NUM_STEPS=" + to_string(num_steps) + "\n";
    configstr += "]";
    // cout << "config str 3"<< endl;
    return configstr;
}

Robot* Robot::create(int index, Map* map, Criminal* criminal, Sherlock* sherlock, Watson* watson) {
    int sherlock_distance = abs(criminal->getCurrentPosition().getRow() - sherlock->getCurrentPosition().getRow()) +
                                         std::abs(criminal->getCurrentPosition().getCol() - sherlock->getCurrentPosition().getCol());
    int watson_distance = abs(criminal->getCurrentPosition().getRow() - watson->getCurrentPosition().getRow()) +
                                         std::abs(criminal->getCurrentPosition().getCol() - watson->getCurrentPosition().getCol());
    if(criminal->getstepcount() <= 2){
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

Robot::Robot(int index, const Position &init_pos, Map * map,RobotType robot_type,string name)
:MovingObject(index, init_pos, map, name), robot_type(robot_type) {
    int p = pos.getCol() * pos.getRow();
    int s = chudao(p);
    if (s == 0 || s == 1)   {
        item = new MagicBook();
    }
    else if (s == 2 || s == 3)  {
        item = new EnergyDrink();
    }
    else if (s == 4 || s == 5)
    {
        item = new FirstAid();
    }
    else if (s == 6 || s == 7)
    {
        item = new ExcemptionCard();
    }
    else if (s == 8 || s == 9)
    {
        int t = (pos.getRow() * 11 + pos.getCol()) % 4;
        if (t == 0)
        {
            item = new PassingCard("RobotS");
        }
        else if (t == 1)
        {
            item = new PassingCard("RobotC");
        }
        else if (t == 2)
        {
            item = new PassingCard("RobotSW");
        }
        else if (t == 3)
        {
            item = new PassingCard("all");
        }
    }else{
        item = nullptr;
    
    }
}
RobotC::RobotC( int index,const Position & init_pos,Map * map,Criminal * criminal)
:Robot(index, init_pos, map, C,"RobotC"), criminal(criminal)
{}
RobotS::RobotS(int index,const Position & init_pos,Map * map,Criminal * criminal,Sherlock *sherlock)
:Robot(index, init_pos, map, S,"RobotS"), criminal(criminal), sherlock(sherlock)
{}
RobotW::RobotW(int index,const Position & init_pos,Map * map,Criminal * criminal,Watson *watson)
:Robot(index, init_pos, map, W,"RobotW"), criminal(criminal), watson(watson)
{}
RobotSW::RobotSW(int index,const Position & init_pos,Map * map,Criminal * criminal,Sherlock * sherlock,Watson * watson)
:Robot(index, init_pos, map, SW,"RobotSW"),criminal(criminal),sherlock(sherlock),watson(watson)
{}
RobotType Robot::getType()
{
    return robot_type;
}
void Robot::move()
{
    Position next_pos = getNextPosition();
    if (!next_pos.isEqual(Position::npos)) pos = next_pos;
}
string RobotC::str() const
{
    return "Robot[pos=" + pos.str() +";type=" +"C"+ ";dist="+"]";
}
string RobotSW::str() const
{
    
    Position sherlock_pos = sherlock -> getCurrentPosition();
    int xs = sherlock_pos.getRow();
    int ys = sherlock_pos.getCol();
    Position w_pos = watson -> getCurrentPosition();
    int xw = w_pos.getRow();
    int yw = w_pos.getCol();
    string d = to_string(discal(xs, pos.getRow(), ys, pos.getCol()) + discal(xw, pos.getRow(), yw, pos.getCol()));
    return "Robot[pos=" + pos.str() +";type=" +"SW"+ ";dist=" + d + "]";
}
string RobotS::str() const  {
    Position sherlock_pos = sherlock -> getCurrentPosition();
    int x = sherlock_pos.getRow();
    int y = sherlock_pos.getCol();
    string d = to_string(discal(x, pos.getRow(), y, pos.getCol()));
    return "Robot[pos=" + pos.str() +";type=" +"S"+ ";dist=" + d + "]";
}
string RobotW::str() const  {
    Position w_pos = watson -> getCurrentPosition();
    int x = w_pos.getRow();
    int y = w_pos.getCol();
    string d = to_string(discal(x, pos.getRow(), y, pos.getCol()));
    return "Robot[pos=" + pos.str() +";type=" +"W"+ ";dist="+d+"]";
}
int RobotC::getDistance(Sherlock * sherlock)
{return  abs(getCurrentPosition().getRow() - sherlock->getCurrentPosition().getRow()) + abs(getCurrentPosition().getCol() - sherlock->getCurrentPosition().getCol());}
int RobotC::getDistance(Watson * watson)
{return  abs(getCurrentPosition().getRow() - watson->getCurrentPosition().getRow()) + abs(getCurrentPosition().getCol() - watson->getCurrentPosition().getCol());}
int RobotS::getDistance()
{return  abs(getCurrentPosition().getRow() - sherlock->getCurrentPosition().getRow()) + abs(getCurrentPosition().getCol() - sherlock->getCurrentPosition().getCol());}
int RobotW::getDistance()
{return  abs(getCurrentPosition().getRow() - watson->getCurrentPosition().getRow()) + abs(getCurrentPosition().getCol() - watson->getCurrentPosition().getCol());}
int RobotSW::getDistance()
{return  abs(getCurrentPosition().getRow() - sherlock->getCurrentPosition().getRow()) + abs(getCurrentPosition().getCol() - sherlock->getCurrentPosition().getCol()) + abs(getCurrentPosition().getRow() - watson->getCurrentPosition().getRow()) + abs(getCurrentPosition().getCol() - watson->getCurrentPosition().getCol());}
Position RobotC::getNextPosition()  {
    Position criminal_pos = criminal -> getpreposition();
    return criminal_pos;
}
Position RobotS::getNextPosition()
{
    Position next = pos;
    Position sherlock_pos = sherlock -> getCurrentPosition();
    Position criminal_pos = criminal -> getpreposition();
    int x = sherlock_pos.getRow();
    int y = sherlock_pos.getCol();
    int robotmove [4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
    int min = discal(next.getRow(), x, next.getCol(), y) + 4, i = 0, j = 0;
    while (i < 4)   {
        next.setRow(pos.getRow() + robotmove[i][0]);
        next.setCol(pos.getCol() + robotmove[i][1]);
        if (map->isValid(next, this))
        {
            if ((discal(next.getRow(), x, next.getCol(), y)) < min)
            {
                min = discal(next.getRow(), x, next.getCol(), y);
                j = i;
            }
            next.setRow(pos.getRow() - robotmove[i][0]);
            next.setCol(pos.getCol() - robotmove[i][1]);
        }
        i++;
    }
    next.setRow(pos.getRow() + robotmove[j][0]);
    next.setCol(pos.getCol() + robotmove[j][1]);
    if (map -> isValid(next, this)) {
        return next;
    }
    else    {
        return Position::npos;
    }
}
void RobotS::move()   {
    Position next = getNextPosition();
    if (!next.isEqual(Position::npos))
    {
        pos = next;
    }
}
Position RobotW::getNextPosition()
{
    Position next = pos;
    Position w_pos = watson -> getCurrentPosition();
    Position criminal_pos = criminal -> getpreposition();
    int x = w_pos.getRow();
    int y = w_pos.getCol();
    int robotmove [4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
    int min = discal(next.getRow(), x, next.getCol(), y) + 4, i = 0, j = 0;
    while (i < 4)   {
        next.setRow(pos.getRow() + robotmove[i][0]);
        next.setCol(pos.getCol() + robotmove[i][1]);
        if (map->isValid(next, this))
        {
            if ((discal(next.getRow(), x, next.getCol(), y)) < min)
            {
                min = discal(next.getRow(), x, next.getCol(), y);
                j = i;
            }
            next.setRow(pos.getRow() - robotmove[i][0]);
            next.setCol(pos.getCol() - robotmove[i][1]);
        }
        i++;
    }
    next.setRow(pos.getRow() + robotmove[j][0]);
    next.setCol(pos.getCol() + robotmove[j][1]);
    if (map -> isValid(next, this)) {
        return next;
    }
    else    {
        return Position::npos;
    }
}
void RobotW::move()   {
    Position next = getNextPosition();
    if (!next.isEqual(Position::npos))
    {
        pos = next;
    }
}

Position RobotSW::getNextPosition()
{
    //TODO
    Position next = pos;
    Position sherlock_pos = sherlock -> getCurrentPosition();
    Position w_pos = watson -> getCurrentPosition();
    Position criminal_pos = criminal -> getpreposition();
    int xw = w_pos.getRow();
    int yw = w_pos.getCol();
    int xs = sherlock_pos.getRow();
    int ys = sherlock_pos.getCol();
    int robotmove [8][2] = {{-2,0},{-1,1},{0,2},{1,1},{2,0},{1,-1},{0,-2},{-1,-1}};
    int min = discal(next.getRow(), xs, next.getCol(), ys) + discal(next.getRow(), xw, next.getCol(), yw) + 100, i = 0, j = 0;
    while (i < 8)   {
        next.setRow(pos.getRow() + robotmove[i][0]);
        next.setCol(pos.getCol() + robotmove[i][1]);
        if (map->isValid(next, this))
        {
            if ((discal(next.getRow(), xs, next.getCol(), ys) + discal(next.getRow(), xw, next.getCol(), yw)) < min)
            {
                min = discal(next.getRow(), xs, next.getCol(), ys) + discal(next.getRow(), xw, next.getCol(), yw);
                j = i;
            }
            next.setRow(pos.getRow() - robotmove[i][0]);
            next.setCol(pos.getCol() - robotmove[i][1]);
        }
        i++;
    }
    next.setRow(pos.getRow() + robotmove[j][0]);
    next.setCol(pos.getCol() + robotmove[j][1]);
    if (map -> isValid(next, this)) {
        return next;
    }
    else    {
        return Position::npos;
    }
}
void RobotSW::move()   {
    Position next = getNextPosition();
    if (!next.isEqual(Position::npos))
    {
        pos = next;
    }
}

// class BaseBag
BaseBag::BaseBag(int capacity){
    this->capacity = capacity;
    count = 0;
    head = nullptr; 
}
bool MagicBook::canUse (Character* obj, Robot * robot)  {
    if(robot){
        return false;
   }else if(obj->getEXP() > 350) return false;
   return true;
}

void MagicBook::use(Character* obj,Robot* robot){
    if(canUse(obj,robot)){
        obj->setEXP(ceil(obj->getEXP()*1.25));
    }
}

bool EnergyDrink::canUse (Character* obj, Robot * robot)  {
    if(robot){
        return false;
    }else if(obj->getHP() > 100) return false;
    return true;
}

void EnergyDrink::use(Character* obj,Robot* robot){
    if(canUse(obj,robot)){
        obj->setHP(ceil(obj->getHP()*1.2));
    }
}

bool FirstAid::canUse (Character* obj, Robot * Robot)  {
    if(Robot){
        return false;
    }else if(obj->getHP() > 100 && obj->getEXP() > 350) return false;
    return true;
}

void FirstAid::use(Character* obj,Robot* robot){
    if(canUse(obj,robot)){
        obj->setHP(ceil(obj->getHP()*1.5));
    }
}

bool ExcemptionCard::canUse (Character* obj, Robot * Robot)  {

    if(!Robot){
        return false;
    }else if((obj->getName()!="Sherlock")||(obj->getHP()%2!=1)) return false;
    return true;
}

bool PassingCard::canUse(Character* obj,Robot* robot){
    if(!robot){
        return false;
    }else if((obj->getName()!="Watson")||(obj->getEXP()%2!=0)) return false;
    return true;
}
void PassingCard::use(Character* obj,Robot* robot){
    if(this->challenge == "RobotS"&&robot->getRobotType() != S){
        obj->setEXP(obj->getEXP() - 50);
    }else if(this->challenge == "RobotC"&&robot->getRobotType() != C){
        obj->setEXP(obj->getEXP() - 50);
    }else if(this->challenge == "RobotW"&&robot->getRobotType() != W){
        obj->setEXP(obj->getEXP() - 50);
    }else if(this->challenge == "RobotSW"&&robot->getRobotType() != SW){
        obj->setEXP(obj->getEXP() - 50);
    }else if(this->challenge == "all"){
        return;
    }
    
}
bool BaseBag::insert(BaseItem* item)    {
    if (count >= capacity)  {
        return false;
    }
    else{
        NodeItem* newItem = new NodeItem(item);
        if (head == nullptr)    {
            head = newItem;
        }
        else
        {
            newItem->next = head;
            head = newItem;
        }
        count++;
        return true;
    }
}
BaseItem* BaseBag::get(ItemType itemtype)    {
    NodeItem *temp= head;
    if(head == nullptr||head->item){
        return nullptr;
    }
    if (head->item->getItem() == itemtype)
    {
        head = head->next;
        count--;
        return temp->item;
    }
    else    {
        while (temp != nullptr) {
            if (temp->item->getItem() == itemtype)
            {
                NodeItem *swapitem;
                swapitem->item = temp -> item;
                temp->item = head->item;
                head->item = swapitem->item;
                head = head->next;
                count--;
                return temp->item;
            }
        }
    }
    return nullptr;
}

// BaseItem* WatsonBag::get(ItemType itemType) {
//     NodeItem* current = head;
//     while (current != nullptr) {
//         if (current->item->getType() == itemType) {
//             BaseItem* item = current->item;
//             // Remove item from bag
//              if (current == head) {
//                     head = head->next;
//                 }else if(head->next == current){
//                     head->next = current->next;
//                     // delete current;
//                     // count--;
//                     // return item;
//                 }
//                  else {
//                         ItemNode* prev = head;
//                     while (prev->next != current) {
//                         prev = prev->next;
//                     }
//                     ItemNode* temp = head->next;
//                     prev->next = head;
//                     head->next = current->next;
//                     head = temp;
//                 }
//             delete current;
//             count--;
//             return item;
//         }
//         current = current->next;
//     }
//     //cerr << "Item type not found in bag." << endl;
//     return nullptr;
// }
string BaseBag::str()  {
    stringstream ss;
    ss << "Bag[count=" << count <<";";
    // if(head!=nullptr){
    //     ss << ";";
    // }
    NodeItem *current = head;
    while (current != nullptr) {
        // ss << current->item->getType(); // Adding item type to the string
        if(current->item->getItem() == ENERGY_DRINK){
            ss << "EnergyDrink";
        }else if(current->item->getItem() == FIRST_AID){
            ss << "FirstAid";
        }else if(current->item->getItem() == MAGIC_BOOK){
            ss << "MagicBook";
        }else if (current->item->getItem() == EXCEMPTION_CARD){
            ss << "ExcemptionCard";
        }else if (current->item->getItem() == PASSING_CARD){
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


bool Sherlock::meet(RobotS* robotS)
{
    // TODO: Xử lý khi gặp robot S
    //cout << "Sherlock Meet RobotS" << endl;
    // bool pass = false;
    //ItemNode* headbag = this->getBag()->getHead();
    BaseItem* item = this->getBag()->get(EXCEMPTION_CARD);
    if(item == nullptr || this->getHP()%2 == 0){
        if(this->getEXP()>400){
        this->getBag()->insert(robotS->getItem());
        }else{
        this->setEXP(ceil(this->getEXP()*0.9));
        }
    }
    NodeItem* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getItem());
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

    NodeItem* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getItem());
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
    
    if(item == nullptr || this->getHP()%2 == 0){
        if(this->getEXP()>300&&this->getHP()>335){
        this->getBag()->insert(robotSW->getItem());
    }else{
        this->setHP(ceil(this->getHP()*0.85));
        this->setEXP(ceil(this->getEXP()*0.85));
    }
    }
    NodeItem* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getItem());
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
    if(item == nullptr || this->getHP()%2 == 0){
        if(this->getEXP()>500){
        return true;
    }else{
        // 
        // cout << robotC->getItem()->getItem() << endl;
        this->getBag()->insert(robotC->getItem());
    }
    }
    NodeItem* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getItem());
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
    NodeItem* gift = this->getBag()->deleteItemSherlock(PASSING_CARD);
    // cout << watson->getCurrentPosition() << endl;
    // cout << watson->getBag()->str() << endl;
    // if(gift!=nullptr){
    //     cout << gift->item->getType() << endl;
    // }
    NodeItem* temp = gift;
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

    NodeItem* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getItem());
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
   // OUTPUT << "Watson Meet RobotW" << endl;

    BaseItem* item = nullptr;
    if(this->getHP()%2==0){
        item = this->getBag()->get(PASSING_CARD);
        if(item!=nullptr){
        item->use(this,robotW);
        }
    }
    if(item == nullptr){
        if(this->getHP()>350){
        //OUTPUT << "RobotW insert: " << robotW->getItem()->getItem() << endl;
        this->getBag()->insert(robotW->getItem());
    }else{
        this->setHP(ceil(this->getHP()*0.95));
    }
    }
    NodeItem* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getItem());
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
    if(this->getHP()%2==0){
        item = this->getBag()->get(PASSING_CARD);
        if(item!=nullptr){
        item->use(this,robotSW);
        }
    }
    if(item == nullptr){
       if(this->getHP()>165&&this->getEXP()>600){
        this->getBag()->insert(robotSW->getItem());
    }else{
        this->setHP(ceil(this->getHP()*0.85));
        this->setEXP(ceil(this->getEXP()*0.85));
    }
    }
    NodeItem* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getItem());
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
    if(this->getHP()%2==0){
        item = this->getBag()->get(PASSING_CARD);
        if(item!=nullptr){
        item->use(this,robotC);
        }
    }
    // if(item == nullptr){
     
    // }
    this->getBag()->insert(robotC->getItem());
    
    NodeItem* headbag = this->getBag()->getHead();
    while(headbag!=nullptr){
        if(headbag->item->canUse(this,nullptr)){
            this->getBag()->get(headbag->item->getItem());
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
    NodeItem* gift = sherlock->getBag()->deleteItemSherlock(PASSING_CARD);
    NodeItem* temp = gift;
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
    
    
bool ArrayMovingObject::checkMeet(int index)
{
   //cout << "Vo ham checkMeet" << endl;
        for(int i = 0; i < count; i++){
            if(i != index){
                if(arr_mv_objs[i]->getCurrentPosition().isEqual(arr_mv_objs[index]->getCurrentPosition().getRow(),arr_mv_objs[index]->getCurrentPosition().getCol())){
                    // cout << "Gap nhau roi ne" << endl;
                    // cout << arr_mv_objs[i]->getName() << " " << arr_mv_objs[index]->getName() << endl;
                    if((arr_mv_objs[index]->getName()=="Sherlock"&&arr_mv_objs[i]->getName()=="Criminal")
                    ||(arr_mv_objs[index]->getName()=="Criminal"&&arr_mv_objs[i]->getName()=="Sherlock")){
                        return true;
                    }
                    if((arr_mv_objs[index]->getName()=="Watson"&&arr_mv_objs[i]->getName()=="Criminal")
                    ||(arr_mv_objs[index]->getName()=="Criminal"&&arr_mv_objs[i]->getName()=="Watson")){
                        return true;
                    }
                    if(arr_mv_objs[index]->getName()=="Sherlock"&&arr_mv_objs[i]->getName()=="RobotS"){
                        // cout << "Sherlock Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[index])->meet(dynamic_cast<RobotS*>(arr_mv_objs[i]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="RobotS"&&arr_mv_objs[i]->getName()=="Sherlock"){
                        // cout << "RobotS Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[i])->meet(dynamic_cast<RobotS*>(arr_mv_objs[index]));
                        //return false;
                    }
                    else if(arr_mv_objs[index]->getName()=="Sherlock"&&arr_mv_objs[i]->getName()=="RobotW"){
                        // cout << "Sherlock Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[index])->meet(dynamic_cast<RobotW*>(arr_mv_objs[i]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="RobotW"&&arr_mv_objs[i]->getName()=="Sherlock"){
                        // cout << "RobotW Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[i])->meet(dynamic_cast<RobotW*>(arr_mv_objs[index]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="Sherlock"&&arr_mv_objs[i]->getName()=="RobotSW"){
                        // cout << "Sherlock Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[index])->meet(dynamic_cast<RobotSW*>(arr_mv_objs[i]));
                        //return false;   
                    }
                    else if(arr_mv_objs[index]->getName()=="RobotSW"&&arr_mv_objs[i]->getName()=="Sherlock"){
                        // cout << "RobotSW Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[i])->meet(dynamic_cast<RobotSW*>(arr_mv_objs[index]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="RobotC"&&arr_mv_objs[i]->getName()=="Sherlock"){
                        // cout << "RobotC Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[i])->meet(dynamic_cast<RobotC*>(arr_mv_objs[index]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="Sherlock"&&arr_mv_objs[i]->getName()=="RobotC"){
                        // cout << "Sherlock Meet: " << arr_mv_objs[i]->getName() << endl;
                        return dynamic_cast<Sherlock*>(arr_mv_objs[index])->meet(dynamic_cast<RobotC*>(arr_mv_objs[i]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="Watson"&&arr_mv_objs[i]->getName()=="RobotS"){
                        // cout << "Watson Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[index])->meet(dynamic_cast<RobotS*>(arr_mv_objs[i]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="RobotS"&&arr_mv_objs[i]->getName()=="Watson"){
                        // cout << "RobotS Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[i])->meet(dynamic_cast<RobotS*>(arr_mv_objs[index]));
                        //return false;
                    }
                    else if(arr_mv_objs[index]->getName()=="Watson"&&arr_mv_objs[i]->getName()=="RobotW"){
                        // cout << "Watson Meet: " << arr_mv_objs[i]->getName() << endl;
                        //cout << "Watson Meet RobotW" << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[index])->meet(dynamic_cast<RobotW*>(arr_mv_objs[i]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="RobotW"&&arr_mv_objs[i]->getName()=="Watson"){
                        // cout << "RobotW Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[i])->meet(dynamic_cast<RobotW*>(arr_mv_objs[index]));
                        //return false;
                    }
                    else if(arr_mv_objs[index]->getName()=="Watson"&&arr_mv_objs[i]->getName()=="RobotSW"){
                        // cout << "Watson Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[index])->meet(dynamic_cast<RobotSW*>(arr_mv_objs[i]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="RobotSW"&&arr_mv_objs[i]->getName()=="Watson"){
                        // cout << "RobotSW Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[i])->meet(dynamic_cast<RobotSW*>(arr_mv_objs[index]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="Watson"&&arr_mv_objs[i]->getName()=="RobotC"){
                        // cout << "Watson Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[index])->meet(dynamic_cast<RobotC*>(arr_mv_objs[i]));
                        //return false;
                    } else if(arr_mv_objs[index]->getName()=="RobotC"&&arr_mv_objs[i]->getName()=="Watson"){
                        // cout << "RobotC Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[i])->meet(dynamic_cast<RobotC*>(arr_mv_objs[index]));
                        //return false;
                    }
                    else if(arr_mv_objs[index]->getName()=="Sherlock"&&arr_mv_objs[i]->getName()=="Watson"){
                        // cout << "Sherlock Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Sherlock*>(arr_mv_objs[index])->meet(dynamic_cast<Watson*>(arr_mv_objs[i]));
                        //return false;
                    }else if(arr_mv_objs[index]->getName()=="Watson"&&arr_mv_objs[i]->getName()=="Sherlock"){
                        // cout << "Watson Meet: " << arr_mv_objs[i]->getName() << endl;
                        dynamic_cast<Watson*>(arr_mv_objs[index])->meet(dynamic_cast<Sherlock*>(arr_mv_objs[i]));
                        //return false;
                    }
                    
                }
            }
        }
        return false;
}
    
    

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
///////////////////////////////////////////////