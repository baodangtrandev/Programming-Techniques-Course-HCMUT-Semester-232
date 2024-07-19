#include "fight.h"
// ! Nội dung task cũ cần bỏ vào (chỉ bỏ dòng #include "moving.h")
// ! Các mục sửa đổi:
// ! HÀM KHỞI TẠO: Sherlock và Watson thêm thuộc tính bag, Robot thêm thuộc tính để sinh item
// !
Robot::Robot(int index, const Position &pos, Map *map, RobotType robot_type, Criminal *criminal, const string &name)
    : MovingObject(index, pos, map, name), criminal(criminal), robot_type(robot_type) //! khác
{
    // TODO: tính toán loại item
}
Sherlock::Sherlock(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
    : Character(index, init_pos, map, "Sherlock"), moving_rule(moving_rule), HP(init_hp), EXP(init_exp), index_moving_rule(0)
{
    // TODO: thêm thuộc tính bag
}
Watson::Watson(int index, const string &moving_rule, const Position &init_pos, Map *map, int init_hp, int init_exp)
    : Character(index, init_pos, map, "Watson"), moving_rule(moving_rule), HP(init_hp), EXP(init_exp), index_moving_rule(0)
{
    // TODO: thêm thuộc tính bag
}
void StudyPinkProgram::run(ofstream &OUTPUT)
{
    if (!OUTPUT.is_open())
    {
        return;
    }
    bool stop = arr_mv_objs->checkMeet(0) || sherlock->getHP() == 0 || watson->getHP() == 0;
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
            if (arr_mv_objs->get(i)->getObjectType() == MovingObjectType::CRIMINAL)
            {
                robot = Robot::create(arr_mv_objs->size(), map, criminal, sherlock, watson);
            }
            arr_mv_objs->get(i)->move();
            if (robot != nullptr)
            {
                if (criminal->getCount() % 3 == 0 && criminal->getCount() > 0)
                {
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
                   << "Sherlock HP_" << sherlock->getHP() << " EXP_" << sherlock->getEXP() << endl
                   << "Watson HP_" << watson->getHP() << " EXP_" << watson->getEXP() << endl
                   << "SherlockBag : " << sherlock->getBag()->str() << endl
                   << "WatsonBag : " << watson->getBag()->str() << endl;
        }
    }
    OUTPUT << "---------------" << endl
           << "RESULT : ";

    if (watson->getHP() == 0)
        OUTPUT << "Watson can not continue the journey";
    else if (sherlock->getHP() == 0)
        OUTPUT << "Sherlock can not continue the journey";
    else if (stop)
        OUTPUT << "The Criminal was caught";
    else
        OUTPUT << "The Criminal escaped";
}
// *------------------------------------------------------------------
// *
// *------------------------------------------------------------------
// !-----------------------------------
// ! Lưu ý về việc xét thông số khi tăng giảm
// ! Các thay đổi thông số là dựa trên thông số hiện tại
// ! Các thông số không phải số nguyên THỰC HIỆN LÀM TRÒN LÊN -> NHÂN VẬT CHỈ HI SINH KHI INIT HP = 0
// !-----------------------------------
// *CLASS: ArrayMovingObject
bool ArrayMovingObject::checkMeet(int index)
{
    // TODO: Xét va chạm của nhân vật (theo index) với các nhân vật khác trong array
    // TODO: Thực hiện xử lý các sự kiện xảy ra (thử thách, thêm item, bắt Criminal)
}
// *CLASS: Sherlock
// ! Lưu ý: ExcemptionCard được dùng để BỎ QUA nếu THỬ THÁCH THẤT BẠI -> xem như không thực hiện thử thách -> không gọi get lần 2
// ! Thực hiện get từ bag sau khi insert item
bool Sherlock::meet(RobotS *robotS)
{
    // TODO: Xử lý khi gặp robot S
}
bool Sherlock::meet(RobotW *robotW)
{
    // TODO: Xử lý khi gặp robot W
}
bool Sherlock::meet(RobotSW *robotSW)
{
    // TODO: Xử lý khi gặp robot SW
}
bool Sherlock::meet(RobotC *robotC)
{
    // TODO: Xử lý khi gặp robot C
}
bool Sherlock::meet(Watson *watson)
{
    // TODO: Xử lý trao đổi thẻ ExcemptionCard
    // TODO: KHI CẢ 2 ĐỀU CÓ THỂ TRAO ĐỔI && ĐỔI TOÀN BỘ NẾU NHIỀU HƠN 1 (KỂ CẢ KHI ĐỐI PHƯƠNG)
}
// *CLASS: Watson
// ! Lưu ý: PassingCard được dùng khi GẶP ROBOT để bỏ qua thử thách nếu đúng loại thẻ
// ! Thực hiện get từ bag sau khi insert item
bool Watson::meet(RobotS *robotS)
{
    // TODO: Xử lý trao đổi khi gặp robot S
}
bool Watson::meet(RobotW *robotW)
{
    // TODO: Xử lý trao đổi khi gặp robot W
}
bool Watson::meet(RobotSW *robotSW)
{
    // TODO: Xử lý trao đổi khi gặp robot SW
}
bool Watson::meet(RobotC *robotC)
{
    // TODO: Xử lý trao đổi khi gặp robot C
}
bool Watson::meet(Sherlock *sherlock)
{
    // TODO: Xử lý trao đổi khi gặp Sherlock
}

BaseBag *Sherlock::getBag() const
{
    // TODO: get bag
}
BaseBag *Watson::getBag() const
{
    // TODO: get bag
}