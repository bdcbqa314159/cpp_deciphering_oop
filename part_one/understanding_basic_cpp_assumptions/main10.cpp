#include <iostream>

enum day
{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

enum workday
{
    Mon = 1,
    Tue,
    Wed,
    Thu,
    Fri
};

enum struct WinterHoliday
{
    Diwali,
    Hanukkah,
    ThreeKings,
    WinterSolstice,
    StLucia,
    StNicholas,
    Christmas,
    Kwanzaa
};

enum class Holiday : short int
{
    NewYear = 1,
    MLK,
    Memorial,
    Independence,
    Labor,
    Thanksgiving
};

int main()
{
    day Birthday = Monday;
    workday payDay = Fri;
    WinterHoliday myTradition = WinterHoliday::StNicholas;
    Holiday favorite = Holiday::NewYear;

    std::cout << "Birthday is " << Birthday << "\n";
    std::cout << "payday is " << payDay << "\n";

    std::cout << "Traditional winter holiday is\n"
              << static_cast<int>(myTradition) << "\n";
    std::cout << "Favorite holiday is \n"
              << static_cast<short int>(favorite) << "\n";

    return 0;
}