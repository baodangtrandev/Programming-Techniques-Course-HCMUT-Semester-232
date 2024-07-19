/**
 * By: Quoc Anh
 * NHẬN BẢN MẪU ĐẦY ĐỦ TẠI ĐÂY: https://www.m.me/quocanhcse
 * 
 * 
 * Facebook: https://www.facebook.com/quocanhcse
 * Group hỗ trợ: https://www.facebook.com/groups/hcmut.thaoluancse
*/

#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Global variables
const Position Position::npos = Position(-1, -1); // not position

// Hàm hỗ trợ - Support functions
// HÀM TÍNH KHOẢNG CÁCH (VÌ CÁI NÀY DÙNG NHIỀU / CÓ THỂ ĐỊNH NGHĨA Ở BẤT KÌ ĐÂU NẾU THẤY HỢP LÍ)

/**
 * CLASS POSITION
 */
Position::Position(const string &str_pos)
{
    // CÓ NHIỀU CÁCH LÀM, DƯỚI ĐÂY MÌNH GỢI Ý 1 CÁCH
    // CHUYỂN CHUỖI THÀNH LUỒNG SAU ĐÓ THAO TÁC
}

/**
 * CLASS MAP
 */
Map::Map(int in_num_rows, int in_num_cols, int in_num_walls, Position *in_array_walls, int in_num_fake_walls, Position *in_array_fake_walls){
    // GỢI Ý MỘT CÁCH LÀM
    /**
     * XIN CẤP PHÁT BỘ NHỚ CHO MỘT MẢNG 2 CHIỀU MAP
     * GÁN TẤT CẢ PHẦN TỬ LÀ PATH
     * THAY THỂ LẦN LƯỢT WALL, FAKEWALL
     */
};

Map::~Map(){
    /**
     * XÓA TOÀN BỘ BỘ NHỚ ĐÃ CẤP PHÁT
     */
};

bool Map::isValid(const Position &pos, MovingObject *mv_obj) const
{
    /**
     * KIỂM TRA VỊ TRÍ THUỘC BẢN ĐỒ KHÔNG
     * KIỂM TRA VỊ TRÍ PHẢI WALL KHÔNG
     * KIỂM TRA VỊ TRÍ CÓ PHẢI FAKEWALL VÀ OBJECT CÓ PHẢI WATSON KHÔNG? PHẢI THÌ KIỂM TRA EXP
     */
}

/**
 * CLASS MOVINGOBJECT
 */
void MovingObject::move()
{
    /**
     * KIỂM TRA NEXTPOS PHẢI NPOS KHÔNG
     * KHÔNG THÌ ĐI TỚI
     * (TĂNG SỐ BƯỚC ĐI NẾU THUẬT TOÁN CÓ)
     */
}

/**
 * CLASS SHERLOCK
 */
Position Sherlock::getNextPosition()
{
    /**
     * KIỂM TRA XEM ĐÃ ĐI BAO NHIÊU BƯỚC
     * TỪ ĐÓ SUY RA INDEX KÍ TỰ TRONG MOVINGRULE
     * TRẢ VỀ KẾT QUẢ
     */
}

void Sherlock::SAUKHIDICHUYEN()
{
    /**
     * DUYỆT QUA TẤT CẢ CÁC OBJECT
     * KIỂM TRA XEM CÓ TRÙNG VỊ TRÍ OBJECT NÀO KHÔNG
     * THỰC HIỆN HÀNH ĐỘNG TƯƠNG ỨNG
     * CÓ THỂ VIẾT THÊM CÁC HÀM KHÁC PHỤ TRỢ HÀM NÀY
     */
}

/**
 * CLASS WATSON
 */
Position Watson::getNextPosition()
{
    /**
     * TƯƠNG TỰ SHERLOCK
     */
}

void Watson::SAUKHIDICHUYEN()
{
    /**
     * TƯƠNG TỰ SHERLOCK
     */
}

/**
 * CLASS CRIMINAL
 */
Position Criminal::getNextPosition()
{
    /**
     * TÍNH KHOẢNG CÁCH CÁC Ô ĐÍCH ĐẾN
     * SO SÁNH
     * CHỌN Ô ĐÍCH ĐẾN
     */
}

void Criminal::TAOROBOT()
{
    /**
     * KIỂM TRA MẢNG OBJECT ĐẦY CHƯA
     * KIỂM TRA SỐ BƯỚC ĐI
     * TẠO ROBOT NẾU ĐỦ ĐIỀU KIỆN
     */
}

void Criminal::move()
{
    /**
     * DI CHUYỂN ĐẾN VỊ TRÍ NEXTPOS NẾU NÓ KHÁC NPOS
     * TĂNG SỐ BƯỚC ĐI SAU KHI DI CHUYỂN (CHỈ TĂNG KHI CÓ DI CHUYỂN)
     */
}

/**
 * CLASS ARRAYMOVINGOBJECT
 */
bool ArrayMovingObject::add(MovingObject *mv_obj)
{
    /**
     * KIỂM TRA ĐẦY CHƯA
     * CHƯA ĐẦY THÌ THÊM VÔ
     */
}

/**
 * CLASS CONFIGURATION
 */
Configuration::Configuration(const string &filepath)
{
    /**
     * GỢI Ý
     * ĐỌC TỪNG DÒNG VÀ CHUYỂN NÓ THÀNH LUỒNG
     * THAO TÁC VỚI NÓ
     * GÁN CÁC GIÁ TRỊ VÔ CÁC THUỘC TÍNH
     */
}

/**
 * CLASS ROBOT
 */
Robot::Robot(int index, const Position &init_pos, Map *map, RobotType robot_type, Criminal *criminal) : MovingObject(index, init_pos, map)
{
    /**
     * GỢI Ý:
     * TÍNH TOÁN VÀ TRẢ VỀ BASEITEM
     * GÁN CÁC GIÁ TRỊ KHÁC CHO CÁC THUỘC TÍNH
     */
}

/**
 * CLASS ROBOTS
 */
Position RobotS::getNextPosition()
{
    /**
     * PHẦN NÀY CÁC BẠN TỰ LÀM THEO YÊU CẦU NHA
     */
}

/**
 * CLASS ROBOTW
 */
RobotW::RobotW(int index, const Position &init_pos, Map *map, Criminal *criminal, Watson *watson);

Position RobotW::getNextPosition()
{
    /**
     * PHẦN NÀY CÁC BẠN TỰ LÀM THEO YÊU CẦU NHA
     */
}

/**
 * CLASS ROBOTSW
 */
Position RobotSW::getNextPosition()
{
    /**
     * PHẦN NÀY CÁC BẠN TỰ LÀM THEO YÊU CẦU NHA
     */
}

/**
 * CLASS MAGICBOOK
 */
bool MagicBook::canUse(Character *character, Robot *robot)
{
    // Kiểm tra xem nhân vật có phải là Sherlock và kinh nghiệm của Sherlock có nhỏ hơn hoặc bằng 350 không
}

void MagicBook::use(Character *character, Robot *robot)
{
    // Nếu có thể sử dụng sách ma thuật
    if (this->canUse(character, robot))
    {
        // Tăng kinh nghiệm của Sherlock lên 1.25 lần, nhưng không quá 500
    }
}

/**
 * CLASS ENERGYDRINK
 */
bool EnergyDrink::canUse(Character *character, Robot *robot)
{
    // Kiểm tra xem nhân vật có phải là Watson hoặc Sherlock và HP của họ có nhỏ hơn hoặc bằng 100 không
}

void EnergyDrink::use(Character *character, Robot *robot)
{
    // Nếu có thể sử dụng nước tăng lực
    if (this->canUse(character, robot))
    {
        // Tăng HP của nhân vật lên 1.1 lần, nhưng không quá 900
    }
}

/**
 * CLASS FIRSTAID
 */
bool FirstAid::canUse(Character *character, Robot *robot)
{
    // Kiểm tra xem nhân vật có phải là Watson hoặc Sherlock và HP hoặc kinh nghiệm của họ có nhỏ hơn hoặc bằng 100 hoặc 350 không
}

void FirstAid::use(Character *character, Robot *robot)
{
    // Nếu có thể sử dụng bộ cấp cứu
    if (this->canUse(character, robot))
    {
        // Tăng HP và kinh nghiệm của nhân vật lên 1.5 và 1.25 lần tương ứng, nhưng không quá 900 và 500
    }
}

/**
 * CLASS EXCEMPTIONCARD
 */
bool ExcemptionCard::canUse(Character *character, Robot *robot)
{
    // Kiểm tra xem nhân vật có phải là Sherlock, có robot và HP của Sherlock có là số lẻ khôn
}

void ExcemptionCard::use(Character *character, Robot *robot)
{
    // Hàm này chưa được định nghĩa
}

/**
 * CLASS PASSINGCARD
 */
bool PassingCard::canUse(Character *character, Robot *robot)
{
    // Kiểm tra xem nhân vật có phải là Watson, có robot và HP của Watson có là số chẵn không
}

void PassingCard::use(Character *character, Robot *robot)
{
    // Nếu có thể sử dụng thẻ PassingCard
    if (this->canUse(character, robot))
    {
        // Kiểm tra xem loại robot có khớp với thử thách không
        // Nếu không khớp, giảm HP của Watson 50 điểm, nhưng không nhỏ hơn 0
    }
}

/**
 * CLASS BASEBAG
 */
bool BaseBag::insert(BaseItem *item)
{
    /**
     * KIỂM TRA FULL CHƯA
     * THÊM VÀO ĐẦU DANH SÁCH
    */
}

BaseItem *BaseBag::get()
{
    // Nếu danh sách chỉ có một phần tử
    // Nếu phần tử đầu tiên có thể sử dụng
    // NẾU KHÔNG, Tìm phần tử có thể sử dụng
    // Nếu không tìm thấy phần tử có thể sử dụnG
    // Đảo chỗ phần tử có thể sử dụng với phần tử đầu tiên
    // Xóa phần tử đầu tiên (phần tử có thể sử dụng hiện tại)
}

BaseItem *BaseBag::get(ItemType itemType)
{
    // Nếu danh sách chỉ có một phần tử
    // Nếu phần tử cần lấy là phần tử đầu tiên

    // NẾU KHÔNG, Tìm phần tử cần lấy
    // Nếu không tìm thấy phần tử cần lấy
    // Đảo chỗ phần tử cần lấy với phần tử đầu tiên
    // Xóa phần tử đầu tiên (phần tử cần lấy hiện tại)
}

/**
 * CLASS SHERLOCKBAG
 */

/**
 * CLASS WATSONBAG
 */

/**
 * CLASS STUDYPINKPROGRAM
 */
StudyPinkProgram::StudyPinkProgram(const string &config_file_path)
{
    this->config = new Configuration(config_file_path);
    this->map = new Map(config->getNumRows(), config->getNumCols(), config->getNumWalls(), config->getArrWalls(), config->getNumFakeWalls(), config->getArrFakeWalls());
    this->sherlock = new Sherlock(1, config->getSherlockMovingRule(), config->getSherlockInitPos(), map, config->getSherlockInitHp(), config->getSherlockInitExp());
    this->watson = new Watson(2, config->getWatsonMovingRule(), config->getWatsonInitPos(), map, config->getWatsonInitHp(), config->getWatsonInitExp());
    this->criminal = new Criminal(0, config->getCriminalInitPos(), map, sherlock, watson);
    this->arr_mv_objs = new ArrayMovingObject(config->getMaxNumMovingObjects());
    this->sherlock_bag = new SherlockBag(sherlock);
    this->watson_bag = new WatsonBag(watson);

    this->arr_mv_objs->add(sherlock);
    this->arr_mv_objs->add(watson);
    this->arr_mv_objs->add(criminal);
}

StudyPinkProgram::~StudyPinkProgram()
{
    /**
     * THU HỒI BỘ NHỚ CẤPPHÁT
    */
}

void StudyPinkProgram::run(bool verbose)
{
    for (int istep = 0; istep < config->getNumSteps(); ++istep)
    {
        for (int i = 0; i < arr_mv_objs->getMovingObjectCount(); ++i)
        {
            arr_mv_objs->get(i)->move();

            if (isStop())
            {
                printStep(istep);
                break;
            }

            if (verbose)
            {
                printStep(istep);
            }

            // CÁC HÀNH ĐỘNG SAU KHI DI CHUYỂN
        }
    }
    printResult();
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////