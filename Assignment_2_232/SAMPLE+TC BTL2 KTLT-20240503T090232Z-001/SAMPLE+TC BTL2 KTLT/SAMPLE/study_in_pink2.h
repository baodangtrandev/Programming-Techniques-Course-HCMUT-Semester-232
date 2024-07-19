/**
 * By: Quoc Anh
 * NHẬN BẢN MẪU ĐẦY ĐỦ TẠI ĐÂY: https://www.m.me/quocanhcse
 * 
 * 
 * Facebook: https://www.facebook.com/quocanhcse
 * Group hỗ trợ: https://www.facebook.com/groups/hcmut.thaoluancse
*/

#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

// Forward declaration
class Position;

class MapElement;
class Path;
class Wall;
class FakeWall;

class Map;

class MovingObject;
class Character;
class Sherlock;
class Watson;
class Criminal;

class ArrayMovingObject;

class Configuration;

class RobotS;
class RobotW;
class RobotSW;
class RobotC;

class BaseItem;
class MagicBook;
class EnergyDrink;
class FirstAid;
class ExemptionCard;
class PassingCard;

class BaseBag;
class SherlockBag;
class WatsonBag;

class StudyPinkProgram;
class TestStudyPink;

enum ItemType
{
    MAGIC_BOOK,
    ENERGY_DRINK,
    FIRST_AID,
    EXCEMPTION_CARD,
    PASSING_CARD
};
enum ElementType
{
    PATH,
    WALL,
    FAKE_WALL
};
enum RobotType
{
    C = 0,
    S,
    W,
    SW
};

// Hàm hỗ trợ - Support functions
// Tao 1 ham ho tro de tinh khoang cach giua 2 vi tri
// dung cho sau nay

/**
 * CLASS POSITION
 **/
class Position
{
private:
    int r, c;

public:
    friend class TestStudyPink;
    static const Position npos;

    // Constructor
    Position(int in_r = 0, int in_c = 0) {}
    Position(const string &str_pos);

    // Getter & Setter
    int getRow() const {}
    int getCol() const {}
    void setRow(int r) {}
    void setCol(int c) {}

    // Tạo chuỗi string Position
    string str() const {}

    // So sánh vị trí
    bool isEqual(int in_r, int in_c) const {}

    // Đinh nghia them ham isEqual với tham số là Position
};

/**
 * CLASS MAP ELEMENT
 * CLASS PATH
 * CLASS WALL
 * CLASS FAKE WALL
 */
class MapElement
{
protected:
    ElementType type;

public:
    friend class TestStudyPink;

    // Constructor & Destructor
    MapElement(ElementType in_type) {}
    virtual ~MapElement() {}

    // Kiểm tra loại phần tử
    virtual ElementType getType() const {}
};

// PATH
class Path : public MapElement
{
public:
    friend class TestStudyPink;

    Path() {}
};

// WALL
class Wall : public MapElement
{
public:
    friend class TestStudyPink;

    Wall() {}
};

// FAKE WALL
class FakeWall : public MapElement
{
private:
    int req_exp;

public:
    friend class TestStudyPink;

    FakeWall(int in_req_exp) {}

    // Lấy số exp cần để vượt qua
    int getReqExp() const {}
};

/**
 * CLASS MAP
 */
class Map
{
private:
    int num_rows, num_cols;
    MapElement ***map;
    // Có thể dùng ** nếu muốn

public:
    friend class TestStudyPink;

    // Constructor & Destructor
    Map(int in_num_rows, int in_num_cols, int in_num_walls, Position *in_array_walls, int in_num_fake_walls, Position *in_array_fake_walls);
    ~Map();

    // Kiểm tra vị trí có hợp lệ với MovingObject không
    bool isValid(const Position &pos, MovingObject *mv_obj) const;
};

/**
 * CLASS MOVING OBJECT
 * CLASS CHARACTER
 * CLASS SHERLOCK
 * CLASS WATSON
 * CLASS CRIMINAL
 */

// MOVING OBJECT
class MovingObject
{
protected:
    int index;
    Position pos;
    Map *map;
    string name;

    // Nên thêm một biến lưu số bước đã đi

public:
    friend class TestStudyPink;

    // Constructor & Destructor
    MovingObject(int index, const Position pos, Map *map, const string &name = "") virtual ~MovingObject() {}

    // Getter
    virtual Position getNextPosition() = 0;
    Position getCurrentPosition() const {}

    // Di chuyển
    virtual void move();

    // Tạo chuỗi string MovingObject
    virtual string str() const = 0;

    // Tạo thêm các hàm getter lấy thông tin khác
};

// CHARACTER
class Character : public MovingObject
{
public:
    friend class TestStudyPink;

    // Constructor
    Character(int index, const Position pos, Map *map, const string &name = "") {}

    // TẠO CHO ĐÚNG YÊU CẦU THÔI CHỨ THÍCH LÀM GÌ THÌ LÀM NHA
};

// SHERLOCK
class Sherlock : public Character
{
private:
    string moving_rule;
    int hp;
    int exp;

public:
    friend class TestStudyPink;

    // Constructor
    Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp) {}

    // Getter & Setter
    // TẠO CÁC HÀM GETTER & SETTER CHO CÁC THUỘC TÍNH ĐỂ DỄ DÀNG TRUY XUẤT

    // Lấy vị trí tiếp theo
    Position getNextPosition() override;

    // Tạo chuỗi string Sherlock
    string str() const override {}

    // Hành động sau khi di chuyển
    // TẠO CÁC HÀM MIÊU TẢ HÀNH ĐỘNG SAU KHI DI CHUYỂN (GẶP ROBOT, GẶP WATSON, ...)
};

// WATSON
class Watson : public Character
{
private:
    string moving_rule;
    int hp;
    int exp;

public:
    friend class TestStudyPink;

    // Constructor
    Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp) {}

    // TƯƠNG TỰ NHƯ SHERLOCK, KHÔNG KHÁC BIỆT GÌ NHIỀU
};

// CRIMINAL
class Criminal : public Character
{
private:
    Sherlock *sherlock;
    Watson *watson;
    // TẠO BIẾN LƯU VỊ TRÍ TRƯỚC ĐÓ ĐỂ TẠO ROBOT
    // TẠO BIẾN LƯU SỐ BƯỚC ĐÃ ĐI THỰC TỂ DÙNG ĐỂ TẠO ROBOT
public:
    friend class TestStudyPink;

    // Constructor
    Criminal(int index, const Position &init_pos, Map *map, Sherlock *sherlock, Watson *watson) {}

    // Lấy vị trí tiếp theo
    Position getNextPosition() override;

    // TẠO CÁC HÀM PHỤC VỤ VIỆC TẠO ROBOT (TÙY THEO YÊU CẦU ĐỀ BÀI)

    // Di chuyển
    void move() override;

    // Tạo chuỗi string Criminal
    string str() const override {}

    // TẠO CÁC HÀM GETTER & SETTER CHO CÁC THUỘC TÍNH ĐỂ DỄ DÀNG TRUY XUẤT
};

/**
 * CLASS ARRAY MOVING OBJECT
 */
class ArrayMovingObject
{
public:
    MovingObject **arr_mv_objs;
    int count;
    int capacity;

public:
    friend class TestStudyPink;

    // Constructor & Destructor
    ArrayMovingObject(int capacity){};

    ~ArrayMovingObject() {}

    // Kiểm tra mảng đầy
    bool isFull() const {}

    // Thêm MovingObject vào mảng
    bool add(MovingObject *mv_obj);

    // Lấy số lượng MovingObject
    int getMovingObjectCount() const {}

    // TẠO HÀM TRẢ VỀ MOVINGOBJECT THEO INDEX, CÓ THỂ TRUY XUẤT TRỰC TIẾP TỪ BIẾN NẾU BIẾN LÀ PUBLIC

    string str() const;
};

/**
 * CLASS CONFIGURATION
 */
class Configuration
{
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

public:
    friend class TestStudyPink;

    // Constructor & Destructor
    Configuration(const string &filepath);
    ~Configuration();
    string str() const;

    // TẠO HÀM GETTER CHO TỪNG THUỘC TÍNH ĐỂ DỄ DÀNG TRUY XUẤT
};

/**
 * CLASS ROBOT
 * CLASS ROBOT C
 * CLASS ROBOT S
 * CLASS ROBOT W
 * CLASS ROBOT SW
 */

// ROBOT
class Robot : public MovingObject
{
private:
    RobotType robot_type;
    BaseItem *item;

public:
    friend class TestStudyPink;

    Criminal *criminal;

    // Constructor & Destructor
    Robot(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal);
    ~Robot();

    // Getter
    // THÊM CÁC PHƯƠNG THỨC GETTER ĐỂ DỄ TRUY XUẤT
};

// ROBOT C
class RobotC : public Robot
{
public:
    friend class TestStudyPink;

    // Constructor
    RobotC(int index, const Position &init_pos, Map *map, Criminal *criminal) {}

    // Lấy vị trí tiếp theo
    Position getNextPosition() override {}

    // Lấy khoảng cách
    int getDistance(Character *character) const {}

    // Tạo chuỗi string RobotC
    string str() const override {}
};

// ROBOT S
class RobotS : public Robot
{
public:
    friend class TestStudyPink;

    Sherlock *sherlock;

    // Constructor
    RobotS(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock) {}

    // Lấy vị trí tiếp theo
    Position getNextPosition() override;

    // Lấy khoảng cách
    int getDistance() const {}

    // Tạo chuỗi string RobotS
    string str() const override {}
};

// ROBOT W
class RobotW : public Robot
{
public:
    friend class TestStudyPink;

    Watson *watson;

    // Constructor
    RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson);

    // Lấy vị trí tiếp theo
    Position getNextPosition() override;

    // Lấy khoảng cách
    int getDistance() const {}

    // Tạo chuỗi string RobotW
    string str() const override {}
};

// ROBOT SW
class RobotSW : public Robot
{
public:
    friend class TestStudyPink;

    Sherlock *sherlock;
    Watson *watson;

    // Constructor
    RobotSW(int index, const Position &init_pos, Map *map, Criminal *criminal, Sherlock *sherlock, Watson *watson) {}

    // Lấy vị trí tiếp theo
    Position getNextPosition() override;

    // Lấy khoảng cách
    int getDistance() const;

    // Tạo chuỗi string RobotSW
    string str() const override {}
};

/**
 * CLASS BASE ITEM
 * CLASS MAGIC BOOK
 * CLASS ENERGY DRINK
 * CLASS FIRST AID
 * CLASS EXCEMPTION CARD
 * CLASS PASSING CARD
 */

// BASE ITEM
class BaseItem
{
public:
    friend class TestStudyPink;

    string name;

    // Constructor
    // TỰ ĐỊNH NGHĨA

    virtual bool canUse(Character *character, Robot *robot = NULL) = 0;
    virtual void use(Character *character, Robot *robot = NULL) = 0;

    // THÊM CÁC PHƯƠNG THỨC GETTER
};

// MAGIC BOOK
class MagicBook : public BaseItem
{
public:
    friend class TestStudyPink;
    // Constructor
    // TỰ ĐỊNH NGHĨA

    bool canUse(Character *character, Robot *robot) override;
    void use(Character *character, Robot *robot) override;
};

// ENERGY DRINK
class EnergyDrink : public BaseItem
{
public:
    friend class TestStudyPink;

    // Constructor
    // TỰ ĐỊNH NGHĨA

    bool canUse(Character *character, Robot *robot) override;
    void use(Character *character, Robot *robot) override;
};

// FIRST AID
class FirstAid : public BaseItem
{
public:
    friend class TestStudyPink;

    // Constructor
    // TỰ ĐỊNH NGHĨA

    bool canUse(Character *character, Robot *robot) override;
    void use(Character *character, Robot *robot) override;
};

// EXCEMPTION CARD
class ExcemptionCard : public BaseItem
{
public:
    friend class TestStudyPink;

    // Constructor
    // TỰ ĐỊNH NGHĨA

    bool canUse(Character *character, Robot *robot) override;
    void use(Character *character, Robot *robot) override;
};

// PASSING CARD
class PassingCard : public BaseItem
{
public:
    friend class TestStudyPink;

    string challenge;

    // Constructor
    // TỰ ĐỊNH NGHĨA

    bool canUse(Character *character, Robot *robot) override;
    void use(Character *character, Robot *robot) override;
};

/**
 * CLASS BASE BAG
 * CLASS SHERLOCK BAG
 * CLASS WATSON BAG
 */

// NODE ITEM
struct NodeItem
{
    BaseItem *item;
    NodeItem *next;

    // LÀM TIẾP THÔI
};

// BASE BAG
class BaseBag
{
protected:
    int capacity;
    int count;
    Character *obj;
    NodeItem *head;

public:
    friend class TestStudyPink;

    // Constructor & Destructor
    BaseBag() {}
    ~BaseBag();

    // Thêm Item vào Bag
    virtual bool insert(BaseItem *item);

    virtual BaseItem *get();
    virtual BaseItem *get(ItemType itemType);

    // Tạo chuỗi string Bag
    virtual string str() const;
};

// SHERLOCK BAG
class SherlockBag : public BaseBag
{
public:
    friend class TestStudyPink;

    // Constructor
    SherlockBag(Sherlock *sherlock);
};

// WATSON BAG
class WatsonBag : public BaseBag
{
public:
    friend class TestStudyPink;

    // Constructor
    WatsonBag(Watson *watson);
};

/**
 * CLASS STUDY PINK PROGRAM
 */
class StudyPinkProgram
{
private:
    Configuration *config;
    Sherlock *sherlock;
    Watson *watson;
    Criminal *criminal;
    Map *map;
    ArrayMovingObject *arr_mv_objs;
    SherlockBag *sherlock_bag;
    WatsonBag *watson_bag;

public:
    friend class TestStudyPink;

    // Constructor & Destructor
    StudyPinkProgram(const string &config_file_path);

    bool isStop() const;
    void printResult() const;
    void printStep(int si) const;
    void run(bool verbose);

    ~StudyPinkProgram();
};

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif // _H_STUDY_IN_PINK_2_H_
